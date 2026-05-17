/*
 * Program: i76.exe
 * Function: mission_vehicle_effect_spawn_context_helper_004a9090
 * Entry: 004a9090
 * Signature: undefined __cdecl mission_vehicle_effect_spawn_context_helper_004a9090(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: mission vehicle effect spawn context
   helper based on adjacent named subsystem context. */

void __cdecl mission_vehicle_effect_spawn_context_helper_004a9090(int param_1)

{
  double dVar1;
  double dVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float10 extraout_ST0;
  float10 fVar9;
  
  piVar5 = HeapAlloc(DAT_005da7b0,0,0x124);
  dVar1 = *(double *)(param_1 + 0x40);
  dVar2 = *(double *)(param_1 + 0x50);
  *piVar5 = param_1;
  rand();
  iVar6 = ftol();
  iVar8 = 0;
  piVar5[1] = 8 - iVar6;
  pfVar7 = (float *)(piVar5 + 3);
  do {
    if (piVar5[1] < iVar8) {
      pfVar7[-1] = 0.0;
    }
    else {
      iVar6 = rand();
      fVar3 = (float)iVar6 * _DAT_004bebbc * _DAT_004bebc4 - _DAT_004bebc8;
      iVar6 = rand();
      fVar4 = (float)iVar6 * _DAT_004bebbc * _DAT_004bebc4;
      *pfVar7 = (float)dVar1 + fVar3;
      fVar3 = (fVar4 - _DAT_004bebc8) + (float)dVar2;
      pfVar7[2] = fVar3;
      apply_world_object_transform_to_bounds_or_geometry((double)*pfVar7,(double)fVar3);
      pfVar7[1] = (float)extraout_ST0;
      fVar9 = get_multiplayer_or_runtime_seconds();
      iVar6 = rand();
      pfVar7[3] = (float)iVar6 * _DAT_004bebbc * _DAT_004bebcc + (float)fVar9;
      pfVar7[-1] = 1.4013e-45;
    }
    iVar8 = iVar8 + 1;
    pfVar7 = pfVar7 + 5;
  } while (iVar8 < 0xe);
  piVar5[0x48] = (int)g_pending_mission_vehicle_effect_spawn_list;
  g_pending_mission_vehicle_effect_spawn_list = piVar5;
  return;
}


