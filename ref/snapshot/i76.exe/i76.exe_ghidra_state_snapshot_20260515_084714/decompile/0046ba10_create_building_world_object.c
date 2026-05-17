/*
 * Program: i76.exe
 * Function: create_building_world_object
 * Entry: 0046ba10
 * Signature: undefined __cdecl create_building_world_object(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence x1_bldx1 */

void __cdecl create_building_world_object(int param_1,float param_2)

{
  int iVar1;
  int iVar2;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c [3];
  
  iVar1 = *(int *)(param_1 + 0x70);
  if ((*(int *)(iVar1 + 0x38) != 0) && ((*(uint *)(iVar1 + 0x454) & 0x8020) == 0)) {
    local_1c = 0xbf000000;
    **(undefined4 **)(iVar1 + 0x508) = 0;
    iVar2 = *(int *)(param_1 + 0x70);
    *(uint *)(iVar2 + 0x454) = *(uint *)(iVar2 + 0x454) | 0x8000;
    *(undefined4 *)(iVar2 + 200) = 0x3e4ccccd;
    local_24 = 0;
    local_20 = 0;
    *(undefined4 *)(iVar2 + 0xcc) = 0;
    *(undefined4 *)(iVar2 + 0xd0) = 0xbf000000;
    local_18 = (float)*(double *)(param_1 + 0x40);
    local_14 = (float)*(double *)(param_1 + 0x48);
    local_10 = (float)*(double *)(param_1 + 0x50);
    strncpy((char *)&local_24,s_x1_bldx1_004f7d34,8);
    spawn_cached_explosion_runtime_object(local_24,local_20,param_1,local_18,local_14,local_10,0);
  }
  if ((*(uint *)(iVar1 + 0x454) & 0x20) == 0) {
    if (((*(uint *)(iVar1 + 0x454) & 0x80) != 0) && (_DAT_004be338 < *(float *)(iVar1 + 0xe4))) {
      iVar2 = *(int *)(param_1 + 0x70);
      *(undefined4 *)(*(int *)(iVar2 + 0x508) + 0x14) = 0x41a00000;
      *(uint *)(iVar2 + 0x454) = *(uint *)(iVar2 + 0x454) & 0xffffff7f;
    }
    building_child_piece_context_helper_0046bd10
              (param_1,(uint *)(iVar1 + 0x454),(float *)(iVar1 + 0xbc),(float *)(iVar1 + 0xac),
               local_c,(float *)(iVar1 + 200),(float *)(param_1 + 0x18),param_2);
    if ((*(byte *)(iVar1 + 0x454) & 0x20) != 0) {
      create_textured_building_piece(param_1);
    }
  }
  return;
}


