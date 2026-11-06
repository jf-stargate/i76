// Run-owned original-instruction experiment; VCF/service scaffold derived from accepted
// i76exe-20261027T031313Z-32de4d1e (source SHA-256 in provenance.json).
import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.file.*;
import java.util.*;
public class I76_CameraBase extends GhidraScript {
 static final long LOADER=0x4ad6f0L,PARSE=0x4b41e0L,VCFC=0x4ad950L,SPEC=0x4ade50L,WEPN=0x4aeb90L,WDFFN=0x4ae5e0L,EXIT=0x4b4290L;
 static final long OBJ=0x26000000L,CTX=0x26002000L,RUNTIME=0x26004000L,NAME=0x26007000L,FILE=0x25000000L;
 static final long WDFCTX=0x26009000L,FIRST=0x26010000L,SECOND=0x26011000L,FRT=0x26012000L,SRT=0x26013000L,NODES=0x26020000L;
 static final long STACK=0x30020000L,SENT=0x70000000L; static final int LIMIT=5000000;
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
 double d64(long at){return Double.longBitsToDouble((u32(at+4L)<<32)|u32(at));}
 String doubles(long at,int count){StringJoiner j=new StringJoiner(",");for(int k=0;k<count;k++)j.add(String.format(Locale.ROOT,"%.12g",d64(at+8L*k)));return j.toString();}
 int invalidDoubles(long at,int count){int n=0;for(int k=0;k<count;k++)if(!Double.isFinite(d64(at+8L*k)))n++;return n;}
 String sha(byte[] data)throws Exception{byte[] hash=java.security.MessageDigest.getInstance("SHA-256").digest(data);StringBuilder b=new StringBuilder();for(byte v:hash)b.append(String.format(Locale.ROOT,"%02x",v&255));return b.toString();}
 int invalidFloats(long at,int words){int n=0;for(int j=0;j<words;j++)if(!Float.isFinite(Float.intBitsToFloat((int)u32(at+4L*j))))n++;return n;}
 void ret(long value){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void retStd(long value,int nargs){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4+4*nargs);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
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
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  ArrayDeque<String> hist=new ArrayDeque<>();boolean done=false;
  for(int n=0;n<LIMIT;n++){
   long pc=reg("EIP"),rsp=reg("ESP");steps=n;
   if(pc==SENT){done=true;break;}
   if(target==0x463120L && pc==0x463189L){log("NATIVE_vehicle_init_prefix_complete",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0ref="+u32(SECOND+0xc)+";mount1ref="+u32(FIRST+0xc));done=true;break;}
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
   if(pc==0x49e0f0L){log("STUB_x87_cosine_helper",pc,"FCOS not supported by Ghidra emulator");ret(0);continue;}
   if(pc==0x461b20L){classReleases++;log("NATIVE_class_destructor_dispatch",pc,"class="+u32(rsp+4)+";runtime="+hx(u32(rsp+8)));}
   if(pc==0x4639a0L)log("NATIVE_vehicle_runtime_destructor",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0="+hx(u32(RUNTIME+0x3a8))+";mount1="+hx(u32(RUNTIME+0x3ac)));
   if(pc==0x46da60L)log("NATIVE_weapon_runtime_destructor",pc,"runtime="+hx(u32(rsp+4)));
   if(pc==0x461a20L){if(u32(rsp+4)==0){log("STUB_NULL_component_visual_unlink",pc,"ptr=00000000");ret(0);continue;}else{log("NATIVE_class_registry_unlink",pc,"ptr="+hx(u32(rsp+4)));}}
   if(pc==0x45f3d0L){log("NATIVE_runtime_allocator_free",pc,"ptr="+hx(u32(rsp+4)));}
   if(pc==0x449e60L||pc==0x477e10L){log("STUB_render_release",pc,"object="+hx(u32(rsp+4)));ret(0);continue;}

   if(pc==0x49c320L){listCount++;long node=NODES+(listCount-1)*0x40;w32(node,u32(rsp+4));w32(node+4,u32(rsp+8));w32(node+8,u32(rsp+12));ret(node);continue;}
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
      if(reg("EAX")!=1||ptr==0||tmt==0||u32(ptr)!=firstMaterialOwner||!cstr(tmt,16).equalsIgnoreCase(firstMaterialResource))throw new Exception("native TMT material binding invalid: "+firstMaterialKey+" -> "+firstMaterialResource+" / "+hx(ptr)+" / "+hx(tmt));
      byte[] sourceTmt=resourceBytes.get(firstMaterialResource.toLowerCase(Locale.ROOT));
      if(sourceTmt==null||sourceTmt.length<0x48)throw new Exception("missing source TMT "+firstMaterialResource);
      String expectedFrame=new String(sourceTmt,0x40,8,java.nio.charset.StandardCharsets.ISO_8859_1).toLowerCase(Locale.ROOT);
      if(!cstr(frames,16).toLowerCase(Locale.ROOT).startsWith(expectedFrame))throw new Exception("native TMT frame mismatch key="+firstMaterialKey+" expected="+expectedFrame);
      nativeMaterialSuccess++;
      firstMaterialReturnPc=0;
   }
   if(pc==0x004b0190L||pc==0x004b0150L||pc==0x004b0290L){log("STUB_optional_material_side_effect",pc,hx(u32(rsp+4)));ret(1);continue;}
   if(pc==0x00467280L){log("STUB_special_equipment_logger",pc,hx(u32(rsp+4)));ret(1);continue;}
   if(pc==0x0042d5d0L){caughtReporter++;log("NATIVE_reporter_RET",pc,"reached");}
   if(pc==0x004b4048L){log("CALLBACK_RESULT",pc,"eax="+reg("EAX"));}
   if(pc==EXIT){log("NATIVE_EXIT",pc,hx(u32(rsp+4)));}
   if(!e.step(monitor))throw new Exception(scenario+" error pc="+hx(pc)+" "+e.getLastError()+" history="+hist);
  }
  if(!done)throw new Exception(scenario+" step limit "+hist);
  log("RETURN",target,"eax="+reg("EAX")+";steps="+steps+";builder="+builderCount+";ctor="+ctorCount+";geo="+geoCount+";allocNodes="+nodeAlloc+";allocRuntime="+runtimeAlloc+";nodeFree="+nodeFree+";runtimeFree="+runtimeFree+";parentFirst="+hx(u32(OBJ+0x64))+";runtimeMount0="+hx(u32(RUNTIME+0x3a8))+";runtimeMount1="+hx(u32(RUNTIME+0x3ac))+";firstClass="+u32(FIRST+0x6c)+";secondClass="+u32(SECOND+0x6c)+";firstRef="+u32(FIRST+0xc)+";secondRef="+u32(SECOND+0xc));
 }
 void initializeCameraNative()throws Exception{
  w32(0x005dd2a8L,2);w32(0x00654b8aL,0);
  for(long p=0x005dcec0L;p<0x005dcfc0L;p+=4)w32(p,0);
  w32(0x005dcedcL,0);w32(0x005dcee0L,0);w32(0x005dcee4L,639);w32(0x005dcee8L,479);w32(0x005dcec0L,640);w32(0x005dcec4L,480);
  long sp=STACK-0x3000L;w32(sp,SENT);w32(sp+4L,0);e.writeRegister("ESP",sp);e.writeRegister("EIP",0x00405970L);
  for(int n=0;n<200000;n++){
    long pc=reg("EIP");if(pc==SENT){log("CAMERA_PROJECTION_INIT_END",pc,"steps="+n+";p4="+hx(u32(0x4c2734L))+";v44="+hx(u32(0x4c2774L)));return;}
    if(pc==0x0049d400L){long raw=u32(reg("ESP")+4L);float rad=Float.intBitsToFloat((int)raw);
      long sin=Float.floatToRawIntBits((float)Math.sin(rad))&0xffffffffL,cos=Float.floatToRawIntBits((float)Math.cos(rad))&0xffffffffL;
      long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",sin);e.writeRegister("EDX",cos);log("CAMERA_INIT_MATH_BOUNDARY",pc,"radians="+hx(raw));continue;}
    if(pc==0x004ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);if(ext.testBit(79))v=-v;int val=(int)v;long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",val&0xffffffffL);for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));log("CAMERA_INIT_MATH_BOUNDARY",pc,"converted="+val+";pop=true");continue;}
    byte[] pre=e.readMemory(a(CAMERA),472);
    if(!e.step(monitor))throw new Exception("Camera initialization failure at "+hx(pc)+" "+e.getLastError());
  diffWrites(pc,CAMERA,pre);
  }throw new Exception("camera init step limit");
 }
 String mode; int frame; long cameraSource;
 static final long CAMERA=0x4c2730L;
 String hexbytes(long p,int n){StringBuilder b=new StringBuilder();for(byte v:e.readMemory(a(p),n))b.append(String.format(Locale.ROOT,"%02x",v&255));return b.toString();}
 void snapshot(String phase){log("SAMPLE",reg("EIP"),"frame="+frame+";phase="+phase+";camera="+hexbytes(CAMERA,472)+";smooth="+hexbytes(0x4c2964L,24)+hexbytes(0x52b93cL,12)+";root="+hexbytes(OBJ+0x18,64)+";velocity="+hexbytes(u32(OBJ+0x70)+0xd4,12)+";mode="+hx(u32(0x4c2728))+";attachment="+hx(u32(u32(OBJ+0x70)+0x398))+";dt="+hx(u32(0x4fe420))+";angles="+vec(0x536770L,5));}
 void pose(int which){
  // Only this method controls the already original-constructed root pose. Never writes camera state.
  float[] basis=which==2?new float[]{0,0,-1,0,1,0,1,0,0}:new float[]{1,0,0,0,1,0,0,0,1};
  if(mode.equals("zero"))Arrays.fill(basis,0);
  for(int i=0;i<9;i++)w32(OBJ+0x18+4*i,Float.floatToRawIntBits(basis[i]));
  for(int i=0;i<3;i++){double v=which==0?0:new double[]{10,20,30}[i];long bits=Double.doubleToRawLongBits(v);w32(OBJ+0x40+8*i,bits);w32(OBJ+0x44+8*i,bits>>>32);}
  log("CONTROLLED_POSE",0,"frame="+frame+";pose="+which+";bytes="+hexbytes(OBJ+0x18,64));
 }
 void continuity(String label)throws Exception {
  w32(0x4c2908L,registeredEntry);
  w32(0x536770L,1);w32(0x536778L,1);w32(0x536780L,1);
  w32(0x4fe420L,Float.floatToRawIntBits(0.016f)); // explicit supplied frame delta, used by original smoothing
  long rt=u32(OBJ+0x70);
  for(int i=0;i<3;i++)w32(rt+0xd4+4*i,Float.floatToRawIntBits(new float[]{2,0,1}[i]));
  log("CONTROLLED_INPUTS",0,"dt=0.016;runtime_d4_velocity=2,0,1;angle_integers=1,1,1;active="+hx(registeredEntry)+";owner="+hx(u32(registeredEntry))+";entry=direct_00406AB0;mode="+mode);
  if(mode.equals("guard")){w32(rt+0x398,0);log("CONTROLLED_GUARD",0,"selected native VLOC detached for negative control");}
  byte[] initial=e.readMemory(a(CAMERA),472),smooth1=e.readMemory(a(0x4c2964L),24),smooth2=e.readMemory(a(0x52b93cL),12);
  int[] sequence=mode.equals("coldB")?new int[]{1,1}:mode.equals("stationary")?new int[]{0,0,0,0,0,0,0,0}:new int[]{0,0,1,1,2,2,0,0};
  for(frame=0;frame<sequence.length;frame++){
   if(mode.equals("reset")){e.writeMemory(a(CAMERA),initial);e.writeMemory(a(0x4c2964L),smooth1);e.writeMemory(a(0x52b93cL),smooth2);log("CONTROLLED_RESET",0,"frame="+frame+";camera_and_smoothing=initial");}
   pose(sequence[frame]);snapshot("before");cameraCall();snapshot("after");
   // Exercise original source-to-view consumer on a fixed point without touching the camera.
   runCall(0x472d30L,0x2600b000L,CAMERA,0,0,0,0,0,0);
   log("VIEW_POINT",0x472d30L,"frame="+frame+";input=0,0,0;result="+vec(0x2600b000L,3));
  }
 }
 void cameraCall()throws Exception {
  long sp=STACK-0x3000;w32(sp,SENT);e.writeRegister("ESP",sp);e.writeRegister("EIP",0x406ab0L);
  log("CAMERA_ENTER",0x406ab0L,"frame="+frame);
  for(int n=0;n<200000;n++){
   long pc=reg("EIP");
   if(pc==SENT){log("CAMERA_RETURN",pc,"frame="+frame+";steps="+n);return;}
   if(pc==0x406b02L||pc==0x406b13L||pc==0x437f90L||pc==0x472400L||pc==0x472990L||pc==0x406df4L||pc==0x458cb0L||pc==0x494e20L){
    log("CALL_EVENT",pc,"frame="+frame+";esp="+hx(reg("ESP"))+";arg1="+hx(u32(reg("ESP")+4))+";arg2="+hx(u32(reg("ESP")+8))+";root="+hexbytes(OBJ+0x18,64));
    if(pc==0x437f90L)trackedMatrixPtr=u32(reg("ESP")+4);
    if(pc==0x472990L){cameraSource=u32(reg("ESP")+8);log("CAMERA_SOURCE",pc,"frame="+frame+";ptr="+hx(cameraSource)+";bytes="+hexbytes(cameraSource,64));}
   }
   if(pc==0x43802eL||pc==0x438031L||pc==0x438045L||pc==0x4380b2L||pc==0x4380bcL||pc==0x4380c6L)log("ROOT_READ_ANCHOR",pc,"frame="+frame+";esi="+hx(reg("ESI"))+";root="+hexbytes(OBJ+0x18,64));
   if(pc==0x406d45L)log("ROOT_MATRIX",pc,"frame="+frame+";bytes="+hexbytes(trackedMatrixPtr,64));
   if(pc==0x49d400L){float v=Float.intBitsToFloat((int)u32(reg("ESP")+4));e.writeRegister("EDX",Float.floatToRawIntBits((float)Math.cos(v))&0xffffffffL);ret(Float.floatToRawIntBits((float)Math.sin(v))&0xffffffffL);log("SERVICE_TRIG",pc,"frame="+frame+";radians="+v);continue;}
   if(pc==0x4ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fff)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);if(ext.testBit(79))v=-v;
    for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));ret(((int)v)&0xffffffffL);log("SERVICE_FTOL",pc,"frame="+frame+";value="+v+";pop=true");continue;}
   byte[] before=e.readMemory(a(CAMERA),472),b1=e.readMemory(a(0x4c2964L),24),b2=e.readMemory(a(0x52b93cL),12),rootBefore=e.readMemory(a(OBJ+0x18),64);
   if(!e.step(monitor))throw new Exception("camera stop "+hx(pc)+" "+e.getLastError());
   diffWrites(pc,CAMERA,before);diffWrites(pc,0x4c2964L,b1);diffWrites(pc,0x52b93cL,b2);if(!Arrays.equals(rootBefore,e.readMemory(a(OBJ+0x18),64)))throw new Exception("Unexpected native root pose write at "+hx(pc));
  }throw new Exception("camera step limit");
 }
 void diffWrites(long pc,long base,byte[] before){byte[] after=e.readMemory(a(base),before.length);for(int off=0;off<before.length;off+=4){if(!Arrays.equals(Arrays.copyOfRange(before,off,off+4),Arrays.copyOfRange(after,off,off+4)))log("NATIVE_CHANGED_DWORD",pc,"frame="+frame+";address="+hx(base+off)+";before="+String.format("%02x%02x%02x%02x",before[off]&255,before[off+1]&255,before[off+2]&255,before[off+3]&255)+";after="+hexbytes(base+off,4));}}
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
    runCall(LOADER,0,CTX,NAME);
    long liveRT=u32(OBJ+0x70L),stagingRT=u32(CTX+4L);
    log("RUNTIME_IDENTITY",LOADER,"obj="+hx(OBJ)+";objClass="+u32(OBJ+0x6cL)+";liveRuntime="+hx(liveRT)+";contextSecond="+hx(stagingRT)+";expectedNativeAlloc=36000000");
    for(int mount=0;mount<6;mount++){
      log("RUNTIME_MOUNT",LOADER,"slot="+mount+";native="+hx(u32(liveRT+0x3a8L+4*mount))+";staging="+hx(u32(RUNTIME+0x3a8L+4*mount))+";wlocFlags="+hx(u32(stagingRT+0x168L+56*mount)));
    }
    for(int j:new int[]{0x108,0x138,0x148,0x168,0x188,0x19c,0x408,0x40c,0x410,0x414,0x454}){
       log("RUNTIME_FIELD",LOADER,"offset="+hx(j)+";native="+hx(u32(liveRT+j))+";staging="+hx(u32(RUNTIME+j)));
    }
    long attached=u32(liveRT+0x398L);
    log("VLOC_ATTACHMENT_FIELDS",LOADER,"pointer="+hx(attached)+";class="+hx(u32(attached+0x6cL))+";parent="+hx(u32(attached+0x68L))+";root="+hx(OBJ));
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
    runCall(0x493c50L);
    initializeCameraNative();
    continuity(label);
   }finally{e.dispose();e=null;}
 }
 @Override public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5 mismatch");
  String[] args=getScriptArgs();
  String[] modes=args[6].equals("all")?new String[]{"persistent","reset","zero","guard","coldB","stationary"}:new String[]{args[6]};
  for(String selectedMode:modes)try(PrintWriter writer=new PrintWriter(args[1]+(args[6].equals("all")?"_"+selectedMode+".tsv":""))){
   trace=writer;trace.println("scenario\tkind\tpc\tdetail");
   mode=selectedMode;selected=true;nativeRoot=true;nativeRegistry=true;String vehicle=args[2];if(!vehicle.equals("gtsi")&&!vehicle.equals("bus"))throw new Exception("Invalid vehicle");testVcfAll(args[0],vehicle.equals("gtsi")?"noal01.vcf":"nobus1.vcf",vehicle+"_selected_native_root_registered");
  }
 }
}
