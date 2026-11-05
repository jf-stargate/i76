"""Bounded original x86 execution. PE bytes are private; services are explicit.
Requires Unicorn 2.1.4. No Windows process or complete-frame claim.
"""
import struct,collections
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE,UC_HOOK_MEM_WRITE,UC_HOOK_MEM_INVALID,UC_HOOK_MEM_READ
from unicorn.x86_const import *
from corpus import sha,EXE
REGS={'eax':UC_X86_REG_EAX,'ebx':UC_X86_REG_EBX,'ecx':UC_X86_REG_ECX,'edx':UC_X86_REG_EDX,'esi':UC_X86_REG_ESI,'edi':UC_X86_REG_EDI,'ebp':UC_X86_REG_EBP,'esp':UC_X86_REG_ESP,'eip':UC_X86_REG_EIP}
SENT=0x70000000;STACK=0x30020000
class Machine:
    def __init__(self,exe):
        raw=exe.read_bytes();assert sha(raw)==EXE
        self.raw=raw;self.u=Uc(UC_ARCH_X86,UC_MODE_32);self.u.mem_map(0x400000,0x300000)
        pe=struct.unpack_from('<I',raw,60)[0];cnt=struct.unpack_from('<H',raw,pe+6)[0];sz=struct.unpack_from('<H',raw,pe+20)[0]
        self.spans=[]
        for i in range(cnt):
            vs,rva,rs,off=struct.unpack_from('<4I',raw,pe+24+sz+40*i+8)
            self.u.mem_write(0x400000+rva,raw[off:off+rs]);self.spans.append((0x400000+rva,rs,off))
        for p,n in [(0x20000000,0x1000000),(0x30000000,0x40000),(SENT,0x20000)]:self.u.mem_map(p,n)
        self.heap=0x20800000;self.resources={};self.events=[];self.seen=collections.Counter();self.allocations=[];self.stores=[];self.reads=[];self.watch_texture=None;self.pc=0;self.hook_extra=None;self.step_limit=2000000
        # Explicit IAT replacement; no retail instructions modified.
        self.services={0x46ffc0:'acquire',0x46fee0:'size',0x46fd40:'release'}
        for i,(iat,name) in enumerate([(0x4bc26c,'strchr'),(0x4bc210,'stricmp'),(0x4bc28c,'strncpy'),(0x4bc108,'HeapAlloc'),(0x4bc104,'HeapFree'),(0x4bc1f8,'strrchr'),(0x4bc1f0,'memmove')]):
            target=SENT+0x100+i*16;self.w32(iat,target);self.services[target]=name
        self.u.hook_add(UC_HOOK_CODE,self.code);self.u.hook_add(UC_HOOK_MEM_WRITE,self.write)
        self.u.hook_add(UC_HOOK_MEM_INVALID,self.invalid)
        self.u.hook_add(UC_HOOK_MEM_READ,self.read)
        self.rw(UC_X86_REG_FPCW,0x037f)
    def rw(self,r,v=None):
        if v is None:return self.u.reg_read(r)
        self.u.reg_write(r,v)
    def r(self,n):return self.rw(REGS[n])&0xffffffff
    def set(self,n,v):self.rw(REGS[n],v&0xffffffff)
    def u32(self,p):return struct.unpack('<I',self.u.mem_read(p,4))[0]
    def w32(self,p,v):self.u.mem_write(p,struct.pack('<I',v&0xffffffff))
    def f32(self,p,v):self.u.mem_write(p,struct.pack('<f',v))
    def cstr(self,p):
        b=bytes(self.u.mem_read(p,256));return b.split(b'\0')[0].decode('ascii')
    def alloc(self,n):
        assert 0<n<=0x100000
        p=self.heap;self.heap=(p+n+63)&~31;assert self.heap<0x21000000
        self.u.mem_write(p-16,b'\xcd'*16);self.u.mem_write(p,b'\xa5'*n);self.u.mem_write(p+n,b'\xcd'*16);self.allocations.append((p,n));return p
    def add_resource(self,n,b):
        p=0x20100000+len(self.resources)*0x40000;assert len(b)<0x40000
        self.u.mem_write(p,b);self.resources[n.lower()]=(p,bytes(b));return p
    def ret(self,value,pop=0):
        sp=self.r('esp');self.set('eax',value);self.set('eip',self.u32(sp));self.set('esp',sp+4+pop)
    def invalid(self,u,access,address,size,value,data):raise RuntimeError(f'unmapped at {self.pc:08x}: {address:08x}+{size}')
    def read(self,u,access,address,size,value,data):
        if not self.watch_texture:return
        p,n=self.watch_texture
        if size==1 and (p<=address<p+n or 0x61b2a0<=address<0x62b2a0 or 0x60afa0<=address<0x61afa0):
            kind='texel' if p<=address<p+n else 'lum' if 0x61b2a0<=address<0x62b2a0 else 'tbl'
            self.reads.append(dict(pc=f'{self.pc:08x}',address=f'{address:08x}',index=bytes(u.mem_read(address,1))[0],kind=kind))
    def write(self,u,access,address,size,value,data):
        if 0x20500000<=address<0x20510000:self.stores.append(dict(pc=f'{self.pc:08x}',address=f'{address:08x}',size=size,value=value))
    def code(self,u,pc,size,data):
        self.pc=pc
        if pc==SENT:u.emu_stop();return
        if pc in self.services:
            name=self.services[pc];sp=self.r('esp');args=[self.u32(sp+4+i*4) for i in range(3)];p=args[0]
            if name in ('acquire','size','release'):
                key=self.cstr(p).lower();res=self.resources.get(key)
                v=(res[0] if name=='acquire' else len(res[1])) if res and name!='release' else 0
                self.events.append(dict(service=name,name=key,result=v));self.ret(v)
            elif name in ('strchr','strrchr'):
                s=self.cstr(p);pos=s.find(chr(args[1]&255)) if name=='strchr' else s.rfind(chr(args[1]&255));self.ret(0 if pos<0 else p+pos)
            elif name=='stricmp':self.ret(0 if self.cstr(p).lower()==self.cstr(args[1]).lower() else 1)
            elif name=='strncpy':
                b=self.cstr(args[1]).encode()[:args[2]].ljust(args[2],b'\0');self.u.mem_write(p,b);self.ret(p)
            elif name=='memmove':
                self.u.mem_write(p,bytes(self.u.mem_read(args[1],args[2])));self.ret(p)
            elif name=='HeapAlloc':
                ptr=self.alloc(args[2]);self.events.append(dict(service=name,heap=args[0],flags=args[1],size=args[2],result=ptr));self.ret(ptr,12)
            elif name=='HeapFree':self.events.append(dict(service=name,ptr=args[2]));self.ret(1,12)
            return
        if not 0x400000<=pc<0x700000:raise RuntimeError(f'unknown service {pc:08x}')
        code=bytes(u.mem_read(pc,size));assert code==self.pe_read(pc,size),f'modified instruction {pc:x}'
        self.seen[(pc,size,sha(code))]+=1
        if self.hook_extra:self.hook_extra(self,pc)
    def pe_read(self,p,n):
        for base,size,off in self.spans:
            if base<=p and p+n<=base+size:return self.raw[off+p-base:off+p-base+n]
        raise ValueError('not file-backed code')
    def call(self,pc,args):
        self.w32(STACK,SENT)
        for i,v in enumerate(args):self.w32(STACK+4+4*i,v)
        self.set('esp',STACK);self.set('eip',pc);self.u.emu_start(pc,SENT,count=self.step_limit)
        assert self.r('eip')==SENT,f'bounded stop {self.r("eip"):08x}'
        return self.r('eax')
    def guards(self):
        return all(bytes(self.u.mem_read(p-16,16))==b'\xcd'*16 and bytes(self.u.mem_read(p+n,16))==b'\xcd'*16 for p,n in self.allocations)
    def coverage(self):return [dict(va=f'{p:08x}',length=s,sha256=h,count=c) for (p,s,h),c in sorted(self.seen.items())]
