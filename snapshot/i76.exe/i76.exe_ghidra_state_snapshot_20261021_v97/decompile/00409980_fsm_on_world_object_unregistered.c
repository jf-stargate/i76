/* Decompiled retail i76.exe, Ghidra v97; 00409980 fsm_on_world_object_unregistered */

void __cdecl fsm_on_world_object_unregistered(int *param_1)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  int *local_8;
  undefined4 *local_4;
  
  pvVar1 = (LPVOID)*param_1;
  if (pvVar1 != (LPVOID)0x0) {
    local_4 = &g_fsm_team_world_object_entry_buckets;
    local_8 = &g_fsm_team_world_object_entry_counts;
    do {
      iVar5 = *local_8;
      puVar8 = local_4;
      if (0 < iVar5) {
        do {
          iVar7 = *(int *)(*(int *)(*(int *)*puVar8 + 0x70) + 0x108);
          if (*(LPVOID *)(iVar7 + 0xa9b4) == pvVar1) {
            finalize_released_world_object_after_damage(pvVar1,&DAT_004c2a10);
            *(undefined4 *)(iVar7 + 0xa9b4) = 0;
          }
          iVar5 = iVar5 + -1;
          puVar8 = puVar8 + 1;
        } while (iVar5 != 0);
      }
      local_8 = local_8 + 1;
      local_4 = local_4 + 0x40;
    } while ((int)local_8 < 0x51f5f0);
  }
  if (*(int *)(*param_1 + 0x6c) != 8) {
    iVar5 = is_vehicle_or_actor_runtime_world_object(*param_1);
    pvVar1 = (LPVOID)*param_1;
    if (iVar5 != 0) {
      param_1 = (int *)0x0;
      uVar6 = *(uint *)((int)pvVar1 + 0x10) >> 0x10 & 7;
      if (0 < (int)(&g_fsm_team_world_object_entry_counts)[uVar6]) {
        puVar8 = &g_fsm_team_world_object_entry_buckets + uVar6 * 0x40;
        do {
          if (*(LPVOID *)*puVar8 == pvVar1) goto LAB_00409a5c;
          param_1 = (int *)((int)param_1 + 1);
          puVar8 = puVar8 + 1;
        } while ((int)param_1 < (int)(&g_fsm_team_world_object_entry_counts)[uVar6]);
      }
      param_1 = (int *)0xffffffff;
LAB_00409a5c:
      iVar5 = 0;
      if (0 < g_fsm_mission_actor_record_count) {
        iVar7 = 0;
        do {
          pvVar2 = *(LPVOID *)(g_fsm_mission_actor_records + 0x58 + iVar7);
          if (pvVar2 == pvVar1) {
            finalize_released_world_object_after_damage(pvVar2,&DAT_004c2a10);
            *(undefined4 *)(g_fsm_mission_actor_records + 0x58 + iVar7) = 0;
          }
          iVar5 = iVar5 + 1;
          iVar7 = iVar7 + 0x60;
        } while (iVar5 < g_fsm_mission_actor_record_count);
      }
      iVar5 = is_vehicle_or_actor_runtime_world_object((int)pvVar1);
      if (iVar5 != 0) {
        iVar5 = *(int *)(*(int *)((int)pvVar1 + 0x70) + 0x108);
        pvVar1 = *(LPVOID *)(iVar5 + 0xa9b4);
        if (pvVar1 != (LPVOID)0x0) {
          finalize_released_world_object_after_damage(pvVar1,&DAT_004c2a10);
          *(undefined4 *)(iVar5 + 0xa9b4) = 0;
        }
      }
      iVar7 = (&g_fsm_team_world_object_entry_counts)[uVar6];
      iVar5 = iVar7 + -1;
      if ((int)param_1 < iVar5) {
        iVar5 = iVar5 - (int)param_1;
        piVar4 = param_1 + uVar6 * 0x10;
        param_1 = (int *)((int)param_1 + iVar5);
        puVar8 = &g_fsm_team_world_object_entry_buckets + (int)piVar4;
        do {
          *puVar8 = puVar8[1];
          puVar8 = puVar8 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      (&g_fsm_team_world_object_entry_counts)[uVar6] = iVar7 + -1;
      puVar8 = &g_fsm_team_world_object_entry_buckets;
      (&g_fsm_team_world_object_entry_buckets)[(int)(param_1 + uVar6 * 0x10)] = 0;
      piVar4 = &g_fsm_team_world_object_entry_counts;
      do {
        iVar5 = *piVar4;
        puVar3 = puVar8;
        if (0 < iVar5) {
          do {
            iVar5 = iVar5 + -1;
            *(undefined4 *)(*(int *)(*(int *)(*(int *)*puVar3 + 0x70) + 0x108) + 0xa714) = 1;
            puVar3 = puVar3 + 1;
          } while (iVar5 != 0);
        }
        piVar4 = piVar4 + 1;
        puVar8 = puVar8 + 0x40;
      } while ((int)piVar4 < 0x51f5f0);
      return;
    }
    if ((pvVar1 != (LPVOID)0x0) && (iVar5 = 0, 0 < g_fsm_mission_actor_record_count)) {
      iVar7 = 0;
      do {
        pvVar2 = *(LPVOID *)(g_fsm_mission_actor_records + 0x58 + iVar7);
        if (pvVar2 == pvVar1) {
          finalize_released_world_object_after_damage(pvVar2,&DAT_004c2a10);
          *(undefined4 *)(g_fsm_mission_actor_records + 0x58 + iVar7) = 0;
        }
        iVar5 = iVar5 + 1;
        iVar7 = iVar7 + 0x60;
      } while (iVar5 < g_fsm_mission_actor_record_count);
    }
  }
  return;
}


