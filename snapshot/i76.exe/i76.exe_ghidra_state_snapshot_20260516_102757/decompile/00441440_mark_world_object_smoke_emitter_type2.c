/*
 * Program: i76.exe
 * Function: mark_world_object_smoke_emitter_type2
 * Entry: 00441440
 * Signature: undefined __cdecl mark_world_object_smoke_emitter_type2(int param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Marks the smoke/effect emitter attached
   to a world object with state/type value 2. */

void __cdecl mark_world_object_smoke_emitter_type2(int param_1)

{
  int iVar1;
  
  if (((DAT_0052ba34 != 0) && (param_1 != 0)) && (iVar1 = DAT_0052ba24, DAT_0052ba24 != 0)) {
    while (*(int *)(iVar1 + 8) != param_1) {
      iVar1 = *(int *)(iVar1 + 0x1c);
      if (iVar1 == 0) {
        return;
      }
    }
    *(undefined4 *)(iVar1 + 4) = 2;
  }
  return;
}


