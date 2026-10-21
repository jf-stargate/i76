/*
 * Program: i76.exe
 * Function: create_building_child_object
 * Entry: 0046cba0
 * Signature: undefined __cdecl create_building_child_object(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence x1_bldx1 */

void __cdecl create_building_child_object(int param_1)

{
  int iVar1;
  uint local_18;
  uint local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = *(int *)(param_1 + 0x70);
  local_10 = 0xbf000000;
  *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x8000;
  *(undefined4 *)(iVar1 + 200) = 0x3e4ccccd;
  local_18 = 0;
  local_14 = 0;
  *(undefined4 *)(iVar1 + 0xcc) = 0;
  *(undefined4 *)(iVar1 + 0xd0) = 0xbf000000;
  local_c = (float)*(double *)(param_1 + 0x40);
  local_8 = (float)*(double *)(param_1 + 0x48);
  local_4 = (float)*(double *)(param_1 + 0x50);
  strncpy((char *)&local_18,s_x1_bldx1_004f7d34,8);
  spawn_cached_explosion_runtime_object(local_18,local_14,param_1,local_c,local_8,local_4,0);
  return;
}


