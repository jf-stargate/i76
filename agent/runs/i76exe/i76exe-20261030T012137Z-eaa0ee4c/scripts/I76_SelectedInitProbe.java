import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.file.*;
import java.util.*;
// CAP-CONTROL-01 owned continuation of merged M-ENG-01, base 980037f.
// Parent SHA256 ca1ad48b130ccf4a4227639104325362c7b90dab949cd03f333502260c8b55b7.
// Original list insertion and descriptor traversal retained. Peripheral post services declared below.
// Direct initializer/peripheral calls are controls only; pending is the primary lifecycle experiment.
//@category i76
public class I76_SelectedInitProbe extends GhidraScript {
 static final long LOADER=0x4ad6f0L,PARSE=0x4b41e0L,VCFC=0x4ad950L,SPEC=0x4ade50L,WEPN=0x4aeb90L,WDFFN=0x4ae5e0L,EXIT=0x4b4290L;
 static final long OBJ=0x26000000L,CTX=0x26002000L,RUNTIME=0x26004000L,NAME=0x26007000L,FILE=0x25000000L;
 static final long WDFCTX=0x26009000L,FIRST=0x26010000L,SECOND=0x26011000L,FRT=0x26012000L,SRT=0x26013000L,NODES=0x26020000L;
 static final long STACK=0x30020000L,SENT=0x70000000L; static final int LIMIT=5000000;
 String mode="math-clock-pop-terrain"; long tick=1000;
 static final long TER=0x40000000L,MSN=0x41000000L;byte[] missionBytes,terrainBytes;int tdefOff,wrldOff,spawnOff;int terrainReads,groundCalls,solverCalls;long terrainReturn,solverReturn;
 Process host;DataOutputStream hostIn;DataInputStream hostOut;long probeReturn,contactPtr,solverFlagsPtr;int positiveProbe,frames=2;long tireReturn,tireRuntime,heightReturn;double heightX,heightZ;
 double x87(){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).intValue()&32767;double v=ext.signum()==0?0:Math.scalb(ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue(),exp-16383-63);return ext.testBit(79)?-v:v;}
 void pop87(){for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));}
 void wd(long p,double v){long bits=Double.doubleToRawLongBits(v);w32(p,bits);w32(p+4,bits>>>32);}
 int tag(byte[] b,String name){byte[] n=name.getBytes(java.nio.charset.StandardCharsets.ISO_8859_1);outer:for(int j=0;j<=b.length-4;j++){for(int k=0;k<4;k++)if(b[j+k]!=n[k])continue outer;return j;}throw new IllegalArgumentException(name);}
 long darg(double d,boolean high){long b=Double.doubleToRawLongBits(d);return high?b>>>32:b&0xffffffffL;}
 void initializeTerrain()throws Exception{
  mem(TER,terrainBytes.length);e.writeMemory(a(TER),terrainBytes);mem(MSN,missionBytes.length);e.writeMemory(a(MSN),missionBytes);
  tdefOff=tag(missionBytes,"TDEF");wrldOff=tag(missionBytes,"WRLD");
  w32(0x005dd2c4L,0x70001000L);
  runCall(0x004b8a10L,MSN+wrldOff);log("WRLD_MATERIALS",0x004b8a10L,"properties="+vec(0x00644220L,40));
  runCall(0x00493910L,MSN+tdefOff+8,0,MSN+tdefOff+u32(MSN+tdefOff+4));
  log("TERRAIN_INITIALIZED",0x00493910L,"return="+reg("EAX")+";scale="+hx(u32(0x006442c4L))+";step="+hx(u32(0x006442c0L))+";mapped="+hx(u32(0x005a6070L)));
  if(reg("EAX")!=1||u32(0x006442c4L)!=0x3e4ccccdL)throw new Exception("terrain initialization invariant");
  Files.write(Paths.get(getScriptArgs()[1]+".grid.bin"),e.readMemory(a(0x00644380L),65536));
  int zm=tag(missionBytes,"ZMAP"),count=missionBytes[zm+8]&255;int mapped=0;
  for(int z=0;z<80;z++)for(int x=0;x<80;x++){int index=missionBytes[zm+9+z*80+x]&255;if(index!=255){long actual=u32(0x00644380L+4L*((z+24)*128+x+24));if(actual!=TER+index*0x8000L)throw new Exception("page pointer");log("TERRAIN_PAGE",0x00493080L,"x="+x+";z="+z+";zone="+index+";pointer="+hx(actual));mapped++;}}
  for(int j=0;j<16384;j++){int gx=j%128-24,gz=j/128-24;int zone=(gx>=0&&gx<80&&gz>=0&&gz<80)?missionBytes[zm+9+gz*80+gx]&255:255;long expect=zone==255?0x0059c588L:TER+zone*0x8000L;if(u32(0x00644380L+j*4L)!=expect)throw new Exception("full page grid mismatch");}
  if(terrainBytes.length!=count*0x8000)throw new Exception("TER count");
  log("TERRAIN_PAGE_CHECK",0x00493080L,"declared="+count+";mapped="+mapped+";fullGridValidated=16384;default="+hx(u32(0x00644380L)));
  for(double[] p:new double[][]{{2952.5,48152.5},{2480,48725},{2560,48640},{2557.5,48637.5},{2560.25,48640.75},{1300,47380},{1940,48020},{2140,48020},{2410,48150},{2250,48525}}){
   runCall(0x00493550L,darg(p[0],false),darg(p[0],true),darg(p[1],false),darg(p[1],true));double y=x87();pop87();
   runCall(0x004927b0L,darg(p[0],false),darg(p[0],true),darg(p[1],false),darg(p[1],true));
   log("TERRAIN_SAMPLE",0x00493550L,"x="+p[0]+";z="+p[1]+";height="+y+";material="+reg("EAX"));
  }
 }
 void initializeEngineVariants()throws Exception{long name=MSN+0x20000L;mem(name,32);e.writeMemory(a(name),"engsnd.dat\0".getBytes());runCall(0x00469b00L,name);long count=u32(0x0058d900L);log("ENGINE_VARIANTS_INITIALIZED",0x00469b00L,"count="+count);if(count==0)throw new Exception("empty original engine variant registry");for(int j=0;j<count;j++)log("ENGINE_VARIANT_ROW",0x00469b00L,"row="+j+";id="+u32(0x00588e00L+j*96L)+";component="+u32(0x00588e04L+j*96L)+";flags="+u32(0x00588e08L+j*96L));}
 void placeRetailPose()throws Exception{
  // Controlled initial pose copied from the first authentic M06 spawn record; no spawn scheduler claimed.
  spawnOff=0;for(int j=0;j<missionBytes.length-108;j++)if(missionBytes[j]=='O'&&missionBytes[j+1]=='B'&&missionBytes[j+2]=='J'&&(missionBytes[j+8]&127)=='s'&&(missionBytes[j+9]&127)=='p'&&(missionBytes[j+10]&127)=='a'&&(missionBytes[j+11]&127)=='w'&&(missionBytes[j+12]&127)=='n'){spawnOff=j;break;}
  if(spawnOff==0)throw new Exception("spawn");
  e.writeMemory(a(OBJ+0x18),Arrays.copyOfRange(missionBytes,spawnOff+16,spawnOff+52));for(int k=0;k<3;k++)wd(OBJ+0x40+8*k,Float.intBitsToFloat((int)u32(MSN+spawnOff+8+44+4*k)));
  if(mode.contains("lowered")){wd(OBJ+0x48,rd64(OBJ+0x48)-1.0);log("DIAGNOSTIC_POSE_OFFSET",0,"sourceSpawnYMinus=1.0;terrain=unaltered_retail");}
  log("CONTACT_GEOMETRY",0x00440740L,"runtime="+hx(u32(OBJ+0x70))+";probeFourPoints="+vec(u32(OBJ+0x70)+4,12));
  log("RETAIL_SPAWN_POSE",0,"offset="+hx(spawnOff)+";basis="+vec(OBJ+0x18,9)+";x="+rd64(OBJ+0x40)+";y="+rd64(OBJ+0x48)+";z="+rd64(OBJ+0x50));
 }

 EmulatorHelper e;boolean selected;boolean nativeRoot,constructingRoot,nativeRegistry;long trackedMatrixPtr,registeredEntry;PrintWriter trace;byte[] bytes;String scenario,wdfName;int steps, n_vcfc,n_spec,n_wepn,n_weapon,n_nested,n_open,n_openfail,n_free;int failNested,failWeapon,failWeaponChunk,failGeo,builderCount,ctorCount,listCount,geoCount, nodeAlloc, runtimeAlloc, failNode, nodeFree, runtimeFree, classReleases, partAlloc, cacheBindings,cacheAlloc;boolean failOpen;long nextGeoReturnPc, firstMaterialReturnPc, firstMaterialOwner;String nextGeoName="",firstMaterialKey="",firstMaterialResource="";String firstError="";int caughtReporter,extraAlloc,materialBinds,nativeMaterialSuccess,realGeoConstructions,realGeoReturns,bodyParts,bodyNodeStart;long bodyBankZero;Map<String,byte[]> resourceBytes=new LinkedHashMap<>();Map<String,Long> resourcePtrs=new LinkedHashMap<>(); long genericHeapCursor=0x36000000L;
 Address a(long v){return toAddr(v&0xffffffffL);}
 String hx(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 long reg(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u32(long p){byte[] b=e.readMemory(a(p),4);if(b==null||b.length!=4)throw new IllegalStateException("invalid read="+hx(p));return (((long)b[0]&255)|(((long)b[1]&255)<<8)|(((long)b[2]&255)<<16)|(((long)b[3]&255)<<24))&0xffffffffL;}
 void w32(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}
 void mem(long p,int n){e.writeMemory(a(p),new byte[n]);}
 String cstr(long p,int max){StringBuilder b=new StringBuilder();for(int i=0;i<max;i++){byte[] x=e.readMemory(a(p+i),1);if(x==null||x.length<1){b.append("?");break;}if(x[0]==0)break;b.append((char)(x[0]&255));}return b.toString();}
 void log(String kind,long pc,String detail){trace.println(scenario+"\t"+kind+"\t"+hx(pc)+"\t"+detail);}
 String vec(long at,int words){StringJoiner out=new StringJoiner(",");for(int j=0;j<words;j++)out.add(hx(u32(at+4L*j)));return out.toString();}
 int invalidFloats(long at,int words){int n=0;for(int j=0;j<words;j++)if(!Float.isFinite(Float.intBitsToFloat((int)u32(at+4L*j))))n++;return n;}
 void ret(long value){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void retStd(long value,int nargs){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4+4*nargs);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 double rd64(long p){return Double.longBitsToDouble((u32(p+4L)<<32)|u32(p));}
 String doubles6(long p){StringJoiner sj=new StringJoiner(",");for(int i=0;i<6;i++)sj.add(String.format(Locale.ROOT,"%.12g",rd64(p+8L*i)));return sj.toString();}
 int nonfinite6(long p){int n=0;for(int i=0;i<6;i++)if(!Double.isFinite(rd64(p+8L*i)))n++;return n;}
 double axisLen2(){double x=Float.intBitsToFloat((int)u32(OBJ+0x30L)),y=Float.intBitsToFloat((int)u32(OBJ+0x34L)),z=Float.intBitsToFloat((int)u32(OBJ+0x38L));return x*x+y*y+z*z;}
 void reset(byte[] content,String file){e=new EmulatorHelper(currentProgram);bytes=content;trackedMatrixPtr=0;constructingRoot=false;registeredEntry=0;
  mem(STACK-0x10000L,0x10800);mem(OBJ,0x800);mem(CTX,0x100);mem(RUNTIME,0x3000);mem(NAME,0x100);
  mem(FILE,Math.max(content.length,0x1000));e.writeMemory(a(FILE),content);mem(WDFCTX,0x200);mem(FIRST,0x1000);mem(SECOND,0x1000);mem(FRT,0x1000);mem(SRT,0x1000);mem(NODES,0x2000);mem(0x27000000L,0x20000);mem(0x28000000L,0x180000);mem(0x29000000L,0x20000);mem(0x2a000000L,0x10000);mem(0x2b000000L,0x200000);mem(0x36000000L,0x800000);
  e.writeMemory(a(NAME),(file+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));
  w32(CTX,OBJ);w32(CTX+4,RUNTIME);w32(WDFCTX,CTX);w32(OBJ+0x70,RUNTIME);w32(FIRST+0xc,1);w32(SECOND+0xc,1);w32(0x54ad34L,0x12350000L);w32(0x54ad38L,0x12340000L);w32(0x54ad2cL,OBJ);w32(0x54ad30L,OBJ);for(int k=0;k<4;k++)w32(0x54b204L+k*4,0);w32(OBJ+0x6c,1);w32(OBJ+0xc,1);w32(OBJ+0x10,0);w32(0x005db97cL,0);w32(0x005db980L,0);
  w32(0x006562c4L,0);w32(0x005dabc0L,1); // not geometry-family mode
  for(String r:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(r,0);
  e.writeRegister("DF",0);e.writeRegister("FPUControlWord",0x037f);
  materialBinds=0;nativeMaterialSuccess=0;realGeoConstructions=0;realGeoReturns=0;nextGeoReturnPc=0;firstMaterialReturnPc=0;firstMaterialOwner=0;nextGeoName="";firstMaterialKey="";firstMaterialResource="";bodyParts=0;bodyNodeStart=0;bodyBankZero=0;genericHeapCursor=0x36000000L;n_vcfc=0;n_spec=0;n_wepn=0;n_weapon=0;n_nested=0;n_open=0;n_openfail=0;n_free=0;failNested=0;failWeapon=0;failWeaponChunk=0;failOpen=false;caughtReporter=0;firstError="";builderCount=0;ctorCount=0;listCount=0;geoCount=0;failGeo=0;nodeAlloc=0;runtimeAlloc=0;failNode=0;nodeFree=0;runtimeFree=0;classReleases=0;partAlloc=0;cacheBindings=0;cacheAlloc=0;
 }
 boolean isImport(long pc,long slot){return pc!=0&&pc==u32(slot);}
 void runCall(long target,long...args)throws Exception {
  log("HARNESS_ENTRY",target,"argc="+args.length);
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  ArrayDeque<String> hist=new ArrayDeque<>();boolean done=false;
  for(int n=0;n<LIMIT;n++){
   long pc=reg("EIP"),rsp=reg("ESP");steps=n;
   if(pc==SENT){log("HARNESS_RETURN",target,"eax="+hx(reg("EAX")));done=true;break;}
   if(pc==0x00461b94L)log("PENDING_VISIT",pc,"pendingNode="+hx(reg("EBP"))+";classNode="+hx(u32(reg("EBP")+8)));
   if(pc==0x00461bffL)log("INIT_DISPATCH",pc,"target="+hx(reg("EAX"))+";owner="+hx(u32(rsp))+";slot="+hx(reg("ESI")+0x4f76e8L));
   if(pc==0x00461c01L)log("INIT_RETURN",pc,"owner="+hx(reg("EBX"))+";targetSlot="+hx(reg("ESI")+0x4f76e8L));
   if(pc==0x00463120L||pc==0x0046f2b0L||pc==0x0045f810L)log("INITIALIZER_ENTER",pc,"owner="+hx(u32(rsp+4))+";return="+hx(u32(rsp)));
   if((target==0x00461b80L||mode.contains("peripheral")||mode.contains("directinit")) && pc!=0x00461b80L && currentProgram.getFunctionManager().getFunctionAt(a(pc))!=null)log("INIT_CALLEE",pc,"arg0="+hx(u32(rsp+4))+";return="+hx(u32(rsp)));
   if(isImport(pc,0x004bc110L)){log("SERVICE_HeapCreate",pc,"options="+hx(u32(rsp+4))+";initial="+u32(rsp+8)+";maximum="+u32(rsp+12));retStd(0x12360000L,3);continue;}
   if(pc==0x0049d409L && !mode.contains("rawx87")){
    java.math.BigInteger ext=e.readRegister("ST0");if((ext.shiftRight(64).intValue()&32767)>=16446)throw new Exception("FSINCOS bridge range requires finite abs(x)<2^63");for(int k=0;k<10;k++)hostIn.writeByte(ext.shiftRight(8*k).intValue()&255);int cw=e.readRegister("FPUControlWord").intValue();if((cw&63)!=63)throw new Exception("FSINCOS bridge requires masked exceptions");hostIn.writeByte(cw&255);hostIn.writeByte(((cw>>>8)&63)|64);hostIn.flush();
    java.math.BigInteger co=java.math.BigInteger.ZERO,si=java.math.BigInteger.ZERO;for(int k=0;k<10;k++)co=co.or(java.math.BigInteger.valueOf(hostOut.readUnsignedByte()).shiftLeft(8*k));for(int k=0;k<10;k++)si=si.or(java.math.BigInteger.valueOf(hostOut.readUnsignedByte()).shiftLeft(8*k));int sw=hostOut.readUnsignedByte()|(hostOut.readUnsignedByte()<<8);
    for(int k=7;k>=2;k--)e.writeRegister("ST"+k,e.readRegister("ST"+(k-1)));e.writeRegister("ST1",si);e.writeRegister("ST0",co);e.writeRegister("C2",0);e.writeRegister("C1",(sw>>>9)&1);e.writeRegister("FPUInstructionPointer",pc);e.writeRegister("EIP",pc+2);
    log("HARDWARE_FSINCOS",pc,"input="+ext.toString(16)+";cw="+Integer.toHexString(cw)+";cos="+co.toString(16)+";sin="+si.toString(16)+";sw="+Integer.toHexString(sw));continue;
   }
   if((pc==0x49d40bL||pc==0x49d40eL) && !mode.contains("rawx87")){
    java.math.BigInteger ext=e.readRegister("ST0");for(int k=0;k<10;k++)hostIn.writeByte(ext.shiftRight(8*k).intValue()&255);int cw=e.readRegister("FPUControlWord").intValue();hostIn.writeByte(cw&255);hostIn.writeByte(((cw>>>8)&31)|32);hostIn.flush();long value=Integer.reverseBytes(hostOut.readInt())&0xffffffffL;long dest=reg("EBP")-(pc==0x49d40bL?4:8);w32(dest,value);pop87();e.writeRegister("EIP",pc+3);log("HARDWARE_FSTP32",pc,"input="+ext.toString(16)+";cw="+Integer.toHexString(cw)+";result="+hx(value));continue;
   }
   if(pc==0x46ea2fL)log("LOCALIZATION_PREREQUISITE",pc,"dataIAT=004BC2A8;unresolvedTarget="+hx(u32(0x4bc2a8L))+";key="+cstr(0x4f8a30L,80)+";functionIAT=004BC2B4;functionTarget="+hx(u32(0x4bc2b4L)));
   if(pc==0x00463960L)log("POST_GATE",pc,"eax="+reg("EAX")+";status="+hx(u32(OBJ+0x10)));
   if(pc==0x00461ca1L||pc==0x00461d71L)log("LOOKUP_RETURN",pc,"owner="+hx(reg("EAX")));
   if(pc==0x00461c91L||pc==0x00461d61L)log("COLLECTION_VISIT",pc,"node="+hx(reg("ESI"))+";next="+hx(u32(reg("ESI")))+";owner="+hx(u32(reg("ESI")+8)));
   if(pc==0x00461d2cL||pc==0x00461dfcL){long slot=0x004f76ecL+reg("EDX")*4+(pc==0x00461dfcL?4:0);log("DESCRIPTOR_FETCH",pc,"slot="+hx(slot)+";target="+hx(u32(slot))+";owner="+hx(reg("EDI"))+";class="+u32(reg("EDI")+0x6c));}
   if(pc==0x00461d38L||pc==0x00461e08L)log("INDIRECT_CALL",pc,"target="+hx(reg("EAX"))+";owner="+hx(u32(rsp))+";return="+hx(pc+2));
   if(pc==0x00463800L||pc==0x00463950L)log("CLASS1_ENTER",pc,"owner="+hx(u32(rsp+4))+";return="+hx(u32(rsp))+";runtime="+hx(u32(OBJ+0x70)));
   if(pc==0x00461d3aL||pc==0x00461e0aL)log("INDIRECT_RETURN",pc,"owner="+hx(reg("EDI")));
   if(pc==0x0049c356L)log("ORIGINAL_LIST_RETURN",pc,"node="+hx(reg("EAX"))+";next="+hx(u32(reg("EAX")))+";prev="+hx(u32(reg("EAX")+4))+";owner="+hx(u32(reg("EAX")+8)));


   if(mode.contains("legacy") && (pc==0x0046f420L||pc==0x0045faf0L)){log("SERVICE_PERIPHERAL_POST",pc,"owner="+hx(u32(rsp+4))+";return="+hx(u32(rsp)));ret(0);continue;}
   if(pc==0x0049e1a1L)log("FILTER_INIT_RETURN",pc,"state="+hx(reg("EAX"))+";a="+rd64(reg("EAX"))+";b="+rd64(reg("EAX")+8)+";gain="+rd64(reg("EAX")+16)+";previous0="+rd64(reg("EAX")+24)+";previous1="+rd64(reg("EAX")+32));
   if(pc==0x0049e0f0L)log("FILTER_INIT_ENTER",pc,"state="+hx(u32(rsp+4))+";a="+Float.intBitsToFloat((int)u32(rsp+8))+";b="+Float.intBitsToFloat((int)u32(rsp+12)));
   if(pc==0x0049e13bL && mode.contains("filter")){java.math.BigInteger ext=e.readRegister("ST0");for(int k=0;k<10;k++)hostIn.writeByte(ext.shiftRight(8*k).intValue()&255);int cw=e.readRegister("FPUControlWord").intValue();hostIn.writeByte(cw&255);hostIn.writeByte(((cw>>>8)&127)|128);hostIn.flush();java.math.BigInteger result=java.math.BigInteger.ZERO;for(int k=0;k<10;k++)result=result.or(java.math.BigInteger.valueOf(hostOut.readUnsignedByte()).shiftLeft(8*k));e.writeRegister("ST0",result);e.writeRegister("FPUInstructionPointer",pc);e.writeRegister("EIP",pc+2);e.writeRegister("C2",0);log("HARDWARE_FCOS",pc,"input="+ext.toString(16)+";cw="+Integer.toHexString(cw)+";result="+result.toString(16));continue;}
   if(mode.contains("host") && (pc==0x004935eeL||pc==0x00493608L)){
    java.math.BigInteger ext=e.readRegister("ST0");for(int k=0;k<10;k++)hostIn.writeByte(ext.shiftRight(8*k).intValue()&255);int cw=e.readRegister("FPUControlWord").intValue();hostIn.writeByte(cw&255);hostIn.writeByte((cw>>>8)&255);hostIn.flush();long value=Long.reverseBytes(hostOut.readLong());long ptr=reg("EBP")-(pc==0x004935eeL?0x14:0xc);w32(ptr,value);w32(ptr+4,value>>>32);pop87();e.writeRegister("FPUInstructionPointer",pc);e.writeRegister("EIP",pc+3);log("HARDWARE_FISTP",pc,"st0="+ext.toString(16)+";cw="+Integer.toHexString(cw)+";result="+value);continue;
   }
   if(pc==0x00440740L){probeReturn=u32(rsp);contactPtr=u32(rsp+8);log("GROUND_PROBE_ENTER",pc,"dt="+Float.intBitsToFloat((int)u32(rsp+12)));}
   if(probeReturn!=0 && pc==probeReturn){if(reg("EAX")!=0)positiveProbe++;log("GROUND_PROBE_RETURN",pc,"eax="+reg("EAX")+";contact="+vec(contactPtr,27));probeReturn=0;}
   if(isImport(pc,0x004bc290L)){long base=u32(rsp+4);String source=cstr(base,65536),set=cstr(u32(rsp+8),64);int found=-1;for(int k=0;k<source.length();k++)if(set.indexOf(source.charAt(k))>=0){found=k;break;}ret(found<0?0:base+found);continue;}
   if(isImport(pc,0x004bc1d0L)){String text=cstr(u32(rsp+4),200),fmt=cstr(u32(rsp+8),200);String[] values=text.trim().split("\\s+");java.util.regex.Matcher matches=java.util.regex.Pattern.compile("%(?:[0-9]+)?([dfs])").matcher(fmt);int count=0;while(matches.find()&&count<values.length){long dest=u32(rsp+12+4*count);String kind=matches.group(1);if(kind.equals("d"))w32(dest,Integer.parseInt(values[count]));else if(kind.equals("f"))w32(dest,Float.floatToRawIntBits(Float.parseFloat(values[count]))&0xffffffffL);else e.writeMemory(a(dest),(values[count]+"\0").getBytes());count++;}log("SERVICE_sscanf",pc,"conversions="+count);ret(count);continue;}
   if(isImport(pc,0x004bc20cL)){log("SERVICE_rand",pc,"deterministic=17");ret(17);continue;}
   if(isImport(pc,0x004bc234L)){String fmt=cstr(u32(rsp+8),120);java.util.regex.Matcher fm=java.util.regex.Pattern.compile("%([0-9]*)([sdiu])").matcher(fmt);StringBuffer formatted=new StringBuffer();int ordinal=0;while(fm.find()){long value=u32(rsp+12+4*ordinal++);String field=fm.group(2).equals("s")?cstr(value,256):Long.toString(fm.group(2).equals("u")?value:(int)value);int width=fm.group(1).isEmpty()?0:Integer.parseInt(fm.group(1));while(field.length()<width)field=(fm.group(1).startsWith("0")?"0":" ")+field;fm.appendReplacement(formatted,java.util.regex.Matcher.quoteReplacement(field));}fm.appendTail(formatted);String out=formatted.toString();e.writeMemory(a(u32(rsp+4)),(out+"\0").getBytes());log("SERVICE_sprintf",pc,"format="+fmt+";result="+out);ret(out.length());continue;}
   if(isImport(pc,0x004bc16cL)){log("SERVICE_stat",pc,cstr(u32(rsp+4),120));mem(u32(rsp+8),40);ret(0);continue;}
   if(isImport(pc,0x004bc0d8L)){log("SERVICE_CreateFileA",pc,cstr(u32(rsp+4),120));retStd(0x11110001L,7);continue;}
   if(isImport(pc,0x004bc0bcL)){log("SERVICE_CreateFileMappingA",pc,"authentic_TER_readonly");retStd(0x11110002L,6);continue;}
   if(isImport(pc,0x004bc0c0L)){log("SERVICE_MapViewOfFile",pc,"base="+hx(TER)+";bytes="+terrainBytes.length);retStd(TER,5);continue;}
   if(pc==0x70001000L){log("SERVICE_palette_callback",pc,"omitted");ret(0);continue;}
   if(target==0x004b8a10L && (pc==0x00423320L||pc==0x00477b00L||pc==0x00478b30L||pc==0x00479780L||pc==0x004b8500L||pc==0x004908f0L||pc==0x00401540L)){log("SERVICE_WRLD_NONPHYSICS",pc,"omitted");ret(0);continue;}
   if(pc==0x0046dc10L){tireReturn=u32(rsp);tireRuntime=u32(u32(rsp+4)+0x70);log("TIRE_CONTACT_UPDATE",pc,"tire="+hx(u32(rsp+4))+";arg1="+hx(u32(rsp+8))+";height="+Float.intBitsToFloat((int)u32(rsp+12))+";dt="+Float.intBitsToFloat((int)u32(rsp+16))+";last="+Float.intBitsToFloat((int)u32(rsp+20)));}
   if(tireReturn!=0 && pc==tireReturn){log("TIRE_CONTACT_RETURN",pc,"runtime="+hx(tireRuntime)+";compression="+Float.intBitsToFloat((int)u32(tireRuntime+0x24))+";height="+Float.intBitsToFloat((int)u32(tireRuntime+0x2c))+";mode="+u32(tireRuntime+0x40)+";rangeMin="+Float.intBitsToFloat((int)u32(tireRuntime+0x3c))+";rangeMax="+Float.intBitsToFloat((int)u32(tireRuntime+0x38)));tireReturn=0;}
   if(pc==0x00437230L)log("SUSPENSION_VISUAL_UPDATE",pc,"root="+hx(u32(rsp+4))+";mode="+hx(u32(rsp+12)));
   if(pc==0x004931c0L)log("TERRAIN_NORMAL_ENTER",pc,"out="+hx(u32(rsp+4))+";x="+rd64(rsp+8)+";z="+rd64(rsp+16));
   if(pc==0x00493550L){groundCalls++;heightReturn=u32(rsp);heightX=rd64(rsp+4);heightZ=rd64(rsp+12);log("HEIGHT_ENTER",pc,"x="+heightX+";z="+heightZ);}
   if(heightReturn!=0 && pc==heightReturn){log("HEIGHT_RETURN",pc,"x="+heightX+";z="+heightZ+";height="+x87());heightReturn=0;}
   if(pc==0x0043a5d0L){solverCalls++;solverReturn=u32(rsp);solverFlagsPtr=u32(rsp+8);log("SOLVER_ENTER",pc,"dt="+Float.intBitsToFloat((int)u32(rsp+32)));}
   if(solverReturn!=0 && pc==solverReturn){log("SOLVER_RETURN",pc,"outputFlags="+hx(u32(solverFlagsPtr))+";runtimeFlags="+hx(u32(u32(OBJ+0x70)+0x454)));solverReturn=0;}
   if(pc==0x004932e1L||pc==0x00493335L||pc==0x00493387L||pc==0x004933eeL||pc==0x00493444L||pc==0x0049349bL||pc==0x0049287bL){long ptr=pc==0x004932e1L?reg("ECX")+reg("ESI")*2:pc==0x00493335L?reg("EAX")+reg("ESI")*2:pc==0x00493387L?reg("EDX")+reg("ECX")*2:pc==0x004933eeL?reg("EDX")+reg("ESI")*2:pc==0x00493444L?reg("ECX")+reg("ESI")*2:pc==0x0049349bL?reg("EAX")+reg("EDX")*2:reg("EAX")+reg("ECX")*2;if(ptr<TER||ptr+2>TER+terrainBytes.length)throw new Exception("NONAUTHENTIC_TERRAIN_READ "+hx(ptr));log("TERRAIN_NATIVE_READ",pc,"address="+hx(ptr)+";offset="+hx(ptr-TER)+";word="+hx(u32(ptr)&65535));}
   if(pc==0x00493652L||pc==0x004936a5L||pc==0x004936f8L||pc==0x0049373dL){long ptr=pc==0x00493652L?reg("EDX")+reg("EDI")*2:pc==0x004936a5L?reg("ECX")+reg("EAX")*2:pc==0x004936f8L?reg("ECX")+reg("EDX")*2:reg("EAX")+reg("ECX")*2;terrainReads++;if(ptr<TER||ptr+2>TER+terrainBytes.length)throw new Exception("NONAUTHENTIC_TERRAIN_READ "+hx(ptr));log("TERRAIN_NATIVE_READ",pc,"address="+hx(ptr)+";offset="+hx(ptr-TER)+";word="+hx(u32(ptr)&65535));}
   if(isImport(pc,0x004bc100L)){log("CLOCK_SERVICE",pc,"tick="+tick);ret(tick);continue;}
   if((target==0x00463800L||target==0x00461c80L) && (pc==0x0049cc20L||pc==0x0049cca0L||pc==0x00440740L||pc==0x0043a5d0L))log("FIXEDSTEP_NATIVE",pc,"argDtRaw="+hx(u32(rsp+(pc==0x00440740L?12:pc==0x0043a5d0L?32:8)))+";timer="+vec(u32(OBJ+0x70)+0x444,3));
   if((target==0x00463800L||target==0x00461c80L) && (pc==0x0043a3c0L||pc==0x0043bdf0L||pc==0x00438fd0L||pc==0x00465370L))log("PHYSICS_NATIVE_CALLEE",pc,"dtRaw="+hx(u32(rsp+(pc==0x0043bdf0L?28:8)))+";return="+hx(u32(rsp))+";rootDir="+vec(OBJ+0x30L,3));
   if(mode.contains("legacy") && pc==0x0049d400L){
      long input=u32(rsp+4L);float radians=Float.intBitsToFloat((int)input);
      long si=Float.floatToRawIntBits((float)Math.sin(radians))&0xffffffffL;
      long co=Float.floatToRawIntBits((float)Math.cos(radians))&0xffffffffL;
      log("PHYSICS_TRIG_BOUNDARY",pc,"input="+hx(input)+";sine="+hx(si)+";cosine="+hx(co));
      ret(si);e.writeRegister("EDX",co);continue;
   }
   if(pc==0x004ba090L){
      java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);if(ext.testBit(79))v=-v;int val=(int)v;
      log("PHYSICS_X87_INTEGER_BOUNDARY",pc,"double="+v+";result="+val);
      if(mode.contains("pop"))for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1))); ret(val&0xffffffffL);continue;
   }

   if(false){log("NATIVE_vehicle_init_prefix_complete",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0ref="+u32(SECOND+0xc)+";mount1ref="+u32(FIRST+0xc));done=true;break;}
   if(hist.size()>18)hist.removeFirst();hist.addLast(hx(pc));
   if(isImport(pc,0x4bc238)){String src=cstr(u32(rsp+4),80);long drive=u32(rsp+8),dir=u32(rsp+12),fname=u32(rsp+16),ext=u32(rsp+20);String base=src.replace("\\","/");base=base.substring(base.lastIndexOf("/")+1);int dot=base.lastIndexOf(".");String stem=dot>=0?base.substring(0,dot):base;String suffix=dot>=0?base.substring(dot):"";e.writeMemory(a(drive),new byte[4]);e.writeMemory(a(dir),new byte[256]);e.writeMemory(a(fname),(stem+"\0").getBytes());e.writeMemory(a(ext),(suffix+"\0").getBytes());log("STUB_splitpath",pc,src+";stem="+stem+";ext="+suffix);ret(0);continue;}
   if(isImport(pc,0x4bc28c)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] b=e.readMemory(a(src),len);if(b==null)throw new Exception("strncpy src");e.writeMemory(a(dst),b);ret(dst);continue;}
   if(isImport(pc,0x4bc260)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);int cnt=(int)u32(rsp+12);int result=x.substring(0,Math.min(cnt,x.length())).equalsIgnoreCase(y.substring(0,Math.min(cnt,y.length())))?0:1;log("STUB_strnicmp",pc,x+"|"+y+"|"+cnt+"|"+result);ret(result);continue;}
   if(pc==u32(0x4bc1f0L)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] copy=e.readMemory(a(src),len);if(copy==null||copy.length!=len)throw new Exception("CRT memcpy src="+hx(src)+" len="+len);e.writeMemory(a(dst),copy);ret(dst);continue;}
   if(pc==u32(0x4bc1e0L)){int ch=(int)u32(rsp+4)&255;ret((ch>=97&&ch<=122)?ch-32:ch);continue;}
   if(pc==0x00477c20L){log("STUB_nonessential_vehicle_light_registration",pc,"fixture registration omitted; body hierarchy continues");ret(1);continue;}
   if(pc==0x004469a0L){nextGeoReturnPc=u32(rsp);nextGeoName=cstr(u32(rsp+4),32);log("NATIVE_GEO_LOAD_ENTER",pc,"key="+nextGeoName);}
   if(nextGeoReturnPc!=0 && pc==nextGeoReturnPc){realGeoReturns++;log("NATIVE_GEO_LOAD_RETURN",pc,"key="+nextGeoName+";handle="+hx(reg("EAX")));nextGeoReturnPc=0;}
   if(pc==0x00446c90L){realGeoConstructions++;long bp=u32(rsp+4);log("NATIVE_GEO_CONSTRUCTOR",pc,"ptr="+hx(bp)+";magic="+hx(u32(bp))+";vertices="+u32(bp+0x18L)+";faces="+u32(bp+0x1cL));}
   if(isImport(pc,0x4bc26cL)){long ptr=u32(rsp+4);int ch=(int)u32(rsp+8)&255;String name=cstr(ptr,256);int where=name.indexOf(ch);ret(where<0?0:ptr+where);continue;}
   if(isImport(pc,0x4bc0e8L)){retStd(0x2000L,3);continue;}
   if(pc==0x004796a0L||pc==0x00470340L||pc==0x0044a0b0L){log("STUB_palette_or_render_service",pc,"pc="+hx(pc));ret(0);continue;}
   if(isImport(pc,0x4bc254)){long ptr=u32(rsp+4);String raw=cstr(ptr,256);e.writeMemory(a(ptr),(raw.toLowerCase(Locale.ROOT)+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));log("STUB_strlwr",pc,raw);ret(ptr);continue;}
   if(isImport(pc,0x4bc210)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);ret(x.equalsIgnoreCase(y)?0:1);continue;}
   if(pc==0x438a90L){log("STUB_nonownership_vehicle_target_context",pc,"target="+hx(u32(rsp+4)));ret(0);continue;}
   if(pc==0x00458bf0L){log("NATIVE_FLAG_PREDICATE",pc,"obj_status="+hx(u32(OBJ+0x10)));}
   if(pc==0x0046ffc0L){n_open++;String name=cstr(u32(rsp+4),64).toLowerCase(Locale.ROOT);Long pos=resourcePtrs.get(name);if(pos==null)n_openfail++;log("STUB_open_resource",pc,name+";return="+(pos==null?"NULL":hx(pos)));ret(pos==null?0:pos);continue;}
   if(pc==0x0046fee0L){String name=cstr(u32(rsp+4),64).toLowerCase(Locale.ROOT);byte[] data=resourceBytes.get(name);log("STUB_get_resource_size",pc,name+";"+(data==null?0:data.length));ret(data==null?0:data.length);continue;}
   if(pc==0x0046fd40L){log("STUB_release_resource_ref",pc,cstr(u32(rsp+4),64));ret(0);continue;}
   if(pc==0x4b47c0L){builderCount++;log("NATIVE_child_builder",pc,"ordinal="+builderCount);}
   if(pc==0x4ae000L){long rec=u32(rsp+4);long klass=u32(rec+8);if(klass==0x28)log("NATIVE_VLOC28_ENTER",pc,"record="+hx(rec)+";flags="+hx(u32(OBJ+0x10))+";rt398="+hx(u32(u32(OBJ+0x70)+0x398)));}
   if(pc==0x4ae2a2L)log("NATIVE_VLOC28_STORE",pc,"value="+hx(reg("EAX"))+";root="+hx(OBJ));
   if(pc==0x4ae2a8L)log("VLOC28_POST_STORE",pc,"runtime398="+hx(u32(u32(OBJ+0x70)+0x398)));
   if(pc==0x46d760L){ctorCount++;log("NATIVE_class30_constructor",pc,"ordinal="+ctorCount);}
   if(isImport(pc,0x4bc108L)){
     long count=u32(rsp+12),out;if(count==0xb0){if(constructingRoot){out=OBJ;log("STUB_ROOT_HEAP_ALLOC",pc,"size="+count+";ptr="+hx(out));}else{nodeAlloc++;out=0x27000000L+(nodeAlloc-1)*0x200L;}}else if(count==0x88){runtimeAlloc++;out=0x2a000000L+(runtimeAlloc-1)*0x200L;}else if(count==0x3c || count==0x74){out=0x28000000L+0x200L*(cacheAlloc++);}else {out=genericHeapCursor;genericHeapCursor=(genericHeapCursor+count+31L)&~15L;if(genericHeapCursor>0x36800000L)throw new Exception("out of emulated generic heap "+count);extraAlloc++;}
     log("STUB_HeapAlloc",pc,"size="+count+";result="+hx(out));retStd(out,3);continue;
   }
   if(isImport(pc,0x4bc104L)){
     long ptr=u32(rsp+12);if(ptr==FIRST || ptr==SECOND || ptr==OBJ || (ptr>=0x27000000L && ptr<0x27020000L))nodeFree++;else runtimeFree++;
     log("STUB_HeapFree",pc,"ptr="+hx(ptr));retStd(1,3);continue;
   }
   if(pc==0x49e0f0L && !mode.contains("filter")){log("STUB_x87_cosine_helper",pc,"FCOS not supported by Ghidra emulator");ret(0);continue;}
   if(pc==0x461b20L){classReleases++;log("NATIVE_class_destructor_dispatch",pc,"class="+u32(rsp+4)+";runtime="+hx(u32(rsp+8)));}
   if(pc==0x4639a0L)log("NATIVE_vehicle_runtime_destructor",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0="+hx(u32(RUNTIME+0x3a8))+";mount1="+hx(u32(RUNTIME+0x3ac)));
   if(pc==0x46da60L)log("NATIVE_weapon_runtime_destructor",pc,"runtime="+hx(u32(rsp+4)));
   if(pc==0x461a20L){if(u32(rsp+4)==0){log("STUB_NULL_component_visual_unlink",pc,"ptr=00000000");ret(0);continue;}else{log("NATIVE_class_registry_unlink",pc,"ptr="+hx(u32(rsp+4)));}}
   if(pc==0x45f3d0L){log("NATIVE_runtime_allocator_free",pc,"ptr="+hx(u32(rsp+4)));}
   if(pc==0x449e60L||pc==0x477e10L){log("STUB_render_release",pc,"object="+hx(u32(rsp+4)));ret(0);continue;}

   if(pc==0x49c320L){listCount++;log("ORIGINAL_LIST_INSERT",pc,"next="+hx(u32(rsp+4))+";prev="+hx(u32(rsp+8))+";value="+hx(u32(rsp+12)));}
   if(pc==0x4b75a0L && u32(rsp+12)==7 && u32(rsp+16)==4){bodyParts=(int)u32(rsp+20);bodyNodeStart=nodeAlloc;bodyBankZero=u32(u32(rsp+4));log("BODY_GEOMETRY_SOURCE",pc,"parts="+bodyParts+";nodeStart="+bodyNodeStart+";bankZero="+hx(bodyBankZero));}
   if(pc==0x4b75a0L){geoCount++;log("NATIVE_GEOCACHE_ENTER",pc,"ordinal="+geoCount+";root="+hx(u32(rsp+8))+";levels="+u32(rsp+12)+";variants="+u32(rsp+16)+";partCount="+u32(rsp+20));}
   if(pc==0x4b8230L){log("NATIVE_TRANSFORM_CHILD",pc,"parent="+hx(u32(rsp+4))+";part="+hx(u32(rsp+8))+";class="+u32(u32(rsp+8)+0x5c));}
   if(pc==0x4464e0L){log("NATIVE_GEOMETRY_UNLINK",pc,"object="+hx(u32(rsp+4)));}
   if(pc==0x461970L){long child=u32(rsp+4);log("NATIVE_CLASS_REGISTRATION",pc,"child="+hx(child)+";class="+u32(rsp+8)+";parentLink="+hx(u32(child+0x68))+";ref="+u32(child+0xc));}
   if(pc==0x4461e0L){cacheBindings++;log("NATIVE_GEOMETRY_BINDING_CACHE",pc,"child="+hx(u32(rsp+4))+";resource="+cstr(u32(rsp+8),24)+";level="+u32(rsp+12)+";variant="+u32(rsp+16));}
   if(pc==0x4ae870L)log("NATIVE_WDFC",pc,"ctx="+hx(u32(rsp+8)));
   if(pc==0x4ae980L)log("NATIVE_WGEO",pc,"ctx="+hx(u32(rsp+8)));
   if(pc==VCFC){n_vcfc++;log("NATIVE_VCFC_BEGIN",pc,"data="+hx(u32(rsp+4))+";context="+hx(u32(rsp+8)));}
   if(pc==SPEC){n_spec++;log("NATIVE_SPEC",pc,"data="+hx(u32(rsp+4)));}
   if(pc==WEPN){n_wepn++;long res=(n_wepn==failWeaponChunk)?0:1;log("STUB_WEPN",pc,"ordinal="+n_wepn+";data="+hx(u32(rsp+4))+";result="+res);ret(res);continue;}
   if(pc==PARSE){n_nested++;log("NATIVE_BWD2_ENTER",pc,"ordinal="+n_nested+";resource="+cstr(u32(rsp+4),72)+";descriptors="+u32(rsp+12));}
   if(pc==WDFFN){log("NATIVE_WDF_WRAPPER",pc,"requested="+cstr(u32(rsp+4),50));}
   if(pc==0x00449680L){materialBinds++;firstMaterialReturnPc=u32(rsp);firstMaterialOwner=u32(rsp+4);firstMaterialKey=cstr(u32(rsp+8),40);firstMaterialResource=cstr(u32(rsp+12),40);log("NATIVE_TEXTURE_MATERIAL_BIND_ENTER",pc,"ordinal="+materialBinds+";object="+hx(firstMaterialOwner)+";key="+firstMaterialKey+";resource="+firstMaterialResource);}
   if(firstMaterialReturnPc!=0 && pc==firstMaterialReturnPc){
      long hash=0;for(int i=0;i<firstMaterialKey.length();i++)hash=((hash*2)^ (firstMaterialKey.charAt(i)&0xdf)) &0xffffffffL;
      hash=((((hash^firstMaterialOwner)*0x6cdL)+0xaabL)&0xffffffffL)%0x7edL;
      long ptr=u32(0x00533fa0L+hash*4),tmt=ptr==0?0:u32(ptr+0x30L);
      long frames=tmt==0?0:u32(tmt+0x2cL);
      log("NATIVE_TEXTURE_MATERIAL_BIND_RESULT",pc,"eax="+reg("EAX")+";owner="+hx(firstMaterialOwner)+";key="+firstMaterialKey+";slot="+hx(ptr)+";slotOwner="+(ptr==0?"NULL":hx(u32(ptr)))+";slotKey="+(ptr==0?"NULL":cstr(ptr+0x14L,32))+";tmt="+hx(tmt)+";tmtName="+(tmt==0?"NULL":cstr(tmt,16))+";tmtRef="+(tmt==0?"NULL":u32(tmt+0x10L))+";frameCount="+(tmt==0?"NULL":u32(tmt+0x1cL))+";firstFrame="+(frames==0?"NULL":cstr(frames,16)));
      if(reg("EAX")!=1 && (target==0x00461b80L||mode.contains("peripheral")||mode.contains("directinit"))){log("OPTIONAL_BIND_FAILED",pc,firstMaterialResource);firstMaterialReturnPc=0;}else{
      if(reg("EAX")!=1||ptr==0||tmt==0||u32(ptr)!=firstMaterialOwner||!cstr(tmt,16).equalsIgnoreCase(firstMaterialResource))throw new Exception("native TMT material binding invalid: "+firstMaterialKey+" -> "+firstMaterialResource+" / "+hx(ptr)+" / "+hx(tmt));
      byte[] sourceTmt=resourceBytes.get(firstMaterialResource.toLowerCase(Locale.ROOT));
      if(sourceTmt==null||sourceTmt.length<0x48)throw new Exception("missing source TMT "+firstMaterialResource);
      String expectedFrame=new String(sourceTmt,0x40,8,java.nio.charset.StandardCharsets.ISO_8859_1).toLowerCase(Locale.ROOT);
      if(!cstr(frames,16).toLowerCase(Locale.ROOT).startsWith(expectedFrame))throw new Exception("native TMT frame mismatch key="+firstMaterialKey+" expected="+expectedFrame);
      nativeMaterialSuccess++;}
      firstMaterialReturnPc=0;
   }
   if(pc==0x004b0190L||pc==0x004b0150L||pc==0x004b0290L){log("STUB_optional_material_side_effect",pc,hx(u32(rsp+4)));ret(1);continue;}
   if(pc==0x00467280L){log("STUB_special_equipment_logger",pc,hx(u32(rsp+4)));ret(1);continue;}
   if(pc==0x0042d5d0L){caughtReporter++;log("NATIVE_reporter_RET",pc,"return="+hx(u32(rsp))+";args="+vec(rsp+4,4));}
   if(pc==0x004b4048L){log("CALLBACK_RESULT",pc,"eax="+reg("EAX"));}
   if(pc==EXIT){log("NATIVE_EXIT",pc,hx(u32(rsp+4)));}
   if(!e.step(monitor))throw new Exception(scenario+" error pc="+hx(pc)+" "+e.getLastError()+" history="+hist);
  }
  if(!done)throw new Exception(scenario+" step limit "+hist);
  log("RETURN",target,"eax="+reg("EAX")+";steps="+steps+";builder="+builderCount+";ctor="+ctorCount+";geo="+geoCount+";allocNodes="+nodeAlloc+";allocRuntime="+runtimeAlloc+";nodeFree="+nodeFree+";runtimeFree="+runtimeFree+";parentFirst="+hx(u32(OBJ+0x64))+";runtimeMount0="+hx(u32(RUNTIME+0x3a8))+";runtimeMount1="+hx(u32(RUNTIME+0x3ac))+";firstClass="+u32(FIRST+0x6c)+";secondClass="+u32(SECOND+0x6c)+";firstRef="+u32(FIRST+0xc)+";secondRef="+u32(SECOND+0xc));
 }
 void caseRun(String test,byte[] data,String file,int nestedFail,int weaponFail,boolean openFail,boolean persist)throws Exception {
  scenario=test;reset(data,file);failNested=nestedFail;failWeapon=weaponFail;failOpen=openFail;
  try {
   runCall(LOADER,0,CTX,NAME);
   if(persist){failOpen=true;materialBinds=0;bodyParts=0;bodyNodeStart=0;bodyBankZero=0;genericHeapCursor=0x36000000L;n_vcfc=0;n_spec=0;n_wepn=0;n_weapon=0;n_nested=0;scenario=test+"_SECOND_MISSING_CALL";runCall(LOADER,0,CTX,NAME);}
  } finally {e.dispose();e=null;}
 }
 void testCombined(byte[] wdfFront,byte[] wdfRear,byte[] wloc,byte[] vg,String label,String rearName)throws Exception{
  scenario=label;wdfName=(label.equals("bus")?"wftck_1a.wdf":"wauto_1a.wdf");reset(wdfFront,wdfName);
  try{
   long mountBytes=0x29018000L,vgeoBytes=0x29000000L;
   e.writeMemory(a(mountBytes),wloc);
   int parts=((vg[0]&255)|((vg[1]&255)<<8)|((vg[2]&255)<<16)|((vg[3]&255)<<24));
   if(vg.length!=4+28*parts*100)throw new Exception("invalid full VGEO body");
   e.writeMemory(a(vgeoBytes),Arrays.copyOfRange(vg,4,vg.length));
   for(int i=0;i<28;i++)w32(WDFCTX+4*i,vgeoBytes+i*parts*100L);
   runCall(0x4ae5a0L,mountBytes,CTX);
   runCall(0x4b75a0L,WDFCTX,OBJ,7,4,parts,0);
   // Validate every complete runtime part, including structurally retained NULL slots.
   for(int j=0;j<parts;j++){
      long rec=vgeoBytes+j*100L,kid=0x27000000L+j*0x200L;
      long klass=u32(rec+0x5c);
      if(u32(kid+0x6c)!=klass)throw new Exception("body class mismatch j="+j);
      if(!Arrays.equals(e.readMemory(a(rec+8),36),e.readMemory(a(kid+0x18),36)))throw new Exception("body rotation mismatch j="+j);
      for(int axis=0;axis<3;axis++){
        float src=Float.intBitsToFloat((int)u32(rec+0x2c+4*axis));
        byte[] d=e.readMemory(a(kid+0x40+axis*8),8);long bits=0;
        for(int k=0;k<8;k++)bits|=(d[k]&255L)<<(8*k);
        if(Double.longBitsToDouble(bits)!=(double)src)throw new Exception("body translation mismatch j="+j+" axis="+axis);
      }
      log("BODY_SLOT_EXACT",0x4b75a0L,"slot="+j+";name="+cstr(rec,8)+";parent_name="+cstr(rec+0x38,8)+";node="+hx(kid)+";class="+klass+";orientation=EXACT;position=EXACT");
   }
   if(nodeAlloc!=parts||cacheBindings!=28*parts)throw new Exception("body creation failed nodes="+nodeAlloc+" cache="+cacheBindings);
   log("BODY_DONE",0x4b75a0L,"nodes="+nodeAlloc+";bindings="+cacheBindings+";rootNewest="+hx(u32(OBJ+0x64)));
   runCall(WDFFN,NAME,CTX,0);
   if(nodeAlloc!=parts+4||ctorCount!=2||cacheBindings!=28*parts+16)throw new Exception("front weapons: nodes="+nodeAlloc+" ctor="+ctorCount+" bindings="+cacheBindings);
   for(int slot=0;slot<2;slot++)validateMount(slot);
   log("FRONT_DONE",WDFFN,"mount0="+hx(u32(RUNTIME+0x3a8))+";mount1="+hx(u32(RUNTIME+0x3ac))+";nodes="+nodeAlloc+";cacheBindings="+cacheBindings);
   bytes=wdfRear;mem(FILE,0x1000);e.writeMemory(a(FILE),wdfRear);wdfName=rearName;e.writeMemory(a(NAME),(wdfName+"\0").getBytes("ISO-8859-1"));
   runCall(WDFFN,NAME,CTX,4);
   if(nodeAlloc!=parts+8||ctorCount!=4||cacheBindings!=28*parts+32)throw new Exception("rear weapons: nodes="+nodeAlloc+" ctor="+ctorCount+" bindings="+cacheBindings);
   for(int slot=4;slot<6;slot++)validateMount(slot);
   if(u32(RUNTIME+0x3b0)!=0||u32(RUNTIME+0x3b4)!=0)throw new Exception("middle mount pair should be empty");
   log("COMBINED_SUCCESS",WDFFN,"body_parts="+parts+";weapon_nodes=4;weapon_geometry_bindings=32;cache_bindings="+cacheBindings+";all_mount_transforms_match=true;class30_ctors="+ctorCount+";retail_WDF_parser=2;native_child_builders="+builderCount);
  }finally{e.dispose();e=null;}
 }
 void validateMount(int slot)throws Exception{
  long kid=u32(RUNTIME+0x3a8L+slot*4);
  if(kid<0x27000000L || kid>=0x27020000L)throw new Exception("wrong mount child pointer slot="+slot+" ptr="+hx(kid));
  if(u32(kid+0x6c)!=30)throw new Exception("wrong weapon class "+u32(kid+0x6c));
  if(!Arrays.equals(e.readMemory(a(RUNTIME+0x168L+slot*56+4),36),e.readMemory(a(kid+0x18),36)))throw new Exception("matrix mismatch at slot "+slot);
  for(int q=0;q<3;q++){
    float src=Float.intBitsToFloat((int)u32(RUNTIME+0x168L+slot*56+40+4*q));
    byte[] d=e.readMemory(a(kid+0x40+q*8),8);long bits=0;
    for(int b=0;b<8;b++)bits|=(d[b]&255L)<<(8*b);
    if(Double.longBitsToDouble(bits)!=(double)src)throw new Exception("position mismatch at slot "+slot+" axis "+q);
  }
  log("VERIFIED_MOUNT",WDFFN,"slot="+slot+";ptr="+hx(kid)+";class=30;transform=EXACT;link68="+hx(u32(kid+0x68)));
 }
 void initializeCameraNative()throws Exception{
  w32(0x005dd2a8L,2);w32(0x00654b8aL,0);
  for(long p=0x005dcec0L;p<0x005dcfc0L;p+=4)w32(p,0);
  w32(0x005dcedcL,0);w32(0x005dcee0L,0);w32(0x005dcee4L,479);w32(0x005dcee8L,639);

  long sp=STACK-0x3000L;w32(sp,SENT);w32(sp+4L,0);e.writeRegister("ESP",sp);e.writeRegister("EIP",0x00405970L);
  for(int n=0;n<200000;n++){
    long pc=reg("EIP");if(pc==SENT){log("CAMERA_PROJECTION_INIT_END",pc,"steps="+n+";p4="+hx(u32(0x4c2734L))+";v44="+hx(u32(0x4c2774L)));return;}
    if(pc==0x0049d400L){long raw=u32(reg("ESP")+4L);float rad=Float.intBitsToFloat((int)raw);
      long sin=Float.floatToRawIntBits((float)Math.sin(rad))&0xffffffffL,cos=Float.floatToRawIntBits((float)Math.cos(rad))&0xffffffffL;
      long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",sin);e.writeRegister("EDX",cos);log("CAMERA_INIT_MATH_BOUNDARY",pc,"radians="+hx(raw));continue;}
    if(pc==0x004ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);if(ext.testBit(79))v=-v;int val=(int)v;long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",val&0xffffffffL);log("CAMERA_INIT_MATH_BOUNDARY",pc,"converted="+val);continue;}
    if(!e.step(monitor))throw new Exception("Camera initialization failure at "+hx(pc)+" "+e.getLastError());
  }throw new Exception("camera init step limit");
 }
 void nativeCameraGuard(String label)throws Exception{
  long active=registeredEntry!=0?registeredEntry:0x26008000L;
  if(registeredEntry==0){mem(active,0x100);w32(active,OBJ);}
  w32(0x004c2908L,active);
  log("ACTIVE_CAMERA_ENTRY",0x004c2908L,"entry="+hx(active)+";owner="+hx(u32(active))+";nativeRegistry="+(registeredEntry!=0));
  // Controlled frame timer integers for the native callback. Not a retail camera clock.
  w32(0x00536770L,1);w32(0x00536778L,1);w32(0x00536780L,1);

  long sp=STACK-0x3000L;w32(sp,SENT);
  e.writeRegister("ESP",sp);e.writeRegister("EIP",0x00406ab0L);
  byte[] cameraBefore=e.readMemory(a(0x004c2730L),0x1b0);
  boolean seen=false,eligible=false;int milestoneCount=0;
  for(int n=0;n<200000;n++){
    long pc=reg("EIP");
    if(pc==0x00406b02L){seen=true;log("CAMERA_RUNTIME_READ",pc,"runtime398="+hx(u32(u32(OBJ+0x70)+0x398L)));}
    if(pc==0x00406b13L){eligible=true;log("CAMERA_POST_GUARD",pc,"child="+hx(u32(u32(OBJ+0x70)+0x398L)));}
    if(pc==0x00406b86L||pc==0x00406c22L||pc==0x00406c90L||pc==0x00406cfeL||pc==0x00406d22L||pc==0x00406d37L||pc==0x00406d40L||pc==0x00406d6aL||pc==0x00406d87L||pc==0x00406db1L||pc==0x00406dc4L||pc==0x00406dd0L||pc==0x00406decL){
      if(++milestoneCount<80)log("CAMERA_POST_GUARD_MILESTONE",pc,"n="+n+";esp="+hx(reg("ESP"))+";eax="+hx(reg("EAX"))+";mode="+hx(u32(0x004c2728L)));
    }
    if(pc==0x00437f90L){trackedMatrixPtr=u32(reg("ESP")+4L);log("ROOT_TO_MATRIX_INPUT",pc,"rootDir="+vec(OBJ+0x30L,3)+";rootBasis="+vec(OBJ+0x18L,9)+";output="+hx(trackedMatrixPtr)+";object="+hx(u32(reg("ESP")+8L)));}
    if(pc==0x00406d45L && trackedMatrixPtr!=0){log("ROOT_TO_MATRIX_RESULT",pc,"invalid="+invalidFloats(trackedMatrixPtr,16)+";matrix="+vec(trackedMatrixPtr,16));trackedMatrixPtr=0;}
    if(pc==0x00493e60L||pc==0x00437f90L||pc==0x00494e20L||pc==0x00458cb0L||pc==0x00472400L||pc==0x00472990L){
      log("CAMERA_NATIVE_CALLEE_ENTER",pc,"n="+n+";return="+hx(u32(reg("ESP"))));
    }
    if(pc==0x00406df4L||pc==SENT){
      byte[] cameraAfter=e.readMemory(a(0x004c2730L),0x1b0);int changed=0;
      for(int j=0;j<cameraAfter.length;j++)if(cameraAfter[j]!=cameraBefore[j])changed++;
      log("CAMERA_CALLBACK_END",pc,"n="+n+";guardReached="+seen+";eligible="+eligible+";cameraViewFlag="+hx(u32(0x005367a4L))+";cameraChangedBytes="+changed+";camera160="+hx(u32(0x004c2890L))+";camera164="+hx(u32(0x004c2894L))+";camera168="+hx(u32(0x004c2898L))+";camera16c="+hx(u32(0x004c289cL))+";camera170="+hx(u32(0x004c28a0L)));
      if(selected && !eligible)throw new Exception("Camera selected did not pass guard");
      if(!selected && eligible)throw new Exception("Camera unselected passed guard");return;
    }
    if(pc==0x0049d400L){
       long raw=u32(reg("ESP")+4L);float radians=Float.intBitsToFloat((int)raw);
       long si=Float.floatToRawIntBits((float)Math.sin(radians))&0xffffffffL, co=Float.floatToRawIntBits((float)Math.cos(radians))&0xffffffffL;
       log("CAMERA_MATH_SUBSTITUTE",pc,"fcos_boundary;input="+hx(raw)+";sin="+hx(si)+";cos="+hx(co));
       long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",si);e.writeRegister("EDX",co);continue;
    }
    if(pc==0x004ba090L){
       java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();
       double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);
       if(ext.testBit(79))v=-v;int val=(int)v;
       log("CAMERA_MATH_SUBSTITUTE",pc,"x87_ftol_boundary;value="+v+";int="+val);
       long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",val&0xffffffffL);if(mode.contains("pop"))for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));continue;
    }
    if(pc==0x004944d0L||pc==0x0049d400L||pc==0x004ba090L){
      log("CAMERA_MATH_BOUNDARY",pc,"unsupported service; not intervening");
    }
    if(!e.step(monitor)){
      log("CAMERA_EXECUTION_STOP",pc,"n="+n+";lastError="+e.getLastError());
      if(!eligible)throw new Exception("Did not reach expected camera guard");
      return;
    }
  }
  log("CAMERA_EXECUTION_LIMIT",reg("EIP"),"steps=200000");
 }
 void createNativeRoot()throws Exception {
    constructingRoot=true;
    try{runCall(0x0045ebd0L,0);}finally{constructingRoot=false;}
    if(reg("EAX")!=OBJ)throw new Exception("Native root returned wrong pointer "+hx(reg("EAX")));
    // Bind the vehicle-class staging context only *after* the original node ctor initialized its 16-word basis.
    w32(OBJ+0x6cL,1);w32(OBJ+0x70L,RUNTIME);w32(OBJ+0xcL,1);
    log("NATIVE_ROOT_CTOR",0x0045ebd0L,"matrix="+vec(OBJ+0x18L,16)+";dir="+vec(OBJ+0x30L,3));
 }
 void runNativeSpawnStatus()throws Exception{
   // Exact original retail 004513C0 creation-policy basic blocks; stop at real 004AD6F0 call boundary.
   e.writeRegister("EBX",OBJ);e.writeRegister("EBP",selected?1:0);e.writeRegister("ESP",STACK);e.writeRegister("EIP",0x451452L);
   boolean formatting=false;boolean arrived=false;
   for(int n=0;n<300;n++){
    long pc=reg("EIP");
    if(pc==0x45148bL){arrived=true;break;}
    if(pc==0x4ad640L){formatting=true;ret(0);continue;}
    if(!e.step(monitor))throw new Exception("Native spawn status instruction error "+hx(pc)+" "+e.getLastError());
   }
   if(!arrived||!formatting)throw new Exception("Spawn block did not reach original VCF call");
   long expected=selected?0x10010:0x20000,got=u32(OBJ+0x10L);
   if(got!=expected)throw new Exception("Original spawn status mismatch "+hx(got)+" expected "+hx(expected));
   log("NATIVE_SPAWN_STATUS",0x45148bL,"status="+hx(got)+";selected="+selected+";originalVCFCallReached=true;formattingBoundary=true");
 }
 void testVcfAll(String fixtureDir,String vcfName,String label)throws Exception{
   scenario=label;
   resourceBytes.clear();resourcePtrs.clear();
   java.nio.file.DirectoryStream<Path> ds=Files.newDirectoryStream(Paths.get(fixtureDir));
   try{java.util.List<Path> ordered=new java.util.ArrayList<>();for(Path p:ds){if(Files.isRegularFile(p)&&!p.getFileName().toString().endsWith(".json"))ordered.add(p);}ordered.sort(java.util.Comparator.comparing(p->p.getFileName().toString()));for(Path p:ordered){
     String key=p.getFileName().toString().toLowerCase(Locale.ROOT);byte[] dat=Files.readAllBytes(p);
     resourceBytes.put(key,dat);
   }}finally{ds.close();}
   byte[] vcf=resourceBytes.get(vcfName);if(vcf==null)throw new Exception("missing retail VCF");
   reset(vcf,vcfName);
   try{
    runCall(0x00461c80L);runCall(0x00461d50L);log("EMPTY_CONTROL_RETURN",0,"head="+hx(u32(0x0054b204L)));
    if(nativeRoot)createNativeRoot();
    log("ROOT_BEFORE_VCF",LOADER,"type="+(nativeRoot?"native_ctor":"manual_zero")+";matrix="+vec(OBJ+0x18L,16)+";dir="+vec(OBJ+0x30L,3));
    runNativeSpawnStatus();
    int idx=0;
    for(Map.Entry<String,byte[]> kv:resourceBytes.entrySet()){
      long base=0x32000000L+(idx++*0x20000L);byte[] dat=kv.getValue();
      if(dat.length>0x20000)throw new Exception("fixture large: "+kv.getKey());
      mem(base,dat.length+32);e.writeMemory(a(base),dat);resourcePtrs.put(kv.getKey(),base);
    }
    log("NATIVE_VCF_BEGIN",LOADER,"source="+vcfName+";resources="+resourcePtrs.keySet().toString());
    if(mode.contains("terrain")){runCall(0x00493c50L);log("MATH_INITIALIZED",0x00493c50L,"table128="+hx(u32(0x00655200L)));initializeTerrain();if(mode.contains("registry"))initializeEngineVariants();}
    runCall(LOADER,0,CTX,NAME);
    long liveRT=u32(OBJ+0x70L),stagingRT=u32(CTX+4L);
    log("COMPONENT_RECORDS",0x004b0d00L,"engine="+vec(u32(u32(liveRT+0x3c4L)+0x70L),8)+";brake="+vec(u32(u32(liveRT+0x3ccL)+0x70L),8)+";suspension="+vec(u32(u32(liveRT+0x3c8L)+0x70L),8));
    log("RUNTIME_IDENTITY",LOADER,"obj="+hx(OBJ)+";objClass="+u32(OBJ+0x6cL)+";liveRuntime="+hx(liveRT)+";contextSecond="+hx(stagingRT)+";expectedNativeAlloc=36000000");
    for(int mount=0;mount<6;mount++){
      log("RUNTIME_MOUNT",LOADER,"slot="+mount+";native="+hx(u32(liveRT+0x3a8L+4*mount))+";staging="+hx(u32(RUNTIME+0x3a8L+4*mount))+";wlocFlags="+hx(u32(stagingRT+0x168L+56*mount)));
    }
    for(int j:new int[]{0x108,0x138,0x148,0x168,0x188,0x19c,0x408,0x40c,0x410,0x414,0x454}){
       log("RUNTIME_FIELD",LOADER,"offset="+hx(j)+";native="+hx(u32(liveRT+j))+";staging="+hx(u32(RUNTIME+j)));
    }
    long attached=u32(liveRT+0x398L);
    log("VLOC_ATTACHMENT_FIELDS",LOADER,"pointer="+hx(attached)+";class="+hx(attached==0?0:u32(attached+0x6cL))+";parent="+hx(attached==0?0:u32(attached+0x68L))+";root="+hx(OBJ));
    if(selected && (attached==0 || u32(attached+0x6cL)!=0x28))throw new Exception("native VLOC child missing or incorrectly bound: "+hx(attached));
    if(!selected && attached!=0)throw new Exception("Unselected VLOC attachment unexpectedly created: "+hx(attached));
    byte[] sourceVdf=resourceBytes.get(label.startsWith("gtsi")?"valeprec.vdf":"vxbus.vdf");
    if(sourceVdf==null)throw new Exception("Missing retail VDF");
    if(selected && !Arrays.equals(Arrays.copyOfRange(sourceVdf,0x10A+12,0x10A+48),e.readMemory(a(attached+0x18L),36)))throw new Exception("VLOC native 9-word transform mismatch");
    log("ROOT_AFTER_VCF",LOADER,"type="+(nativeRoot?"native_ctor":"manual_zero")+";matrix="+vec(OBJ+0x18L,16)+";dir="+vec(OBJ+0x30L,3));
    log("FLAGGED_VCF_POST",LOADER,"status="+hx(u32(OBJ+0x10))+";runtime398="+hx(attached)+";class28="+(attached==0?"NULL":u32(attached+0x6cL))+";vlocNineWords="+(selected?"EXACT":"NOT_CREATED")+";nodes="+nodeAlloc);
    log("NATIVE_VCF_COMPLETE",LOADER,"vcfc="+n_vcfc+";opens="+n_open+";missing="+n_openfail+";parsers="+n_nested+";nodes="+nodeAlloc+";geoBindings="+cacheBindings+";weaponConstructors="+ctorCount+";materialBinds="+materialBinds+";nativeMaterialSuccess="+nativeMaterialSuccess+";mount0="+hx(u32(liveRT+0x3a8))+";mount4="+hx(u32(liveRT+0x3b8)));
    if(bodyParts!=(label.startsWith("gtsi")?31:29))throw new Exception("unexpected VDF body parts "+bodyParts);
    if(!((label.startsWith("gtsi") && nodeAlloc==(selected?47:46)) || (label.startsWith("bus")&& nodeAlloc==(selected?45:44))))throw new Exception("Unexpected node count: "+nodeAlloc);
    if(selected && attached==0 || !selected && attached!=0)throw new Exception("Attachment/status policy mismatch");
    if(nativeRegistry){
      long oldRef=u32(OBJ+0xcL),oldCount=u32(0x0054a25cL);
      runCall(0x004572b0L,OBJ,0,0);
      registeredEntry=reg("EAX");
      log("NATIVE_WORLD_REGISTRATION",0x004572b0L,"entry="+hx(registeredEntry)+";owner="+hx(u32(registeredEntry))+";countBefore="+oldCount+";countAfter="+u32(0x0054a25cL)+";refBefore="+oldRef+";refAfter="+u32(OBJ+0xcL)+";rootDirection="+vec(OBJ+0x30L,3));
      if(registeredEntry!=0x00542830L||u32(registeredEntry)!=OBJ||u32(0x0054a25cL)!=1)throw new Exception("Original world registration failed");
    }
    log("COLLECTION_READY",0,"head="+hx(u32(0x0054b204L))+";pending="+hx(u32(0x0054b208L))+";count="+u32(0x0054b210L));
    if(mode.contains("peripheral")){
     for(long node=u32(0x54b204L);node!=0;node=u32(node)){long owner=u32(node+8),klass=u32(owner+0x6c);if(klass==31||klass==34){long rt=u32(owner+0x70);log("PERIPHERAL_BEFORE",0,"class="+klass+";owner="+hx(owner)+";runtime="+hx(rt)+";fields="+(klass==31?"animation="+hx(u32(rt))+";animationWords="+(u32(rt)==0?"NULL":vec(u32(rt),4)):"animation="+hx(u32(rt+8))+";root="+hx(u32(rt+0x78))+";self="+hx(u32(rt+0x7c))));
      if(!mode.contains("noinit"))runCall(klass==31?0x46f2b0L:0x45f810L,owner);
      log("PERIPHERAL_INITIALIZED",0,"class="+klass+";owner="+hx(owner)+";runtime="+hx(rt)+";fields="+(klass==31?"animation="+hx(u32(rt))+";animationWords="+(u32(rt)==0?"NULL":vec(u32(rt),4)):"animation="+hx(u32(rt+8))+";root="+hx(u32(rt+0x78))+";self="+hx(u32(rt+0x7c))));
      runCall(klass==31?0x46f420L:0x45faf0L,owner);log("PERIPHERAL_POST_RETURN",0,"class="+klass+";owner="+hx(owner)+";fields="+(klass==31?"animation="+hx(u32(rt))+";animationWords="+(u32(rt)==0?"NULL":vec(u32(rt),4)):"animation="+hx(u32(rt+8))+";root="+hx(u32(rt+0x78))+";self="+hx(u32(rt+0x7c))));
     }}return;
    }
    if(mode.contains("directinit")){try{runCall(0x463120L,OBJ);log("CLASS1_INIT_RETURN",0,"flags="+hx(u32(liveRT+0x454))+";counts="+vec(liveRT+0x1a0,7));}catch(Exception ex){log("BOUNDED_STOP",reg("EIP"),ex.toString());throw ex;}if(mode.contains("postcontrol")){try{runCall(0x463950L,OBJ);log("CLASS1_POST_RETURN",0,"status="+hx(u32(OBJ+0x10)));}catch(Exception ex){log("BOUNDED_STOP",reg("EIP"),ex.toString());throw ex;}}return;}
    if(mode.contains("pending")){
     log("PENDING_BEFORE",0,"head="+hx(u32(0x54b208L))+";count="+u32(0x54b20cL)+";classCount="+u32(0x54b210L));
     try{runCall(0x00461b80L);log("PENDING_AFTER",0,"head="+hx(u32(0x54b208L))+";count="+u32(0x54b20cL)+";classCount="+u32(0x54b210L));}
     catch(Exception ex){log("BOUNDED_STOP",reg("EIP"),ex.toString());throw ex;}
    }
    if(mode.contains("initonly"))return;
    initializeCameraNative();
    if(mode.contains("terrain"))placeRetailPose();
    if(mode.contains("clock")) {runCall(0x0049c7f0L);runCall(0x0049cbe0L,liveRT+0x444L,0x3d4ccccdL);log("CLOCK_INITIALIZED",0x0049c7f0L,"reciprocals="+vec(0x005a7e20L,4));}
    log("NO_CONTROL_INJECTION",0,"fieldsE4_104_AC="+vec(liveRT+0xe4L,1)+","+hx(u32(liveRT+0x104L))+","+hx(u32(liveRT+0xacL)));
    double lastPosition=rd64(OBJ+0x50L);
    for(int frame=0;frame<frames;frame++){
      log("POSE_BEFORE_FRAME",0x00463800L,"frame="+frame+";rootBasis="+vec(OBJ+0x18L,16)+";runtimeVelocity="+vec(liveRT+0xbcL,3)+";candidateMatrix="+vec(liveRT+0xc8L,16)+";runtimeFlags="+hx(u32(liveRT+0x454L)));
      // Force a controlled active-vehicle relevance distance while leaving original 00406840 instructions intact.
      w32(0x004c2890L,0x00000000L);w32(0x004c2894L,0x408F4000L); // camera x=1000.0 double
      if(mode.contains("clock")){tick+=mode.contains("slow")?100:16;runCall(0x0049c920L);log("CLOCK_UPDATED",0x0049c920L,"dt="+Float.intBitsToFloat((int)u32(0x004fe420L)));}else w32(0x004fe420L,0x3c888889L); // synthetic original-delta service reads 1/60 second
      w32(0x005dd360L,u32(0x004f4ca4L)); // original input-pause gate equal
      log("PHYSICS_CONTROLLED_FRAME",0x00463800L,"frame="+frame+";camera=controlled_near_root;dt=original_clock;tickIncrementMs="+(mode.contains("slow")?100:16)+";paused=0");
      if(mode.contains("terrain")){wd(0x004c2890L,rd64(OBJ+0x40));wd(0x004c2898L,rd64(OBJ+0x48));wd(0x004c28a0L,rd64(OBJ+0x50));}
      try {
        log("PHASE_STATE",0,"phase=before_pre;frame="+frame+";status="+hx(u32(OBJ+0x10))+";position="+rd64(OBJ+0x40)+","+rd64(OBJ+0x48)+","+rd64(OBJ+0x50)+";flags="+hx(u32(liveRT+0x454))+";basis="+vec(OBJ+0x18,9)+";velocity="+vec(liveRT+0xbc,3)+";timer="+vec(liveRT+0x444,3));
        if(mode.contains("direct"))runCall(0x00463800L,OBJ);else runCall(0x00461c80L);
        log("PHASE_STATE",0,"phase=after_pre;frame="+frame+";status="+hx(u32(OBJ+0x10))+";position="+rd64(OBJ+0x40)+","+rd64(OBJ+0x48)+","+rd64(OBJ+0x50)+";flags="+hx(u32(liveRT+0x454))+";basis="+vec(OBJ+0x18,9)+";velocity="+vec(liveRT+0xbc,3)+";timer="+vec(liveRT+0x444,3));
        if(mode.contains("direct"))runCall(0x00463950L,OBJ);else runCall(0x00461d50L);
        log("PHASE_STATE",0,"phase=after_post;frame="+frame+";status="+hx(u32(OBJ+0x10))+";position="+rd64(OBJ+0x40)+","+rd64(OBJ+0x48)+","+rd64(OBJ+0x50)+";flags="+hx(u32(liveRT+0x454))+";basis="+vec(OBJ+0x18,9)+";velocity="+vec(liveRT+0xbc,3)+";timer="+vec(liveRT+0x444,3));
        log("POSE_CLASS_CALLBACK_END",0x00463800L,"frame="+frame+";rootBasis="+vec(OBJ+0x18L,16)+";runtimeVelocity="+vec(liveRT+0xbcL,3)+";candidateMatrix="+vec(liveRT+0xc8L,16)+";rootPosition="+vec(OBJ+0x40L,6));
      } catch(Exception exp) {
        log("POSE_CLASS_CALLBACK_ERROR",0x00463800L,"frame="+frame+";message="+exp.getMessage().replace('\t',' '));
        throw exp;
      }
      double[] b=new double[9];for(int k=0;k<9;k++)b[k]=Float.intBitsToFloat((int)u32(OBJ+0x18L+k*4));
      StringJoiner gram=new StringJoiner(",");for(int r=0;r<3;r++)for(int c=r;c<3;c++){double g=0;for(int k=0;k<3;k++)g+=b[r*3+k]*b[c*3+k];gram.add(String.format(Locale.ROOT,"%.12g",g));}
      log("POSE_GRAM",0x00463800L,"frame="+frame+";upper="+gram+";basis="+vec(OBJ+0x18L,9));
      nativeCameraGuard(label+"_frame"+frame);
      double position=rd64(OBJ+0x50L), axis=axisLen2();
      int badRoot=invalidFloats(OBJ+0x18L,9), badCamera=nonfinite6(0x004c2890L),badPosition=0;for(int k=0;k<3;k++)if(!Double.isFinite(rd64(OBJ+0x40L+8*k)))badPosition++;
      log("TWO_FRAME_NUMERICAL_RESULT",0x00406DF4L,"frame="+frame+";axisNormSq="+String.format(Locale.ROOT,"%.12g",axis)+";rootDir="+vec(OBJ+0x30L,3)+";basisBadF32="+badRoot+";positionBadD64="+badPosition+";rootPositionXYZ="+doubles6(OBJ+0x40L).split(",")[0]+","+rd64(OBJ+0x48L)+","+position+";rootZChanged="+(position!=lastPosition)+";cameraBadD64="+badCamera+";cameraDoubles="+doubles6(0x004c2890L)+";flags="+hx(u32(liveRT+0x454))+";contact="+vec(liveRT+0x38,27)+";groundPositive="+positiveProbe+";solverCalls="+solverCalls+";terrainReads="+terrainReads+";smoothing="+vec(0x0052b93cL,3));
      if(selected && (badRoot!=0||badPosition!=0||badCamera!=0||!(axis>0&&axis<10)))throw new Exception("Two-frame moving-state numerical invariant failed frame="+frame+" axis="+axis+" position="+position+" prev="+lastPosition);
      lastPosition=position;
    }
   }finally{e.dispose();e=null;}
 }
 @Override public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5 mismatch");
  String[] args=getScriptArgs();mode=args.length>6?args[6]:"math-clock-pop-terrain-host-filter-registry";frames=args.length>10?Integer.parseInt(args[10]):2;if(mode.contains("host")||mode.contains("filter")){host=new ProcessBuilder(args[9]).start();hostIn=new DataOutputStream(host.getOutputStream());hostOut=new DataInputStream(host.getInputStream());}missionBytes=Files.readAllBytes(Paths.get(args[7]));terrainBytes=Files.readAllBytes(Paths.get(args[8]));
  java.security.MessageDigest md=java.security.MessageDigest.getInstance("SHA-256");String mh=java.util.HexFormat.of().formatHex(md.digest(missionBytes)),th=java.util.HexFormat.of().formatHex(md.digest(terrainBytes));if(!mh.equals("923d47e189e087b604e7b2d2825668433b9ccf1547437938fd31b5573202a97f")||!th.equals("fdd18c8b8a4dc1b280ae5ccf780b988a928cadbcf9170cd8c1907da97e4002ea"))throw new Exception("M06 retail fixture identity mismatch");
  try(PrintWriter writer=new PrintWriter(args[1])){
   trace=writer;trace.println("scenario\tkind\tpc\tdetail");
   if(mode.contains("x87only")){reset(new byte[32],"x87");scenario="x87";for(int cw:new int[]{0x37f,0x77f,0xb7f,0xf7f})for(int raw:new int[]{0,0x80000000,0x3f800000,0xbf800000,0x3fc90fdb,0x40490fdb,0x42c80000}){e.writeRegister("FPUControlWord",cw);runCall(0x49d400L,raw&0xffffffffL);log("X87_RESULT",0x49d400L,"input="+hx(raw)+";cw="+Integer.toHexString(cw)+";sin="+hx(reg("EAX"))+";cos="+hx(reg("EDX")));}e.dispose();return;}
   selected=Integer.parseInt(args[3])!=0;nativeRoot=Integer.parseInt(args[4])!=0;nativeRegistry=Integer.parseInt(args[5])!=0;String vehicle=args[2];if(!vehicle.equals("gtsi")&&!vehicle.equals("bus"))throw new Exception("Invalid vehicle");testVcfAll(args[0],vehicle.equals("gtsi")?"noal01.vcf":"nobus1.vcf",vehicle+"_"+(selected?"selected":"unselected")+"_"+(nativeRoot?"native_root":"zero_root")+(nativeRegistry?"_registered":""));
  }finally{if(hostIn!=null)hostIn.close();if(host!=null){int code=host.waitFor();if(code!=0)throw new Exception("host FISTP service exit "+code);}}
 }
}
