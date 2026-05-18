/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_one_road_geometry_chunk
 * Entry: 00401389
 * Signature: int __cdecl i76edit_export_one_road_geometry_chunk(int param_1)
 */


int __cdecl i76edit_export_one_road_geometry_chunk(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 0x40);
  iVar2 = param_1;
  if (((iVar1 != 0) && (*(int *)(*(int *)(param_1 + 8) + 0x44) != 0)) &&
     (iVar2 = iVar1, iVar3 = param_1, iVar1 != 0)) {
    while (iVar2 = iVar1, iVar2 != param_1) {
      iVar1 = *(int *)(iVar2 + 8);
      if (*(int *)(iVar1 + 0x40) == 0) {
        return iVar2;
      }
      if (*(int *)(iVar1 + 0x44) == 0) {
        return iVar2;
      }
      iVar1 = *(int *)(iVar1 + 0x40 + (uint)(iVar3 == *(int *)(iVar1 + 0x40)) * 4);
      if (**(int **)(iVar1 + 8) == 3) {
        return iVar2;
      }
      if (**(int **)(iVar1 + 8) == 2) {
        return iVar2;
      }
      iVar3 = iVar2;
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  return iVar2;
}


