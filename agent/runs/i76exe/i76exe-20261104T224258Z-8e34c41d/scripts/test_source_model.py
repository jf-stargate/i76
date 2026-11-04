import unittest
from source_model import *
class TestSourceModel(unittest.TestCase):
 def test_first_member(self):self.assertEqual(select([Source(1),Source(1)],3,False,-1),Selection(0))
 def test_later_member(self):self.assertEqual(select([Source(1),Source(1)],2,False,-1),Selection(1))
 def test_no_media_member(self):self.assertEqual(select([Source(1),Source(1)],3,True,-1),Selection(0))
 def test_earlier_loose_override(self):self.assertEqual(select([Source(1),Source(0,2)],3,True,-1),Selection(0))
 def test_active_media(self):self.assertEqual(select([Source(0,1),Source(0,2)],3,True,2),Selection(1))
 def test_active_media_over_later_direct(self):self.assertEqual(select([Source(0,1),Source(1),Source(0,2)],7,True,2),Selection(2))
 def test_switch_first_media(self):self.assertEqual(select([Source(0,1),Source(1)],3,True,2),Selection(0,True,1))
 def test_media_disabled(self):self.assertEqual(select([Source(0,1),Source(0,2)],3,False,2),Selection(0))
 def test_duplicate_media_first(self):self.assertEqual(select([Source(0,1),Source(0,1)],3,True,1),Selection(0))
 def test_256th_bit(self):self.assertEqual(select([Source(1)]*256,1<<255,True,-1),Selection(255))
 def test_empty_membership(self):
  with self.assertRaises(KeyError):select([Source(1)],0,True,-1)
 def test_invalid_membership(self):
  for bits in (-1,2):
   with self.assertRaises(ValueError):select([Source(1)],bits,True,-1)
if __name__=='__main__':unittest.main(verbosity=2)
