/*
 * Program: i76.exe
 * Function: vehicle_damage_texture_dirty_context_helper_00466ca0
 * Entry: 00466ca0
 * Signature: undefined __cdecl vehicle_damage_texture_dirty_context_helper_00466ca0(undefined4 * param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: vehicle damage texture dirty context
   helper based on adjacent named subsystem context. */

void __cdecl vehicle_damage_texture_dirty_context_helper_00466ca0(undefined4 *param_1,float param_2)

{
  undefined4 uVar1;
  
  if (_DAT_004be1e8 <= param_2) {
    if ((param_1[0x115] & 0x100) != 0) {
      unregister_world_object_smoke_emitter(*(LPVOID *)*param_1);
      param_1[0x115] = param_1[0x115] & 0xfffffeff;
    }
    return;
  }
  if (param_2 <= _DAT_004be22c) {
    if (param_2 <= _DAT_004be230) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  if ((param_1[0x115] & 0x100) == 0) {
    register_world_object_smoke_emitter
              (*(int *)*param_1,param_1 + 0x29,0,0x3e4ccccd,*(undefined4 *)(param_1[0x104] + 0x9c));
    param_1[0x115] = param_1[0x115] | 0x100;
    set_world_object_smoke_emitter_mode(*(int *)*param_1,uVar1);
    return;
  }
  mark_world_object_smoke_emitter_type2(*(int *)*param_1);
  set_world_object_smoke_emitter_mode(*(int *)*param_1,uVar1);
  return;
}


