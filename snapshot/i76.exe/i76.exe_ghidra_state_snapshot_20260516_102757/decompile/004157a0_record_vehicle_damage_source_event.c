/*
 * Program: i76.exe
 * Function: record_vehicle_damage_source_event
 * Entry: 004157a0
 * Signature: undefined __cdecl record_vehicle_damage_source_event(int param_1, byte param_2, undefined4 param_3, uint param_4, int param_5)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Records source/attacker object and
   timestamp data into vehicle damage-event state. */

void __cdecl
record_vehicle_damage_source_event
          (int param_1,byte param_2,undefined4 param_3,uint param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float10 fVar6;
  
                    /* I76 semantic baseline: record_vehicle_damage_source_event
                       Records recent/latest damage source into vehicle FSM/damage event state. */
  iVar2 = is_vehicle_or_actor_runtime_world_object(param_4);
  if ((iVar2 != 0) && (iVar2 = is_damage_side_effects_suppressed(), iVar2 == 0)) {
    iVar2 = get_vehicle_runtime_context(param_4);
    iVar3 = get_vehicle_damage_event_state_block(iVar2);
    if (((param_2 & 6) == 0) && (param_1 != 0)) {
      iVar4 = is_vehicle_or_actor_runtime_world_object(param_1);
      uVar1 = g_vehicle_damage_source_event_state;
      if (iVar4 != 0) {
        if ((param_5 != 0) && (*(int *)(param_5 + 0x70) != 0)) {
                    /* I76 semantic baseline note:
                       AIO patch semantic delta: retail reads [runtime+0x44], AIO reads
                       [runtime+0x10] as gate for categorized damage-source attribution. Affects FSM
                       queries such as whoRammed/whoShot style behavior, not raw damage amount. */
          param_4 = (uint)(*(int *)(*(int *)(param_5 + 0x70) + 0x44) == 0);
        }
        if (param_4 == 0) {
          if ((param_2 & 0x18) == 0) {
            *(int *)(iVar3 + 0xa6e4) = param_1;
            *(undefined4 *)(iVar3 + 0xa6d8) = uVar1;
          }
          else {
            *(int *)(iVar3 + 0xa6e8) = param_1;
            *(undefined4 *)(iVar3 + 0xa6d4) = uVar1;
          }
        }
        uVar1 = g_vehicle_damage_source_event_state;
        *(int *)(iVar3 + 0xa6ec) = param_1;
        *(undefined4 *)(iVar3 + 0xa6dc) = uVar1;
        fVar6 = get_gameplay_runtime_seconds();
        *(float *)(iVar3 + 0xa6f0) = (float)fVar6;
        if ((*(byte *)(iVar2 + 0x454) & 0x20) != 0) {
          piVar5 = (int *)get_active_player_or_camera_world_object_entry();
          if (piVar5 == (int *)0x0) {
            *(undefined4 *)(iVar3 + 0xa6e0) = 0;
            return;
          }
          if (param_1 == *piVar5) {
            *(undefined4 *)(iVar3 + 0xa6e0) = 1;
            return;
          }
        }
      }
    }
    else {
      fVar6 = get_gameplay_runtime_seconds();
      *(float *)(iVar3 + 0x9d00) = (float)fVar6;
    }
  }
  return;
}


