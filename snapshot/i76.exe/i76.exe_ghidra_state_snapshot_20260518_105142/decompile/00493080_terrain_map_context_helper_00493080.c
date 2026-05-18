/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00493080
 * Entry: 00493080
 * Signature: undefined4 __cdecl terrain_map_context_helper_00493080(undefined4 param_1, int param_2, float param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00493080. Remove
   duplicated terrain wording. */

undefined4 __cdecl terrain_map_context_helper_00493080(undefined4 param_1,int param_2,float param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  _DAT_004fad24 = 0x3b2aaaab;
  _DAT_004fad20 = 0x41800000;
  if (param_2 == 0) {
    _DAT_004fad20 = 0x40cccccd;
    _DAT_004fad24 = 0x3b800000;
  }
  else if (param_2 == 2) {
    _DAT_004fad20 = 0x42200000;
    _DAT_004fad24 = 0x3ae353f8;
  }
  _DAT_006442c4 = _DAT_004be830 / param_3;
  DAT_006442c0 = param_3;
  _DAT_006442d0 = param_1;
  puVar5 = &DAT_00644380;
  for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = &DAT_0059c588;
    puVar5 = puVar5 + 1;
  }
  pbVar1 = (byte *)zone_satellite_map_context_helper_00493bf0();
  iVar3 = 0xc18;
  do {
    iVar4 = 0;
    do {
      if (*pbVar1 != 0xff) {
        uVar2 = i76_runtime_get_active_zone_page_ptr((uint)*pbVar1);
        (&DAT_00644380)[iVar4 + iVar3] = uVar2;
      }
      pbVar1 = pbVar1 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x50);
    iVar3 = iVar3 + 0x80;
  } while (iVar3 < 0x3418);
  return 1;
}


