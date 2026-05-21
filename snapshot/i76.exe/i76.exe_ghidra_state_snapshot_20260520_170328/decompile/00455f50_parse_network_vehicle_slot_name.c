/*
 * Program: i76.exe
 * Function: parse_network_vehicle_slot_name
 * Entry: 00455f50
 * Signature: undefined __stdcall parse_network_vehicle_slot_name(void)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Parses a network vehicle slot
   name such as nvcl%1x.vcf. */

void parse_network_vehicle_slot_name(void)

{
  int iVar1;
  byte local_4 [4];
  
  iVar1 = sscanf(&stack0x00000004,s_nvcl_1x_vcf_004c2038,local_4);
  if (iVar1 != 0) {
    DAT_005419b8 = DAT_005419b8 & ~(1 << (local_4[0] & 0x1f));
  }
  return;
}


