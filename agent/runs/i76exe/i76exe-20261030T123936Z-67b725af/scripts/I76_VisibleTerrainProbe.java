// Original-instruction terrain experiment. Loader lineage: accepted terrain run 3f1f83f8.
//@category i76
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;import java.nio.file.*;import java.util.*;
public class I76_VisibleTerrainProbe extends GhidraScript {
 static final long TER=0x40000000L,MSN=0x41000000L,STACK=0x30020000L,SENT=0x70000000L;
 boolean outputGuard=false;int harnessOutputWrites=0;
 void guard(long p,int n){if(outputGuard&&p<0x44400000L&&p+n>0x42000000L){harnessOutputWrites++;throw new IllegalStateException("harness output write "+hx(p));}}
 EmulatorHelper e;PrintWriter trace;String scenario;byte[] missionBytes,terrainBytes,preTransformBytes;int tdefOff,wrldOff;List<Long> polygonRecords=new ArrayList<>();List<byte[]> polygonSnapshots=new ArrayList<>();
 Process host;DataInputStream hostOut;DataOutputStream hostIn;
 void wd(long p,double v){long b=Double.doubleToRawLongBits(v);w32(p,b);w32(p+4,b>>>32);}
 int tag(byte[] b,String n){byte[] v=n.getBytes();outer:for(int j=0;j<b.length-4;j++){for(int k=0;k<4;k++)if(b[j+k]!=v[k])continue outer;return j;}throw new IllegalArgumentException(n);}
 Address a(long v){return toAddr(v&0xffffffffL);}
 String hx(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 long reg(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u32(long p){byte[] b=e.readMemory(a(p),4);if(b==null||b.length!=4)throw new IllegalStateException("invalid read="+hx(p));return (((long)b[0]&255)|(((long)b[1]&255)<<8)|(((long)b[2]&255)<<16)|(((long)b[3]&255)<<24))&0xffffffffL;}
 void w32(long p,long v){guard(p,4);e.writeMemoryValue(a(p),4,v&0xffffffffL);}
 void mem(long p,int n){guard(p,n);e.writeMemory(a(p),new byte[n]);}
 String cstr(long p,int max){StringBuilder b=new StringBuilder();for(int i=0;i<max;i++){byte[] x=e.readMemory(a(p+i),1);if(x==null||x.length<1){b.append("?");break;}if(x[0]==0)break;b.append((char)(x[0]&255));}return b.toString();}
 void log(String kind,long pc,String detail){trace.println(scenario+"\t"+kind+"\t"+hx(pc)+"\t"+detail);}
 String vec(long at,int words){StringJoiner out=new StringJoiner(",");for(int j=0;j<words;j++)out.add(hx(u32(at+4L*j)));return out.toString();}
 void ret(long value){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void retStd(long value,int nargs){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4+4*nargs);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 double rd64(long p){return Double.longBitsToDouble((u32(p+4L)<<32)|u32(p));}
 void initializeTerrain()throws Exception{
  mem(TER,terrainBytes.length);e.writeMemory(a(TER),terrainBytes);mem(MSN,missionBytes.length);e.writeMemory(a(MSN),missionBytes);
  tdefOff=tag(missionBytes,"TDEF");wrldOff=tag(missionBytes,"WRLD");
  w32(0x005dd2c4L,0x70001000L);
  runCall(0x004b8a10L,MSN+wrldOff);log("WRLD_MATERIALS",0x004b8a10L,"properties="+vec(0x00644220L,40));
  runCall(0x00493910L,MSN+tdefOff+8,0,MSN+tdefOff+u32(MSN+tdefOff+4));
  log("TERRAIN_INITIALIZED",0x00493910L,"return="+reg("EAX")+";scale="+hx(u32(0x006442c4L))+";step="+hx(u32(0x006442c0L))+";mapped="+hx(u32(0x005a6070L)));
  if(reg("EAX")!=1||u32(0x006442c4L)!=0x3e4ccccdL)throw new Exception("terrain initialization invariant");
  Files.write(Paths.get(getScriptArgs()[2]+".grid.bin"),e.readMemory(a(0x00644380L),65536));
  int zm=tag(missionBytes,"ZMAP"),count=missionBytes[zm+8]&255;int mapped=0;
  for(int z=0;z<80;z++)for(int x=0;x<80;x++){int index=missionBytes[zm+9+z*80+x]&255;if(index!=255){long actual=u32(0x00644380L+4L*((z+24)*128+x+24));if(actual!=TER+index*0x8000L)throw new Exception("page pointer");log("TERRAIN_PAGE",0x00493080L,"x="+x+";z="+z+";zone="+index+";pointer="+hx(actual));mapped++;}}
  for(int j=0;j<16384;j++){int gx=j%128-24,gz=j/128-24;int zone=(gx>=0&&gx<80&&gz>=0&&gz<80)?missionBytes[zm+9+gz*80+gx]&255:255;long expect=zone==255?0x0059c588L:TER+zone*0x8000L;if(u32(0x00644380L+j*4L)!=expect)throw new Exception("full page grid mismatch");}
  if(terrainBytes.length!=count*0x8000)throw new Exception("TER count");
  log("TERRAIN_PAGE_CHECK",0x00493080L,"declared="+count+";mapped="+mapped+";fullGridValidated=16384;default="+hx(u32(0x00644380L)));

 }

 void pop87(){for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));}
 void instructionService(long pc)throws Exception{
  int op=pc==0x492eafL?1:0;java.math.BigInteger st0=e.readRegister("ST0"),st1=e.readRegister("ST1");
  hostIn.writeByte(op);for(java.math.BigInteger v:new java.math.BigInteger[]{st0,st1})for(int k=0;k<10;k++)hostIn.writeByte(v.shiftRight(8*k).intValue()&255);
  int cw=e.readRegister("FPUControlWord").intValue();hostIn.writeByte(cw&255);hostIn.writeByte((cw>>>8)&255);hostIn.flush();
  byte[] answer=hostOut.readNBytes(op==1?10:8);if(answer.length!=(op==1?10:8))throw new Exception("instruction service EOF");
  java.math.BigInteger value=java.math.BigInteger.ZERO;for(int k=0;k<answer.length;k++)value=value.or(java.math.BigInteger.valueOf(answer[k]&255).shiftLeft(8*k));
  pop87();if(op==1)e.writeRegister("ST0",value);else{long ptr=reg("EBP")-(pc==0x4935eeL?0x14:0xc);w32(ptr,value.longValue());w32(ptr+4,value.shiftRight(32).longValue());}
  e.writeRegister("EIP",pc+(op==1?2:3));e.writeRegister("FPUInstructionPointer",pc);
  log("HARDWARE_INSTRUCTION",pc,"op="+op+";st0="+st0.toString(16)+";st1="+st1.toString(16)+";cw="+Integer.toHexString(cw)+";result="+value.toString(16));
 }
 void runCall(long target,long...args)throws Exception{
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  for(int n=0;n<5000000;n++){
   long pc=reg("EIP"),rsp=reg("ESP");
   if(pc==SENT){log("RETURN",target,"eax="+reg("EAX")+";steps="+n);return;}
   // Continue through transform, projection and the original adaptive leaf walker.
   if(target==0x490a00L&&pc==0x490f90L){log("POSTWALKER_BOUNDARY",pc,"vertices="+u32(0x6442ecL)+";original_walker_returned=true");return;}
   if(target==0x490a00L&&pc==0x4937c0L){preTransformBytes=e.readMemory(a(0x42000000L),(int)u32(0x6442ecL)*12);log("PRETRANSFORM_VERTEX_SNAPSHOT",pc,"count="+u32(0x6442ecL)+";bytes="+preTransformBytes.length);}
   if(pc==0x492eafL||pc==0x4935eeL||pc==0x493608L){if(scenario.equals("raw")&&pc==0x492eafL){log("RAW_UNSUPPORTED_BOUNDARY",pc,"attempting original fpatan without service");if(!e.step(monitor))throw new Exception("original unsupported FPATAN "+e.getLastError());continue;}instructionService(pc);continue;}
   if(pc==0x4931a4L){long ptr=reg("EAX")+reg("ECX")*2;log("VISUAL_HEIGHT_READ",pc,"address="+hx(ptr)+";word="+hx(u32(ptr)&65535));}
   if(pc==0x491810L)log("LEAF_ENTER",pc,"cursor="+hx(u32(0x654380L))+";edges="+vec(rsp+4,4));
   if(pc==0x4922f0L||pc==0x4924b0L){long list=u32(rsp+4),count=u32(rsp+8);StringJoiner ids=new StringJoiner(",");if(count<=32)for(int k=0;k<count;k++)ids.add(Long.toString(u32(list+4L*k)));log("POLYGON_EMITTER_ENTRY",pc,"vertices_ptr="+hx(list)+";count="+count+";color_or_mode="+hx(u32(rsp+12))+";indices="+ids);}
   if(pc==0x490590L)log("POLYGON_ALLOCATOR_ENTRY",pc,"stack="+vec(rsp,5));
   if(pc==0x4922f9L){long rec=reg("EAX");polygonRecords.add(rec);log("POLYGON_ALLOCATOR_RETURN",pc,"record="+hx(rec));}
   if(pc==0x4923abL){long rec=reg("EDI");if(rec!=0){int count=(int)u32(rec);byte[] record=e.readMemory(a(rec),0xb4);polygonSnapshots.add(record);log("POLYGON_RECORD_BEFORE_CLIP",pc,"address="+hx(rec)+";vertex_count="+count+";bytes="+java.util.HexFormat.of().formatHex(record));}else log("POLYGON_RECORD_NULL",pc,"allocator_return=00000000;record_snapshot_suppressed=true");}
   if(pc==0x4923b1L)log("POLYGON_CLIP_CALL",pc,"target="+hx(u32(0x004f9538L))+";view="+hx(u32(0x006442d4L))+";record="+hx(reg("EDI")));
   if(pc==0x4923beL)log("POLYGON_CLIP_RESULT",pc,"accepted="+(reg("EAX")!=0)+";eax="+hx(reg("EAX")));
   if(pc==0x48fe10L)log("POLYGON_BIN_ENTRY",pc,"stack="+vec(rsp,4));

   if(pc==0x490b23L)log("BOUNDS_RESULT",pc,"eax="+reg("EAX")+";grid="+vec(0x6442e0L,3)+";planes="+u32(0x6442f0L));
   if(pc==0x474ea0L){log("SERVICE_EMPTY_FILL",pc,"original empty-region branch; no framebuffer");ret(0);continue;}
   if(pc==0x4915f7L||pc==0x49160fL||pc==0x491627L||pc==0x49163fL){long ptr=reg(pc==0x4915f7L?"EBX":pc==0x49160fL?"EDI":pc==0x491627L?"ECX":"ESI");log("MATERIAL_PREDICATE_READ",pc,"address="+hx(ptr)+";word="+hx(u32(ptr)&65535));}
   if(pc==0x4911e0L||pc==0x4929b0L||pc==0x490b8bL)log("ORIGINAL_ENTER",pc,"stack="+vec(rsp,5));
   if(pc==0x4b4048L)log("CALLBACK_RESULT",pc,"eax="+reg("EAX"));
   if(pc==0x4ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).intValue()&32767;double v=Math.scalb(ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue(),exp-16383-63);if(ext.testBit(79))v=-v;int value=(int)v;pop87();log("SERVICE_FTOL",pc,"st0="+ext.toString(16)+";result="+value);ret(value&0xffffffffL);continue;}
   if(target==0x4b8a10L&&(pc==0x423320L||pc==0x477b00L||pc==0x478b30L||pc==0x479780L||pc==0x4b8500L||pc==0x4908f0L||pc==0x401540L)){log("SERVICE_WRLD",pc,"peripheral body omitted");ret(0);continue;}
   if(pc==0x42d5d0L){log("SERVICE_REPORTER",pc,"message="+cstr(u32(rsp+4),200));ret(0);continue;}
   if(pc==0x46ffc0L){log("SERVICE_RESOURCE_ABSENT",pc,"name="+cstr(u32(rsp+4),100));ret(0);continue;}
   if(pc==0x70001000L){log("SERVICE_PALETTE",pc,"omitted");ret(0);continue;}
   if(pc==u32(0x4bc234L)){String fmt=cstr(u32(rsp+8),120),name=cstr(u32(rsp+12),120),out=fmt.replace("%s",name);guard(u32(rsp+4),out.length()+1);e.writeMemory(a(u32(rsp+4)),(out+"\0").getBytes());log("SERVICE_SPRINTF",pc,out);ret(out.length());continue;}
   if(pc==u32(0x4bc16cL)){mem(u32(rsp+8),40);log("SERVICE_STAT",pc,"success");ret(0);continue;}
   if(pc==u32(0x4bc0d8L)){log("SERVICE_CREATEFILE",pc,cstr(u32(rsp+4),100));retStd(0x11110001L,7);continue;}
   if(pc==u32(0x4bc0bcL)){log("SERVICE_MAPPING",pc,"read-only TER");retStd(0x11110002L,6);continue;}
   if(pc==u32(0x4bc0c0L)){log("SERVICE_MAPVIEW",pc,"base="+hx(TER));retStd(TER,5);continue;}
   if(pc==u32(0x4bc1f0L)){long dst=u32(rsp+4);guard(dst,(int)u32(rsp+12));e.writeMemory(a(dst),e.readMemory(a(u32(rsp+8)),(int)u32(rsp+12)));log("SERVICE_MEMCPY",pc,"destination="+hx(dst));ret(dst);continue;}
   long vp=(pc==0x490c2dL||pc==0x490cb8L||pc==0x490d45L||pc==0x490dd0L||pc==0x49199dL)?reg("EAX")+reg("ESI")+4:0;
   long leaf=pc==0x491892L?reg("ESI"):0;
   if(!e.step(monitor))throw new Exception("original step "+hx(pc)+" "+e.getLastError());
   if(vp!=0)log("ORIGINAL_VERTEX_WRITE",pc,"address="+hx(vp-4)+";xyz="+vec(vp-4,3));
   if(leaf!=0)log("ORIGINAL_LEAF_WRITE",pc,"address="+hx(leaf)+";data="+vec(leaf,7));
  }throw new Exception("step limit");
 }
 void wf(long p,float f){w32(p,Float.floatToRawIntBits(f));}
 void capture()throws Exception{
  log("OUTPUT",reg("EIP"),"vertices="+u32(0x6442ecL)+";leaves="+u32(0x59c56cL)+";edges="+u32(0x59c568L)+";head="+hx(u32(0x59c560L))+";cursor="+hx(u32(0x654380L))+";harnessOutputWrites="+harnessOutputWrites+";bounds="+vec(0x6442e0L,4));
  for(int j=0;j<u32(0x6442ecL);j++)log("VERTEX",reg("EIP"),"index="+j+";xyz="+vec(0x42000000L+j*12L,3));
  long node=u32(0x59c560L);int count=0;while(node!=0){if(++count>10000)throw new Exception("leaf cycle");log("LEAF",reg("EIP"),"address="+hx(node)+";data="+vec(node,7));node=u32(node+8);}
  Files.write(Paths.get(getScriptArgs()[2]+".vertices.bin"),u32(0x6442ecL)==0?new byte[0]:e.readMemory(a(0x42000000L),(int)u32(0x6442ecL)*12));
  Files.write(Paths.get(getScriptArgs()[2]+".pretransform.bin"),preTransformBytes==null?new byte[0]:preTransformBytes);
  Files.write(Paths.get(getScriptArgs()[2]+".arena.bin"),u32(0x654380L)==0x44000000L?new byte[0]:e.readMemory(a(0x44000000L),(int)(u32(0x654380L)-0x44000000L)));
  try(DataOutputStream polygons=new DataOutputStream(Files.newOutputStream(Paths.get(getScriptArgs()[2]+".polygons.bin")))){polygons.writeInt(Integer.reverseBytes(polygonRecords.size()));for(long p:polygonRecords)polygons.writeInt(Integer.reverseBytes((int)p));}
  try(DataOutputStream records=new DataOutputStream(Files.newOutputStream(Paths.get(getScriptArgs()[2]+".polygon_records.bin")))){records.writeInt(Integer.reverseBytes(polygonSnapshots.size()));for(byte[] record:polygonSnapshots)records.write(record);}
  if(!polygonRecords.isEmpty()&&polygonRecords.get(0)!=0)Files.write(Paths.get(getScriptArgs()[2]+".polygon_pool.bin"),e.readMemory(a(0x47000000L),Math.min(0x100000,Math.max(0xb4,polygonRecords.size()*0xb4))));
 }
 @Override public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5");
  String[] args=getScriptArgs();missionBytes=Files.readAllBytes(Paths.get(args[0]));terrainBytes=Files.readAllBytes(Paths.get(args[1]));
  java.security.MessageDigest md=java.security.MessageDigest.getInstance("SHA-256");
  if(!java.util.HexFormat.of().formatHex(md.digest(missionBytes)).equals("923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f")||!java.util.HexFormat.of().formatHex(md.digest(terrainBytes)).equals("fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea"))throw new Exception("M06 identity");
  scenario=args[3];
  try(PrintWriter out=new PrintWriter(args[2])){trace=out;trace.println("scenario\tkind\tpc\tdetail");
   e=new EmulatorHelper(currentProgram);mem(STACK-0x10000L,0x10800);for(String reg:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(reg,0);e.writeRegister("DF",0);e.writeRegister("FPUControlWord",0x037f);
   host=new ProcessBuilder(args[4]).start();hostIn=new DataOutputStream(host.getOutputStream());hostOut=new DataInputStream(host.getInputStream());
   runCall(0x493c50L);initializeTerrain();
   mem(0x42000000L,0x100000);mem(0x43000000L,0x100000);mem(0x44000000L,0x400000);mem(0x45000000L,0x1000);mem(0x46000000L,0x1000);mem(0x47000000L,0x100000);
   if(scenario.equals("pool")){w32(0x006543c0L,0x47000000L);log("CONTROLLED_POLYGON_POOL",0x490a00L,"service-owned backing=47000000;bytes=00100000;original allocator body retained");}
   w32(0x5dd320L,0x42000000L);w32(0x5dd2ecL,0x43000000L);w32(0x5dd324L,0x44000000L);w32(0x5dd2a8L,0);w32(0x58db00L,0);
   long view=0x45000000L;wf(view+8,320);wf(view+0x2c,1);w32(view+0x3c,0x46000000L);w32(0x46000000L,640);
   // Controlled affine view: row-major identity 3x3 basis at record+0x40,
   // zero double translation in primary/contrast/below; the pool diagnostic
   // uses (-2860,-28,-47900) to center the accepted source region in camera
   // coordinates. These are explicit test inputs, not game-produced cameras.
   for(int row=0;row<3;row++)for(int col=0;col<3;col++)wf(view+0x40+row*12+col*4,row==col?1.0f:0.0f);
   wd(view+0x68,scenario.equals("pool")?-2860.0:0.0);wd(view+0x70,scenario.equals("pool")?-28.0:0.0);wd(view+0x78,scenario.equals("pool")?-47900.0:0.0);
   double x=scenario.equals("contrast")?3152.5:2952.5,z=48152.5,y=scenario.equals("below")?-100:200;
   wd(view+0x160,x);wd(view+0x168,y);wd(view+0x170,z);
   for(int j=0;j<4;j++){long p=view+0x178+j*24;wd(p,x+(j==0||j==3?-80:80));wd(p+8,1);wd(p+16,z+(j<2?-80:80));}
   if(scenario.equals("poison")){for(long ptr:new long[]{0x42000000L,0x43000000L,0x44000000L}){byte[] poison=new byte[ptr==0x44000000L?0x400000:0x100000];Arrays.fill(poison,(byte)0xa5);e.writeMemory(a(ptr),poison);}log("POISON_STORAGE",0,"initialOutputBytes=A5;no_mesh");}
   log("CONTROLLED_VIEW",0,"record="+vec(view,118));
   outputGuard=true;try{runCall(0x490a00L,view);}catch(Exception ex){log("BLOCKER",reg("EIP"),ex.toString());}
   capture();e.dispose();hostIn.close();if(host.waitFor()!=0)throw new Exception("instruction service exit");
  }
 }
}
