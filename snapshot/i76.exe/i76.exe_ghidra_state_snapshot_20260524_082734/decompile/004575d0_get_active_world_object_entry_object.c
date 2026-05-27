/*
 * Program: i76.exe
 * Function: get_active_world_object_entry_object
 * Entry: 004575d0
 * Signature: undefined4 * __cdecl get_active_world_object_entry_object(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small helper in active
   world-object entry path; returns/normalizes active entry object pointer. */

undefined4 * __cdecl get_active_world_object_entry_object(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = get_root_ancestor_world_object(param_1);
  iVar3 = 0;
  piVar2 = &g_active_world_object_entries;
  do {
    if (*piVar2 == iVar1) {
      return &g_active_world_object_entries + iVar3 * 0x1e;
    }
    piVar2 = piVar2 + 0x1e;
    iVar3 = iVar3 + 1;
  } while ((int)piVar2 < 0x54a030);
  return (undefined4 *)0x0;
}


