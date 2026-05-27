/*
 * Program: i76.exe
 * Function: handle_roadwar_atomic_behavior
 * Entry: 00416650
 * Signature: undefined __cdecl handle_roadwar_atomic_behavior(int * param_1, int * param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Unknown atomic behavior in road war */

void __cdecl handle_roadwar_atomic_behavior(int *param_1,int *param_2,int param_3)

{
  double dVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int *piVar10;
  int *piVar11;
  int iVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  int *piVar17;
  float10 fVar18;
  
  piVar11 = param_2;
  piVar10 = param_1;
  fVar6 = (float)*(double *)(param_1 + 0x10);
  fVar7 = (float)*(double *)(param_1 + 0x12);
  iVar14 = *(int *)(param_1[0x1c] + 0x108);
  iVar4 = *(int *)(param_2[0x1c] + 0x108);
  fVar8 = (float)*(double *)(param_1 + 0x14);
  piVar17 = (int *)(iVar14 + 0xa950);
  dVar1 = *(double *)(param_2 + 0x10);
  dVar2 = *(double *)(param_2 + 0x12);
  dVar3 = *(double *)(param_2 + 0x14);
  piVar16 = (int *)(iVar4 + 0xa950);
  param_2 = (int *)(iVar14 + 0xa96c);
  project_point_to_path_segment_context_helper_0048e700
            (fVar6,fVar7,fVar8,(int *)(iVar14 + 0xa96c),piVar17);
  param_1 = (int *)(iVar4 + 0xa96c);
  project_point_to_path_segment_context_helper_0048e700
            ((float)dVar1,(float)dVar2,(float)dVar3,param_1,piVar16);
  iVar12 = *param_1;
  iVar15 = *param_2;
  if (iVar15 == iVar12) {
    param_2 = (int *)(((*piVar16 <= *piVar17) - 1 & 2) - 1);
  }
  else {
    iVar5 = *(int *)(iVar15 + 0xc);
    while (iVar5 == 0) {
      if (iVar15 == iVar12) {
        param_2 = (int *)0x1;
        goto LAB_00416747;
      }
      iVar15 = *(int *)(iVar15 + 4);
      iVar5 = *(int *)(iVar15 + 0xc);
    }
    param_2 = (int *)((-(uint)(iVar15 != iVar12) & 0xfffffffe) + 1);
  }
LAB_00416747:
  *(int **)(iVar14 + 0xa954) = param_2;
  *(int *)(iVar4 + 0xa954) = -(int)param_2;
  param_1 = (int *)(*piVar17 - *piVar16);
  iVar12 = ftol();
  if (iVar12 == 0) {
    param_1 = (int *)0x0;
  }
  else {
    param_1 = (int *)((8 < iVar12) + 1);
  }
  classify_roadwar_path_segment_progress(fVar6,fVar7,fVar8,piVar17);
  classify_roadwar_path_segment_progress((float)dVar1,(float)dVar2,(float)dVar3,piVar16);
  uVar13 = classify_roadwar_next_turn_direction((uint)piVar10,piVar17,(int)param_1,(uint)piVar11);
  *(undefined4 *)(iVar14 + 0xa95c) = uVar13;
  iVar12 = classify_roadwar_next_turn_direction((uint)piVar11,piVar16,(int)param_1,(uint)piVar10);
  fVar9 = *(float *)(iVar4 + 0xa964) - _DAT_004bc898;
  *(int *)(iVar4 + 0xa95c) = iVar12;
  if (fVar9 <= *(float *)(iVar14 + 0xa964)) {
    if (*(float *)(iVar14 + 0xa964) <= *(float *)(iVar4 + 0xa964) - _DAT_004bc89c) {
      iVar15 = 1;
    }
    else {
      iVar15 = 0;
    }
  }
  else {
    iVar15 = 2;
  }
  switch(*(undefined4 *)
          (&DAT_004c3480 +
          (iVar12 + (*(int *)(iVar14 + 0xa95c) + ((int)param_1 + (iVar15 + param_3 * 3) * 3) * 4) *
                    4) * 4)) {
  case 0:
    roadwar_advance_to_next_road_segment
              ((int)piVar10,fVar6,fVar7,fVar8,piVar17,20.0,*(float *)(iVar4 + 0xa964),
               (float *)&param_1);
    break;
  case 1:
    roadwar_advance_to_next_road_segment
              ((int)piVar10,fVar6,fVar7,fVar8,piVar17,20.0,
               *(float *)(iVar4 + 0xa964) - _DAT_004bc880,(float *)&param_1);
    goto LAB_00416a43;
  case 2:
    param_1 = (int *)0x41200000;
    if (_DAT_004bc884 <= *(float *)(iVar4 + 0xa964)) {
      param_1 = (int *)0x0;
    }
    *(int *)(iVar14 + 0xa954) = -*(int *)(iVar14 + 0xa954);
    roadwar_advance_to_next_road_segment
              ((int)piVar10,fVar6,fVar7,fVar8,piVar17,20.0,(float)param_1,(float *)&param_1);
LAB_00416a43:
    update_ai_vehicle_steering_control((int)piVar10,(float)param_1);
    iVar14 = get_vehicle_runtime_context((int)piVar10);
    if ((float)_DAT_004bc850 < ABS(*(float *)(iVar14 + 0xe0))) {
      fVar18 = get_ai_vehicle_damage_state_speed_scalar((int)piVar10);
      set_ai_vehicle_throttle_brake_toward_speed((float)piVar10,(float)fVar18);
      return;
    }
    if ((float)_DAT_004bc858 < ABS(*(float *)(iVar14 + 0xe0))) {
      set_ai_vehicle_throttle_brake_toward_speed((float)piVar10,30.0);
      return;
    }
    goto LAB_00416aaa;
  case 3:
    update_ai_vehicle_full_throttle_intercept_control((float)piVar10,(int)piVar11);
    return;
  case 4:
    update_roadwar_vehicle_steering_and_speed_control
              ((float)piVar10,fVar6,fVar7,fVar8,piVar17,piVar16,20.0,(int)piVar11);
    return;
  case 5:
    if ((int)param_1 < 3) {
      if ((*(float *)(iVar4 + 0xa964) < _DAT_004bc830) ||
         (_DAT_004bc888 < *(float *)(iVar4 + 0xa964))) {
        if (param_2 != (int *)0x1) goto LAB_004168fc;
        param_1 = (int *)0x3fd9999a;
      }
      else if (_DAT_004bc884 <= *(float *)(iVar4 + 0xa964)) {
        param_1 = (int *)0x0;
      }
      else {
        param_1 = (int *)0x41200000;
      }
    }
    else if (param_2 == (int *)0x1) {
      param_1 = (int *)0x3fd9999a;
    }
    else {
LAB_004168fc:
      param_1 = (int *)0x41033333;
    }
    roadwar_advance_to_next_road_segment
              ((int)piVar10,fVar6,fVar7,fVar8,piVar17,20.0,(float)param_1,(float *)&param_1);
    break;
  case 6:
    update_roadwar_vehicle_steering_and_speed_control
              ((float)piVar10,fVar6,fVar7,fVar8,piVar17,piVar16,20.0,(int)piVar11);
    return;
  default:
    report_error();
    return;
  }
  update_ai_vehicle_steering_control((int)piVar10,(float)param_1);
  iVar14 = get_vehicle_runtime_context((int)piVar10);
  if ((float)_DAT_004bc850 < ABS(*(float *)(iVar14 + 0xe0))) {
    fVar18 = get_ai_vehicle_damage_state_speed_scalar((int)piVar10);
    set_ai_vehicle_throttle_brake_toward_speed((float)piVar10,(float)fVar18);
    return;
  }
  if ((float)_DAT_004bc858 < ABS(*(float *)(iVar14 + 0xe0))) {
    set_ai_vehicle_throttle_brake_toward_speed((float)piVar10,30.0);
    return;
  }
LAB_00416aaa:
  set_ai_vehicle_throttle_brake_toward_speed((float)piVar10,100.0);
  return;
}


