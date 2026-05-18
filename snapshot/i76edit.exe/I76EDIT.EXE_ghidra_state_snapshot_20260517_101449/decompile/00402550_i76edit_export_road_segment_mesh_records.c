/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_road_segment_mesh_records
 * Entry: 00402550
 * Signature: int __cdecl i76edit_export_road_segment_mesh_records(int param_1, int param_2)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Road export helper that dispatches to lower-level segment
   writers 00402720/004029b0 based on road/edge state.
   
   [cgpt_i76edit_level_renames_v6:high] Road export helper called from RSEG writer. Walks road
   segment nodes and emits interpolated road mesh/segment records. */

int __cdecl i76edit_export_road_segment_mesh_records(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  bool bVar7;
  float local_4;
  
  DAT_00434070 = 0xbf800000;
  DAT_00434074 = 0xbf800000;
  iVar6 = 0;
  DAT_00434078 = 0xbf800000;
  local_4 = 0.0;
  DAT_00434080 = 0;
  bVar7 = *(int *)(*(int *)(param_2 + 8) + 0x44) == 0;
  DAT_0043407c = 0x41200000;
  if (*(short *)(*(int *)(param_2 + 8) + 6) != 2) {
    DAT_0043407c = 0x41a00000;
  }
  uVar3 = 0;
  iVar4 = 0;
  iVar2 = param_2;
  if (param_2 != 0) {
    while( true ) {
      uVar5 = (uint)bVar7;
      piVar1 = *(int **)(param_2 + 8);
      iVar2 = param_2;
      if ((piVar1[0x14] & 1U) != 0) break;
      piVar1[0x14] = piVar1[0x14] | 1;
      if (*piVar1 == 0) {
        iVar2 = FUN_00402720(param_1,(int)piVar1,uVar5,1.0,&local_4);
LAB_004025f7:
        iVar6 = iVar6 + iVar2;
      }
      else if (*piVar1 == 1) {
        iVar2 = FUN_004029b0(param_1,(int)piVar1,uVar5,1.0,&local_4);
        goto LAB_004025f7;
      }
      iVar2 = piVar1[0x11 - uVar5];
      uVar3 = uVar5;
      iVar4 = param_2;
      if (iVar2 == 0) break;
      bVar7 = *(int *)(*(int *)(iVar2 + 8) + 0x40) != param_2;
      param_2 = iVar2;
    }
  }
  if (iVar2 != 0) {
    __write(param_1,&DAT_00439a38,0xc);
    __write(param_1,&DAT_00439a28,0xc);
    return iVar6 + 1;
  }
  piVar1 = *(int **)(iVar4 + 8);
  if (*piVar1 != 0) {
    if (*piVar1 != 1) {
      return iVar6;
    }
    iVar2 = FUN_00402df0(param_1,(int)piVar1,(1 - uVar3) * 3);
    return iVar6 + iVar2;
  }
  iVar2 = FUN_00402d70(param_1,(int)piVar1,(1 - uVar3) * 3);
  return iVar6 + iVar2;
}


