import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.nio.file.*;
import java.util.*;
import java.io.*;
public class I76_VlocCameraAttachmentProbe extends GhidraScript {
 static final long OBJ=0x21000000L,RT=0x21002000L,CTX=0x21004000L,CHILD=0x21005000L,VLOC=0x21006000L,ACTIVE=0x21007000L,STACK=0x30020000L,SENT=0x70000000L;
 EmulatorHelper e;PrintWriter out;String name;int childAlloc, classReg,steps,optionalFlagVisits,defaultEligible,defaultMissing;
 Address a(long x){return toAddr(x&0xffffffffL);}String hex(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 long read(long addr){byte[] b=e.readMemory(a(addr),4);if(b==null||b.length!=4)throw new RuntimeException("Invalid read "+hex(addr));return ((long)b[0]&255)|(((long)b[1]&255)<<8)|(((long)b[2]&255)<<16)|(((long)b[3]&255)<<24);}
 void write(long addr,long v){e.writeMemoryValue(a(addr),4,v&0xffffffffL);}void map(long addr,int size){e.writeMemory(a(addr),new byte[size]);}
 long r(String k){return e.readRegister(k).longValue()&0xffffffffL;}
 void popret(long val){long sp=r("ESP");long next=read(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",val);}
 void record(String type,String detail){out.printf("%s\t%s\t%s%n",name,type,detail);}
 void reset(byte[] vloc,int flag){e=new EmulatorHelper(currentProgram);map(OBJ,0x1000);map(RT,0x1000);map(CTX,0x1000);map(CHILD,0x1000);map(VLOC,0x1000);map(ACTIVE,0x1000);map(STACK-0x10000,0x11000);e.writeMemory(a(VLOC),vloc);
  write(OBJ+0x70,RT);write(OBJ+0x6c,1);write(OBJ+0x10,flag);write(OBJ+0xc,3);write(CTX,OBJ);write(ACTIVE,OBJ);write(0x004c2908L,ACTIVE);
  for(String rr:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(rr,0);e.writeRegister("DF",0);childAlloc=classReg=steps=optionalFlagVisits=defaultEligible=defaultMissing=0;
 }
 long call(long func,long...args)throws Exception{long sp=STACK-0x2000;write(sp,SENT);for(int i=0;i<args.length;i++)write(sp+4+4L*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",func);
  for(int i=0;i<200000;i++) {long pc=r("EIP"),rsp=r("ESP");steps++;if(pc==SENT)return r("EAX");
    if(pc==0x458bf0L){optionalFlagVisits++;record("NATIVE_FLAG_TEST_ENTER","status="+hex(read(OBJ+0x10)));}
    if(pc==0x45ebd0L){childAlloc++;record("STUB_NODE_ALLOCATION","object="+hex(CHILD)+";caller="+hex(read(rsp)));popret(CHILD);continue;}
    if(pc==0x461970L){classReg++;long obj=read(rsp+4),cls=read(rsp+8);write(obj+0x6c,cls);record("STUB_CLASS_RUNTIME_BIND","object="+hex(obj)+";class="+hex(cls));popret(0);continue;}
    if(!e.step(monitor))throw new Exception("Emulation error "+hex(pc)+" "+e.getLastError());
  }throw new Exception("Step budget exhausted "+hex(r("EIP")));
 }
 void cameraGuard() throws Exception{long sp=STACK-0x2000;write(sp,SENT);e.writeRegister("ESP",sp);e.writeRegister("EIP",0x00406ab0L);boolean entered=false;
  for(int i=0;i<10000;i++){long pc=r("EIP");steps++;
   if(pc==0x00406b02L){entered=true;record("NATIVE_CAMERA_RUNTIME_READ","runtime398="+hex(read(RT+0x398)));}
   if(pc==0x00406b13L){defaultEligible++;record("NATIVE_CAMERA_POST_GUARD","pc="+hex(pc)+";runtime398="+hex(read(RT+0x398)));return;}
   if(pc==0x00406df4L||pc==SENT){defaultMissing++;record("NATIVE_CAMERA_NULL_EXIT","pc="+hex(pc));return;}
   if(!e.step(monitor))throw new Exception("Camera original instruction error "+hex(pc)+" "+e.getLastError());
  }throw new Exception("Camera step budget exhausted");
 }
 void scenario(Path base,String vdf,int flag)throws Exception{
   byte[] file=Files.readAllBytes(base.resolve(vdf));int off=-1;for(int i=0;i+60<=file.length;i++)if(file[i]=='V'&&file[i+1]=='L'&&file[i+2]=='O'&&file[i+3]=='C'&&(file[i+8]&255)==0x28&&file[i+9]==0&&file[i+10]==0&&file[i+11]==0){off=i;break;}
   if(off<0)throw new Exception("No VLOC 0x28 in retail "+vdf);byte[] rec=Arrays.copyOfRange(file,off,off+60);name=vdf+(flag!=0?"_flagged":"_unflagged");reset(rec,flag);
   try{record("RETAIL_VLOC","offset="+off+";record_type=0x28;bytes=60;status="+hex(flag));
    long result=call(0x004ae000L,VLOC,CTX),stored=read(RT+0x398);record("VLOC_NATIVE_RETURN","eax="+hex(result)+";runtime398="+hex(stored)+";nodeAllocBoundary="+childAlloc+";classBindBoundary="+classReg+";optionalFlagInvocations="+optionalFlagVisits);
    if(result!=1 || (flag==0 && stored!=0) || (flag!=0 && stored!=CHILD))throw new Exception("VLOC native field invariant failed for "+name);
    if(flag!=0){for(int k=0;k<9;k++){long source=read(VLOC+12L+4L*k),actual=read(CHILD+24L+4L*k);if(source!=actual)throw new Exception("Transform mismatch index "+k);}record("NATIVE_LOCAL_TRANSFORM","nine_source_dwords_copied_exactly=true;childClass="+hex(read(CHILD+0x6c)));}
    cameraGuard();if(flag==0&&defaultMissing!=1||flag!=0&&defaultEligible!=1)throw new Exception("Camera guard transition wrong for "+name);
    record("ASSERT_PASS","callbackCase=40;guardFieldCorrect=true;steps="+steps);
   } finally{e.dispose();e=null;}
 }
 public void run()throws Exception{if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("Retail binary mismatch");String[] args=getScriptArgs();try(PrintWriter p=new PrintWriter(new FileWriter(args[1]))){out=p;out.println("scenario\tevent\tdetail");for(String v:new String[]{"valeprec.vdf","vxbus.vdf"})for(int flag:new int[]{0,0x10})scenario(Paths.get(args[0]),v,flag);}}
}
