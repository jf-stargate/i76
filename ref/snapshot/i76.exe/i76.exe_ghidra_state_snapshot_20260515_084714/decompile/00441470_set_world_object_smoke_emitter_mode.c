/*
 * Program: i76.exe
 * Function: set_world_object_smoke_emitter_mode
 * Entry: 00441470
 * Signature: undefined __cdecl set_world_object_smoke_emitter_mode(int param_1, undefined4 param_2)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Sets the mode/state field on a
   world-object-attached smoke/effect emitter. */

void __cdecl set_world_object_smoke_emitter_mode(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  if (((DAT_0052ba34 != 0) && (param_1 != 0)) &&
     (puVar1 = DAT_0052ba24, DAT_0052ba24 != (undefined4 *)0x0)) {
    while (puVar1[2] != param_1) {
      puVar1 = (undefined4 *)puVar1[7];
      if (puVar1 == (undefined4 *)0x0) {
        return;
      }
    }
    *puVar1 = param_2;
  }
  return;
}


