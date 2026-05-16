/*
 * Program: i76.exe
 * Function: force_feedback_runtime_helper_00445ba0
 * Entry: 00445ba0
 * Signature: undefined __cdecl force_feedback_runtime_helper_00445ba0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v18: was player_force_feedback_force_feedback_helper_00445ba0. Remove
   duplicated force_feedback wording. */

void __cdecl force_feedback_runtime_helper_00445ba0(int param_1)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  LPVOID pvVar4;
  LPVOID pvVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int *piVar9;
  bool bVar10;
  float10 fVar11;
  float local_c [3];
  
  if (g_runtime_parameter_heap_ready != 0) {
    _DAT_004f248c = &DAT_005dcf3c;
    _DAT_004f2490 = DAT_005dcf7c;
    fVar11 = get_runtime_frame_delta_seconds();
    _DAT_004f2488 = (float)fVar11;
    iVar1 = *(int *)(param_1 + 0x70);
    if ((iVar1 != 0) && (iVar2 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar2 != 0)) {
      _DAT_004f2348 = 0;
      _DAT_004f2344 = 0;
      _DAT_004f233c = (*(uint *)(iVar1 + 0x454) & 0xff) >> 3 & 1;
      piVar9 = (int *)(iVar1 + 0x3ec);
      iVar8 = 3;
      do {
        if (*piVar9 != 0) {
          iVar6 = get_special_equipment_runtime_index(*piVar9);
          if (iVar6 == 2) {
            _DAT_004f2344 = *(uint *)(iVar1 + 0x454) & 0x800;
          }
          else if (iVar6 == 3) {
            _DAT_004f2348 = 1;
          }
        }
        piVar9 = piVar9 + 1;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      _DAT_004f2338 = *(uint *)(iVar1 + 0x454) & 1;
      building_child_piece_context_helper_0046a790(iVar2);
      _DAT_004f2334 = ftol();
      iVar1 = *(int *)(iVar2 + 8);
      bVar10 = iVar1 != DAT_004f2314;
      if (bVar10) {
        DAT_004f2314 = iVar1;
      }
      _DAT_004f2340 = (uint)bVar10;
    }
    iVar1 = *(int *)(param_1 + 0x70);
    if ((iVar1 != 0) && (iVar2 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar2 != 0)) {
      _DAT_004f2424 = (uint)((float)_DAT_004bd388 < *(float *)(iVar1 + 0xe4));
      _DAT_004f2428 = (uint)(*(float *)(iVar1 + 0xe4) < (float)_DAT_004bd390);
      fVar11 = building_child_piece_context_helper_0046a7b0(iVar2);
      if (fVar11 <= (float10)_DAT_004bd380) {
        _DAT_004f2470 = 0;
      }
      else {
        _DAT_004f2470 = *(int *)(iVar1 + 0x45c) + 1;
      }
      if ((float10)_DAT_004bd398 < fVar11) {
        fVar11 = (float10)_DAT_004bd398;
      }
      _DAT_004f242c = (float)fVar11;
      puVar7 = (undefined4 *)
               mat3_transform_vec3(local_c,(float *)(iVar1 + 0xd4),(float *)(param_1 + 0x18));
      _DAT_004f2418 = *puVar7;
      _DAT_004f241c = puVar7[1];
      _DAT_004f2420 = puVar7[2];
      _DAT_004f2400 = 0;
      _DAT_004f2404 = 0;
      _DAT_004f2408 = 0;
      _DAT_004f240c = *(undefined4 *)(iVar1 + 0xbc);
      _DAT_004f2410 = *(undefined4 *)(iVar1 + 0xbc);
      _DAT_004f2414 = *(undefined4 *)(iVar1 + 0xbc);
    }
    iVar1 = *(int *)(param_1 + 0x70);
    if (iVar1 != 0) {
      _DAT_004f2450 = *(uint *)(iVar1 + 0x454) & 4;
      _DAT_004f2458 = *(uint *)(iVar1 + 0x454) & 2;
      _DAT_004f2460 = *(uint *)(iVar1 + 0x454) & 0x2000;
      _DAT_004f2468 = *(uint *)(iVar1 + 0x454) & 0x400;
      _DAT_004f2430 = is_tire_contact_active(*(int *)(iVar1 + 0x3a8));
      _DAT_004f2434 = is_tire_contact_active(*(int *)(iVar1 + 0x3ac));
      _DAT_004f2438 = is_tire_contact_active(*(int *)(iVar1 + 0x3b8));
      _DAT_004f243c = is_tire_contact_active(*(int *)(iVar1 + 0x3bc));
    }
    dispatch_force_feedback_effect();
    pvVar3 = g_damage_runtime_param_front_angle;
    while (pvVar4 = pvVar3, pvVar3 = g_damage_runtime_param_up_angle, pvVar4 != (LPVOID)0x0) {
      pvVar3 = *(LPVOID *)((int)pvVar4 + 0x18);
      if ((*(int *)((int)pvVar4 + 0x10) == 0) && (*(int *)((int)pvVar4 + 0x14) == 0)) {
        force_feedback_runtime_update_helper_00445fd0(&g_damage_runtime_param_front_angle,pvVar4);
      }
    }
    while (pvVar4 = pvVar3, pvVar3 = g_damage_runtime_param_side_angle, pvVar4 != (LPVOID)0x0) {
      pvVar3 = *(LPVOID *)((int)pvVar4 + 0x18);
      if ((*(int *)((int)pvVar4 + 0x10) == 0) && (*(int *)((int)pvVar4 + 0x14) == 0)) {
        force_feedback_runtime_update_helper_00445fd0(&g_damage_runtime_param_up_angle,pvVar4);
      }
    }
    while (pvVar4 = pvVar3, pvVar3 = g_damage_runtime_param_impulse_angle, pvVar4 != (LPVOID)0x0) {
      pvVar3 = *(LPVOID *)((int)pvVar4 + 0x18);
      if ((*(int *)((int)pvVar4 + 0x10) == 0) && (*(int *)((int)pvVar4 + 0x14) == 0)) {
        force_feedback_runtime_update_helper_00445fd0(&g_damage_runtime_param_side_angle,pvVar4);
      }
    }
    while (pvVar4 = pvVar3, pvVar4 != (LPVOID)0x0) {
      pvVar3 = *(LPVOID *)((int)pvVar4 + 0x18);
      if (((*(int *)((int)pvVar4 + 0x10) == 0) && (*(int *)((int)pvVar4 + 0x14) == 0)) &&
         (pvVar4 != (LPVOID)0x0)) {
        pvVar5 = pvVar3;
        if (*(int *)((int)pvVar4 + 0x1c) != 0) {
          *(LPVOID *)(*(int *)((int)pvVar4 + 0x1c) + 0x18) = pvVar3;
          pvVar5 = g_damage_runtime_param_impulse_angle;
        }
        g_damage_runtime_param_impulse_angle = pvVar5;
        if (*(int *)((int)pvVar4 + 0x18) != 0) {
          *(undefined4 *)(*(int *)((int)pvVar4 + 0x18) + 0x1c) = *(undefined4 *)((int)pvVar4 + 0x1c)
          ;
        }
        HeapFree(g_runtime_parameter_heap,0,pvVar4);
      }
    }
  }
  return;
}


