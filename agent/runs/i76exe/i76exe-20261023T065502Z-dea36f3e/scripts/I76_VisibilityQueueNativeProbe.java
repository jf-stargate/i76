import ghidra.app.script.GhidraScript;
import ghidra.app.emulator.EmulatorHelper;
import ghidra.program.model.address.Address;
import java.io.*;
import java.nio.file.*;
import java.util.*;
public class I76_VisibilityQueueNativeProbe extends GhidraScript {
 static final long LOADER=0x4ad6f0L,PARSE=0x4b41e0L,VCFC=0x4ad950L,SPEC=0x4ade50L,WEPN=0x4aeb90L,WDFFN=0x4ae5e0L,EXIT=0x4b4290L;
 static final long OBJ=0x26000000L,CTX=0x26002000L,RUNTIME=0x26004000L,NAME=0x26007000L,FILE=0x25000000L;
 static final long WDFCTX=0x26009000L,FIRST=0x26010000L,SECOND=0x26011000L,FRT=0x26012000L,SRT=0x26013000L,NODES=0x26020000L;
 static final long STACK=0x30020000L,SENT=0x70000000L; static final int LIMIT=5000000;
 EmulatorHelper e;PrintWriter trace;byte[] bytes;String scenario,wdfName;boolean inRaster,inTraversal,inProducer,acceptVisibility;int visibilityCalls,producerRecordAllocs,producerBins,producerSecondary,producerPrimary; boolean consumerFromProducer=false; long pendingVisReturnPc=0;long selectedClip,selectedDraw;int sceneSubmissions,sceneSectionBuilds,sceneTextures;int nativeBuilderEntries,nativeBuilderReturns,nativeTextureLookups,textureLoaderBoundaries,geometryRecordCount,nativeSubmitCalls,clipBoundaryCalls,drawBoundaryCalls, steps, n_vcfc,n_spec,n_wepn,n_weapon,n_nested,n_open,n_openfail,n_free;int failNested,failWeapon,failWeaponChunk,failGeo,builderCount,ctorCount,listCount,geoCount, nodeAlloc, runtimeAlloc, failNode, nodeFree, runtimeFree, classReleases, partAlloc, cacheBindings,cacheAlloc;boolean failOpen;long nextGeoReturnPc, firstMaterialReturnPc, firstMaterialOwner;String nextGeoName="",firstMaterialKey="",firstMaterialResource="";String firstError="";int caughtReporter,extraAlloc,materialBinds,nativeMaterialSuccess,realGeoConstructions,realGeoReturns,bodyParts,bodyNodeStart;long bodyBankZero;Map<String,byte[]> resourceBytes=new LinkedHashMap<>();Map<String,Long> resourcePtrs=new LinkedHashMap<>(); long genericHeapCursor=0x36000000L;
 Address a(long v){return toAddr(v&0xffffffffL);}
 String hx(long v){return String.format(Locale.ROOT,"%08X",v&0xffffffffL);}
 long reg(String n){return e.readRegister(n).longValue()&0xffffffffL;}
 long u32(long p){byte[] b=e.readMemory(a(p),4);if(b==null||b.length!=4)throw new IllegalStateException("invalid read="+hx(p));return (((long)b[0]&255)|(((long)b[1]&255)<<8)|(((long)b[2]&255)<<16)|(((long)b[3]&255)<<24))&0xffffffffL;}
 void w32(long p,long v){e.writeMemoryValue(a(p),4,v&0xffffffffL);}
 void mem(long p,int n){e.writeMemory(a(p),new byte[n]);}
 String cstr(long p,int max){StringBuilder b=new StringBuilder();for(int i=0;i<max;i++){byte[] x=e.readMemory(a(p+i),1);if(x==null||x.length<1){b.append("?");break;}if(x[0]==0)break;b.append((char)(x[0]&255));}return b.toString();}
 void log(String kind,long pc,String detail){trace.println(scenario+"\t"+kind+"\t"+hx(pc)+"\t"+detail);}
 void ret(long value){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void retStd(long value,int nargs){long sp=reg("ESP");long next=u32(sp);e.writeRegister("ESP",sp+4+4*nargs);e.writeRegister("EIP",next);e.writeRegister("EAX",value);}
 void reset(byte[] content,String file){e=new EmulatorHelper(currentProgram);bytes=content;
  mem(STACK-0x10000L,0x10800);mem(OBJ,0x800);mem(CTX,0x100);mem(RUNTIME,0x3000);mem(NAME,0x100);
  mem(FILE,Math.max(content.length,0x1000));e.writeMemory(a(FILE),content);mem(WDFCTX,0x200);mem(FIRST,0x1000);mem(SECOND,0x1000);mem(FRT,0x1000);mem(SRT,0x1000);mem(NODES,0x2000);mem(0x27000000L,0x20000);mem(0x28000000L,0x180000);mem(0x29000000L,0x20000);mem(0x2a000000L,0x10000);mem(0x2b000000L,0x200000);mem(0x36000000L,0x800000);
  e.writeMemory(a(NAME),(file+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));
  w32(CTX,OBJ);w32(CTX+4,RUNTIME);w32(WDFCTX,CTX);w32(OBJ+0x70,RUNTIME);w32(FIRST+0xc,1);w32(SECOND+0xc,1);w32(0x54ad34L,0x12350000L);w32(0x54ad38L,0x12340000L);w32(0x54ad2cL,OBJ);w32(0x54ad30L,OBJ);for(int k=0;k<4;k++)w32(0x54b204L+k*4,0);w32(OBJ+0x6c,1);w32(OBJ+0xc,1);w32(0x005db97cL,0);w32(0x005db980L,0);
  w32(0x006562c4L,0);w32(0x005dabc0L,1); // not geometry-family mode
  for(String r:new String[]{"EAX","EBX","ECX","EDX","ESI","EDI","EBP"})e.writeRegister(r,0);
  e.writeRegister("DF",0);
  materialBinds=0;nativeMaterialSuccess=0;realGeoConstructions=0;realGeoReturns=0;nextGeoReturnPc=0;firstMaterialReturnPc=0;firstMaterialOwner=0;nextGeoName="";firstMaterialKey="";firstMaterialResource="";bodyParts=0;bodyNodeStart=0;bodyBankZero=0;genericHeapCursor=0x36000000L;n_vcfc=0;n_spec=0;n_wepn=0;n_weapon=0;n_nested=0;n_open=0;n_openfail=0;n_free=0;failNested=0;failWeapon=0;failWeaponChunk=0;failOpen=false;caughtReporter=0;firstError="";builderCount=0;ctorCount=0;listCount=0;geoCount=0;failGeo=0;nodeAlloc=0;runtimeAlloc=0;failNode=0;nodeFree=0;runtimeFree=0;classReleases=0;partAlloc=0;cacheBindings=0;cacheAlloc=0;
 }
 boolean isImport(long pc,long slot){return pc!=0&&pc==u32(slot);}
 void setupRenderMemory(){
  mem(0x2c000000L,0x4000);mem(0x2d000000L,0x100000);mem(0x2e000000L,0x200000);
  long ctx=0x2c000000L;for(int i=0;i<16;i++){
   w32(ctx+4L*i,(i==0||i==5||i==10||i==15)?0x3f800000L:0);
   w32(ctx+0x40L+4L*i,(i==0||i==5||i==10||i==15)?0x3f800000L:0);
  }
  w32(0x0054acb8L,0x2e000000L);w32(0x0054acbcL,0x2d000000L);
  w32(0x0054ad28L,0);w32(0x0054acc8L,ctx);w32(0x005dd320L,0x2e000000L);w32(0x005dd324L,0x2d000000L);
  mem(0x3b000000L,0x10000);w32(0x3b001000L,0x12345678L);w32(0x3b001004L,0x00000002L);
  w32(0x2c00003cL,0x3b00c000L);nativeBuilderEntries=nativeBuilderReturns=nativeTextureLookups=textureLoaderBoundaries=geometryRecordCount=nativeSubmitCalls=clipBoundaryCalls=drawBoundaryCalls=0;inRaster=false;inTraversal=false;sceneSubmissions=sceneSectionBuilds=sceneTextures=0;
 }
 void inspectRealSections(long body,String resource) throws Exception {
  long geo=u32(body+0x5cL),first=u32(geo+0x14L),cur=first;int cnt=0;
  while(cur!=0&&cnt<400){long next=u32(cur+0x30L),count=u32(cur+4L);
   String name=cstr(cur+0x20L,16);
   log("RETAIL_GEO_SECTION",0x45cbe0L,"geometry="+resource+";section="+cnt+";source="+hx(cur)+";corners="+count+";material="+name+";flags="+hx(u32(cur+0x1cL))+";next="+hx(next));
   cnt++;cur=next;
  }if(cur!=0||cnt==0)throw new Exception("invalid GEO section chain "+resource+" count="+cnt);
  log("RETAIL_GEO_SECTION_COUNT",0x45cbe0L,"geometry="+resource+";sections="+cnt+";vertexCount="+u32(geo+4L));
 }
 void runRealSectionPreparation(long body,String resource) throws Exception {
  setupRenderMemory();inspectRealSections(body,resource);
  long start=u32(0x54acbcL);
  log("RENDER_NATIVE_START",0x45cbe0L,"body="+hx(body)+";geo="+hx(u32(body+0x5cL))+";scratch="+hx(start));
  runCall(0x0045cbe0L,body,body+0x18L,0x2c000000L);
  long end=u32(0x54acbcL),root=u32(0x54ad28L);
  if(end<=start||end>0x2d100000L)throw new Exception("no valid render record output "+hx(end));
  long rec=start;int index=0;
  while(rec<end&&index<400){long n=u32(rec+4L),stride=0x48L+n*0x18L;
    if(n>2048||rec+stride>end)throw new Exception("bad render stride "+hx(rec)+" n="+n+" end="+hx(end));
    String name=cstr(rec+0xcL,16);long flags=u32(rec+0x20L),owner=u32(rec+8L);
    if(n>0&&owner!=body)throw new Exception("render owner mismatch "+hx(owner)+" / "+hx(body));
    log("REAL_GEO_RENDER_RECORD",0x45cbe0L,"ordinal="+index+";record="+hx(rec)+";owner="+hx(owner)+";name="+name+";corners="+n+";stride="+stride+";flags="+hx(flags)+";nextA="+hx(u32(rec+0x40L))+";nextB="+hx(u32(rec+0x44L)));
    if(n>=3&&name.length()>0&&(flags&4)!=0){
       long h=0;for(int q=0;q<name.length();q++)h=((h*2)^(name.charAt(q)&0xdf))&0xffffffffL;
       h=(((h^body)*0x6cdL+0xaabL)&0xffffffffL)%0x7edL;
       long node=u32(0x00533fa0L+4*h),matched=0;
       for(int q=0;q<100&&node!=0;q++){if(u32(node)==body && cstr(node+0x14L,16).equalsIgnoreCase(name)){matched=node;break;}node=u32(node+0x40L);}
       long tmt=matched==0?0:u32(matched+0x30L),frames=tmt==0?0:u32(tmt+0x2cL);
       log("REAL_RENDER_OWNER_TMT_SLOT",0x44a290L,"owner="+hx(body)+";name="+name+";slot="+hx(matched)+";tmt="+hx(tmt)+";tmtName="+(tmt==0?"none":cstr(tmt,16))+";frame0="+(frames==0?"none":cstr(frames,16)));
       // Native material binder with actual object instance, name and TMT slots; VQM payload service substituted.
       runCall(0x0044a290L,body,rec+0xcL,0);
       log("REAL_RECORD_TEXTURE_RESULT",0x44a290L,"record="+hx(rec)+";material="+name+";result="+hx(reg("EAX")));
       nativeTextureLookups++;
       long clipIndex=flags&0x1ffL,texture=reg("EAX");
       if(texture!=0){
         selectedClip=u32(0x004f9538L+clipIndex*4);selectedDraw=u32(0x004f8d38L+clipIndex*4);
         log("NATIVE_RASTER_DISPATCH_SELECTED",0x471fd0L,"record="+hx(rec)+";flags="+hx(flags)+";clipIndex="+clipIndex+";clipTarget="+hx(selectedClip)+";drawTarget="+hx(selectedDraw));
         if(selectedClip==0||selectedDraw==0)throw new Exception("missing original raster dispatch target");
         inRaster=true;
         try{runCall(0x00471fd0L,0x2c000000L,rec+0x48L,n,texture,flags);}finally{inRaster=false;}
         nativeSubmitCalls++;
         log("RETAIL_POLYGON_SUBMIT_RETURN",0x471fd0L,"record="+hx(rec)+";result="+hx(reg("EAX"))+";clipCalls="+clipBoundaryCalls+";drawCalls="+drawBoundaryCalls);
       }
    }
    rec+=stride;index++;
  }
  if(rec!=end)throw new Exception("render record cursor discrepancy");
  geometryRecordCount+=index;
  log("REAL_GEO_RENDER_COMPLETE",0x45cbe0L,"geometry="+resource+";count="+index+";root="+hx(root)+";renderBytes="+(end-start)+";textureCalls="+nativeTextureLookups+";vqmLoaderStubCalls="+textureLoaderBoundaries+";originalSubmitCalls="+nativeSubmitCalls+";clipStubCalls="+clipBoundaryCalls+";drawStubCalls="+drawBoundaryCalls);
 }
 void runNativeSceneTraversal(long body,String label,int variant,int mode)throws Exception {
   setupRenderMemory();
   long component=0x2c002000L,ctx=0x2c000000L;
   // Native geometry dispatcher consumes component+0x1c and branches on component+0x38.
   // Use the same original body pointer/geometry and camera identity as the earlier GEO probe.
   w32(component+0x1cL,body);w32(component+0x30L,variant);w32(component+0x34L,0);
   w32(component+0x38L,mode==1?1:0);w32(component+0x3cL,0);
   long before=u32(body+0x5cL);
   inTraversal=true;
   log("NATIVE_SCENE_TRAVERSAL_BEGIN",0x48f4c0L,"vehicle="+label+";component="+hx(component)+";body="+hx(body)+";variant="+variant+";mode="+mode+";beforeGeo="+hx(before));
   try{runCall(0x0048f4c0L,component,ctx);}finally{inTraversal=false;inRaster=false;}
   long end=u32(0x54acbcL),root=u32(0x54ad28L);
   log("NATIVE_SCENE_TRAVERSAL_END",0x48f4c0L,"vehicle="+label+";variant="+variant+";mode="+mode+";afterGeo="+hx(u32(body+0x5cL))+";root="+hx(root)+";end="+hx(end)+";createdBytes="+(end-0x2d000000L)+";nativeBuilders="+sceneSectionBuilds+";textureLookups="+sceneTextures+";submissions="+sceneSubmissions+";clipStubs="+clipBoundaryCalls+";drawStubs="+drawBoundaryCalls);
   if(end<0x2d000000L||end>0x2d100000L)throw new Exception("bad native scene scratch cursor");
   if(mode==1 && sceneSectionBuilds==0)throw new Exception("primary pass did not construct any GEO sections");
 }
 void runNativeSpatialBucketFlush(long body,String label)throws Exception {
  setupRenderMemory();
  long ctx=0x2c000000L,buckets=0x2e100000L,rec=0x2e180000L;
  // One synthetic queue envelope with authentic original subtype-6 fields and actual VCF body pointer.
  // This tests original bucket consumption, not real visibility/culling production.
  w32(rec,0);w32(rec+0xcL,6);w32(rec+0x14L,0);w32(rec+0x1cL,body);
  w32(rec+0x30L,0);w32(rec+0x34L,0);w32(rec+0x38L,1);w32(rec+0x3cL,0);
  w32(buckets,rec);w32(buckets+4L,rec);w32(buckets+8L,1);
  w32(0x006543b0L,buckets);w32(0x006543a4L,Float.floatToRawIntBits(4096.0f));w32(0x006543acL,0);
  w32(0x006543b4L,0);w32(0x006543a0L,0);w32(0x0059c498L,0);w32(0x0059c540L,0);
  inTraversal=true;
  log("NATIVE_BUCKET_FLUSH_BEGIN",0x48fac0L,"vehicle="+label+";workRecord="+hx(rec)+";body="+hx(body)+";bucket="+hx(buckets)+";type=6;depth=0");
  try{runCall(0x0048fac0L,ctx,0);}finally{inTraversal=false;inRaster=false;}
  log("NATIVE_BUCKET_FLUSH_END",0x48fac0L,"vehicle="+label+";entriesAfter="+u32(buckets+8L)+";headAfter="+hx(u32(buckets))+";submissions="+sceneSubmissions+";clipStubs="+clipBoundaryCalls+";drawStubs="+drawBoundaryCalls+";builders="+sceneSectionBuilds);
  if(sceneSectionBuilds!=1 || sceneSubmissions!=1 || clipBoundaryCalls!=1 || drawBoundaryCalls!=1)throw new Exception("native bucket did not render known body section");
 }

 void putDouble(long p,double val){long bits=Double.doubleToRawLongBits(val);for(int i=0;i<8;i++)e.writeMemoryValue(a(p+i),1,(bits>>(8*i))&255);}
 void putFloat(long p,float val){w32(p,Float.floatToRawIntBits(val)&0xffffffffL);}
 void producerExperiment(long body,String label,boolean visible)throws Exception{
   setupRenderMemory();
   long ctx=0x2c000000L,entry=0x00542830L,recordStart=0x2e180000L,buckets=0x2e100000L;
   mem(recordStart,0x20000);mem(buckets,0xc000);
   for(int i=0;i<0x78;i+=4)w32(entry+i,0);
   w32(0x0054a25cL,1);w32(entry,body);
   putFloat(entry+0x10L,1.0f);w32(entry+0x30L,1);putFloat(entry+0x24L,1.0f);
   // Original world-object transform is used; camera view matrix is synthetic.
   putFloat(ctx+8L,1.0f);putDouble(ctx+0x68L,0.0);putDouble(ctx+0x70L,0.0);putDouble(ctx+0x78L,100.0);
   for(int i=0;i<12;i++)putFloat(ctx+0x40L+i*4,0.0f);
   for(int i=0;i<3;i++)putFloat(ctx+0x40L+i*0x14L,1.0f);
   putFloat(ctx+0xfcL,visible?0.0f:-1000.0f); w32(0x006543c0L,recordStart);w32(0x0065439cL,recordStart);w32(0x00654398L,recordStart);
   w32(0x006543b0L,buckets);w32(0x006543a4L,Float.floatToRawIntBits(4096.0f));w32(0x006543acL,Float.floatToRawIntBits(label.startsWith("gtsi")?99.0f:100.0f));
   w32(0x006543b4L,0);w32(0x006543a0L,0);w32(0x0059c540L,0);
   w32(0x004c2724L,0);w32(0x004c2908L,0);w32(0x0054a264L,0);
   w32(0x00654b86L,0);w32(0x00654b89L,0);
   long oldstatus=u32(body+0x10L);w32(body+0x10L,oldstatus&~0x100L);
   visibilityCalls=producerRecordAllocs=producerBins=producerSecondary=producerPrimary=0;inProducer=true;acceptVisibility=visible;
   log("PRODUCER_BEGIN",0x457ff0L,"label="+label+";body="+hx(body)+";eligibleClass="+u32(body+0x6cL)+";visible="+visible+";cameraOffsetZ=100;activeEntry="+hx(entry));
   try{runCall(0x00457ff0L,ctx);}finally{inProducer=false;w32(body+0x10L,oldstatus);}
   int bins=0,records=0;long first=0;for(int i=0;i<0x1000;i++){long ptr=u32(buckets+12L*i),n=u32(buckets+12L*i+8L);if(n!=0){bins++;records+=n;if(first==0)first=ptr;log("PRODUCER_BUCKET",0x48fe10L,"bin="+i+";head="+hx(ptr)+";count="+n);if(bins>10)break;}}
   long cursor=u32(0x006543c0L);
   log("PRODUCER_END",0x457ff0L,"label="+label+";visible="+visible+";visibilityCalls="+visibilityCalls+";recordAllocations="+producerRecordAllocs+";binCalls="+producerBins+";cursor="+hx(cursor)+";buckets="+bins+";records="+records+";first="+hx(first));
   if(visibilityCalls<1)throw new Exception("visibility classifier not reached "+label);
   if(visible && (producerRecordAllocs<1||producerBins<1))throw new Exception("visible record not produced");
   if(!visible && (producerRecordAllocs!=0||producerBins!=0||records!=0))throw new Exception("culled record was queued");
   if(visible && records<1)throw new Exception("original bin did not accept record");
   if(visible){
      if(first==0||u32(first+0xcL)!=6||u32(first+0x1cL)!=body)throw new Exception("bad native produced kind6 record");
      log("ORIGINAL_PRODUCER_RECORD",0x457ff0L,"type="+u32(first+0xcL)+";owner="+hx(u32(first+0x1cL))+";activeEntry="+hx(u32(first+0x40L))+";depth="+hx(u32(first+0x10L))+";flags="+hx(u32(first+0x34L))+";dispatchMode="+u32(first+0x38L));
      inTraversal=true;consumerFromProducer=true;sceneSubmissions=sceneSectionBuilds=sceneTextures=0;
      log("NATIVE_PRODUCER_CONSUMER_BEGIN",0x48fac0L,"label="+label+";bucketRecords="+records);
      try{runCall(0x0048fac0L,ctx,0);}finally{inTraversal=false;inRaster=false;consumerFromProducer=false;}
      int after=0;for(int i=0;i<4096;i++)after+=u32(buckets+12L*i+8L);
      log("NATIVE_PRODUCER_CONSUMER_END",0x48fac0L,"label="+label+";bucketRecordsRemaining="+after+";sceneBuilds="+sceneSectionBuilds+";secondaryPasses="+producerSecondary+";primaryPasses="+producerPrimary+";submissions="+sceneSubmissions+";textures="+sceneTextures);
      if(after!=0||producerSecondary!=1||producerPrimary!=0)throw new Exception("native producer work did not dispatch once to secondary");
   }

 }
 void runCall(long target,long...args)throws Exception {
  long sp=STACK-0x3000L;w32(sp,SENT);for(int i=0;i<args.length;i++)w32(sp+4+4*i,args[i]);e.writeRegister("ESP",sp);e.writeRegister("EIP",target);
  ArrayDeque<String> hist=new ArrayDeque<>();boolean done=false;
  for(int n=0;n<LIMIT;n++){
   long pc=reg("EIP"),rsp=reg("ESP");steps=n;
   if(pc==SENT){done=true;break;}
   if(inProducer && pc==0x00477ed0L){log("PRODUCER_STUB_PALETTE_UNLOCK",pc,"render side-effect omitted");ret(0);continue;}
   if(inProducer && pc==0x00407930L){log("PRODUCER_STUB_CAMERA_MODE",pc,"false");ret(0);continue;}
   if(inProducer && pc==0x00472c10L){visibilityCalls++;pendingVisReturnPc=u32(rsp);log("PRODUCER_NATIVE_VISIBILITY_ENTER",pc,"entry="+hx(u32(0x00542830L))+";frustumOffset="+(acceptVisibility?0:-1000));}
   if(inProducer && pendingVisReturnPc!=0 && pc==pendingVisReturnPc){log("PRODUCER_NATIVE_VISIBILITY_RESULT",pc,"eax="+hx(reg("EAX"))+";signed="+(int)reg("EAX"));pendingVisReturnPc=0;}
   if(inProducer && pc==0x00490590L){producerRecordAllocs++;log("PRODUCER_NATIVE_RECORD_ALLOC_ENTER",pc,"cursor="+hx(u32(0x006543c0L)));}
   if(inProducer && pc==0x0048fe10L){producerBins++;log("PRODUCER_NATIVE_BIN_ENTER",pc,"record="+hx(u32(0x006543c0L))+";type="+u32(u32(0x006543c0L)+0xcL));}
   if(consumerFromProducer && pc==0x0045d530L)producerSecondary++;
   if(consumerFromProducer && pc==0x0045d100L)producerPrimary++;
   if(inProducer && pc==0x00477ac0L){log("PRODUCER_STUB_HEADLIGHT_CONTEXT",pc,"false");ret(0);continue;}
   if((inRaster||inTraversal) && pc==selectedClip){clipBoundaryCalls++;long src=u32(rsp+12L),dst=u32(rsp+8L),count=u32(rsp+16L);long flags=u32(rsp+20L);
     if(count>100)throw new Exception("unreasonable clipped vertex count");
     log("STUB_RASTER_CLIP_PREPARE",pc,"source="+hx(src)+";dest="+hx(dst)+";inputCount="+count+";flags="+hx(flags));
     if(count!=0){byte[] raw=e.readMemory(a(src),(int)count*24);e.writeMemory(a(dst),raw);}
     ret(count);continue;}
   if((inRaster||inTraversal) && pc==selectedDraw){drawBoundaryCalls++;log("STUB_RASTER_DRAW_SUBMIT",pc,"context="+hx(u32(rsp+4L))+";vertices="+u32(rsp+12L)+";texture="+hx(u32(rsp+16L)));ret(1);continue;}
   if(inTraversal && pc==0x0044a290L){sceneTextures++;log("SCENE_MATERIAL_BIND_ENTER",pc,"owner="+hx(u32(rsp+4L))+";name="+cstr(u32(rsp+8L),20));}
   if(inTraversal && pc==0x00471fd0L){sceneSubmissions++;long flags=u32(rsp+20L),ix=flags&0x1ffL;selectedClip=u32(0x004f9538L+ix*4);selectedDraw=u32(0x004f8d38L+ix*4);log("SCENE_NATIVE_SUBMIT_ENTER",pc,"count="+u32(rsp+12L)+";texture="+hx(u32(rsp+16L))+";flags="+hx(flags)+";index="+ix+";clip="+hx(selectedClip)+";draw="+hx(selectedDraw));if(selectedClip==0||selectedDraw==0)throw new Exception("missing native renderer callback");}
   if(inTraversal && pc==0x0048f4c0L){log("SCENE_NATIVE_DISPATCH",pc,"component="+hx(u32(rsp+4L))+";view="+hx(u32(rsp+8L)));}
   if(inTraversal && (pc==0x0045d100L || pc==0x0045d530L)){log("SCENE_ORIGINAL_TREE_ENTRY",pc,"componentRecord="+hx(u32(rsp+4L))+";context="+hx(u32(rsp+8L)));}
   if(pc==0x45cbe0L){if(inTraversal)sceneSectionBuilds++;nativeBuilderEntries++;log("NATIVE_GEO_SECTION_BUILDER_ENTER",pc,"owner="+hx(u32(rsp+4))+";geometry="+hx(u32(u32(rsp+4)+0x5cL)));}
   if(pc==0x4474b0L){textureLoaderBoundaries++;String name=cstr(u32(rsp+4),32);log("STUB_VQM_PIXEL_ACQUIRE",pc,"name="+name+";status=substituted_pixel_loader");ret(0x3b000000L+textureLoaderBoundaries*0x1000L);continue;}
   if(pc==0x471980L){log("STUB_M16_TEXTURE_ACQUIRE",pc,"full_resolution_context_unavailable");ret(0);continue;}
   if(pc==0x447b20L||pc==0x471b70L){log("STUB_TEXTURE_RELEASE",pc,"reference_release_substituted");ret(1);continue;}
   if(target==0x463120L && pc==0x463189L){log("NATIVE_vehicle_init_prefix_complete",pc,"flags="+hx(u32(RUNTIME+0x454))+";mount0ref="+u32(SECOND+0xc)+";mount1ref="+u32(FIRST+0xc));done=true;break;}
   if(hist.size()>18)hist.removeFirst();hist.addLast(hx(pc));
   if(isImport(pc,0x4bc238)){String src=cstr(u32(rsp+4),80);long drive=u32(rsp+8),dir=u32(rsp+12),fname=u32(rsp+16),ext=u32(rsp+20);String base=src.replace("\\","/");base=base.substring(base.lastIndexOf("/")+1);int dot=base.lastIndexOf(".");String stem=dot>=0?base.substring(0,dot):base;String suffix=dot>=0?base.substring(dot):"";e.writeMemory(a(drive),new byte[4]);e.writeMemory(a(dir),new byte[256]);e.writeMemory(a(fname),(stem+"\0").getBytes());e.writeMemory(a(ext),(suffix+"\0").getBytes());log("STUB_splitpath",pc,src+";stem="+stem+";ext="+suffix);ret(0);continue;}
   if(isImport(pc,0x4bc28c)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] b=e.readMemory(a(src),len);if(b==null)throw new Exception("strncpy src");e.writeMemory(a(dst),b);ret(dst);continue;}
   if(isImport(pc,0x4bc260)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);int cnt=(int)u32(rsp+12);int result=x.substring(0,Math.min(cnt,x.length())).equalsIgnoreCase(y.substring(0,Math.min(cnt,y.length())))?0:1;log("STUB_strnicmp",pc,x+"|"+y+"|"+cnt+"|"+result);ret(result);continue;}
   if(pc==u32(0x4bc1f0L)){long dst=u32(rsp+4),src=u32(rsp+8);int len=(int)u32(rsp+12);byte[] copy=e.readMemory(a(src),len);if(copy==null||copy.length!=len)throw new Exception("CRT memcpy src="+hx(src)+" len="+len);e.writeMemory(a(dst),copy);ret(dst);continue;}
   if(pc==u32(0x4bc1e0L)){int ch=(int)u32(rsp+4)&255;ret((ch>=97&&ch<=122)?ch-32:ch);continue;}
   if(pc==0x00477c20L){log("STUB_nonessential_vehicle_light_registration",pc,"fixture registration omitted; body hierarchy continues");ret(1);continue;}
   if(pc==0x0044a0b0L){log("NATIVE_GEOMETRY_TEXTURE_REFRESH_ENTER",pc,"owner="+hx(u32(rsp+4)));}
   if(pc==0x004469a0L){nextGeoReturnPc=u32(rsp);nextGeoName=cstr(u32(rsp+4),32);log("NATIVE_GEO_LOAD_ENTER",pc,"key="+nextGeoName);}
   if(nextGeoReturnPc!=0 && pc==nextGeoReturnPc){realGeoReturns++;log("NATIVE_GEO_LOAD_RETURN",pc,"key="+nextGeoName+";handle="+hx(reg("EAX")));nextGeoReturnPc=0;}
   if(pc==0x00446c90L){realGeoConstructions++;long bp=u32(rsp+4);log("NATIVE_GEO_CONSTRUCTOR",pc,"ptr="+hx(bp)+";magic="+hx(u32(bp))+";vertices="+u32(bp+0x18L)+";faces="+u32(bp+0x1cL));}
   if(isImport(pc,0x4bc26cL)){long ptr=u32(rsp+4);int ch=(int)u32(rsp+8)&255;String name=cstr(ptr,256);int where=name.indexOf(ch);ret(where<0?0:ptr+where);continue;}
   if(isImport(pc,0x4bc0e8L)){retStd(0x2000L,3);continue;}
   if(pc==0x004796a0L||pc==0x00470340L ){log("STUB_palette_or_render_service",pc,"pc="+hx(pc));ret(0);continue;}
   if(isImport(pc,0x4bc254)){long ptr=u32(rsp+4);String raw=cstr(ptr,256);e.writeMemory(a(ptr),(raw.toLowerCase(Locale.ROOT)+"\0").getBytes(java.nio.charset.StandardCharsets.ISO_8859_1));log("STUB_strlwr",pc,raw);ret(ptr);continue;}
   if(isImport(pc,0x4bc210)){String x=cstr(u32(rsp+4),32),y=cstr(u32(rsp+8),32);ret(x.equalsIgnoreCase(y)?0:1);continue;}
   if(pc==0x438a90L){log("STUB_nonownership_vehicle_target_context",pc,"target="+hx(u32(rsp+4)));ret(0);continue;}
   if(pc==0x00458bf0L){log("STUB_optional_flag",pc,"0");ret(0);continue;}
   if(pc==0x0046ffc0L){n_open++;String name=cstr(u32(rsp+4),64).toLowerCase(Locale.ROOT);Long pos=resourcePtrs.get(name);if(pos==null)n_openfail++;log("STUB_open_resource",pc,name+";return="+(pos==null?"NULL":hx(pos)));ret(pos==null?0:pos);continue;}
   if(pc==0x0046fee0L){String name=cstr(u32(rsp+4),64).toLowerCase(Locale.ROOT);byte[] data=resourceBytes.get(name);log("STUB_get_resource_size",pc,name+";"+(data==null?0:data.length));ret(data==null?0:data.length);continue;}
   if(pc==0x0046fd40L){log("STUB_release_resource_ref",pc,cstr(u32(rsp+4),64));ret(0);continue;}
   if(pc==0x4b47c0L){builderCount++;log("NATIVE_child_builder",pc,"ordinal="+builderCount);}
   if(pc==0x46d760L){ctorCount++;log("NATIVE_class30_constructor",pc,"ordinal="+ctorCount);}
   if(isImport(pc,0x4bc108L)){
     long count=u32(rsp+12),out;if(count==0xb0){nodeAlloc++;out=0x27000000L+(nodeAlloc-1)*0x200L;}else if(count==0x88){runtimeAlloc++;out=0x2a000000L+(runtimeAlloc-1)*0x200L;}else if(count==0x3c || count==0x74){out=0x28000000L+0x200L*(cacheAlloc++);}else {out=genericHeapCursor;genericHeapCursor=(genericHeapCursor+count+31L)&~15L;if(genericHeapCursor>0x36800000L)throw new Exception("out of emulated generic heap "+count);extraAlloc++;}
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
    log("NATIVE_VCF_COMPLETE",LOADER,"vcfc="+n_vcfc+";opens="+n_open+";missing="+n_openfail+";parsers="+n_nested+";nodes="+nodeAlloc+";geoBindings="+cacheBindings+";weaponConstructors="+ctorCount+";materialBinds="+materialBinds+";nativeMaterialSuccess="+nativeMaterialSuccess+";mount0="+hx(u32(liveRT+0x3a8))+";mount4="+hx(u32(liveRT+0x3b8)));
    if(bodyParts!=(label.startsWith("gtsi")?31:29))throw new Exception("unexpected VDF body parts "+bodyParts);
    for(int part=0;part<bodyParts;part++){
      long rec=bodyBankZero+part*100L,node=0x27000000L+(bodyNodeStart+part)*0x200L;
      int cls=(int)u32(rec+0x5c);if(u32(node+0x6cL)!=cls)throw new Exception("native body class mismatch "+part);
      if(!Arrays.equals(e.readMemory(a(rec+8),36),e.readMemory(a(node+0x18L),36)))throw new Exception("native body basis mismatch "+part);
      for(int axis=0;axis<3;axis++){
        float value=Float.intBitsToFloat((int)u32(rec+0x2cL+axis*4));
        byte[] raw=e.readMemory(a(node+0x40L+axis*8L),8);long bits=0;for(int q=0;q<8;q++)bits|=((long)raw[q]&255)<<(8*q);
        if(Double.longBitsToDouble(bits)!=(double)value)throw new Exception("native body position mismatch "+part+" axis "+axis);
      }
      log("BODY_SLOT_VERIFIED",LOADER,"slot="+part+";node="+hx(node)+";resource="+cstr(rec,8)+";parent_label="+cstr(rec+0x38L,8)+";runtime_parent="+hx(u32(node+0x68L))+";class="+cls+";basis=exact;position=exact");
    }
    log("BODY_VERIFIED",LOADER,"parts="+bodyParts+";sourceFirstBank="+hx(bodyBankZero)+";each_class_basis_position=exact");
    if(nativeMaterialSuccess!=materialBinds || n_vcfc!=1 || n_nested!=7 || ctorCount!=4 || u32(OBJ+0x6cL)!=1)throw new Exception("native construction invariant mismatch");
    if(label.startsWith("gtsi")&&(nodeAlloc!=46||cacheBindings!=912||materialBinds!=24))throw new Exception("GTSi regression mismatch");
    for(int mount:new int[]{0,1,4,5}){
      long kid=u32(liveRT+0x3a8L+mount*4);if(kid==0||u32(kid+0x6cL)!=30)throw new Exception("invalid mounted class30 slot="+mount);
      long src=stagingRT+0x16cL+mount*56L;
      if(!Arrays.equals(e.readMemory(a(src),36),e.readMemory(a(kid+0x18L),36)))throw new Exception("mount orientation mismatch slot="+mount);
      for(int axis=0;axis<3;axis++){
        float expected=Float.intBitsToFloat((int)u32(src+0x24L+axis*4L));
        byte[] raw=e.readMemory(a(kid+0x40L+axis*8L),8);long bits=0;for(int z=0;z<8;z++)bits|=(raw[z]&255L)<<(8*z);
        if(Double.longBitsToDouble(bits)!=(double)expected)throw new Exception("mount translation mismatch slot="+mount+" axis="+axis);
      }
      log("MOUNT_VERIFIED",LOADER,"slot="+mount+";pointer="+hx(kid)+";class=30;orientation=exact;translation=exact;reference="+u32(kid+0xcL));
    }
    if(u32(liveRT+0x3b0L)!=0||u32(liveRT+0x3b4L)!=0)throw new Exception("non-empty middle WDF mount");
    // Exercise real variant selection after complete native VCF construction.
    long bodyNode=0x27000000L+(bodyNodeStart)*0x200L;
    byte[] startingOrientation=e.readMemory(a(bodyNode+0x18L),36),startingPosition=e.readMemory(a(bodyNode+0x40L),24);
    long startingParent=u32(bodyNode+0x68L),startingClass=u32(bodyNode+0x6cL);
    long firstActiveHandle=0;
    int ordinal=0;
    for(int group:new int[]{0,4,0}){
      String resource=(label.startsWith("gtsi")?(group==0?"al11bdym.geo":"al51bdym.geo"):(group==0?"xb11bdym.geo":"xb51bdym.geo"));
      int previousConstructions=realGeoConstructions;
      runCall(0x004466c0L,bodyNode,group);
      long got=reg("EAX"),handle=u32(bodyNode+0x5cL);ordinal++;
      if(got!=1||handle==0)throw new Exception("native GEO selector did not bind "+resource+" return="+got);
      if(!Arrays.equals(e.readMemory(a(bodyNode+0x18L),36),startingOrientation)||!Arrays.equals(e.readMemory(a(bodyNode+0x40L),24),startingPosition)||u32(bodyNode+0x68L)!=startingParent||u32(bodyNode+0x6cL)!=startingClass)throw new Exception("GEO selector modified structural transform or hierarchy");
      byte[] srcResource=resourceBytes.get(resource);
      if(srcResource==null||u32(handle+4L)!=(((long)srcResource[0x18]&255)|(((long)srcResource[0x19]&255)<<8)|(((long)srcResource[0x1a]&255)<<16)|(((long)srcResource[0x1b]&255)<<24)))throw new Exception("native GEO vertex count mismatch "+resource);
      if(ordinal==1)firstActiveHandle=handle;
      if(ordinal==3 && handle!=firstActiveHandle)throw new Exception("return to exterior did not reuse GEO handle");
      log("NATIVE_BODY_MESH_SELECTED",0x004466c0L,"ordinal="+ordinal+";group="+group+";node="+hx(bodyNode)+";resource="+resource+";geometryHandle="+hx(handle)+";vertices="+u32(handle+4L)+";newConstructors="+(realGeoConstructions-previousConstructions)+";stableClassBasisPositionParent=true");
    }
    // Real GEO from the existing native VCF construction, original record builder, and material binder in one emulator session.
    runRealSectionPreparation(bodyNode,(label.startsWith("gtsi")?"al11bdym.geo":"xb11bdym.geo"));
    runCall(0x004466c0L,bodyNode,4);
    long cockpit=u32(bodyNode+0x5cL);if(cockpit==0)throw new Exception("cockpit geometry absent");
    runRealSectionPreparation(bodyNode,(label.startsWith("gtsi")?"al51bdym.geo":"xb51bdym.geo"));
    // Execute the original dispatcher + full primary tree traversal over the actual live exterior body.
    // Defer secondary until its parent-child precondition can be established without synthetic cycles.
    runNativeSceneTraversal(bodyNode,label,4,1);
    runNativeSceneTraversal(bodyNode,label,0,1);
    runNativeSceneTraversal(OBJ,label,0,0);
    runNativeSpatialBucketFlush(bodyNode,label);
    producerExperiment(bodyNode,label+"_visible",true);
    producerExperiment(bodyNode,label+"_culled",false);


   }finally{e.dispose();e=null;}
 }
 @Override public void run()throws Exception{
  if(!"a640ea0097dbb62e0c77b7f2847c7161".equalsIgnoreCase(currentProgram.getExecutableMD5()))throw new Exception("retail MD5 mismatch");
  String[] args=getScriptArgs();
  try(PrintWriter writer=new PrintWriter(args[1])){
   trace=writer;trace.println("scenario\tkind\tpc\tdetail");
   testVcfAll(args[0],"noal01.vcf","gtsi_top_level_vcf");testVcfAll(args[0],"nobus1.vcf","bus_top_level_vcf");
  }
 }
}
