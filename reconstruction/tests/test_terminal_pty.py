#!/usr/bin/env python3
"""Exercise real POSIX arrow-key escape sequences in a pseudo-terminal.

No retail resources or display server are needed. Piped CTest cases separately
verify that non-TTY stdin remains a normal line-oriented command stream.
"""

import os
import pty
import select
import subprocess
import sys
import time


def read_until(master, expected, transcript, timeout=7.0, start=0):
    deadline = time.monotonic() + timeout
    while expected not in transcript[start:]:
        remaining = deadline - time.monotonic()
        if remaining <= 0:
            raise AssertionError(
                f"timed out waiting for {expected!r}; tail={bytes(transcript[-600:])!r}"
            )
        ready, _, _ = select.select([master], [], [], remaining)
        if ready:
            try:
                chunk = os.read(master, 65536)
            except OSError:
                break
            if not chunk:
                break
            transcript.extend(chunk)
    if expected not in transcript[start:]:
        raise AssertionError(f"missing {expected!r}; tail={bytes(transcript[-600:])!r}")


def run_case(executable, options, operations):
    master, slave = pty.openpty()
    process = None
    transcript = bytearray()
    try:
        process = subprocess.Popen(
            [executable, *options], stdin=slave, stdout=slave, stderr=slave,
            start_new_session=True, close_fds=True,
        )
        os.close(slave)
        slave = -1
        read_until(master, b"i76> ", transcript)
        for typed, expected in operations:
            start = len(transcript)
            os.write(master, typed)
            read_until(master, expected, transcript, start=start)
        os.write(master, b"exit\r" if "--shell" in options else b"quit\r")
        process.wait(timeout=7.0)
        if process.returncode != 0:
            raise AssertionError(f"terminal subprocess failed: {process.returncode}")
        if b"exit requested" not in transcript:
            read_until(master, b"exit requested", transcript, timeout=2.0)
    finally:
        if process is not None and process.poll() is None:
            process.kill()
            process.wait(timeout=5)
        os.close(master)
        if slave >= 0:
            os.close(slave)


def main():
    executable = sys.argv[1]
    run_case(executable, ["--shell"], [
        (b"play\r", b"TEST SESSION"),
        # Left-arrow twice; repair 'staus' to 'status' in the middle.
        (b"staus\x1b[D\x1b[Dt\r", b"ticks=0 paused=false"),
        (b"step 3\r", b"stepped 3 tick(s)"),
        # Up recalls step 3 (the most recent command); Enter resubmits it.
        (b"\x1b[A\r", b"stepped 3 tick(s)"),
        (b"status\r", b"ticks=6 paused=false"),
        # Mount list and stable ID; removal must affect subsequent listing.
        (b"resource list\r", b"resource mounts=1"),
        (b"menu\r", b"main menu"),
        (b"resource unmount 1\r", b"unmounted resource [1]"),
        (b"resource list\r", b"resource mounts=0"),
    ])
    run_case(executable, ["--headless", "--interactive"], [
        (b"step 2\r", b"stepped 2 tick(s)"),
        (b"\x1b[A\r", b"stepped 2 tick(s)"),
        (b"status\r", b"ticks=4 paused=false"),
        (b"statusX\x01\x05\x7f\r", b"ticks=4 paused=false"),
        (b"statusx\x1b[D\x1b[3~\r", b"ticks=4 paused=false"),
        (b"junk\x03status\r", b"ticks=4 paused=false"),
        (b"\x1bstatus\r", b"ticks=4 paused=false"),
    ])
    print("PTY interactive cursor keys and history passed")


if __name__ == "__main__":
    main()
