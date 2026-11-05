"""Synthetic differences from historical comparator, without retail execution."""
from survey import module
from test_zfs import fixture, setword
from zfs_reader import Archive, InvalidArchive, DecodeError

def check(path):
 old=module(path);backend=old.LzoDecompressor(required=True);out=[]
 b=fixture();setword(b,4,2);old.parse_header(b)
 try:Archive(b)
 except InvalidArchive:out.append({'case':'version2','historical':'accepts header','bounded':'rejects'})
 b=fixture();setword(b,28,28);h=old.parse_header(b);rows,_=old.parse_records(b,h);assert len(rows)==1
 try:Archive(b)
 except InvalidArchive:out.append({'case':'cycle after declared count','historical':'stops without following cycle','bounded':'rejects'})
 for flags,label in ((6,'both compression bits'),(8,'unknown flag')):
  payload=b'\x16hello\x11\0\0';b=bytes(fixture([('one.dat',payload,flags|(5<<8))]))
  h=old.parse_header(b);rows,_=old.parse_records(b,h);historical,method=old.decode_payload(b,rows[0],backend)
  assert historical==payload and method.startswith('unknown_mode')
  if flags==6:
   assert Archive(b).read('one.dat')==b'hello';bounded='selects X and decodes'
  else:
   try:Archive(b).read('one.dat')
   except DecodeError:bounded='rejects'
  out.append({'case':label,'historical':'unknown mode returned raw','bounded':bounded})
 b=bytes(fixture(xor=1));h=old.parse_header(b);rows,_=old.parse_records(b,h)
 historical,_=old.decode_payload(b,rows[0],backend)
 assert historical==b'hello' and Archive(b).read('one.dat')==b'iello'
 out.append({'case':'nonzero XOR','historical':'no XOR transform','bounded':'XORs full logical words'})
 b=bytes(fixture([('one.dat',b'x',0x80000002)]));h=old.parse_header(b);rows,_=old.parse_records(b,h)
 assert rows[0].logical_size==0x800000 and Archive(b).entries[0].expected_size==-0x800000
 out.append({'case':'packed sign bit','historical':'unsigned logical length 8388608','bounded':'retail SAR gives -8388608; read rejects'})
 assert len(out)==6
 return {'cases':out,'corpus_disagreements':0,'scope':'synthetic comparator behavior, not original execution'}
