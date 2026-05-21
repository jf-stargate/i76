/*
 * Program: i76.exe
 * Function: unregister_world_object_smoke_emitter
 * Entry: 004413b0
 * Signature: undefined __cdecl unregister_world_object_smoke_emitter(LPVOID param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Finds a world-object-attached
   smoke/effect emitter, releases the object tree refcount, unlinks it, and returns it to the free
   list. */

void __cdecl unregister_world_object_smoke_emitter(LPVOID param_1)

{
  int iVar1;
  
  if (((DAT_0052ba34 != 0) && (param_1 != (LPVOID)0x0)) && (iVar1 = DAT_0052ba24, DAT_0052ba24 != 0)
     ) {
    while (*(LPVOID *)(iVar1 + 8) != param_1) {
      iVar1 = *(int *)(iVar1 + 0x1c);
      if (iVar1 == 0) {
        return;
      }
    }
    finalize_released_world_object_after_damage(param_1,&DAT_004f1b84);
    if (*(int *)(iVar1 + 0x20) != 0) {
      *(undefined4 *)(*(int *)(iVar1 + 0x20) + 0x1c) = *(undefined4 *)(iVar1 + 0x1c);
    }
    if (*(int *)(iVar1 + 0x1c) != 0) {
      *(undefined4 *)(*(int *)(iVar1 + 0x1c) + 0x20) = *(undefined4 *)(iVar1 + 0x20);
    }
    if (DAT_0052b950 == iVar1) {
      DAT_0052b950 = *(int *)(iVar1 + 0x20);
    }
    if (DAT_0052ba24 == iVar1) {
      DAT_0052ba24 = *(int *)(iVar1 + 0x1c);
    }
    *(undefined4 *)(iVar1 + 0x20) = 0;
    *(int *)(iVar1 + 0x1c) = DAT_0052b958;
    DAT_0052b958 = iVar1;
  }
  return;
}


