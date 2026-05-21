#!/usr/bin/env python3
"""
Interstate '76 / ZFSF LZO1Y decompressor draft v1.

Implements the unsafe LZO1Y decompressor used by i76.exe at 004baa00,
corresponding to LZO 1.x lzo1y_decompress with M2_MAX_OFFSET=0x400.

Return codes mirror LZO where practical:
  0   success / input consumed exactly
 -4   input overrun
 -8   input not fully consumed
This Python implementation raises LzoError for malformed streams before the
terminal marker, but the CLI reports those as failures with partial state.
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path
import argparse
import csv
import sys
sys.setrecursionlimit(1000000)

LZO_E_OK = 0
LZO_E_INPUT_OVERRUN = -4
LZO_E_INPUT_NOT_CONSUMED = -8
LZO_E_LOOKBEHIND_OVERRUN = -6

class LzoError(Exception):
    def __init__(self, code: int, message: str):
        super().__init__(message)
        self.code = code

@dataclass
class LzoResult:
    data: bytes
    code: int
    ip: int
    op: int
    message: str = ""

class Lzo1YDecoder:
    def __init__(self, src: bytes):
        self.src = src
        self.ip = 0
        self.out = bytearray()

    @property
    def n(self) -> int:
        return len(self.src)

    def getb(self) -> int:
        if self.ip >= self.n:
            raise LzoError(LZO_E_INPUT_OVERRUN, "input overrun reading byte")
        v = self.src[self.ip]
        self.ip += 1
        return v

    def getw(self) -> int:
        if self.ip + 2 > self.n:
            raise LzoError(LZO_E_INPUT_OVERRUN, "input overrun reading little-endian word")
        v = self.src[self.ip] | (self.src[self.ip + 1] << 8)
        self.ip += 2
        return v

    def copy_literals(self, count: int) -> None:
        if count < 0:
            raise LzoError(LZO_E_INPUT_OVERRUN, f"negative literal count {count}")
        if self.ip + count > self.n:
            raise LzoError(LZO_E_INPUT_OVERRUN, f"input overrun copying {count} literal bytes")
        self.out.extend(self.src[self.ip:self.ip + count])
        self.ip += count

    def copy_match(self, m_pos: int, count: int) -> None:
        if m_pos < 0 or m_pos >= len(self.out):
            raise LzoError(LZO_E_LOOKBEHIND_OVERRUN, f"lookbehind overrun m_pos={m_pos} op={len(self.out)} count={count}")
        if count < 0:
            raise LzoError(LZO_E_INPUT_OVERRUN, f"negative match count {count}")
        # Byte-at-a-time copy intentionally handles overlapping matches.
        for _ in range(count):
            self.out.append(self.out[m_pos])
            m_pos += 1

    def read_extended_length(self, base: int) -> int:
        # LZO extension loop: while (*ip == 0) { t += 255; ip++; } t += base + *ip++
        t = 0
        while True:
            b = self.getb()
            if b != 0:
                return t + base + b
            t += 255

    def finish(self) -> LzoResult:
        code = LZO_E_OK if self.ip == self.n else (LZO_E_INPUT_NOT_CONSUMED if self.ip < self.n else LZO_E_INPUT_OVERRUN)
        return LzoResult(bytes(self.out), code, self.ip, len(self.out))

    def decompress(self) -> LzoResult:
        try:
            t = self.getb()

            # Optional initial literal prologue.
            if t > 17:
                literal_count = t - 17
                if literal_count < 4:
                    # Upstream jumps to match_next with t in 1..3.
                    self.copy_literals(literal_count)
                    t = self.getb()
                    return self._match_loop(t, have_dispatch_token=True)
                self.copy_literals(literal_count)
                # first_literal_run: next token is either a match token or the initial M2 form.
                t = self.getb()
                if t < 16:
                    self._copy_initial_m2(t)
                    tail = t & 3
                    if tail:
                        self.copy_literals(tail)
                        t = self.getb()
                        return self._match_loop(t, have_dispatch_token=True)
                    return self._literal_state_loop()
                return self._match_loop(t, have_dispatch_token=True)

            # General literal-state loop starts with no reusable token. The first byte <=17
            # from entry is not itself used as a literal run in upstream; the loop reads a
            # fresh token at the top.
            return self._literal_state_loop()
        except LzoError as e:
            return LzoResult(bytes(self.out), e.code, self.ip, len(self.out), str(e))

    def _copy_initial_m2(self, t: int) -> None:
        # LZO1Y initial M2: m_pos = op - (1 + 0x400) - (t >> 2) - (next << 2), len 3.
        b = self.getb()
        m_pos = len(self.out) - 0x401 - (t >> 2) - (b << 2)
        self.copy_match(m_pos, 3)

    def _literal_state_loop(self) -> LzoResult:
        while True:
            t = self.getb()
            if t >= 16:
                return self._match_loop(t, have_dispatch_token=True)

            if t == 0:
                # literal count before +3 copy is t + 15 + next; total literal copy is +3.
                lit = self.read_extended_length(15) + 3
            else:
                lit = t + 3
            self.copy_literals(lit)

            # first_literal_run: after literals, a token <16 is the initial M2 form.
            t = self.getb()
            if t < 16:
                self._copy_initial_m2(t)
                tail = t & 3
                if tail:
                    self.copy_literals(tail)
                    t = self.getb()
                    return self._match_loop(t, have_dispatch_token=True)
                # No tail: stay in literal-state reader.
                continue
            return self._match_loop(t, have_dispatch_token=True)

    def _match_loop(self, t: int, have_dispatch_token: bool) -> LzoResult:
        # have_dispatch_token is retained for clarity; this loop always starts with token t.
        while True:
            prev_low_tail = 0

            if t >= 64:
                # M2 match, LZO1Y form.
                b = self.getb()
                m_pos = len(self.out) - 1 - ((t >> 2) & 3) - (b << 2)
                match_len = (t >> 4) - 1
                self.copy_match(m_pos, match_len)
                prev_low_tail = b & 3  # ip[-1] == b, ip[-2] may be token; source uses ip[-2] after consuming one byte? See note below.
                # IMPORTANT: upstream non-LZO1Z uses ip[-2] & 3. For M2, after one offset byte,
                # ip[-2] is the token, so the tail is token & 3.
                prev_low_tail = t & 3

            elif t >= 32:
                # M3 match.
                length_code = t & 31
                if length_code == 0:
                    # t += 31 + next; total copy length is t + 2.
                    match_len = self.read_extended_length(31) + 2
                else:
                    match_len = length_code + 2
                w_ip = self.ip
                w = self.getw()
                m_pos = len(self.out) - 1 - (w >> 2)
                self.copy_match(m_pos, match_len)
                # Upstream tail: ip[-2] & 3, i.e. first byte of LE16 word.
                prev_low_tail = self.src[w_ip] & 3

            elif t >= 16:
                # M4 / terminal marker.
                length_code = t & 7
                high = (t & 8) << 11
                if length_code == 0:
                    match_len = self.read_extended_length(7) + 2
                else:
                    match_len = length_code + 2
                w_ip = self.ip
                w = self.getw()
                encoded = high + (w >> 2)
                if encoded == 0:
                    return self.finish()
                m_pos = len(self.out) - 0x4000 - encoded
                self.copy_match(m_pos, match_len)
                prev_low_tail = self.src[w_ip] & 3

            else:
                # M1 short match. This path is only valid from the main match dispatcher,
                # not from literal-state token handling.
                b = self.getb()
                m_pos = len(self.out) - 1 - (t >> 2) - (b << 2)
                self.copy_match(m_pos, 2)
                # For M1, ip[-2] is the token.
                prev_low_tail = t & 3

            if prev_low_tail == 0:
                return self._literal_state_loop()
            self.copy_literals(prev_low_tail)
            t = self.getb()
            # Continue main match dispatcher with this freshly read token.


def lzo1y_decompress_unsafe(src: bytes) -> LzoResult:
    return Lzo1YDecoder(src).decompress()


def _read_sample_records(sample_dir: Path):
    with (sample_dir / "sample_records.tsv").open(newline="") as f:
        return list(csv.DictReader(f, delimiter="\t"))


def validate_samples(sample_dir: Path) -> int:
    rows = _read_sample_records(sample_dir)
    failures = 0
    for r in rows:
        path = sample_dir / r["sample_file"]
        data = path.read_bytes()
        expected = int(r["logical_size"])
        res = lzo1y_decompress_unsafe(data)
        ok = res.code == 0 and res.op == expected
        if not ok:
            failures += 1
        head = res.data[:16].hex(" ")
        print(f"{r['name']:<16} code={res.code:>3} out={res.op:>7}/{expected:<7} ip={res.ip:>6}/{len(data):<6} {'OK' if ok else 'FAIL'} head={head} {res.message}")
    return failures


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description="Decode I76 ZFSF LZO1Y mode-0x04 payloads.")
    sub = ap.add_subparsers(dest="cmd", required=True)
    p_dec = sub.add_parser("decode", help="decode one raw compressed payload")
    p_dec.add_argument("input", type=Path)
    p_dec.add_argument("output", type=Path)
    p_dec.add_argument("--expect-size", type=int, default=None)
    p_val = sub.add_parser("validate-samples", help="validate against sample_records.tsv bundle")
    p_val.add_argument("sample_dir", type=Path)
    args = ap.parse_args(argv)

    if args.cmd == "decode":
        res = lzo1y_decompress_unsafe(args.input.read_bytes())
        args.output.write_bytes(res.data)
        ok = res.code == 0 and (args.expect_size is None or res.op == args.expect_size)
        print(f"code={res.code} out={res.op} ip={res.ip} ok={ok} {res.message}")
        return 0 if ok else 1
    if args.cmd == "validate-samples":
        failures = validate_samples(args.sample_dir)
        print(f"failures={failures}")
        return 0 if failures == 0 else 1
    return 2

if __name__ == "__main__":
    raise SystemExit(main())
