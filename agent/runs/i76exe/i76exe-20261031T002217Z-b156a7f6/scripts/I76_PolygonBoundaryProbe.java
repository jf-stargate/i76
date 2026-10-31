import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.file.*;
import java.util.*;
public class I76_PolygonBoundaryProbe extends GhidraScript {
 static final long LOADER=0x4ad6f0L,PARSE=0x4b41e0L,VCFC=0x4ad950L,SPEC=0x4ade50L,WEPN=0x4aeb90L,WDFFN=0x4ae5e0L,EXIT=0x4b4290L;
 long OBJ=0x26000000L,CTX=0x26002000L,RUNTIME=0x26004000L,NAME=0x26007000L,FILE=0x25000000L;
 static final long WDFCTX=0x26009000L,FIRST=0x26010000L,SECOND=0x26011000L,FRT=0x26012000L,SRT=0x26013000L,NODES=0x26020000L;
 static final long STACK=0x30020000L,SENT=0x70000000L; static final int LIMIT=5000000;
 boolean producing=false; EmulatorHelper e;boolean selected;boolean nativeRoot,constructingRoot,nativeRegistry;long trackedMatrixPtr,registeredEntry;PrintWriter trace;byte[] bytes;String scenario,wdfName;int steps, n_vcfc,n_spec,n_wepn,n_weapon,n_nested,n_open,n_openfail,n_free;int failNested,failWeapon,failWeaponChunk,failGeo,builderCount,ctorCount,listCount,geoCount, nodeAlloc, runtimeAlloc, failNode, nodeFree, runtimeFree, classReleases, partAlloc, cacheBindings,cacheAlloc;boolean failOpen;long nextGeoReturnPc, firstMaterialReturnPc, firstMaterialOwner;String nextGeoName="",firstMaterialKey="",firstMaterialResource="";String firstError="";int caughtReporter,extraAlloc,materialBinds,nativeMaterialSuccess,realGeoConstructions,realGeoReturns,bodyParts,bodyNodeStart;long bodyBankZero;Map<String,byte[]> resourceBytes=new LinkedHashMap<>();Map<String,Long> resourcePtrs=new LinkedHashMap<>(); long genericHeapCursor=0x36000000L;
 Address a(long v){return toAddr(v&0xffffffffL);}
 String hx(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 long reg(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u32(long p){byte[] b=e.readMemory(a(p),4);if(b==null||b.length!=4)throw new IllegalStateException("invalid read="+hx(p));return (((long)b[0]&255)|(((long)b[1]&255)<<8)|(((long)b[2]&255)<<16)|(((long)b[3]&255)<<24))&0xffffffffL;}
 void w32(long p,long v){if(producing)throw new IllegalStateException("harness write during producer");checkHostWrite(p,4);e.writeMemoryValue(a(p),4,v&0xffffffffL);}
 void mem(long p,int n){if(producing)throw new IllegalStateException("harness memory allocation during producer");hostWrite(p,new byte[n]);}
 boolean viewSealed=false;boolean queueSealed=false;long sealedEnd;int hostWrites;
 void checkHostWrite(long p,int n){
  hostWrites++;if(viewSealed&&p<CAMERA+472&&p+n>CAMERA)throw new IllegalStateException("host camera write after callbacks");
  if(queueSealed && ((p<sealedEnd&&p+n>0x38000000L)||(p<0x6543c8L&&p+n>0x654380L)))throw new IllegalStateException("host write to original queue at "+hx(p));
 }
 void hostWrite(long p,byte[] b){checkHostWrite(p,b.length);e.writeMemory(a(p),b);}
 String cstr(long p,int max){StringBuilder b=new StringBuilder();for(int i=0;i<max;i++){byte[] x=e.readMemory(a(p+i),1);if(x==null||x.length<1){b.append("?");break;}if(x[0]==0)break;b.append((char)(x[0]&255));}return b.toString();}
 void log(String kind,long pc,String detail){trace.println(scenario+"\t"+kind+"\t"+hx(pc)+"\t"+detail);}
 String vec(long at,int words){StringJoiner out=new StringJoiner(",");for(int j=0;j<words;j++)out.add(hx(u32(at+4L*j)));return out.toString();}
 double d64(long at){return Double.longBitsToDouble((u32(at+4L)<<32)|u32(at));}
 String doubles(long at,int count){StringJoiner j=new StringJoiner(",");for(int k=0;k<count;k++)j.add(String.format(Locale.ROOT,"%.12g",d64(at+8L*k)));return j.toString();}
 int invalidDoubles(long at,int count){int n=0;for(int k=0;k<count;k++)if(!Double.isFinite(d64(at+8L*k)))n++;return n;}
 String sha(byte[] data)throws Exception{byte[] hash=java.security.MessageDigest.getInstance("SHA-256").digest(data);StringBuilder b=new StringBuilder();for(byte v:hash)b.append(String.format(Locale.ROOT,"%02x",v&255));return b.toString();}
 int invalidFloats(long at,int words){int n=0;for(int j=0;j<words;j++)if(!Float.isFinite(Float.intBitsToFloat((int)u32(at+4L*j))))n++;return n;}
 void ret(long value){if(producing && reg("EIP")>0x100000L && reg("EIP")!=0x46ffc0L && reg("EIP")!=0x46fee0L && reg("EIP")!=0x46fd40L)throw new IllegalStateException("service reached during original producer at "+hx(reg("EIP")));if(producing)log("PRODUCER_CRT_RETURN",reg("EIP"),"eax="+hx(value));long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void retStd(long value,int nargs){if(producing)throw new IllegalStateException("import reached during original producer");long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4+4*nargs);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void reset(byte[] content,String file){e=new EmulatorHelper(currentProgram);bytes=content;trackedMatrixPtr=0;constructingRoot=false;registeredEntry=0;
  mem(STACK-0x10000L,0x10800);mem(OBJ,0x800);mem(CTX,0x100);mem(RUNTIME,0x3000);mem(NAME,0x100);
  mem(FILE,Math.max(content.length,0x1000));hostWrite(FILE,content);mem(WDFCTX,0x200);mem(FIRST,0x1000);mem(SECOND,0x1000);mem(FRT,0x1000);mem(SRT,0x1000);mem(NODES,0x2000);mem(0x27000000L,0x20000);mem(0x28000000L,0x180000);mem(0x29000000L,0x20000);mem(0x2a000000L,0x10000);mem(0x2b000000L,0x200000);mem(0x36000000L,0x800000);
  hostWrite(NAME,(file+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));
  w32(CTX,OBJ);w32(CTX+4,RUNTIME);w32(WDFCTX,CTX);w32(OBJ+0x70,RUNTIME);w32(FIRST+0xc,1);w32(SECOND+0xc,1);w32(0x54ad34L,0x12350000L);w32(0x54ad38L,0x12340000L);w32(0x54ad2cL,OBJ);w32(0x54ad30L,OBJ);for(int k=0;k<4;k++)w32(0x54b204L+k*4,0);w32(OBJ+0x6c,1);w32(OBJ+0xc,1);w32(OBJ+0x10,0);w32(0x005db97cL,0);w32(0x005db980L,0);
  w32(0x006562c4L,0);w32(0x005dabc0L,1); // not geometry-family mode
  for(String r:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(r,0);
  mem(0x3c000000L,0x1000);w32(0x3c000000L,0xffffffffL);e.writeRegister("FS_OFFSET",0x3c000000L);e.writeRegister("DF",0);for(int fpu=0;fpu<8;fpu++)e.writeRegister("ST"+fpu,0);e.writeRegister("FPUControlWord",0x37f);
  materialBinds=0;nativeMaterialSuccess=0;realGeoConstructions=0;realGeoReturns=0;nextGeoReturnPc=0;firstMaterialReturnPc=0;firstMaterialOwner=0;nextGeoName="";firstMaterialKey="";firstMaterialResource="";bodyParts=0;bodyNodeStart=0;bodyBankZero=0;genericHeapCursor=0x36000000L;n_vcfc=0;n_spec=0;n_wepn=0;n_weapon=0;n_nested=0;n_open=0;n_openfail=0;n_free=0;failNested=0;failWeapon=0;failWeaponChunk=0;failOpen=false;caughtReporter=0;firstError="";builderCount=0;ctorCount=0;listCount=0;geoCount=0;failGeo=0;nodeAlloc=0;runtimeAlloc=0;failNode=0;nodeFree=0;runtimeFree=0;classReleases=0;partAlloc=0;cacheBindings=0;cacheAlloc=0;
 }
 boolean isImport(long pc,long slot){return pc!=0&&pc==u32(slot);}
 void runCall(long target,long...args)throws Exception {
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  ArrayDeque<String> hist=new ArrayDeque<>();boolean done=false;producing=target==0x457ff0L;consuming=target==0x48fac0L;
  for(int n=0;n<LIMIT;n++){
   long pc=reg("EIP"),rsp=reg("ESP");steps=n;
   if(pc==SENT){done=true;break;}
   if(target==0x463120L && pc==0x463189L){log("NATIVE_vehicle_init_prefix_complete",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0ref="+u32(SECOND+0xc)+";mount1ref="+u32(FIRST+0xc));done=true;break;}
   visibilityEvent(pc,rsp);
   if(consumerEvent(pc,rsp))continue;
   if(pc==0x498940L || pc==0x499ce0L){long size=u32(rsp+4),out=arenaHeap;arenaHeap=(arenaHeap+size+15)&~15L;mem(out,(int)size);log("ARENA_ALLOC",pc,"size="+size+";ptr="+hx(out));ret(out);continue;}
   if(pc==0x477ed0L)log("ORIGINAL_LIGHT_CONTEXT",pc,"count="+u32(0x58db04L));
   if(hist.size()>18)hist.removeFirst();hist.addLast(hx(pc));
   if(isImport(pc,0x4bc238)){String src=cstr(u32(rsp+4),80);long drive=u32(rsp+8),dir=u32(rsp+12),fname=u32(rsp+16),ext=u32(rsp+20);String base=src.replace("\\","/");base=base.substring(base.lastIndexOf("/")+1);int dot=base.lastIndexOf(".");String stem=dot>=0?base.substring(0,dot):base;String suffix=dot>=0?base.substring(dot):"";hostWrite(drive,new byte[4]);hostWrite(dir,new byte[256]);hostWrite(fname,(stem+"\0").getBytes());hostWrite(ext,(suffix+"\0").getBytes());log("STUB_splitpath",pc,src+";stem="+stem+";ext="+suffix);ret(0);continue;}
   if(isImport(pc,0x4bc28c)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] b=e.readMemory(a(src),len);if(b==null)throw new Exception("strncpy src");hostWrite(dst,b);ret(dst);continue;}
   if(isImport(pc,0x4bc260)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);int cnt=(int)u32(rsp+12);int result=x.substring(0,Math.min(cnt,x.length())).equalsIgnoreCase(y.substring(0,Math.min(cnt,y.length())))?0:1;log("STUB_strnicmp",pc,x+"|"+y+"|"+cnt+"|"+result);ret(result);continue;}
   if(pc==u32(0x4bc1f0L)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] copy=e.readMemory(a(src),len);if(copy==null||copy.length!=len)throw new Exception("CRT memcpy src="+hx(src)+" len="+len);log("SERVICE_MEMCPY",pc,"dst="+hx(dst)+";src="+hx(src)+";bytes="+len+";producer="+producing);hostWrite(dst,copy);boolean saved=producing;producing=false;try{ret(dst);}finally{producing=saved;}continue;}
   if(pc==u32(0x4bc1e0L)){int ch=(int)u32(rsp+4)&255;ret((ch>=97&&ch<=122)?ch-32:ch);continue;}
   if(pc==0x00477c20L){log("STUB_nonessential_vehicle_light_registration",pc,"fixture registration omitted; body hierarchy continues");ret(1);continue;}
   if(pc==0x004469a0L){nextGeoReturnPc=u32(rsp);nextGeoName=cstr(u32(rsp+4),32);log("NATIVE_GEO_LOAD_ENTER",pc,"key="+nextGeoName);}
   if(nextGeoReturnPc!=0 && pc==nextGeoReturnPc){realGeoReturns++;log("NATIVE_GEO_LOAD_RETURN",pc,"key="+nextGeoName+";handle="+hx(reg("EAX")));nextGeoReturnPc=0;}
   if(pc==0x00446c90L){realGeoConstructions++;long bp=u32(rsp+4);log("NATIVE_GEO_CONSTRUCTOR",pc,"ptr="+hx(bp)+";magic="+hx(u32(bp))+";vertices="+u32(bp+0x18L)+";faces="+u32(bp+0x1cL));}
   if(isImport(pc,0x4bc26cL)){long ptr=u32(rsp+4);int ch=(int)u32(rsp+8)&255;String name=cstr(ptr,256);int where=name.indexOf(ch);ret(where<0?0:ptr+where);continue;}
   if(isImport(pc,0x4bc0e8L)){retStd(0x2000L,3);continue;}
   if(pc==0x004796a0L||pc==0x00470340L||(pc==0x0044a0b0L&&!producing&&!consuming)){log("STUB_palette_or_render_service",pc,"pc="+hx(pc));ret(0);continue;}
   if(isImport(pc,0x4bc254)){long ptr=u32(rsp+4);String raw=cstr(ptr,256);hostWrite(ptr,(raw.toLowerCase(Locale.ROOT)+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));log("STUB_strlwr",pc,raw);ret(ptr);continue;}
   if(isImport(pc,0x4bc210)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);log("SERVICE_STRICMP",pc,"x="+x+";y="+y+";producer="+producing);boolean saved=producing;producing=false;try{ret(x.equalsIgnoreCase(y)?0:1);}finally{producing=saved;}continue;}
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

   if(pc==0x49c320L){listCount++;log("ORIGINAL_LIST_INSERT",pc,"value="+hx(u32(rsp+12)));}
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
   long writeAt=0;
   if(producing){if(pc==0x458677L)writeAt=reg("EAX")+12;else if(pc==0x458688L)writeAt=reg("EAX")+0x1c;else if(pc==0x458690L)writeAt=reg("EAX")+0x40;else if(pc==0x4901a2L)writeAt=reg("ESI");else if(pc==0x4901afL)writeAt=reg("EAX")+4;else if(pc==0x4903e7L)writeAt=reg("ESI")+8;}
   long qbase=queueSealed?u32(0x654398L):0,bucket=queueSealed?u32(0x654384L):0;
   byte[] qb=queueSealed?e.readMemory(a(qbase),0x200):null;
   byte[] bb=queueSealed&&bucket>=u32(0x6543b0L)&&bucket<u32(0x6543b0L)+49152?e.readMemory(a(bucket),12):null;
   byte[] prepareBefore=nativeReturn!=0?e.readMemory(a(nativeDst),(int)nativeCount*24):null;
   if(!e.step(monitor)){log("ORIGINAL_FAILURE",pc,"error="+e.getLastError()+";registers="+reg("EAX")+","+reg("EBX")+","+reg("ECX")+","+reg("EDX")+","+reg("ESP"));throw new Exception(scenario+" error pc="+hx(pc)+" "+e.getLastError()+" history="+hist);}
   if(prepareBefore!=null)prepareDiff(pc,nativeDst,prepareBefore);
   if(queueSealed){queueDiff(pc,qbase,qb);if(bb!=null)queueDiff(pc,bucket,bb);}
   if(writeAt!=0)log("ORIGINAL_WRITE_RETIRED",pc,"address="+hx(writeAt)+";value="+hx(u32(writeAt)));
  }
  producing=false;consuming=false;
  if(!done)throw new Exception(scenario+" step limit "+hist);
  log("RETURN",target,"eax="+reg("EAX")+";steps="+steps+";builder="+builderCount+";ctor="+ctorCount+";geo="+geoCount+";allocNodes="+nodeAlloc+";allocRuntime="+runtimeAlloc+";nodeFree="+nodeFree+";runtimeFree="+runtimeFree+";parentFirst="+hx(u32(OBJ+0x64))+";runtimeMount0="+hx(u32(RUNTIME+0x3a8))+";runtimeMount1="+hx(u32(RUNTIME+0x3ac))+";firstClass="+u32(FIRST+0x6c)+";secondClass="+u32(SECOND+0x6c)+";firstRef="+u32(FIRST+0xc)+";secondRef="+u32(SECOND+0xc));
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
    if(pc==0x004ba090L){java.math.BigInteger ext=e.readRegister("ST0");int exp=ext.shiftRight(64).and(java.math.BigInteger.valueOf(0x7fffL)).intValue();double mant=ext.and(java.math.BigInteger.ONE.shiftLeft(64).subtract(java.math.BigInteger.ONE)).doubleValue();double v=(exp==0&&mant==0)?0:Math.scalb(mant,exp-16383-63);if(ext.testBit(79))v=-v;int val=(int)v;for(int k=0;k<7;k++)e.writeRegister("ST"+k,e.readRegister("ST"+(k+1)));e.writeRegister("ST7",0);long rsp=reg("ESP"),next=u32(rsp);e.writeRegister("ESP",rsp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",val&0xffffffffL);log("CAMERA_INIT_MATH_BOUNDARY",pc,"converted="+val);continue;}
    if(!e.step(monitor))throw new Exception("Camera initialization failure at "+hx(pc)+" "+e.getLastError());
  }throw new Exception("camera init step limit");
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
 long arenaHeap=0x38000000L,insertReturn,insertRecord;
 String mode;
 void visibilityEvent(long pc,long sp)throws Exception{
  if(pc==0x458086L)log("WORLD_VISIT",pc,"entry="+hx(reg("ECX"))+";owner="+hx(u32(reg("ECX")))+";status="+hx(u32(u32(reg("ECX"))+0x10)));
  if(pc==0x472c10L)log("CULL_INPUT",pc,"view="+hx(u32(sp+4))+";point="+vec(u32(sp+8),3)+";radius="+hx(u32(sp+12)));
  if(pc==0x45829bL)log("CULL_RESULT",pc,"eax="+hx(reg("EAX")));
  if(pc==0x490590L)log("RECORD_PREPARE",pc,"cursor="+hx(u32(0x6543c0L))+";caller="+hx(u32(sp)));
  if(pc==0x458677L)log("KIND6_WRITE",pc,"record="+hx(reg("EAX"))+";owner="+hx(reg("EBX"))+";entry="+hx(reg("ESI")));
  if(pc==0x48fe10L){insertReturn=u32(sp);insertRecord=u32(0x6543c0L);log("INSERT_ENTER",pc,"return="+hx(insertReturn)+";record="+hx(insertRecord)+";depth="+hx(u32(sp+4))+";words="+vec(insertRecord,17));}
  if(insertReturn!=0&&pc==insertReturn){log("INSERT_RETURN",pc,"record="+hx(insertRecord)+";bucket="+hx(u32(0x654384L))+";bucketWords="+vec(u32(0x654384L),3)+";cursor="+hx(u32(0x6543c0L))+";words="+vec(insertRecord,17));insertReturn=0;}
 }
 void prepareDiff(long pc,long base,byte[] b){byte[] after=e.readMemory(a(base),b.length);for(int i=0;i<b.length;i+=4)if(!Arrays.equals(Arrays.copyOfRange(b,i,i+4),Arrays.copyOfRange(after,i,i+4)))log("PREPARE_DWORD",pc,"address="+hx(base+i)+";before="+rawhex(Arrays.copyOfRange(b,i,i+4))+";after="+rawhex(Arrays.copyOfRange(after,i,i+4)));}
 void queueDiff(long pc,long base,byte[] b){byte[] after=e.readMemory(a(base),b.length);for(int i=0;i<b.length;i+=4)if(!Arrays.equals(Arrays.copyOfRange(b,i,i+4),Arrays.copyOfRange(after,i,i+4)))log("QUEUE_DWORD",pc,"address="+hx(base+i)+";before="+rawhex(Arrays.copyOfRange(b,i,i+4))+";after="+rawhex(Arrays.copyOfRange(after,i,i+4)));}
 String rawhex(byte[] b){StringBuilder o=new StringBuilder();for(byte v:b)o.append(String.format("%02x",v&255));return o.toString();}
 void queueSnapshot(String phase)throws Exception{
  long base=u32(0x654398L);log("QUEUE_SNAPSHOT",0,"phase="+phase+";base="+hx(base)+";bytes="+hexbytes(base,0xb8)+";camera="+hexbytes(CAMERA,472));
 }
 void summary(String phase)throws Exception{
  long base=u32(0x6543b0L);int count=0,heads=0;
  for(int j=0;j<4096;j++){long p=base+12L*j;if(u32(p)!=0){heads++;log("BUCKET",0x6543b0L,"phase="+phase+";index="+j+";words="+vec(p,3));}count+=u32(p+8);}
  log("ARENA_GLOBALS",0x6543acL,"phase="+phase+";near="+hx(u32(0x6543acL))+";far="+hx(u32(0x6543a4L))+";worldCount="+u32(0x54a25cL));
  log("ARENA_SUMMARY",0x6543b0L,"phase="+phase+";base="+hx(base)+";heads="+heads+";count="+count+";cursor="+hx(u32(0x6543c0L))+";recordBase="+hx(u32(0x654398L)));
 }
 static final long CAMERA=0x4c2730L; int frame; long cameraSource;
 String hexbytes(long p,int n){StringBuilder b=new StringBuilder();for(byte v:e.readMemory(a(p),n))b.append(String.format(Locale.ROOT,"%02x",v&255));return b.toString();}
 void snapshot(String phase){log("SAMPLE",reg("EIP"),"frame="+frame+";phase="+phase+";camera="+hexbytes(CAMERA,472)+";smooth="+hexbytes(0x4c2964L,24)+hexbytes(0x52b93cL,12)+";root="+hexbytes(OBJ+0x18,64)+";velocity="+hexbytes(u32(OBJ+0x70)+0xd4,12)+";mode="+hx(u32(0x4c2728))+";attachment="+hx(u32(u32(OBJ+0x70)+0x398))+";dt="+hx(u32(0x4fe420))+";angles="+vec(0x536770L,5));}
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


 long nativeReturn,nativeSrc,nativeDst,nativeCount; int nativeCalls;long fallbackSrc,fallbackDst,fallbackCount;
 boolean consuming;long selectedClip,selectedDraw;int builders,submits;long buildReturn;int currentKind;
 void setupRenderScratch(){
  mem(0x2d000000L,0x100000);mem(0x2e000000L,0x200000);
  w32(0x005dd320L,0x2e000000L);w32(0x005dd324L,0x2d000000L);
  log("SUPPLIED_RENDER_SCRATCH",0,"positions=2E000000;records=2D000000;no_queue_writes=true");
 }
 boolean consumerEvent(long pc,long sp)throws Exception{
  if(!consuming)return false;
  if(nativeReturn!=0&&pc==nativeReturn){log("NATIVE_PREPARE_RETURN",pc,"eax="+hx(reg("EAX"))+";src="+hexbytes(nativeSrc,(int)nativeCount*24)+";dst="+hexbytes(nativeDst,(int)nativeCount*24));nativeReturn=0;}
  if(pc>=0x47c8d0L&&pc<=0x47c92fL&&nativeReturn!=0)log("PREPARE_INSTRUCTION",pc,"eax="+hx(reg("EAX"))+";ebx="+hx(reg("EBX"))+";ecx="+hx(reg("ECX"))+";edx="+hx(reg("EDX"))+";esi="+hx(reg("ESI"))+";edi="+hx(reg("EDI"))+";esp="+hx(sp));
  if(pc==0x47bf00L&&pc!=selectedClip){fallbackSrc=u32(sp+12);fallbackDst=u32(sp+8);fallbackCount=u32(sp+16);log("FALLBACK_ORIGINAL_ENTER",pc,"count="+fallbackCount+";return="+hx(u32(sp))+";viewport="+vec(u32(u32(sp+4)+0x3c),16)+";src="+hexbytes(fallbackSrc,(int)fallbackCount*24)+";dst="+hexbytes(fallbackDst,(int)fallbackCount*24));}
  if(pc==0x47214cL)log("FALLBACK_ORIGINAL_RETURN",pc,"eax="+hx(reg("EAX"))+";src="+hexbytes(fallbackSrc,(int)fallbackCount*24)+";dst="+hexbytes(fallbackDst,(int)fallbackCount*24));
  if(pc==0x4720a8L||pc==0x472145L||pc==0x4721acL)log("DISPATCH_CALL",pc,"index="+hx(reg(pc==0x4721acL?"EDX":"EBX"))+";target="+hx(u32((pc==0x4721acL?0x4f8d38L:0x4f9538L)+4*reg(pc==0x4721acL?"EDX":"EBX")))+";args="+vec(sp,5));
  if(pc==0x47c8d0L){nativeCalls++;nativeReturn=u32(sp);nativeSrc=u32(sp+12);nativeDst=u32(sp+8);nativeCount=u32(sp+16);log("NATIVE_PREPARE_ENTER",pc,"kind="+currentKind+";return="+hx(nativeReturn)+";view="+hx(u32(sp+4))+";srcPtr="+hx(nativeSrc)+";dstPtr="+hx(nativeDst)+";count="+nativeCount+";flags="+hx(u32(sp+20))+";viewport="+vec(u32(u32(sp+4)+0x3c),16)+";viewBytes="+hexbytes(u32(sp+4),472)+";src="+hexbytes(nativeSrc,(int)nativeCount*24)+";dst="+hexbytes(nativeDst,(int)nativeCount*24));}

  if(buildReturn!=0&&pc==buildReturn){log("GEO_BUILD_RETURN",pc,"transformedVertices="+hexbytes(0x2e000000L,16*12)+";cursor="+hx(u32(0x54acbcL))+";tree="+hx(u32(0x54ad28L))+";bytes="+(u32(0x54acbcL)-0x2d000000L));for(long p=0x2d000000L;p<u32(0x54acbcL);){long count=u32(p+4);log("GEO_OUTPUT",pc,"record="+hx(p)+";count="+count+";owner="+hx(u32(p+8))+";flags="+hx(u32(p+0x20))+";plane="+vec(p+0x30,4)+";vertices="+(count>0?hexbytes(p+0x48,(int)count*24):"none"));if(count>200)throw new Exception("record count");p+=72+24*count;}buildReturn=0;}

  if(pc==0x48f4c0L||pc==0x490640L){currentKind=(int)u32(u32(sp+4)+12);log("CONSUME_RECORD",pc,"record="+hx(u32(sp+4))+";view="+hx(u32(sp+8))+";words="+vec(u32(sp+4),17));}
  if(pc==0x45d100L||pc==0x45d530L)log("GEO_TRAVERSAL",pc,"record="+hx(u32(sp+4))+";view="+hx(u32(sp+8)));
  if(pc==0x45cbe0L){buildReturn=u32(sp);builders++;long owner=u32(sp+4),geo=u32(owner+0x5c),vp=u32(geo+0xc),vc=u32(geo+4);StringJoiner chain=new StringJoiner(",");for(long cur=u32(OBJ+0x64);cur!=0;cur=u32(cur+0x60)){chain.add(hx(cur));if(chain.length()>1000)throw new Exception("sibling cycle");}

   log("GEO_SOURCE",pc,"owner="+hx(owner)+";root="+hx(OBJ)+";rootChildren="+chain+";geometry="+hx(geo)+";vertexCount="+vc+";vertices_sha256="+sha(e.readMemory(a(vp),(int)vc*12))+";matrix="+hexbytes(u32(sp+8),64));
   for(long sec=u32(geo+0x14);sec!=0;sec=u32(sec+0x30))log("GEO_SECTION",pc,"address="+hx(sec)+";count="+u32(sec+4)+";material="+cstr(sec+0x20,16));log("GEO_BUILD",pc,"owner="+hx(owner)+";geometry="+hx(u32(owner+0x5c))+";matrix="+hx(u32(sp+8))+";view="+hx(u32(sp+12)));}
  if(pc==0x44a290L)log("MATERIAL_LOOKUP",pc,"kind="+currentKind+";owner="+hx(u32(sp+4))+";name="+cstr(u32(sp+8),20));
  if(pc==0x471fd0L){submits++;long flags=u32(sp+20),ix=flags&0x1ff;selectedClip=u32(0x4f9538L+ix*4);selectedDraw=u32(0x4f8d38L+ix*4);log("POLYGON_WRAPPER",pc,"kind="+currentKind+";count="+u32(sp+12)+";vertices="+hexbytes(u32(sp+8),(int)u32(sp+12)*24)+";texture="+hx(u32(sp+16))+";flags="+hx(flags)+";clip="+hx(selectedClip)+";draw="+hx(selectedDraw));}
  if((pc==selectedClip&&pc!=0&&pc!=0x47c8d0L)){long src=u32(sp+12),dst=u32(sp+8),count=u32(sp+16);if(count>100)throw new Exception("clip count");log("SERVICE_CLIP",pc,"count="+count);if(count>0)hostWrite(dst,e.readMemory(a(src),(int)count*24));ret(count);return true;}
  if(pc==selectedDraw&&pc!=0){log("SERVICE_DRAW",pc,"count="+u32(sp+12)+";vertices="+hexbytes(u32(sp+8),(int)u32(sp+12)*24));ret(1);return true;}
  if(pc==0x4474b0L||pc==0x471980L||pc==0x447b20L||pc==0x471b70L){log("SERVICE_TEXTURE",pc,"arg="+hx(u32(sp+4)));ret(0);return true;}
  return false;
 }
 void experiment(String dir)throws Exception{
  scenario=mode;resourceBytes.clear();resourcePtrs.clear();
  try(var ds=Files.newDirectoryStream(Paths.get(dir))){List<Path> paths=new ArrayList<>();for(Path p:ds)if(Files.isRegularFile(p)&&!p.toString().endsWith(".json"))paths.add(p);paths.sort(Comparator.comparing(p->p.getFileName().toString()));for(Path p:paths)resourceBytes.put(p.getFileName().toString().toLowerCase(Locale.ROOT),Files.readAllBytes(p));}
  reset(resourceBytes.get("nobus1.vcf"),"nobus1.vcf");
  try{
   runCall(0x493c50L);
   if(!mode.equals("empty")){
    createNativeRoot();runNativeSpawnStatus();int idx=0;
    for(var kv:resourceBytes.entrySet()){long p=0x32000000L+(idx++*0x20000L);mem(p,kv.getValue().length+32);hostWrite(p,kv.getValue());resourcePtrs.put(kv.getKey(),p);}
    runCall(LOADER,0,CTX,NAME);
    // Explicit controlled root pose, before original registration computes bounds.
    double z=0;long bits=Double.doubleToRawLongBits(z);w32(OBJ+0x50,bits);w32(OBJ+0x54,bits>>>32);
    log("CONTROLLED_POSE",0,"root="+hx(OBJ)+";z="+z+";basis="+vec(OBJ+0x18,9));
    runCall(0x4572b0L,OBJ,0,0);registeredEntry=reg("EAX");
    log("WORLD_REGISTERED",0x4572b0L,"entry="+hx(registeredEntry)+";words="+vec(registeredEntry,30)+";root="+hx(OBJ)+";class="+u32(OBJ+0x6c)+";count="+u32(0x54a25cL));
   }
   initializeCameraNative();
   if(registeredEntry!=0){
    w32(0x4c2908L,registeredEntry);w32(0x536770L,1);w32(0x536778L,1);w32(0x536780L,1);w32(0x4fe420L,Float.floatToRawIntBits(0.016f));
    long rt=u32(OBJ+0x70);for(int i=0;i<3;i++)w32(rt+0xd4+4*i,Float.floatToRawIntBits(new float[]{2,0,1}[i]));
    for(frame=0;frame<2;frame++){snapshot("before");cameraCall();snapshot("after");}
   }
   viewSealed=true;
   if(registeredEntry!=0){long light=u32(u32(0x26000000L+0x70)+0x440);log("PREBIND_CAMERA_LIGHT",0x4466c0L,"owner="+hx(light)+";variant=4");runCall(0x4466c0L,light,4);}
   if(registeredEntry!=0 && !mode.equals("camera_only")){
    // A second original stock bus is the unselected visibility target. Keep selected camera owner untouched.
    OBJ=0x26100000L;CTX=OBJ+0x2000;RUNTIME=OBJ+0x4000;NAME=OBJ+0x7000;
    mem(OBJ,0x30000);w32(CTX,OBJ);w32(CTX+4,RUNTIME);w32(WDFCTX,CTX);hostWrite(NAME,"nobus1.vcf\0".getBytes());
    selected=false;createNativeRoot();runNativeSpawnStatus();runCall(LOADER,0,CTX,NAME);
    float[] basis={0,0,-1,0,1,0,1,0,0};for(int i=0;i<9;i++)w32(OBJ+0x18+4*i,Float.floatToRawIntBits(basis[i]));
    double z=mode.equals("behind")?-50.0:50.0;long bits=Double.doubleToRawLongBits(z);w32(OBJ+0x50,bits);w32(OBJ+0x54,bits>>>32);log("CONTROLLED_TARGET_POSE",0,"z="+z+";root="+hexbytes(OBJ+0x18,64));
    runCall(0x4572b0L,OBJ,0,0);registeredEntry=reg("EAX");log("TARGET_REGISTERED",0x4572b0L,"entry="+hx(registeredEntry)+";words="+vec(registeredEntry,30)+";root="+hx(OBJ)+";count="+u32(0x54a25cL));
   }
   setupRenderScratch();log("VIEW_RECORD",0x4c2730L,"words="+vec(0x4c2730L,118));
   runCall(0x48f9b0L);w32(0x6543a4L,Float.floatToRawIntBits(4095f));summary("before");sealedEnd=arenaHeap;queueSealed=true;log("QUEUE_SEALED",0,"start=38000000;end="+hx(sealedEnd)+";globals=00654380..006543C7");
   runCall(0x457ff0L,0x4c2730L);summary("after");queueSnapshot("produced");
   runCall(0x48fac0L,0x4c2730L,0);summary("consumed");queueSnapshot("consumed");log("HOST_WRITE_GUARD",0,"violations=0;writes_checked="+hostWrites);
   if(registeredEntry!=0)log("WORLD_AFTER",registeredEntry,"words="+vec(registeredEntry,30));
   log("PRODUCER_COMPLETE",0x457ff0L,"worldCount="+u32(0x54a25cL));
  }finally{e.dispose();}
 }
 @Override public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5 mismatch");
  String[] args=getScriptArgs();mode=args[2];if(!Arrays.asList("visible","behind","empty","camera_only").contains(mode))throw new Exception("unknown mode");selected=true;nativeRoot=true;nativeRegistry=true;
  try(PrintWriter writer=new PrintWriter(args[1])){trace=writer;trace.println("scenario\tkind\tpc\tdetail");experiment(args[0]);}
 }
}
