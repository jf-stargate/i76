/*
 * Program: i76.exe
 * Function: or_world_object_and_descendant_status_flags
 * Entry: 00458810
 * Signature: undefined __cdecl or_world_object_and_descendant_status_flags(int param_1, uint param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small world-object class/id
   accessor used by vehicle damage callback.
   [I76 v66] REVIEW: called with world-object status masks including 0x200 in destruction paths.
   Existing getter name requires verification. Do not rename without examining implementation.
   [I76 v67] ORs supplied mask into object+10 and propagates it to the child subtree */

void __cdecl or_world_object_and_descendant_status_flags(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 100);
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | param_2;
    if (iVar1 != 0) {
      if (*(int *)(iVar1 + 0x60) != 0) {
        or_world_object_subtree_status_flags_recursive(*(int *)(iVar1 + 0x60),param_2);
      }
      if (*(int *)(iVar1 + 100) != 0) {
        or_world_object_subtree_status_flags_recursive(*(int *)(iVar1 + 100),param_2);
      }
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | param_2;
    }
  }
  return;
}


