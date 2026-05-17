/*
 * Program: i76.exe
 * Function: release_world_object_light_runtime
 * Entry: 00477e10
 * Signature: undefined __cdecl release_world_object_light_runtime(int param_1)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Removes a world object from the
   runtime light table, clears the light flag, and compacts the fixed-size light entry array. */

void __cdecl release_world_object_light_runtime(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = 0;
  if (0 < g_runtime_light_entry_count) {
    piVar2 = &g_runtime_light_entries;
    while (param_1 != *piVar2) {
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x1b;
      if (g_runtime_light_entry_count <= iVar1) {
        return;
      }
    }
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) & 0xfffff7ff;
    g_runtime_light_entry_count = g_runtime_light_entry_count + -1;
    puVar4 = &g_runtime_light_entries + g_runtime_light_entry_count * 0x1b;
    puVar5 = &g_runtime_light_entries + iVar1 * 0x1b;
    for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  return;
}


