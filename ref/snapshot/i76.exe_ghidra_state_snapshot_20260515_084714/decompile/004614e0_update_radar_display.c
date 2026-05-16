/*
 * Program: i76.exe
 * Function: update_radar_display
 * Entry: 004614e0
 * Signature: undefined __cdecl update_radar_display(int param_1, LPVOID param_2, int param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence: radar */

void __cdecl update_radar_display(int param_1,LPVOID param_2,int param_3)

{
  int iVar1;
  LPVOID pvVar2;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    if (param_3 == 1) {
      pvVar2 = release_world_object_tree_reference(param_2,s_radar_004f7694);
      *(LPVOID *)(iVar1 + 0x68) = pvVar2;
    }
    if (param_3 == 2) {
      pvVar2 = release_world_object_tree_reference(param_2,s_radar_004f7694);
      *(LPVOID *)(iVar1 + 0x6c) = pvVar2;
    }
    if (param_3 == 8) {
      pvVar2 = release_world_object_tree_reference(param_2,s_radar_004f7694);
      *(LPVOID *)(iVar1 + 0x70) = pvVar2;
    }
    if (param_3 == 0x10) {
      pvVar2 = release_world_object_tree_reference(param_2,s_radar_004f7694);
      *(LPVOID *)(iVar1 + 0x74) = pvVar2;
    }
  }
  return;
}


