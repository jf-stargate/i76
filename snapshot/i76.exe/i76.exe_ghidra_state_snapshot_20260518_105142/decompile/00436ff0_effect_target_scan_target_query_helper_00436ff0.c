/*
 * Program: i76.exe
 * Function: effect_target_scan_target_query_helper_00436ff0
 * Entry: 00436ff0
 * Signature: undefined4 __cdecl effect_target_scan_target_query_helper_00436ff0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: likely effect_target_scan /
   target_query_helper based on address neighborhood and prior focused closure context. */

undefined4 __cdecl effect_target_scan_target_query_helper_00436ff0(int param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  int iVar7;
  
  fVar2 = *(float *)(param_1 + 0x24);
  iVar5 = *(int *)(param_1 + 0x70);
  fVar3 = *(float *)(param_1 + 0x28);
  fVar4 = *(float *)(param_1 + 0x2c);
  pfVar1 = (float *)(iVar5 + 200);
  fVar6 = *(float *)(iVar5 + 0x468) * fVar4 +
          *(float *)(iVar5 + 0x464) * fVar3 + fVar2 * *(float *)(iVar5 + 0x460);
  if ((((float)_DAT_004bd030 <= ABS(*pfVar1)) ||
      ((float)_DAT_004bd030 <= ABS(*(float *)(iVar5 + 0xd0)))) || (ABS(fVar6) <= _DAT_004bd038)) {
    return 1;
  }
  if (((*(uint *)(iVar5 + 0x454) & 0x24) == 0) && (fVar6 < _DAT_004bd03c)) {
    if ((*(byte *)(param_1 + 0x10) & 0x20) == 0) {
      if ((*(uint *)(iVar5 + 0x454) & 0x10000) != 0) {
        iVar7 = is_damage_side_effects_suppressed();
        if (iVar7 == 0) {
          *(float *)(param_1 + 0x28) = -fVar3;
          *(float *)(param_1 + 0x24) = -fVar2;
          *(float *)(param_1 + 0x2c) = -fVar4;
          *(float *)(param_1 + 0x18) = -*(float *)(param_1 + 0x18);
          *(float *)(param_1 + 0x1c) = -*(float *)(param_1 + 0x1c);
          *(float *)(param_1 + 0x20) = -*(float *)(param_1 + 0x20);
          dispatch_vehicle_runtime_sound_event(4,param_1,(undefined4 *)0x0);
          goto LAB_004371ea;
        }
      }
      trigger_vehicle_forced_damage_or_actor_cleanup(param_1);
      *pfVar1 = 0.0;
      *(undefined4 *)(iVar5 + 0xcc) = 0;
    }
    else {
      *pfVar1 = 0.0;
      *(undefined4 *)(iVar5 + 0xcc) = 0;
    }
    *(undefined4 *)(iVar5 + 0xd0) = 0;
  }
LAB_004371ea:
  if ((*(uint *)(iVar5 + 0x454) & 0x200) != 0) {
    dispatch_vehicle_runtime_sound_event(4,param_1,(undefined4 *)0x0);
    *(uint *)(iVar5 + 0x454) = *(uint *)(iVar5 + 0x454) & 0xfffffdff;
  }
  return 0;
}


