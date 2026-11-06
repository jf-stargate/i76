import unittest
from fractions import Fraction as F
from model import *
class Tests(unittest.TestCase):
    def test_ieee_decode(self):
        self.assertEqual(f32(0x3f800000),1)
        self.assertEqual(f32(0xbf800000),-1)
        self.assertEqual(f64(0x3ff0000000000000),1)
        self.assertEqual(f64(0xbff0000000000000),-1)
    def test_round_ties_and_directions(self):
        self.assertEqual(rounded(F(9,8),3),1)
        self.assertEqual(rounded(F(11,8),3),F(3,2))
        self.assertEqual(rounded(-F(9,8),3,1),-F(5,4))
        self.assertEqual(rounded(-F(9,8),3,2),-1)
        self.assertEqual(rounded(F(9,8),3,3),1)
    def test_integer_truncation(self):
        for x,y in [(F(999,1000),0),(-F(999,1000),0),(F(2147483648),2147483648),(-F(3,2),-1)]:self.assertEqual(int(x),y)
    def test_nearest_tie_and_cache(self):
        p=bytes([0,0,0,4,0,0]+[255,255,255]*253+[2,0,0]);n=Nearest(p)
        self.assertEqual(n.lookup((2,0,0)),0)
        self.assertEqual(n.lookup((4,0,0)),0)
        self.assertEqual(Nearest(p).lookup((4,0,0)),1)
        self.assertEqual(Nearest(p).lookup((2,0,0),tie_last=True),1)
    def test_precision_counterexample(self):
        a=Arithmetic();pairs=[]
        for v in range(256):
            _,x=a.channels(v);_,y=a.channels(v,True)
            if x!=y:pairs.append(v)
        self.assertTrue(pairs)
    def test_layout_and_extension(self):
        b=lum(synthetic()['gray'])
        self.assertEqual(len(b),65536)
        self.assertEqual(b[32*256:144*256],b[31*256:32*256]*112)
        self.assertEqual(b[144*256:],b[:256]*112)
        self.assertNotEqual(b,lum(synthetic()['gray'],cache=False))
    def test_complete_original_validated_synthetic_hash(self):
        self.assertEqual(digest(lum(synthetic()['permuted'])),'a88396031e8c95f8af9572df6ac411e3d9ef7c0676dadf92a99dfe0c1c73000a')
    def test_generation_order_changes_output(self):
        p=synthetic()['permuted'];a=lum(p);b=lum(p,row_major=True)
        self.assertEqual(sum(x!=y for x,y in zip(a,b)),1214)
    def test_gamma_near_integer_boundary(self):
        returned_double=f64(0x3f70101010101010)
        self.assertEqual(int(Arithmetic(0x37f).op(returned_double*255)),0)
        self.assertEqual(int(Arithmetic(0x27f).op(returned_double*255)),1)
    def test_exhaustive_channel_mode_invariance(self):
        gold=[Arithmetic().channels(v)[0] for v in range(256)]
        for pc in [0,2,3]:
            for rc in range(4):
                a=Arithmetic((pc<<8)|(rc<<10)|127)
                self.assertEqual([a.channels(v)[0] for v in range(256)],gold)
if __name__=='__main__':unittest.main()
