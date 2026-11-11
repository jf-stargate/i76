// Uses immutable #140 observer/services from the same pinned checkout.
import java.nio.file.*;
public class BoundaryGeometryProbe extends I76_TopologyProbe {
 @Override void initializeTerrain()throws Exception {
  if(!mode.equals("retail")) {
   for(int i=1;i<terrainBytes.length;i+=2)terrainBytes[i]&=31;
   int zm=tag(missionBytes,"ZMAP")+9;
   if(mode.equals("alias"))missionBytes[zm+75*80+4]=missionBytes[zm+74*80+4];
   if(mode.equals("default"))missionBytes[zm+75*80+4]=(byte)255;
   if(mode.equals("class2")||mode.equals("class5")) {
    int x=543,z=9695,page=missionBytes[zm+(z/128)*80+x/128]&255;
    if(page==255)throw new Exception("controlled class point is default");
    int off=page*32768+2*((z&127)*128+(x&127));
    terrainBytes[off+1]|=(byte)((mode.equals("class2")?2:5)<<5);
    log("CONTROLLED_CLASS",0,"x="+x+";z="+z+";offset="+off+";class="+(mode.equals("class2")?2:5));
   }
  }
  Files.write(Paths.get(terrainOutput+".input.msn"),missionBytes);
  Files.write(Paths.get(terrainOutput+".input.ter"),terrainBytes);
  super.initializeTerrain();
 }
}
