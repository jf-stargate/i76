/*
 * Program: i76.exe
 * Function: update_ai_roadwar_path_follow_drive_control
 * Entry: 004171a0
 * Signature: undefined __cdecl update_ai_roadwar_path_follow_drive_control(float param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Roadwar/path-following drive control update: advances
   route segment, applies steering, and sets throttle/brake target speed. */

void __cdecl update_ai_roadwar_path_follow_drive_control(float param_1,uint param_2)

{
  int *piVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  int *piVar6;
  bool bVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int *piVar14;
  float10 fVar15;
  float local_1c;
  
  fVar8 = (float)*(double *)((int)param_1 + 0x40);
  iVar5 = *(int *)(*(int *)((int)param_1 + 0x70) + 0x108);
  fVar9 = (float)*(double *)((int)param_1 + 0x48);
  piVar13 = (int *)(iVar5 + 0xa950);
  piVar1 = (int *)(iVar5 + 0xa96c);
  fVar10 = (float)*(double *)((int)param_1 + 0x50);
  project_point_to_path_segment_context_helper_0048e700(fVar8,fVar9,fVar10,piVar1,piVar13);
  iVar11 = *piVar1;
  if (*(int *)(iVar11 + 0xc) == 0) {
    bVar7 = false;
  }
  else {
    bVar7 = *(int *)(iVar11 + 0x14) + -5 < *piVar13;
  }
  if (bVar7) {
    *(undefined4 *)(iVar5 + 0xa954) = 0xffffffff;
    local_1c = 8.2;
  }
  else {
    if (*(int *)(iVar11 + 8) == 0) {
      bVar7 = *piVar13 < 5;
    }
    else if (*(int *)(*(int *)(iVar11 + 8) + 0xc) == 0) {
      bVar7 = false;
    }
    else {
      bVar7 = *piVar13 < 5;
    }
    if (bVar7) {
      *(undefined4 *)(iVar5 + 0xa954) = 1;
      local_1c = 1.7;
    }
    else {
      iVar11 = is_vehicle_or_actor_runtime_world_object(param_2);
      if (iVar11 != 0) {
        dVar2 = *(double *)(param_2 + 0x40);
        dVar3 = *(double *)(param_2 + 0x48);
        iVar11 = *(int *)(*(int *)(param_2 + 0x70) + 0x108);
        dVar4 = *(double *)(param_2 + 0x50);
        piVar14 = (int *)(iVar11 + 0xa950);
        project_point_to_path_segment_context_helper_0048e700
                  ((float)dVar2,(float)dVar3,(float)dVar4,(int *)(iVar11 + 0xa96c),piVar14);
        piVar6 = *(int **)(iVar11 + 0xa96c);
        piVar1 = (int *)*piVar1;
        if (((piVar6 != (int *)0x0) && (piVar1 != (int *)0x0)) && (*piVar6 == *piVar1)) {
          local_1c = *(float *)(iVar5 + 0xa964);
          if (piVar1 == piVar6) {
            iVar12 = ((*piVar14 <= *piVar13) - 1 & 2) - 1;
          }
          else {
            iVar12 = piVar1[3];
            while (iVar12 == 0) {
              if (piVar1 == piVar6) {
                iVar12 = 1;
                goto LAB_0041732c;
              }
              piVar1 = (int *)piVar1[1];
              iVar12 = piVar1[3];
            }
            iVar12 = (-(uint)(piVar1 != piVar6) & 0xfffffffe) + 1;
          }
LAB_0041732c:
          *(int *)(iVar5 + 0xa954) = iVar12;
          classify_roadwar_path_segment_progress(fVar8,fVar9,fVar10,piVar13);
          *(int *)(iVar11 + 0xa954) = -iVar12;
          classify_roadwar_path_segment_progress((float)dVar2,(float)dVar3,(float)dVar4,piVar14);
          *(int *)(iVar5 + 0xa954) = -*(int *)(iVar5 + 0xa954);
          if (_DAT_004bc8c0 <= *(float *)(iVar11 + 0xa964)) {
            if (_DAT_004bc8c4 < *(float *)(iVar11 + 0xa964)) {
              local_1c = 1.7;
            }
          }
          else {
            local_1c = 8.2;
          }
        }
      }
    }
  }
  if ((*(int *)(iVar5 + 0xa954) != 1) && (*(int *)(iVar5 + 0xa954) != -1)) {
    *(undefined4 *)(iVar5 + 0xa954) = 1;
    local_1c = 1.7;
  }
  *(float *)(iVar5 + 0xa964) = local_1c;
  iVar11 = get_vehicle_runtime_context((int)param_1);
  iVar12 = roadwar_advance_to_next_road_segment
                     ((int)param_1,fVar8,fVar9,fVar10,piVar13,9.0,local_1c,(float *)(iVar5 + 0xa968)
                     );
  if (iVar12 != 0) {
    update_ai_vehicle_steering_control((int)param_1,*(float *)(iVar5 + 0xa968));
    fVar15 = (float10)world_object_geometry_context_helper_004589f0((uint)param_1,param_2);
    if ((fVar15 <= (float10)_DAT_004bc8c8) &&
       (ABS(*(float *)(iVar11 + 0xe0)) <= (float)_DAT_004bc8d0)) {
      set_ai_vehicle_throttle_brake_toward_speed(param_1,50.0);
      return;
    }
    fVar15 = get_ai_vehicle_damage_state_speed_scalar((int)param_1);
    set_ai_vehicle_throttle_brake_toward_speed(param_1,(float)fVar15);
  }
  return;
}


