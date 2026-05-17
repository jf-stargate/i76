/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e8d0
 * Entry: 004012f8
 * Signature: undefined __cdecl thunk_FUN_0041e8d0(int * param_1, int * param_2, int param_3)
 */


void __cdecl thunk_FUN_0041e8d0(int *param_1,int *param_2,int param_3)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  undefined8 uVar4;
  uint auStack_18 [3];
  int iStack_c;
  int iStack_8;
  int iStack_4;
  
  uVar4 = thunk_FUN_0040c580(*param_1,*param_2);
  uVar3 = (uint)((ulonglong)uVar4 >> 0x20);
  uVar1 = (uint)uVar4;
  auStack_18[0] = uVar1;
  piVar2 = (int *)i76edit_world_xy_to_zone_local_triplet((int *)auStack_18,uVar1,uVar3);
  iStack_c = *piVar2;
  iStack_8 = piVar2[1];
  iStack_4 = piVar2[2];
  if ((iStack_c == -1) && (param_3 != 0)) {
    i76edit_get_or_assign_zone_map_cell_id
              ((int)(uVar1 + ((int)uVar1 >> 0x1f & 0x7fU)) >> 7,
               (int)(uVar3 + ((int)uVar3 >> 0x1f & 0x7fU)) >> 7,param_3);
  }
  *param_1 = iStack_8;
  *param_2 = iStack_4;
  return;
}


