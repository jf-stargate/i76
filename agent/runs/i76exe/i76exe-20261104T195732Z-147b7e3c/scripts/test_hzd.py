import unittest
from hzd import parse, FormatError


def fixture(names=None):
    return b''.join(n + b'\r\n' for n in (names or [f'X{i:02}.MAP'.encode() for i in range(16)]))

class HzdTests(unittest.TestCase):
    def reject(self, b):
        with self.assertRaises(FormatError): parse(b)
    def test_valid(self):
        m=parse(fixture()); self.assertEqual(len(m.names),16); self.assertEqual(m.offsets[1],9)
    def test_duplicates_preserved(self):
        m=parse(fixture([b'A.MAP']*16)); self.assertEqual(len(m.references()),16); self.assertEqual(len(set(m.names)),1)
    def test_truncations(self):
        b=fixture()
        for i in range(len(b)):
            with self.subTest(i=i): self.reject(b[:i])
    def test_missing_delimiter(self): self.reject(fixture().replace(b'\r\n',b'',1))
    def test_lf_only(self): self.reject(fixture().replace(b'\r\n',b'\n'))
    def test_cr_only(self): self.reject(fixture().replace(b'\r\n',b'\r'))
    def test_space_and_comma(self):
        for d in [b' ', b',', b'\t']: self.reject(fixture().replace(b'\r\n',d))
    def test_oversize_name(self): self.reject(fixture([b'A'*16]+[b'B']*15))
    def test_limit_name(self): self.assertEqual(parse(fixture([b'A'*15]*16)).names[0],'A'*15)
    def test_missing_entries(self): self.reject(fixture([b'A']*15))
    def test_empty_field(self): self.reject(fixture([b'']+[b'A']*15))
    def test_blank_line(self): self.reject(fixture()[:9]+b'\r\n'+fixture()[9:])
    def test_non_ascii(self): self.reject(fixture([b'\xff.MAP']+[b'A']*15))
    def test_nul(self): self.reject(fixture([b'A\0.MAP']+[b'A']*15))
    def test_unexpected_bytes(self):
        for n in [b'A/B',b'A B',b'A,B',b'A\tB',b'A\x01B',b'_A',b'1A',b'A;X']:
            self.reject(fixture([n]+[b'A']*15))
    def test_excess_records(self): self.reject(fixture([b'A']*17))
    def test_trailing(self):
        for tail in [b'\0',b' ',b'\r\n',b'UNKNOWN']: self.reject(fixture()+tail)
    def test_repeated_parsing(self):
        a=parse(fixture());parse(fixture([b'B']*16)); self.assertEqual(a,parse(fixture()))
    def test_lossless(self):
        b=fixture([b'A-1.mAp']*16);self.assertEqual(parse(b).serialize(),b)
    def test_owned_input(self):
        b=bytearray(fixture()); m=parse(b); b[0]=90;self.assertEqual(m.raw,fixture())

if __name__=='__main__': unittest.main(verbosity=2)
