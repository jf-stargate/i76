/*
 * Program: i76.exe
 * Function: write_network_vehicle_file
 * Entry: 00455e60
 * Signature: undefined8 __cdecl write_network_vehicle_file(void * param_1, size_t param_2)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium-high] Writes or publishes
   network vehicle VCF data using NVCL/VCL filename patterns. */

undefined8 __cdecl write_network_vehicle_file(void *param_1,size_t param_2)

{
  uint uVar1;
  FILE *_File;
  char *pcVar2;
  uint uVar3;
  undefined4 local_18;
  undefined4 local_14;
  char local_10 [16];
  
  uVar3 = 0;
  uVar1 = DAT_005419b8 & 1;
  while (uVar1 != 0) {
    if (0xf < uVar3) goto LAB_00455e87;
    uVar3 = uVar3 + 1;
    uVar1 = DAT_005419b8 & 1 << ((byte)uVar3 & 0x1f);
  }
  if (uVar3 < 0x10) {
    sprintf(local_10,s__s_nvcl_1x_vcf_004c2028,&DAT_004c20a8,uVar3);
    DAT_005419b8 = DAT_005419b8 | 1 << ((byte)uVar3 & 0x1f);
    _File = fopen(local_10,s_wb_004edf28);
    fwrite(param_1,1,param_2,_File);
    fclose(_File);
    local_18 = 0;
    local_14 = 0;
    _splitpath(local_10,(char *)0x0,(char *)0x0,(char *)&local_18,(char *)0x0);
    pcVar2 = format_8char_resource_basename_with_suffix(local_18,local_14,&s_dot_vcf);
    canonicalize_resource_key_16byte(pcVar2);
    return CONCAT44(local_14,local_18);
  }
LAB_00455e87:
  report_chunk_parse_error();
  return 0;
}


