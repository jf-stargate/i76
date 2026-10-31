import ghidra.app.emulator.EmulatorHelper;
import java.io.*;import java.nio.file.*;import java.util.*;
public class I76_CameraTerrainProbe extends I76_CameraBase {
 static final long TER=0x40000000L,MSN=0x41000000L;
 long currentLeaf=0,polygon=0;int polygonCount=0,allocIndex=0;boolean transformed=false,outputGuard=false;int harnessOutputWrites=0;
 byte[] missionBytes,terrainBytes;int tdefOff,wrldOff;String terrainOutput;
 Process host;DataInputStream hostOut;DataOutputStream hostIn;
 void guard(long p,int n){if(outputGuard&&((p<0x44400000L&&p+n>0x42000000L)||(p<0x48500000L&&p+n>0x48000000L)||(p<0x4c2908L&&p+n>0x4c2730L))){harnessOutputWrites++;throw new IllegalStateException("sealed output write "+hx(p));}}
 @Override void w32(long p,long v){guard(p,4);super.w32(p,v);}
 @Override void mem(long p,int n){guard(p,n);super.mem(p,n);}
 void wd(long p,double v){long b=Double.doubleToRawLongBits(v);w32(p,b);w32(p+4,b>>>32);}
 int tag(byte[] b,String n){byte[] v=n.getBytes();outer:for(int j=0;j<b.length-4;j++){for(int k=0;k<4;k++)if(b[j+k]!=v[k])continue outer;return j;}throw new IllegalArgumentException(n);}
 double rd64(long p){return Double.longBitsToDouble((u32(p+4L)<<32)|u32(p));}
 void initializeTerrain()throws Exception{
  mem(TER,terrainBytes.length);e.writeMemory(a(TER),terrainBytes);mem(MSN,missionBytes.length);e.writeMemory(a(MSN),missionBytes);
  tdefOff=tag(missionBytes,"TDEF");wrldOff=tag(missionBytes,"WRLD");
  w32(0x005dd2c4L,0x70001000L);
  terrainCall(0x004b8a10L,MSN+wrldOff);log("WRLD_MATERIALS",0x004b8a10L,"properties="+vec(0x00644220L,40));
  terrainCall(0x00493910L,MSN+tdefOff+8,0,MSN+tdefOff+u32(MSN+tdefOff+4));
  log("TERRAIN_INITIALIZED",0x00493910L,"return="+reg("EAX")+";scale="+hx(u32(0x006442c4L))+";step="+hx(u32(0x006442c0L))+";mapped="+hx(u32(0x005a6070L)));
  if(reg("EAX")!=1||u32(0x006442c4L)!=0x3e4ccccdL)throw new Exception("terrain initialization invariant");
  Files.write(Paths.get(terrainOutput+".grid.bin"),e.readMemory(a(0x00644380L),65536));
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
 void terrainCall(long target,long...args)throws Exception{
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  for(int n=0;n<5000000;n++){
   long pc=reg("EIP"),rsp=reg("ESP");
   if(pc==SENT){log("RETURN",target,"eax="+reg("EAX")+";steps="+n);return;}
   if(target==0x490a00L&&pc==0x4937c0L){
    log("PRETRANSFORM_BOUNDARY",pc,"caller="+hx(u32(rsp)));save("pre");
   }
   if(target==0x490a00L&&pc==0x490ef2L){transformed=true;log("TRANSFORM_RETURN",pc,"eax="+hx(reg("EAX"))+";near="+hx(u32(0x6543acL))+";far="+hx(u32(0x6543a4L))+";minHeight="+hx(u32(0x6442f4L)));save("post");if(mode.equals("transform"))return;}
   if(pc==0x493839L)log("COMPOSED_MATRIX",pc,"data="+vec(reg("EBP")-0x4c,16));
   if(pc==0x491a30L)log("WALK_ENTER",pc,"callbacks="+vec(rsp+4,2)+";head="+hx(u32(0x59c560L)));
   if(pc==0x48e190L||pc==0x4923f0L){currentLeaf=u32(rsp+4);log("LEAF_CALLBACK",pc,"leaf="+hx(currentLeaf)+";args="+vec(rsp,3));}
   if(pc==0x4922f0L||pc==0x4924b0L){polygonCount++;long count=u32(rsp+8);log("EMITTER_ENTER",pc,"leaf="+hx(currentLeaf)+";args="+vec(rsp,4)+";indices="+vec(u32(rsp+4),(int)count));}
   if(pc==0x490590L)log("ALLOCATOR_ENTER",pc,"caller="+hx(u32(rsp))+";cursor="+hx(u32(0x6543c0L))+";active="+hx(u32(0x65439cL)));
   if(pc==0x4922f9L||pc==0x4924b9L){polygon=reg("EAX");log("ALLOCATOR_RETURN",pc,"record="+hx(polygon)+";active="+hx(u32(0x65439cL)));if(mode.equals("baseline")){log("BASELINE_STOP",pc,"unmodified allocator result captured before emitter stores");return;}}
   if(pc==0x471f00L)log("DESCRIPTOR_SELECT",pc,"args="+vec(rsp,3)+";pair="+vec(u32(rsp+4),2));
   if(pc==0x49249dL)log("DESCRIPTOR_RETURN",pc,"value="+hx(reg("EAX")));
   if(mode.equals("alternate")&&pc==0x4924e0L){log("ALTERNATE_HEADER_STOP",pc,"record="+hx(polygon)+";header="+vec(polygon,7)+";flags="+hx(u32(0x59c548L))+";descriptor="+hx(u32(0x59c558L)));return;}
   if(pc==0x47bf00L){log("CLIP_ENTER",pc,"record="+hx(polygon)+";args="+vec(rsp,6)+";data="+vec(polygon,7+(int)u32(polygon)*6));}
   if(pc==0x4923b7L||pc==0x4925afL)log("CLIP_RETURN",pc,"count="+reg("EAX")+";record="+hx(polygon)+";data="+vec(polygon,7+Math.max((int)reg("EAX"), (int)u32(polygon))*6));
   if(pc==0x48fe10L)log("BIN_ENTER",pc,"record="+hx(polygon)+";depth="+hx(u32(rsp+4))+";cursor="+hx(u32(0x6543c0L)));
   if(pc==0x4923c9L||pc==0x4925c1L)log("BIN_RETURN",pc,"record="+hx(polygon)+";cursor="+hx(u32(0x6543c0L))+";bucket="+hx(u32(0x654384L))+";bucketData="+vec(u32(0x654384L),3)+";data="+vec(polygon,7));
   if(pc==0x498940L||pc==0x499ce0L){long size=u32(rsp+4),ptr=0x48000000L+allocIndex++*0x100000L;mem(ptr,(int)size);log("SERVICE_DIAGNOSTIC_HEAP",pc,"bytes="+size+";pointer="+hx(ptr));ret(ptr);continue;}

   if(pc==0x492eafL||pc==0x4935eeL||pc==0x493608L){if(scenario.equals("raw")&&pc==0x492eafL){log("RAW_UNSUPPORTED_BOUNDARY",pc,"attempting original fpatan without service");if(!e.step(monitor))throw new Exception("original unsupported FPATAN "+e.getLastError());continue;}instructionService(pc);continue;}
   if(pc==0x4931a4L){long ptr=reg("EAX")+reg("ECX")*2;log("VISUAL_HEIGHT_READ",pc,"address="+hx(ptr)+";word="+hx(u32(ptr)&65535));}
   if(pc==0x491810L)log("LEAF_ENTER",pc,"cursor="+hx(u32(0x654380L))+";edges="+vec(rsp+4,4));

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
   if(pc==u32(0x4bc1f0L)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);
    if(dst>=0x48000000L&&dst<0x48500000L){if(u32(rsp)!=0x47bedfL||dst!=polygon+28||src<STACK-0x10000L||src+len>STACK||len<=0||len>32*24)throw new IllegalStateException("unexpected clip memcpy");log("SERVICE_CLIP_MEMCPY",pc,"caller="+hx(u32(rsp))+";source="+hx(src)+";destination="+hx(dst)+";bytes="+len+";data="+vec(src,len/4));}
    else guard(dst,len);
    e.writeMemory(a(dst),e.readMemory(a(src),len));log("SERVICE_MEMCPY",pc,"destination="+hx(dst));ret(dst);continue;}

   long proj=(pc==0x47c29dL?reg("EDX")-24:pc==0x47c2abL?reg("EBX")+reg("EAX")-24:pc==0x47c2afL?reg("EDI")+reg("EAX")-24:pc==0x47c2b6L?reg("ESI")+reg("EAX")-24:0);
   long tv=(pc==0x4938a8L?reg("EAX"):pc==0x4938aaL?reg("EAX")+8:pc==0x4938bcL?reg("EAX")+4:0);
   long pv=(pc==0x49233aL?reg("ESI"):pc==0x49233fL?reg("ESI")+4:pc==0x492345L?reg("ESI")+8:pc==0x49250aL?reg("EBX"):pc==0x49250fL?reg("EBX")+4:pc==0x492515L?reg("EBX")+8:0);
   long vp=(pc==0x490c2dL||pc==0x490cb8L||pc==0x490d45L||pc==0x490dd0L||pc==0x49199dL)?reg("EAX")+reg("ESI")+4:0;
   long leaf=pc==0x491892L?reg("ESI"):0;
   long initBucket=(pc==0x48fa65L?reg("ESI")+8:pc==0x48fa6eL?reg("ESI")+4:pc==0x48fa77L?reg("ESI"):0);
   long bp=(pc>=0x48fe10L&&pc<=0x490465L)?u32(0x654384L):0;String beforeBucket=(bp>=0x48200000L&&bp<0x4820c000L)?vec(bp,3):"";
   long binCursor=(pc>=0x48fe10L&&pc<=0x490465L)?u32(0x6543c0L):-1;
   byte[] contextBefore=e.readMemory(a(0x654380L),72);
   if(!e.step(monitor))throw new Exception("original step "+hx(pc)+" "+e.getLastError());
   diffWrites(pc,0x654380L,contextBefore);
   if(initBucket!=0)log("ORIGINAL_BUCKET_INITIALIZE",pc,"address="+hx(initBucket)+";value="+hx(u32(initBucket)));
   if(!beforeBucket.equals("")&&!beforeBucket.equals(vec(bp,3)))log("ORIGINAL_BUCKET_WRITE",pc,"address="+hx(bp)+";before="+beforeBucket+";after="+vec(bp,3));
   if(binCursor>=0&&binCursor!=u32(0x6543c0L))log("ORIGINAL_BIN_CURSOR_WRITE",pc,"before="+hx(binCursor)+";after="+hx(u32(0x6543c0L)));
   if(proj!=0)log("ORIGINAL_PROJECTION_WRITE",pc,"address="+hx(proj)+";value="+hx(u32(proj)));
   if(tv!=0)log("TRANSFORM_WRITE",pc,"address="+hx(tv)+";value="+hx(u32(tv)));
   if(pv!=0)log("POLYGON_XYZ_WRITE",pc,"address="+hx(pv)+";value="+hx(u32(pv)));
   if(pc==0x49059aL||pc==0x4905a6L)log("ALLOCATOR_WRITE",pc,"address="+hx(reg("EAX")+(pc==0x49059aL?0x14:0))+";value=00000000");
   if(vp!=0)log("ORIGINAL_VERTEX_WRITE",pc,"address="+hx(vp-4)+";xyz="+vec(vp-4,3));
   if(leaf!=0)log("ORIGINAL_LEAF_WRITE",pc,"address="+hx(leaf)+";data="+vec(leaf,7));
  }throw new Exception("step limit");
 }
 void save(String stage)throws Exception{int count=(int)u32(0x6442ecL);Files.write(Paths.get(terrainOutput+"."+stage+".bin"),count==0?new byte[0]:e.readMemory(a(0x42000000L),count*12));}
 void capture()throws Exception{
  if(allocIndex>0){long used=u32(0x6543c0L)-0x48000000L;Files.write(Paths.get(terrainOutput+".polygons.bin"),used==0?new byte[0]:e.readMemory(a(0x48000000L),(int)used));Files.write(Paths.get(terrainOutput+".buckets.bin"),e.readMemory(a(0x48200000L),49152));log("POLYGON_STORAGE",reg("EIP"),"bytes="+used+";heapServices="+allocIndex);}

  log("OUTPUT",reg("EIP"),"vertices="+u32(0x6442ecL)+";leaves="+u32(0x59c56cL)+";edges="+u32(0x59c568L)+";head="+hx(u32(0x59c560L))+";cursor="+hx(u32(0x654380L))+";harnessOutputWrites="+harnessOutputWrites+";bounds="+vec(0x6442e0L,4));
  for(int j=0;j<u32(0x6442ecL);j++)log("VERTEX",reg("EIP"),"index="+j+";xyz="+vec(0x42000000L+j*12L,3));
  long node=u32(0x59c560L);int count=0;while(node!=0){if(++count>10000)throw new Exception("leaf cycle");log("LEAF",reg("EIP"),"address="+hx(node)+";data="+vec(node,7));node=u32(node+8);}
  Files.write(Paths.get(terrainOutput+".vertices.bin"),u32(0x6442ecL)==0?new byte[0]:e.readMemory(a(0x42000000L),(int)u32(0x6442ecL)*12));
  Files.write(Paths.get(terrainOutput+".arena.bin"),u32(0x654380L)==0x44000000L?new byte[0]:e.readMemory(a(0x44000000L),(int)(u32(0x654380L)-0x44000000L)));
 }

