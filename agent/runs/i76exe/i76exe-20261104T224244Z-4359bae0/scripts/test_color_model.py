import unittest
from color_model import *
class ColorTests(unittest.TestCase):
 def test_act_full_precision_channel_order(self):
  p=bytes([1,63,255])*256
  self.assertEqual(act(p)[17],(1,63,255))
  self.assertEqual(pack_palette(p,(0xf800,0x7e0,0x1f))[17],(63>>2)<<5|31)
  self.assertNotEqual(pack_palette(p,(0xf800,0x7e0,0x1f))[17],pack_palette(bytes([255,63,1])*256,(0xf800,0x7e0,0x1f))[17])
 def test_bounds(self):
  for n in [0,767,769]:
   with self.assertRaises(ValueError):act(bytes(n))
  for n in [0,65535,65537]:
   with self.assertRaises(ValueError):tbl_init(bytes(n))
  for i in [-1,256,True]:
   with self.assertRaises(ValueError):compose(bytes(65536),i,0)
  with self.assertRaises(ValueError):shade(bytes(65536),1,0)
  with self.assertRaises(ValueError):pack_palette(bytes(768),(0xf800,0x7e0,0x7e0))
 def test_lum_axes_and_unsigned(self):
  t=bytes((r+3*c)&255 for r in range(256) for c in range(256))
  self.assertEqual(shade(t,200*256,129),(200+3*129)&255)
  self.assertNotEqual(shade(t,200*256,129),shade(t,129*256,200))
  self.assertEqual(masked_shade(t,0xffffc700,129),shade(t,7*256,129))
 def test_null_lum_explicit_unsupported(self):
  with self.assertRaises(NotImplementedError):lum_init(None)
 def test_tbl_axes_and_init(self):
  raw=bytes((5*s+d)&255 for s in range(256) for d in range(256));t=tbl_init(raw)
  self.assertEqual(compose(t,7,19),54)
  self.assertNotEqual(compose(t,7,19),compose(t,19,7))
  self.assertEqual(bytes(t[:65280]),raw[:65280]);self.assertEqual(bytes(t[65280:]),bytes(range(256)))
  self.assertNotEqual(t[65280:],raw[65280:])
 def test_temporary_column_restore(self):
  t=tbl_init(bytes(65536));before=bytes(t)
  try:
   with identity_destination_255(t):
    self.assertEqual(t[255::256],bytes(range(256)));raise RuntimeError('synthetic')
  except RuntimeError:pass
  self.assertEqual(bytes(t),before)
 def test_auxiliary(self):
  a=auxiliary_tables();self.assertEqual(a['identity'],bytes(range(256)))
  self.assertEqual(a['constant_key'],bytes([255])*256)
  self.assertEqual(compose(a['composition'],19,8),19);self.assertEqual(compose(a['composition'],255,8),8)
 def test_lum_column_rounding_and_extension(self):
  b=update_lum_column(bytes(65536),255,0,129)
  self.assertEqual(b[129],255);self.assertEqual(b[31*256+129],8)
  self.assertEqual(b[143*256+129],8);self.assertEqual(b[144*256+129],255)
  self.assertEqual(b[128],0)
  self.assertEqual(update_lum_column(bytes(65536),0,255,2)[16*256+2],128)
 def test_correction_and_timing(self):
  lut=bytes(255-i for i in range(256));p=bytes([10,40,200])*256;l=bytes(65536)
  sw=callback_buffers(p,l,'00475a30',lut);hw=callback_buffers(p,l,'0042dbe0',lut)
  self.assertEqual(sw['nearest_samples'][3:6],bytes([245,215,55]))
  self.assertEqual(hw['nearest_samples'][3:6],bytes([10,40,200]))
  self.assertEqual(hw['context'][3:6],sw['context'][3:6]);self.assertNotEqual(sw['display_input'],hw['display_input'])
  self.assertEqual(sw['raw_act'],p);self.assertEqual(hw['lum'],l)
  self.assertEqual(correction_slot(0,0),3);self.assertEqual(correction_slot(0,266),10)
  self.assertEqual(correction_slot(11,2),3);self.assertEqual(correction_slot(1,2),1)
 def test_pixel_masks_truncation_and_reserved(self):
  p=bytes([255,255,255])*256;out=pack_palette(p,(0xf800,0x7e0,0x1f))
  self.assertEqual(out[1],65535);self.assertEqual(out[255],0)
  p=bytes([0,0,0])*256;out=pack_palette(p,(0xf800,0x7e0,0x1f),avoid_zero=True)
  self.assertEqual(out[1],1);self.assertEqual(out[255],0)
  self.assertEqual(pack_palette(p,(0x7c00,0x3e0,0x1f),alpha=0x8000)[1],0x8000)
 def test_nearest_cache_first_visit_and_excluded255(self):
  p=bytes([0,0,0,7,0,0])+bytes([255,255,255])*253+bytes([6,0,0])
  c=NearestCache(p);self.assertEqual(c.lookup(1,0,0),0);self.assertEqual(c.lookup(6,0,0),0)
  self.assertEqual(NearestCache(p).lookup(6,0,0),1)
  self.assertEqual(NearestCache(p).lookup(255,255,255),2)
if __name__=='__main__':unittest.main()
