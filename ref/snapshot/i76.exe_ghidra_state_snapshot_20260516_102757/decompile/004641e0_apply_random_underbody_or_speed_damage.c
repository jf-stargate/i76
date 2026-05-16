/*
 * Program: i76.exe
 * Function: apply_random_underbody_or_speed_damage
 * Entry: 004641e0
 * Signature: undefined __cdecl apply_random_underbody_or_speed_damage(int param_1, float param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle physics integrator rename v31; confidence=medium] Applies randomized part
   damage when speed/grounding conditions are met, then may update vehicle damage state based on
   current speed. */

void __cdecl apply_random_underbody_or_speed_damage(int param_1,float param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  int local_18;
  undefined2 local_14;
  uint local_4;
  
                    /* I76 semantic baseline: apply_random_underbody_or_speed_damage
                       Applies terrain/speed-scaled random underbody or speed damage. */
  piVar1 = *(int **)(param_1 + 0x70);
  if (((*(byte *)(piVar1 + 0x115) & 0x20) == 0) &&
     (local_18 = weapon_target_ordnance_query_context_helper_004a82b0(), local_18 == 0)) {
    piVar1[0x116] = (int)(param_2 + (float)piVar1[0x116]);
    piVar4 = &local_18;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar4 = 0;
      piVar4 = piVar4 + 1;
    }
    local_14 = 8;
    local_4 = ftol();
    piVar1[0x116] = (int)((float)piVar1[0x116] - (float)local_4);
    iVar2 = rand();
    iVar3 = param_1;
    switch(iVar2 % 6) {
    case 0:
      iVar3 = world_object_has_optional_runtime_flag(param_1);
      iVar3 = apply_vehicle_damage_record_to_accumulators
                        ((int)piVar1,(int *)0x0,(int)&local_18,iVar3);
      break;
    case 1:
    case 2:
      iVar3 = world_object_has_optional_runtime_flag(param_1);
      iVar3 = apply_vehicle_damage_record_to_accumulators
                        ((int)piVar1,(int *)0x1,(int)&local_18,iVar3);
      break;
    case 3:
    case 4:
      iVar3 = world_object_has_optional_runtime_flag(param_1);
      iVar3 = apply_vehicle_damage_record_to_accumulators
                        ((int)piVar1,(int *)0x2,(int)&local_18,iVar3);
      break;
    case 5:
      iVar3 = world_object_has_optional_runtime_flag(param_1);
      iVar3 = apply_vehicle_damage_record_to_accumulators
                        ((int)piVar1,(int *)0x3,(int)&local_18,iVar3);
    }
    while (iVar3 != 0) {
      iVar3 = apply_vehicle_part_damage_and_special_equipment_effects
                        (piVar1,(float)(iVar2 % 6),(int)&local_18,0,100.0);
    }
    fVar5 = compute_world_object_damage_integrity_percent(param_1);
    if (fVar5 * (float10)_DAT_004be1d4 < (float10)_DAT_004be1a4) {
      vehicle_damage_texture_dirty_context_helper_00466ca0
                (piVar1,(float)(fVar5 * (float10)_DAT_004be1d4));
    }
  }
  return;
}


