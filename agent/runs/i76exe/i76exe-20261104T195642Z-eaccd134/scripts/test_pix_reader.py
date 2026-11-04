"""Synthetic fixtures authored here; no retail contents."""
import struct
import tempfile
from pathlib import Path
import unittest
from pix_reader import (parse_index, key16, compare16, Reader, FormatError,
                        AmbiguousKey, validate_ranges, sibling_pak)

class PixTests(unittest.TestCase):
    def test_empty(self):
        self.assertEqual(parse_index(b"0\n").entries, ())

    def test_one(self):
        e = parse_index(b"1\r\nA.GEO 2 3\r\n").lookup("a.geo")
        self.assertEqual((e.offset,e.size,e.name_offset),(2,3,3))

    def test_multiple(self):
        i=parse_index(b"2\na.geo 0 3\nb.tmt 3 2\n")
        self.assertEqual(i.lookup("B.TMT").offset,3)

    def test_duplicate(self):
        i=parse_index(b"2\na.geo 0 1\na.geo 1 1\n")
        with self.assertRaises(AmbiguousKey): i.lookup("a.geo")
        self.assertEqual(i.lookup("a.geo",ordinal=1).offset,1)

    def test_case_variants(self):
        i=parse_index(b"2\nA.GEO 0 1\na.geo 1 1\n")
        self.assertEqual(len(i.candidates("A.Geo")),2)
        with self.assertRaises(AmbiguousKey): i.lookup("a.geo")

    def test_truncated_records(self):
        for raw in [b"",b"1",b"1\n",b"1\na.geo 0\n",b"1\na.geo 0 1"]:
            with self.subTest(raw=raw),self.assertRaises(FormatError):parse_index(raw)

    def test_bad_counts(self):
        for raw in [b"-1\n",b"2147483648\n",b"250001\n",b"1x\n",b"0\nx 0 0\n"]:
            with self.subTest(raw=raw),self.assertRaises(FormatError):parse_index(raw)

    def test_integer_overflow(self):
        for token in [b"2147483648",b"4294967295",b"999999999999999999999999"]:
            with self.subTest(token=token),self.assertRaises(FormatError):
                parse_index(b"1\na.geo "+token+b" 1\n")

    def test_negative_and_hex(self):
        for token in [b"-1",b"0x10",b"1z"]:
            with self.subTest(token=token),self.assertRaises(FormatError):
                parse_index(b"1\na.geo 0 "+token+b"\n")

    def test_decimal_leading_zero(self):
        self.assertEqual(parse_index(b"1\na.geo 0010 +02\n").entries[0].offset,10)

    def test_names(self):
        for name in ["", "a"*16,"../a","a/b","a\\b","a:b","café","a\0b"]:
            with self.subTest(name=name),self.assertRaises(FormatError):key16(name)

    def test_encoding(self):
        for raw in [b"1\na\0b 0 1\n",b"1\n\xff 0 1\n"]:
            with self.subTest(raw=raw),self.assertRaises(FormatError):parse_index(raw)

    def test_out_of_range(self):
        i=parse_index(b"1\na.geo 4 2\n")
        with self.assertRaises(FormatError):validate_ranges(i,5)

    def test_zero_length(self):
        i=parse_index(b"1\na.geo 3 0\n")
        validate_ranges(i,3)
        with self.assertRaises(FormatError):validate_ranges(i,2)

    def test_overlapping_regions(self):
        i=parse_index(b"2\na.geo 0 3\nb.geo 1 3\n")
        validate_ranges(i,4)

    def test_word_order(self):
        # DWORD order differs from lexical order: second byte dominates first.
        self.assertLess(compare16(key16("zA"),key16("aB")),0)
        self.assertGreater(key16("zA"),key16("aB"))
        self.assertNotEqual(compare16(b"a\0"+b"x"*14,b"a\0"+b"y"*14),0)
        self.assertEqual(compare16(key16("A.GEO"),key16("a.geo")),0)
        self.assertEqual(compare16(struct.pack("<4I",0,0,0,0),struct.pack("<4I",0xffffffff,0,0,0)),1)

    def test_failed_acquire_recovery(self):
        with tempfile.TemporaryDirectory() as td:
            pix=Path(td)/"x.pix";pix.write_bytes(b"1\na.geo 1 3\n")
            r=Reader(pix)
            with self.assertRaises(FileNotFoundError):r.acquire("a.geo")
            pak=Path(td)/"X.PAK";pak.write_bytes(b"xx")
            with self.assertRaises(FormatError):r.acquire("a.geo")
            pak.write_bytes(b"xABC")
            self.assertEqual(bytes(r.acquire("A.GEO")),b"ABC")

    def test_repeated_and_close(self):
        with tempfile.TemporaryDirectory() as td:
            pix=Path(td)/"x.pix";pix.write_bytes(b"2\na.geo 0 2\nb.geo 1 2\n")
            (Path(td)/"x.pak").write_bytes(b"ABC")
            r=Reader(pix);a=r.acquire("a.geo");b=r.acquire("b.geo")
            self.assertTrue(a.readonly)
            self.assertIs(a.obj,b.obj)
            for _ in range(10):self.assertEqual(bytes(r.acquire("A.GEO")),b"AB")
            r.close();self.assertEqual(bytes(a),b"AB")
            self.assertEqual(bytes(r.acquire("a.geo")),b"AB")

    def test_empty_pak_zero_entry(self):
        with tempfile.TemporaryDirectory() as td:
            pix=Path(td)/"x.pix";pix.write_bytes(b"1\na.geo 0 0\n")
            (Path(td)/"x.pak").write_bytes(b"")
            self.assertEqual(bytes(Reader(pix).acquire("a.geo")),b"")

    def test_case_ambiguous_pak(self):
        with tempfile.TemporaryDirectory() as td:
            pix=Path(td)/"x.pix";pix.write_bytes(b"0\n")
            (Path(td)/"x.pak").write_bytes(b"")
            (Path(td)/"X.PAK").write_bytes(b"")
            with self.assertRaises(FormatError):sibling_pak(pix)

    def test_symlink_escape(self):
        with tempfile.TemporaryDirectory() as td, tempfile.TemporaryDirectory() as other:
            pix=Path(td)/"x.pix";pix.write_bytes(b"0\n")
            target=Path(other)/"data";target.write_bytes(b"")
            (Path(td)/"x.pak").symlink_to(target)
            with self.assertRaises(FormatError):sibling_pak(pix)

if __name__ == "__main__":
    unittest.main(verbosity=2)
