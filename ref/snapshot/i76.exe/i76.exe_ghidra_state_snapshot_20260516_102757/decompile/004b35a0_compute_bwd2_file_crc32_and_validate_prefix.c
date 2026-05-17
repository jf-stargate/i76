/*
 * Program: i76.exe
 * Function: compute_bwd2_file_crc32_and_validate_prefix
 * Entry: 004b35a0
 * Signature: undefined4 __cdecl compute_bwd2_file_crc32_and_validate_prefix(byte * param_1, undefined4 param_2, byte * param_3)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Initializes CRC32 table/state, parses
   a BWD2/VCFC validation stream, and returns complemented CRC result. */

undefined4 __cdecl
compute_bwd2_file_crc32_and_validate_prefix(byte *param_1,undefined4 param_2,byte *param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  uint *puVar3;
  int iVar4;
  int iVar5;
  
  param_3[0] = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  param_3[3] = 0;
  param_3[4] = 0;
  param_3[5] = 0;
  param_3[6] = 0;
  param_3[7] = 0;
  DAT_005dacd4 = param_2;
  DAT_005db7c4 = 0;
  DAT_005db960 = 0;
  DAT_005db974 = 0;
  DAT_005dacd0 = 1;
  iVar4 = 0;
  puVar3 = &g_crc32_table_msb;
  do {
    iVar5 = 8;
    uVar2 = iVar4 << 0x18;
    do {
      if ((uVar2 & 0x80000000) == 0) {
        uVar2 = uVar2 << 1;
      }
      else {
        uVar2 = uVar2 * 2 ^ 0x4c11db7;
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    *puVar3 = uVar2;
    puVar3 = puVar3 + 1;
    iVar4 = iVar4 + 1;
  } while ((int)puVar3 < 0x5db0e0);
  param_3[4] = 0xff;
  param_3[5] = 0xff;
  param_3[6] = 0xff;
  param_3[7] = 0xff;
  bVar1 = parse_bwd2_resource_with_descriptor_table(param_1,&DAT_00500050,4,param_3);
  if ((CONCAT31(extraout_var,bVar1) != 0) && (DAT_005dacd0 != 0)) {
    *(uint *)(param_3 + 4) = ~*(uint *)(param_3 + 4);
    return 1;
  }
  *(uint *)(param_3 + 4) = ~*(uint *)(param_3 + 4);
  return 0;
}


