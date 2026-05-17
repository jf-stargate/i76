/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_path_tree_nodes_recursive
 * Entry: 00411550
 * Signature: int __cdecl i76edit_export_runtime_path_tree_nodes_recursive(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v3] Recursive runtime path tree node writer; emits scaled x/y/z
   coordinate triples.
   
   [cgpt_i76edit_level_renames_v6:high] Recursive path node writer. Emits 12-byte xyz triples scaled
   by 00432110, with z currently written as zero. */

int __cdecl i76edit_export_runtime_path_tree_nodes_recursive(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  float local_c [3];
  
  uVar3 = 0xffffffff;
  iVar5 = 0;
  iVar6 = *(int *)(param_2 + 8);
  uVar1 = *(uint *)(iVar6 + 0x50);
  if (((uVar1 & 1) == 0) || ((uVar1 & 2) == 0)) {
    if (((uVar1 & 1) == 0) || (uVar4 = 0, (uVar1 & 2) != 0)) {
      uVar4 = (uint)(*(int *)(iVar6 + 0x18) != 0);
    }
  }
  else {
    uVar4 = 1;
  }
  if (param_2 != 0) {
    while( true ) {
      uVar3 = uVar4;
      iVar6 = *(int *)(param_2 + 8);
      local_c[0] = *(float *)(iVar6 + uVar3 * 0xc) * _DAT_00432110;
      iVar5 = iVar5 + 1;
      local_c[1] = 0.0;
      local_c[2] = *(float *)(iVar6 + uVar3 * 0xc + 4) * _DAT_00432110;
      __write(param_1,local_c,0xc);
      iVar2 = *(int *)(iVar6 + uVar3 * -4 + 0x1c);
      if (iVar2 == 0) break;
      uVar4 = (uint)(*(int *)(*(int *)(iVar2 + 8) + 0x18) != param_2);
      param_2 = iVar2;
    }
  }
  iVar6 = iVar6 + uVar3 * -0xc;
  local_c[0] = *(float *)(iVar6 + 0xc) * _DAT_00432110;
  local_c[1] = 0.0;
  local_c[2] = *(float *)(iVar6 + 0x10) * _DAT_00432110;
  __write(param_1,local_c,0xc);
  return iVar5 + 1;
}


