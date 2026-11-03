// Read-only comparison: structural semantics separate from Ghidra isEquivalent.
//@category i76
import ghidra.program.model.data.*;
import java.util.*;
import java.nio.file.*;
public class TerrainShapeAudit extends ConsolidateSemantics {
 String shape(DataType t,Set<String> seen){if(t==null)return "void-target";if(t instanceof Pointer p)return "ptr"+p.getLength()+"("+shape(p.getDataType(),seen)+")";if(t instanceof Array a)return "array"+a.getNumElements()+":"+a.getElementLength()+"("+shape(a.getDataType(),seen)+")";if(t instanceof Structure s){String id=s.getPathName();if(!seen.add(id))return "recursive:"+id;StringBuilder b=new StringBuilder(id+":"+s.getLength()+"{");for(var c:s.getDefinedComponents())b.append(c.getOffset()+":"+c.getLength()+":"+c.getFieldName()+":"+shape(c.getDataType(),new HashSet<>(seen))+";");return b+"}";}return t.getPathName()+":"+t.getLength();}
 List<String> rows=new ArrayList<>();
 void compare(DataType want)throws Exception{var old=currentProgram.getDataTypeManager().getDataType(want.getCategoryPath(),want.getName());String a=old==null?"MISSING":shape(old,new HashSet<>()),b=shape(want,new HashSet<>());rows.add(want.getPathName()+"\t"+(old!=null&&old.isEquivalent(want))+"\t"+a.equals(b)+"\t"+a+"\t"+b);}
 @Override void type(StructureDataType t)throws Exception{compare(t);types.put(t.getName(),t);}
 @Override public void run()throws Exception{types();var m=I76_SemanticPass_v99.class.getDeclaredMethod("makeStructures");m.setAccessible(true);for(Object t:(List<?>)m.invoke(new I76_SemanticPass_v99()))compare((DataType)t);Files.writeString(Paths.get(getScriptArgs()[0]),"type\tghidra_equivalent\tsame_layout_names_types\tactual_shape\texpected_shape\n"+String.join("\n",rows)+"\n");println("SHAPE_AUDIT "+rows.size());}
}
