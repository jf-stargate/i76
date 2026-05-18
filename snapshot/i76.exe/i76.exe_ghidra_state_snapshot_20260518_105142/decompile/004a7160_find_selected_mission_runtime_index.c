/*
 * Program: i76.exe
 * Function: find_selected_mission_runtime_index
 * Entry: 004a7160
 * Signature: int __cdecl find_selected_mission_runtime_index(int param_1)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Searches mission runtime table at
   0x00655280..0x006562c0 for mission id and returns the 0xd0-byte record index. */

int __cdecl find_selected_mission_runtime_index(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = &g_mission_runtime_vehicle_table;
  do {
    if (*piVar2 == param_1) {
      return iVar1;
    }
    piVar2 = piVar2 + 0x34;
    iVar1 = iVar1 + 1;
  } while ((int)piVar2 < 0x6562c0);
  return -1;
}


