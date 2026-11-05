"""Independent bounded research model. No game payloads or maintained renderer.
Only complete integer/copy contracts are executable; null-LUM generation and
native pow/x87 gamma-table construction remain explicitly unsupported.
"""
from contextlib import contextmanager

def buffer(data, size, label):
    try: b = bytes(memoryview(data))
    except TypeError as e: raise ValueError(label + ' requires a byte buffer') from e
    if len(b) != size: raise ValueError(label + ' length must be ' + str(size))
    return b

def u8(value):
    if type(value) is not int or not 0 <= value <= 255: raise ValueError('expected uint8')
    return value

def act(data):
    b = buffer(data, 768, 'ACT')
    return tuple(tuple(b[i:i+3]) for i in range(0,768,3))

def lum_init(data):
    if data is None: raise NotImplementedError('null-LUM x87 generator is not modeled')
    return buffer(data,65536,'LUM')

def shade(data, shade_offset, source_index):
    """Offset already produced by the selected original span path."""
    b = buffer(data,65536,'LUM'); u8(source_index)
    if type(shade_offset) is not int or shade_offset & 255 or not 0 <= shade_offset <= 65280:
        raise ValueError('expected bounded row offset')
    return b[shade_offset + source_index]

def masked_shade(data, accumulator, source_index):
    if type(accumulator) is not int or not 0 <= accumulator <= 0xffffffff: raise ValueError('expected uint32')
    return shade(data,accumulator & 0x1f00,source_index)

def tbl_init(data):
    b = bytearray(buffer(data,65536,'TBL')); b[0xff00:] = bytes(range(256)); return b

def compose(table, source_index, destination_index):
    b = buffer(table,65536,'runtime TBL'); return b[(u8(source_index)<<8) | u8(destination_index)]

@contextmanager
def identity_destination_255(table):
    """00483cc0/00484630 temporary mutation, restoring all cells on exit."""
    if not isinstance(table,bytearray) or len(table)!=65536: raise ValueError('expected mutable runtime TBL')
    saved=table[255::256]
    try:
        table[255::256]=bytes(range(256)); yield table
    finally: table[255::256]=saved

def auxiliary_tables(key=255):
    key=u8(key); identity=bytes(range(256)); c=bytearray(x for x in range(256) for _ in range(256))
    c[key*256:(key+1)*256]=identity
    return {'identity':identity,'constant_key':bytes([key])*256,'composition':bytes(c)}

def update_lum_column(data, first, last, column):
    """00478b80: low-byte operands, signed delta /32 truncated toward zero."""
    b=bytearray(buffer(data,65536,'runtime LUM'))
    for v in (first,last,column):
        if type(v) is not int or not 0<=v<=0xffffffff: raise ValueError('expected uint32')
    first &=255; last &=255; column &=255
    delta=(last-first)*65536
    step=delta//32 if delta>=0 else -((-delta)//32)
    v=first*65536+32768
    for row in range(32):
        b[row*256+column]=(v>>16)&255; v+=step
    for row in range(32,144): b[row*256+column]=b[31*256+column]
    for row in range(144,256): b[row*256+column]=b[column]
    return bytes(b)

def correction_slot(explicit, global_setting):
    if type(explicit) is not int or type(global_setting) is not int: raise ValueError('expected integer setting')
    value=explicit if explicit>=1 else global_setting &255
    return value if 1<=value<=10 else 3

def correct_palette(data, lut):
    b=buffer(data,768,'ACT'); lut=buffer(lut,256,'correction LUT')
    return bytes(lut[v] for v in b)

def callback_buffers(data, lum, callback, correction_lut):
    """Full WRLD update only: start=0,end/count=256, successful context.
    Exposes timing: software builds shade samples after correction, hardware before.
    Supplied LUM bytes do not depend on palette correction.
    Display buffers here omit device submission side effects.
    """
    raw=buffer(data,768,'ACT'); lut=buffer(correction_lut,256,'correction LUT')
    if callback not in ('0048dc60','00475a30','0042dbe0','004345b0'): raise ValueError('unknown callback')
    hardware=callback in ('0042dbe0','004345b0')
    context=bytes([1 if hardware else 0])*3+raw[3:]
    before=context
    context=correct_palette(context,lut)
    return {'raw_act':raw,'context':context,'nearest_samples':context if not hardware else before,
            'lum':lum_init(lum),'display_input':context if not hardware else before}

def pack_palette(data,masks,alpha=0,avoid_zero=False,force_first_zero=False):
    """Contiguous non-overlapping <=8-bit fields fitting uint16 only.
    0042d800 palette branch; plugin RGB565 is masks=(f800,7e0,1f).
    Does not model the separate 65536-entry PCF translation.
    """
    triples=act(data)
    if len(masks)!=3 or type(alpha) is not int or not 0<=alpha<=65535: raise ValueError('invalid masks/alpha')
    specs=[];used=alpha
    for mask in masks:
        if type(mask) is not int or not 0<mask<=65535 or used & mask: raise ValueError('overlapping/invalid mask')
        shift=(mask & -mask).bit_length()-1; bits=(mask>>shift).bit_length()
        if bits>8 or mask>>shift!=(1<<bits)-1: raise ValueError('unsupported mask')
        specs.append((bits,shift));used|=mask
    fallback=masks[2]&-masks[2] if avoid_zero and alpha==0 else 0
    out=[]
    for triple in triples:
        v=sum(((c*(1<<bits))//256)<<shift for c,(bits,shift) in zip(triple,specs))
        if v==0:v=fallback
        out.append(v|alpha)
    out[255]=0
    if force_first_zero:out[0]=0
    return tuple(out)

class NearestCache:
    """004796a0: cache cell chosen by top 5 bits per channel.
    First query in cell determines result from unquantized squared distance.
    Palette index 255 is excluded; ties choose the earliest entry.
    """
    def __init__(self,palette):self.palette=act(palette);self.cache={}
    def lookup(self,r,g,b):
        query=tuple(u8(v) for v in (r,g,b));key=((r>>3)*32+(g>>3))*32+(b>>3)
        if key not in self.cache:
            self.cache[key]=min(range(255),key=lambda i:sum((v-c)**2 for v,c in zip(query,self.palette[i])))
        return self.cache[key]
