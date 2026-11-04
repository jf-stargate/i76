import struct
import unittest
from zfs_reader import *


def fixture(rows=None, xor=0, count=None):
    rows=rows if rows is not None else [('one.dat',b'hello',0)]
    count=len(rows) if count is None else count
    out=bytearray(HEADER.pack(b'ZFSF',1,16,100,count,xor,28)+bytes(TABLE_BYTES))
    for i,(name,payload,flags) in enumerate(rows):
        off=len(out);out.extend(payload)
        RECORD.pack_into(out,32+i*36,name.encode().ljust(16,b'\0'),off,i,len(payload),0,flags)
    return out


def setword(data,offset,value):struct.pack_into('<I',data,offset,value);return data

class TestArchive(unittest.TestCase):
    def test_truncated_header(self):
        for length in range(28):
            with self.subTest(length=length),self.assertRaises(InvalidArchive):Archive(bytes(length))
    def test_bad_magic(self):
        b=fixture();b[0]=0
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_unsupported_version(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),4,2))
    def test_unsupported_name_width(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),8,12))
    def test_unsupported_capacity(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),12,99))
    def test_directory_pointer(self):
        for offset in (0,1,0xffffffff,999999):
            with self.subTest(offset=offset),self.assertRaises(InvalidArchive):Archive(setword(fixture(),24,offset))
    def test_truncated_table(self):
        with self.assertRaises(InvalidArchive):Archive(fixture()[:100])
    def test_cycle(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),28,28))
    def test_longer_chain(self):
        b=fixture();second=len(b);b.extend(bytes(TABLE_BYTES));setword(b,28,second)
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_count_mismatch(self):
        for count in (0,2,100,0xffffffff):
            with self.subTest(count=count),self.assertRaises(InvalidArchive):Archive(setword(fixture(),16,count))
    def test_invalid_payload_offset(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),32+16,999999))
    def test_invalid_payload_size(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),32+24,999999))
    def test_integer_overflow(self):
        with self.assertRaises(InvalidArchive):extent(0x7ffffff0,32,0xffffffff)
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),32+16,0xfffffff0))
    def test_tombstone(self):
        a=Archive(fixture([('one.dat',b'x',1)]))
        self.assertFalse(a.entries[0].active);self.assertEqual(a.candidates('one.dat'),())
        with self.assertRaises(KeyError):a.read('one.dat')
        with self.assertRaises(DecodeError):a.read_entry(a.entries[0])
    def test_duplicate_normalized_names(self):
        a=Archive(fixture([('ONE.dat',b'a',0),('one.DAT',b'b',0)]))
        self.assertEqual(len(a.candidates('one.dat')),2)
        with self.assertRaises(AmbiguousKey):a.read('one.dat')
        self.assertEqual(a.read_entry(a.entries[1]),b'b')
    def test_partial_overlap(self):
        b=fixture([('one.dat',b'abcd',0),('two.dat',b'abcd',0)])
        setword(b,32+36+16,28+TABLE_BYTES+1)
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_exact_alias(self):
        b=fixture([('one.dat',b'abcd',0),('two.dat',b'abcd',0)])
        setword(b,32+36+16,28+TABLE_BYTES);a=Archive(b)
        self.assertEqual(a.aliases,((0,1),));self.assertEqual(a.read('one.dat'),a.read('two.dat'))
    def test_incompatible_alias(self):
        b=fixture([('one.dat',b'abcd',0),('two.dat',b'abcd',4|(4<<8))])
        setword(b,32+36+16,28+TABLE_BYTES)
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_payload_overlaps_directory(self):
        with self.assertRaises(InvalidArchive):Archive(setword(fixture(),32+16,28))
    def test_unsupported_flag(self):
        a=Archive(fixture([('one.dat',b'a',8)]))
        with self.assertRaises(DecodeError):a.read('one.dat')
    def test_truncated_stream(self):
        a=Archive(fixture([('one.dat',b'\x16hello\x11',2|(5<<8))]))
        with self.assertRaises(DecodeError):a.read('one.dat')
    def test_length_mismatch_small(self):
        a=Archive(fixture([('one.dat',b'\x16hello\x11\0\0',2|(4<<8))]))
        with self.assertRaises(DecodeError):a.read('one.dat')
    def test_length_mismatch_large(self):
        a=Archive(fixture([('one.dat',b'\x16hello\x11\0\0',2|(6<<8))]))
        with self.assertRaises(DecodeError):a.read('one.dat')
    def test_signed_length(self):
        a=Archive(fixture([('one.dat',b'x',0x80000002)]))
        self.assertLess(a.entries[0].expected_size,0)
        with self.assertRaises(DecodeError):a.read('one.dat')
    def test_mode_dispatch(self):
        for flag in (2,4,6):
            a=Archive(fixture([('one.dat',b'\x16hello\x11\0\0',flag|(5<<8))]))
            self.assertEqual(a.read('one.dat'),b'hello')
            self.assertEqual(a.entries[0].mode,2 if flag&2 else 4)
    def test_failure_recovery(self):
        a=Archive(fixture([('bad.dat',b'x',2|(5<<8)),('good.dat',b'\x16hello\x11\0\0',2|(5<<8))]))
        for _ in range(3):
            with self.assertRaises(DecodeError):a.read('bad.dat')
            self.assertEqual(a.read('good.dat'),b'hello')
    def test_independent_lifetimes(self):
        a=Archive(fixture());x=a.read('one.dat');y=a.read('one.dat');a.close()
        self.assertEqual(x,b'hello');self.assertEqual(y,b'hello')
        with self.assertRaises(ValueError):a.read('one.dat')
    def test_xor_full_words_remainder(self):
        key=0x12345678;b=fixture([('one.dat',b'abcdefg',0)],xor=key);a=Archive(b)
        self.assertEqual(a.read('one.dat'),struct.pack('<I',struct.unpack('<I',b'abcd')[0]^key)+b'efg')
    def test_xor_after_decode(self):
        a=Archive(fixture([('one.dat',b'\x16hello\x11\0\0',4|(5<<8))],xor=1))
        self.assertEqual(a.read('one.dat'),b'iello')
    def test_invalid_names(self):
        for name in ('../a','a\\b','a:b','..','', 'a'*16,'a b'):
            with self.subTest(name=name),self.assertRaises(InvalidArchive):normalize(name)
        b=fixture();b[32:48]=b'x'*16
        with self.assertRaises(InvalidArchive):Archive(b)
        b=fixture();b[32]=255
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_nonempty_after_terminator(self):
        b=fixture();b[32:68]=bytes(36);RECORD.pack_into(b,68,b'late.dat',28+TABLE_BYTES,1,1,0,0)
        with self.assertRaises(InvalidArchive):Archive(b)
    def test_empty_archive(self):
        self.assertEqual(Archive(fixture([])).entries,())
    def test_exact_capacity_requires_extra_table(self):
        b=fixture([(f'f{i}.dat',b'x',0) for i in range(100)])
        with self.assertRaises(InvalidArchive):Archive(b)
        nextoff=len(b);b.extend(bytes(TABLE_BYTES));setword(b,28,nextoff)
        self.assertEqual(len(Archive(b).entries),100)
    def test_foreign_entry(self):
        a=Archive(fixture());b=Archive(fixture())
        with self.assertRaises(InvalidArchive):a.read_entry(b.entries[0])
    def test_snapshot(self):
        b=fixture();a=Archive(b);b[-1]=0
        self.assertEqual(a.read('one.dat'),b'hello')
    def test_missing_key(self):
        with self.assertRaises(KeyError):Archive(fixture()).read('missing.dat')
    def test_raw_ignores_upper_bits(self):
        a=Archive(fixture([('one.dat',b'hello',0xffff0000)]))
        self.assertEqual(a.read('one.dat'),b'hello')
    def test_trailing_compressed_input(self):
        a=Archive(fixture([('one.dat',b'\x16hello\x11\0\0x',2|(5<<8))]))
        with self.assertRaises(DecodeError):a.read('one.dat')

if __name__=='__main__':unittest.main(verbosity=2)
