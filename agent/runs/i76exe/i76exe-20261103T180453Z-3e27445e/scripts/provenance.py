"""Read-only PE provenance check; prints metadata, never executable payloads."""
import pathlib,struct,re,json,sys
b=pathlib.Path(sys.argv[1]).read_bytes();u=lambda p:struct.unpack_from('<I',b,p)[0];pe=u(60);o=pe+24
syms,count=struct.unpack_from('<II',b,pe+12);debug=struct.unpack_from('<II',b,o+96+48)
strings=[(m.start(),m.group().decode()) for m in re.finditer(rb'[\x20-\x7e]{4,}',b)]
candidates=[(hex(a),s) for a,s in strings if re.search(r'(?i)(?:^|[\\/\s])[^\s\\/]+\.(?:c|cpp|cxx|h|hpp|pdb|obj|lib)(?:$|[\s:])',s)]
rich=b.find(b'Rich'); info={'offset':hex(rich)} if rich>=0 else None
if rich>=0:
 key=u(rich+4); start=next((a for a in range(64,rich,4) if u(a)^key==0x536e6144),None)
 info.update(valid_dans=start is not None,product_build_counts=[] if start is None else [{'product':(u(a)^key)>>16,'build':(u(a)^key)&65535,'count':u(a+4)^key} for a in range(start+16,rich,8)])
print(json.dumps(dict(coff_symbol_pointer=syms,coff_symbol_count=count,debug_directory_rva=debug[0],debug_directory_size=debug[1],linker_version=[b[o+2],b[o+3]],codeview_markers={x.decode():b.find(x) for x in [b'RSDS',b'NB10',b'NB09',b'NB11']},source_path_candidates=candidates,rich=info),indent=2))
