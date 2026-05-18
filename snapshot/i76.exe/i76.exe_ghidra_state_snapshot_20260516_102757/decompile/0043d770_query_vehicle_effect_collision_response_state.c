/*
 * Program: i76.exe
 * Function: query_vehicle_effect_collision_response_state
 * Entry: 0043d770
 * Signature: undefined4 __stdcall query_vehicle_effect_collision_response_state(void)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Collision/effect predicate over
   vehicle/effect state selectors 1/2/3 with output state written through stack arguments. */

undefined4 query_vehicle_effect_collision_response_state(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  int *piVar9;
  float *pfVar10;
  int iVar11;
  float *pfVar12;
  undefined4 *puVar13;
  float *pfVar14;
  int *piVar15;
  float *pfVar16;
  int *in_stack_0000001c;
  int *in_stack_00000020;
  float *in_stack_00000024;
  float *in_stack_00000028;
  float in_stack_fffffef8;
  float in_stack_fffffefc;
  float in_stack_ffffff00;
  float in_stack_ffffff04;
  float in_stack_ffffff08;
  float in_stack_ffffff0c;
  float in_stack_ffffff10;
  float in_stack_ffffff14;
  float in_stack_ffffff18;
  float in_stack_ffffff1c;
  float fVar17;
  float fVar18;
  float local_b0 [4];
  float local_a0;
  float local_9c;
  int local_98 [6];
  float local_80 [16];
  float local_40 [16];
  
  iVar11 = in_stack_0000001c[5];
  if (iVar11 == 1) {
    pfVar14 = local_b0;
    pfVar10 = (float *)register0x00000010;
    for (iVar11 = 6; pfVar10 = pfVar10 + 1, iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar14 = *pfVar10;
      pfVar14 = pfVar14 + 1;
    }
    piVar9 = (int *)vehicle_ground_contact_probe_context_helper_00440670
                              (local_98,(int)in_stack_0000001c);
    piVar15 = local_98;
    for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
      *piVar15 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar15 = piVar15 + 1;
    }
    pfVar10 = (float *)compose_matrix_or_transform_b((void *)(*in_stack_0000001c + 0x18),local_40);
    pfVar14 = local_80;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar14 = *pfVar10;
      pfVar10 = pfVar10 + 1;
      pfVar14 = pfVar14 + 1;
    }
    pfVar10 = local_b0;
    fVar17 = 6.230638e-39;
    transform_vec3_array_by_matrix(pfVar10,local_b0,1,local_80);
    iVar11 = *in_stack_0000001c;
    fVar18 = 0.0;
    fVar2 = *(float *)(iVar11 + 0x24) * local_b0[3];
    fVar3 = *(float *)(iVar11 + 0x34) * local_a0;
    fVar4 = *(float *)(iVar11 + 0x30) * local_b0[3];
    fVar1 = *(float *)(iVar11 + 0x38);
    local_b0[3] = local_b0[3] * *(float *)(iVar11 + 0x18) +
                  *(float *)(iVar11 + 0x1c) * local_a0 + *(float *)(iVar11 + 0x20) * local_9c;
    local_a0 = *(float *)(iVar11 + 0x28) * local_a0 + *(float *)(iVar11 + 0x2c) * local_9c + fVar2;
    piVar9 = local_98;
    piVar15 = (int *)&stack0xffffff10;
    pfVar14 = in_stack_00000028;
    for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
      *piVar15 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar15 = piVar15 + 1;
    }
    local_9c = fVar1 * local_9c + fVar4 + fVar3;
    pfVar12 = local_b0;
    pfVar16 = (float *)&stack0xfffffef8;
    for (iVar11 = 6; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar16 = *pfVar12;
      pfVar12 = pfVar12 + 1;
      pfVar16 = pfVar16 + 1;
    }
    iVar11 = test_swept_aabb_axis_interval_collision
                       (in_stack_fffffef8,in_stack_fffffefc,in_stack_ffffff00,in_stack_ffffff04,
                        in_stack_ffffff08,in_stack_ffffff0c,in_stack_ffffff10,in_stack_ffffff14,
                        in_stack_ffffff18,in_stack_ffffff1c,fVar17,(float)pfVar10,in_stack_00000024,
                        pfVar14,fVar18);
    if (iVar11 != 0) {
      iVar11 = *in_stack_0000001c;
      fVar1 = *(float *)(iVar11 + 0x28);
      fVar2 = *(float *)(iVar11 + 0x34);
      fVar3 = *(float *)(iVar11 + 0x38);
      fVar4 = *(float *)(iVar11 + 0x2c);
      fVar17 = *(float *)(iVar11 + 0x1c);
      fVar18 = *in_stack_00000028;
      fVar5 = *(float *)(iVar11 + 0x20);
      fVar6 = *in_stack_00000028;
      fVar7 = in_stack_00000028[1];
      *in_stack_00000028 =
           *in_stack_00000028 * *(float *)(iVar11 + 0x18) +
           *(float *)(iVar11 + 0x30) * in_stack_00000028[2] +
           *(float *)(iVar11 + 0x24) * in_stack_00000028[1];
      in_stack_00000028[1] =
           fVar17 * fVar18 + fVar2 * in_stack_00000028[2] + fVar1 * in_stack_00000028[1];
      in_stack_00000028[2] = fVar5 * fVar6 + fVar4 * fVar7 + fVar3 * in_stack_00000028[2];
      *in_stack_00000020 = *in_stack_0000001c;
      return 1;
    }
  }
  else {
    if (iVar11 == 2) {
      *in_stack_00000020 = *in_stack_0000001c;
      return 1;
    }
    if (iVar11 != 3) {
      return 0;
    }
    if (*in_stack_0000001c != 0) {
      puVar13 = (undefined4 *)&stack0xffffff00;
      for (iVar11 = 6; register0x00000010 = (BADSPACEBASE *)((int)register0x00000010 + 4),
          iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar13 = *(undefined4 *)register0x00000010;
        puVar13 = puVar13 + 1;
      }
      uVar8 = update_vehicle_effect_collision_response();
      return uVar8;
    }
  }
  return 0;
}


