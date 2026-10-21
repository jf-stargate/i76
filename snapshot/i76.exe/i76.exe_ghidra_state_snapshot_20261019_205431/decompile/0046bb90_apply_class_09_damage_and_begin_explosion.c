/*
 * Program: i76.exe
 * Function: apply_class_09_damage_and_begin_explosion
 * Entry: 0046bb90
 * Signature: undefined4 __cdecl apply_class_09_damage_and_begin_explosion(int param_1, int param_2)
 */


undefined4 __cdecl apply_class_09_damage_and_begin_explosion(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  uint local_18;
  uint local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  float local_4;
  
  piVar1 = *(int **)(*(int *)(param_1 + 0x70) + 0x508);
  if ((((param_2 != 0) && ((*(byte *)(param_1 + 0x10) & 0x20) == 0)) && (param_2 != 0)) &&
     ((*(uint *)(*(int *)(param_1 + 0x70) + 0x454) & 0x8020) == 0)) {
    iVar2 = 0;
    piVar3 = (int *)(param_2 + 8);
    do {
      if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
        if (*piVar1 < *piVar3) {
          *piVar1 = 0;
          iVar2 = *(int *)(param_1 + 0x70);
          local_10 = 0xbf000000;
          *(uint *)(iVar2 + 0x454) = *(uint *)(iVar2 + 0x454) | 0x8000;
          *(undefined4 *)(iVar2 + 200) = 0x3e4ccccd;
          *(undefined4 *)(iVar2 + 0xcc) = 0;
          *(undefined4 *)(iVar2 + 0xd0) = 0xbf000000;
          local_c = (float)*(double *)(param_1 + 0x40);
          local_18 = 0;
          local_14 = 0;
          local_8 = (float)*(double *)(param_1 + 0x48);
          local_4 = (float)*(double *)(param_1 + 0x50);
          strncpy((char *)&local_18,s_x1_bldx1_004f7d34,8);
          spawn_cached_explosion_runtime_object(local_18,local_14,param_1,local_c,local_8,local_4,0)
          ;
          return 1;
        }
        *piVar1 = *piVar1 - *piVar3;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 < 4);
    return 0;
  }
  return 0;
}


