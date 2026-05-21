/*
 * Program: i76.exe
 * Function: fsm_teleport_object
 * Entry: 00414bc0
 * Signature: undefined __cdecl fsm_teleport_object(int param_1, int param_2, int * param_3, int * param_4, int * param_5, int * param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: FSM - teleport angle out of bounds */

void __cdecl
fsm_teleport_object(int param_1,int param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  float10 extraout_ST0;
  float local_40 [16];
  
  if ((*param_4 < 0) || (0x168 < *param_4)) {
    report_error();
  }
  iVar6 = *param_4;
  if (0xb3 < iVar6) {
    iVar6 = iVar6 + -0x168;
  }
  fVar2 = (float)iVar6 * _DAT_004bc7a0;
  if (param_5 == (int *)0x0) {
    param_4 = param_5;
  }
  else {
    param_5 = (int *)((float)*param_5 * _DAT_004bc7a8);
    param_4 = (int *)((float)*param_6 * _DAT_004bc7a8);
  }
  apply_world_object_transform_to_bounds_or_geometry
            ((double)**(float **)(param_2 + 0x54),(double)(*(float **)(param_2 + 0x54))[2]);
  *(float *)(*(int *)(param_2 + 0x54) + 4) = (float)extraout_ST0;
  pfVar1 = *(float **)(param_2 + 0x54);
  puVar5 = (undefined4 *)
           zone_satellite_map_context_helper_00493e60
                     (local_40,0.0,fVar2,0.0,(float)param_5 + *pfVar1,pfVar1[1],
                      pfVar1[2] + (float)param_4);
  puVar7 = (undefined4 *)(param_1 + 0x18);
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar7 = puVar7 + 1;
  }
  iVar6 = get_vehicle_runtime_context(param_1);
  *(undefined4 *)(iVar6 + 0xe4) = 0;
  *(undefined4 *)(iVar6 + 0xe0) = 0;
  fVar2 = *(float *)(param_1 + 0x34);
  fVar3 = *(float *)(param_1 + 0x38);
  fVar4 = (float)*param_3;
  *(float *)(iVar6 + 0xbc) = fVar4 * *(float *)(param_1 + 0x30);
  *(float *)(iVar6 + 0xc0) = fVar2 * fVar4;
  *(float *)(iVar6 + 0xc4) = fVar3 * fVar4;
  *(float *)(iVar6 + 0xac) = (float)*param_3;
  fVar2 = (float)*param_3;
  if ((fVar2 <= _DAT_004bc7ac) || (_DAT_004bc7b0 <= fVar2)) {
    *(float *)(iVar6 + 0xb0) = _DAT_004bc7b4 / fVar2;
  }
  else {
    *(undefined4 *)(iVar6 + 0xb0) = 0x7f7fffff;
  }
  *(undefined4 *)(iVar6 + 200) = 0;
  *(undefined4 *)(iVar6 + 0xcc) = 0;
  *(undefined4 *)(iVar6 + 0xd0) = 0;
  mark_active_player_object_control_changed(param_1);
  return;
}


