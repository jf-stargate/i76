/*
 * Program: i76.exe
 * Function: register_network_vehicle_file
 * Entry: 00455de0
 * Signature: undefined __stdcall register_network_vehicle_file(void)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium-high] Registers network vehicle
   files using NVCL/*.vcf patterns. */

void register_network_vehicle_file(void)

{
  int iVar1;
  char local_10 [16];
  
  iVar1 = _access(&DAT_004c20a8,0);
  if (iVar1 == 0) {
    _unlink(s_NVCL___vcf_004c209c);
  }
  else {
    _mkdir(&DAT_004c20a8);
  }
  iVar1 = 0;
  do {
    sprintf(local_10,s_nvcl_1x_vcf_004c2038,iVar1);
    register_resource_key_for_zix_path(local_10,&DAT_004c20a8);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  DAT_005419b8 = 0;
  return;
}


