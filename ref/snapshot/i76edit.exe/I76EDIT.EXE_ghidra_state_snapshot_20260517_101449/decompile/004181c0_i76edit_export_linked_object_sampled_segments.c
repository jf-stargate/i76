/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_linked_object_sampled_segments
 * Entry: 004181c0
 * Signature: int __cdecl i76edit_export_linked_object_sampled_segments(int param_1, int param_2)
 */


/* [cgpt_i76edit_level_renames_v6:medium] Chooses linked-object sampling mode based on payload +0xbc
   and +0x78/+0xc8 flags, dispatching to 00418270 or 00418490. */

int __cdecl i76edit_export_linked_object_sampled_segments(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  undefined4 local_4;
  
  iVar4 = 0;
  local_4 = 0;
  DAT_00436494 = 0;
  uVar2 = (uint)(*(int *)(*(int *)(param_2 + 8) + 0xbc) == 0);
  do {
    if (param_2 == 0) {
      return iVar4;
    }
    iVar1 = *(int *)(param_2 + 8);
    piVar3 = (int *)(iVar1 + 0x78);
    if ((*(uint *)(iVar1 + 200) & 1) != 0) {
      return iVar4;
    }
    *(uint *)(iVar1 + 200) = *(uint *)(iVar1 + 200) | 1;
    if (*piVar3 == 0) {
      iVar1 = i76edit_export_linked_object_linear_samples(param_1,(int)piVar3,uVar2,0.1);
LAB_00418235:
      iVar4 = iVar4 + iVar1;
    }
    else if (*piVar3 == 1) {
      iVar1 = i76edit_export_linked_object_curved_samples(param_1,(int)piVar3,uVar2,0.1,&local_4);
      goto LAB_00418235;
    }
    uVar2 = 0xffffffff;
  } while( true );
}


