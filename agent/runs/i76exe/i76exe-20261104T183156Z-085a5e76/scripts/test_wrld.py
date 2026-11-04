"""Synthetic bounded-reader tests; no retail assets or engine execution."""
import struct
import unittest
import wrld

def chunk(tag,p=b''):
    return tag+struct.pack('<I',len(p)+8)+p

def mission(p=None,revision=9):
    if p is None:p=bytes(wrld.SIZE)
    return chunk(b'BWD2')+chunk(b'REV\0',struct.pack('<I',2))+chunk(b'WDEF',chunk(b'WREV',struct.pack('<I',revision))+chunk(b'WRLD',p)+chunk(b'EXIT'))+chunk(b'EXIT')

class ReaderTests(unittest.TestCase):
    def test_sibling_marker_and_empty_fields(self):
        data=mission(); r=wrld.inspect(data);self.assertEqual(len(r),1);self.assertEqual(r[0][-1].names['palette'],'')
    def test_all_truncated_headers(self):
        for n in range(8):
            with self.subTest(n=n),self.assertRaises(wrld.FormatError):wrld.inspect(mission()[:n])
        for n in range(1,8):
            with self.subTest(n=n),self.assertRaises(wrld.FormatError):wrld.inspect(mission()+b'X'*n)
    def test_every_truncated_payload(self):
        data=mission()
        for n in range(8,len(data)-8):
            with self.subTest(n=n),self.assertRaises(wrld.FormatError):wrld.inspect(data[:n])
    def test_invalid_declared_lengths(self):
        for value in (0,1,7,0xffffffff):
            b=bytearray(mission());struct.pack_into('<I',b,24,value)
            with self.subTest(value=value),self.assertRaises(wrld.FormatError):wrld.inspect(b)
    def test_short_long_wrld(self):
        for n in (0,330,332,1000):
            with self.subTest(n=n),self.assertRaises(wrld.FormatError):wrld.inspect(mission(bytes(n)))
    def test_nonterminated_each_name(self):
        for name,(o,n) in wrld.NAMES.items():
            p=bytearray(wrld.SIZE);p[o:o+n]=b'A'*n
            with self.subTest(name=name),self.assertRaises(wrld.FormatError):wrld.inspect(mission(p))
    def test_non_ascii_each_name(self):
        for name,(o,n) in wrld.NAMES.items():
            p=bytearray(wrld.SIZE);p[o]=255
            with self.subTest(name=name),self.assertRaises(wrld.FormatError):wrld.inspect(mission(p))
    def test_unexpected_revisions(self):
        for rev in (0,1,8,10,0xffffffff):
            with self.subTest(rev=rev),self.assertRaises(wrld.FormatError):wrld.inspect(mission(revision=rev))
    def test_name_variation(self):
        for value in ('x.ACT','abc_16.ACT','Mixed.MAP','12345678.M16',''):
            p=bytearray(wrld.SIZE);o,n=wrld.NAMES['palette'];v=value.encode();p[o:o+len(v)]=v
            self.assertEqual(wrld.inspect(mission(p))[0][-1].names['palette'],value)
    def test_unknown_and_padding_preserved(self):
        p=bytearray((i*71)%256 for i in range(wrld.SIZE))
        for o,n in wrld.NAMES.values():p[o]=0
        w=wrld.inspect(mission(p))[0][-1];self.assertEqual(w.serialize(),bytes(p))
    def test_no_revision_in_wrld_first_word(self):
        p=bytearray(wrld.SIZE);struct.pack_into('<I',p,0,15)
        self.assertEqual(wrld.inspect(mission(p))[0][-1].audio_word,15)
    def test_parent_boundary(self):
        b=bytearray(mission());struct.pack_into('<I',b,24,20)
        with self.assertRaises(wrld.FormatError):wrld.inspect(b)
    def test_missing_duplicate_bad_wrev(self):
        for p in (chunk(b'WRLD',bytes(wrld.SIZE)),chunk(b'WREV',b'X')+chunk(b'WRLD',bytes(wrld.SIZE)),chunk(b'WREV',struct.pack('<I',9))*2+chunk(b'WRLD',bytes(wrld.SIZE))):
            with self.assertRaises(wrld.FormatError):wrld.inspect(chunk(b'BWD2')+chunk(b'WDEF',p))
    def test_resource_and_chunk_limit(self):
        with self.assertRaises(wrld.FormatError):wrld.inspect(bytes(16*1024*1024+1))
        with self.assertRaises(wrld.FormatError):wrld.inspect(mission()+chunk(b'TEST')*16384)
    def test_depth_limit(self):
        p=chunk(b'TEST')
        for _ in range(18):p=chunk(b'WDEF',p)
        with self.assertRaises(wrld.FormatError):wrld.inspect(chunk(b'BWD2')+p)
    def test_full_marker_required(self):
        with self.assertRaises(wrld.FormatError):wrld.inspect(chunk(b'BWD2',chunk(b'WRLD',bytes(wrld.SIZE))))

if __name__=='__main__':unittest.main()