 @Override void continuity(String label)throws Exception {
  String[] args=getScriptArgs(); terrainOutput=args[1];
  w32(0x4c2908L,registeredEntry);w32(0x4fe420L,Float.floatToRawIntBits(0.016f));
  for(long p:new long[]{0x536770L,0x536778L,0x536780L})w32(p,1);
  long rt=u32(OBJ+0x70);for(int j=0;j<3;j++)w32(rt+0xd4+j*4,Float.floatToRawIntBits(new float[]{2,0,1}[j]));
  // Controlled test root pose in original terrain world units; no mission-spawn claim.
  double x=mode.equals("contrast")?3152.5:2952.5,y=mode.equals("below")?-100:60,z=48152.5;
  for(int j=0;j<9;j++)w32(OBJ+0x18+j*4,Float.floatToRawIntBits(j%4==0?1:0));
  wd(OBJ+0x40,x);wd(OBJ+0x48,y);wd(OBJ+0x50,z);
  log("CONTROLLED_ROOT",0,"bytes="+hexbytes(OBJ+0x18,64)+";units=terrain_world;mission_spawn=false");
  for(frame=0;frame<2;frame++){snapshot("before");cameraCall();snapshot("after");}
  byte[] view=e.readMemory(a(CAMERA),472);Files.write(Paths.get(terrainOutput+".view.bin"),view);
  missionBytes=Files.readAllBytes(Paths.get(args[3]));terrainBytes=Files.readAllBytes(Paths.get(args[4]));
  host=new ProcessBuilder(args[5]).start();hostIn=new DataOutputStream(host.getOutputStream());hostOut=new DataInputStream(host.getInputStream());
  initializeTerrain();
  mem(0x42000000L,0x100000);mem(0x43000000L,0x100000);mem(0x44000000L,0x400000);
  w32(0x5dd320L,0x42000000L);w32(0x5dd2ecL,0x43000000L);w32(0x5dd324L,0x44000000L);w32(0x5dd2a8L,0);w32(0x58db00L,0);
  terrainCall(0x48f9b0L);
  log("NATIVE_VIEW",0,"pointer="+hx(CAMERA)+";record="+vec(CAMERA,118));
  outputGuard=true;
  try{terrainCall(0x490a00L,CAMERA);}catch(Exception ex){log("BLOCKER",reg("EIP"),ex.toString());}
  if(!Arrays.equals(view,e.readMemory(a(CAMERA),472)))throw new Exception("terrain modified sealed camera");
  capture();log("COHERENT_COMPLETE",reg("EIP"),"viewUnchanged=true");
  hostIn.close();if(host.waitFor()!=0)throw new Exception("host exit");
 }
 @Override public void run()throws Exception {
  String[] args=getScriptArgs();mode=args[6];selected=true;nativeRoot=true;nativeRegistry=true;
  try(PrintWriter out=new PrintWriter(args[1])){trace=out;trace.println("scenario\tkind\tpc\tdetail");testVcfAll(args[0],"nobus1.vcf","bus_coherent_"+mode);}
 }
}
