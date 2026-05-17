/*
 * Program: i76.exe
 * Function: register_vehicle_fsm_runtime_for_world_object
 * Entry: 00409850
 * Signature: undefined __cdecl register_vehicle_fsm_runtime_for_world_object(int * param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: World-object registration callback: inserts
   vehicle/actor objects into team buckets, initializes vehicle damage/FSM state, parses tactics
   tag, and caches terrain material. */

void __cdecl register_vehicle_fsm_runtime_for_world_object(int *param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined2 extraout_var;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  undefined4 *puVar8;
  
  if ((*(int *)(*param_1 + 0x6c) != 8) &&
     (iVar2 = is_vehicle_or_actor_runtime_world_object(*param_1), iVar2 != 0)) {
    iVar7 = 0;
    uVar3 = *(uint *)(*param_1 + 0x10) >> 0x10 & 7;
    iVar2 = (&DAT_0051f5d0)[uVar3];
    if (0 < iVar2) {
      puVar8 = &DAT_00507da0 + uVar3 * 0x40;
      do {
        if (*(int *)*puVar8 == *param_1) break;
        iVar7 = iVar7 + 1;
        puVar8 = puVar8 + 1;
      } while (iVar7 < iVar2);
    }
    (&DAT_0051f5d0)[uVar3] = iVar2 + 1;
    (&DAT_00507da0)[uVar3 * 0x40 + iVar2] = param_1;
    iVar2 = *param_1;
    iVar7 = get_vehicle_runtime_context(iVar2);
    piVar4 = (int *)get_vehicle_damage_event_state_block(iVar7);
    *piVar4 = iVar2 + 0x18;
    if (*(int *)(iVar2 + 0x6c) == 9) {
      piVar4[0x2745] = 0;
    }
    else {
      piVar4[0x2745] = 1;
      update_vehicle_damage_state_speed_scalar_from_tire_load(iVar2);
    }
    parse_fsm_tactics_tag(piVar4[0x2a06],(int)(piVar4 + 0x2a0b));
    uVar1 = lookup_terrain_material_index_at_world_xz
                      (*(double *)(iVar2 + 0x40),*(double *)(iVar2 + 0x50));
    *(uint *)(iVar7 + 0x45c) = CONCAT22(extraout_var,uVar1);
    puVar8 = &DAT_00507da0;
    piVar6 = &DAT_0051f5d0;
    do {
      iVar2 = *piVar6;
      puVar5 = puVar8;
      if (0 < iVar2) {
        do {
          iVar2 = iVar2 + -1;
          *(undefined4 *)(*(int *)(*(int *)(*(int *)*puVar5 + 0x70) + 0x108) + 0xa714) = 1;
          puVar5 = puVar5 + 1;
        } while (iVar2 != 0);
      }
      piVar6 = piVar6 + 1;
      puVar8 = puVar8 + 0x40;
    } while ((int)piVar6 < 0x51f5f0);
    piVar4[2] = 1;
  }
  return;
}


