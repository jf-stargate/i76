/*
 * Program: i76.exe
 * Function: probe_effect_target_surface_height_at_position
 * Entry: 0043e530
 * Signature: undefined __cdecl probe_effect_target_surface_height_at_position(double param_1, float param_2, float * param_3, undefined4 * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v9 vehicle effect/collision/particle cluster: Scans effect-target collision/surface
   records near a position and returns the best surface height/fallback transform result. */

void __cdecl
probe_effect_target_surface_height_at_position
          (double param_1,float param_2,float *param_3,undefined4 *param_4)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int *piVar4;
  float fVar5;
  undefined4 uVar6;
  float fVar7;
  undefined4 *puVar8;
  float *pfVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  float10 fVar13;
  float10 extraout_ST0;
  float local_3c;
  float local_38;
  undefined4 uStack_34;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c [3];
  
                    /* I76 semantic baseline: probe_effect_target_surface_height_at_position
                       Probes effect target/surface height at world position. */
  fVar7 = param_2;
  local_3c = -1e+30;
  local_38 = -1e+30;
  if (DAT_0052b94c != (int *)0x0) {
    fVar5 = param_1._0_4_;
    piVar12 = DAT_0052b94c;
    do {
      piVar4 = (int *)piVar12[2];
      pfVar9 = (float *)entity_instance_table_context_helper_004577a0(local_c,piVar4);
      if ((param_2 - pfVar9[1]) * (param_2 - pfVar9[1]) +
          (param_1._0_4_ - *pfVar9) * (param_1._0_4_ - *pfVar9) <= pfVar9[2] * pfVar9[2]) {
        for (piVar4 = (int *)piVar4[6]; piVar4 != (int *)0x0; piVar4 = (int *)piVar4[2]) {
          iVar10 = point_in_polygon_xz((int *)*piVar4,piVar4[1],fVar5,fVar7);
          if (iVar10 != 0) {
            fVar13 = solve_plane_y_from_xz(*piVar4,fVar5,fVar7);
            fVar1 = (float)fVar13;
            iVar10 = *piVar4;
            if (((local_3c == _DAT_004bd220) && (fVar1 < param_1._4_4_)) && (local_38 < fVar1)) {
              local_18 = *(undefined4 *)(iVar10 + 4);
              local_14 = *(undefined4 *)(iVar10 + 8);
              local_10 = *(undefined4 *)(iVar10 + 0xc);
              local_38 = fVar1;
            }
            if (((param_1._4_4_ < fVar1 - _DAT_004bd224) && (fVar1 - _DAT_004bd228 < param_1._4_4_))
               && (local_3c < fVar1)) {
              local_24 = *(undefined4 *)(iVar10 + 4);
              local_20 = *(undefined4 *)(iVar10 + 8);
              local_1c = *(undefined4 *)(iVar10 + 0xc);
              local_3c = fVar1;
            }
            break;
          }
        }
      }
      piVar12 = (int *)*piVar12;
    } while (piVar12 != (int *)0x0);
  }
  if (local_3c <= _DAT_004bd220) {
    if (local_38 <= _DAT_004bd220) {
      dVar2 = (double)param_2;
      uStack_34 = (undefined4)((ulonglong)dVar2 >> 0x20);
      local_38 = SUB84(dVar2,0);
      dVar3 = (double)param_1._0_4_;
      param_1._4_4_ = (float)((ulonglong)dVar3 >> 0x20);
      uVar6 = param_1._4_4_;
      param_1 = dVar3;
      apply_world_object_transform_to_bounds_or_geometry(dVar3,dVar2);
      puVar8 = param_4;
      *param_3 = (float)extraout_ST0;
      if (param_4 != (undefined4 *)0x0) {
        puVar11 = (undefined4 *)
                  sample_runtime_terrain_packed_word
                            ((float *)&param_1,(double)CONCAT44(uVar6,param_1._0_4_),local_38,
                             uStack_34);
        *puVar8 = *puVar11;
        puVar8[1] = puVar11[1];
        puVar8[2] = puVar11[2];
      }
    }
    else {
      *param_3 = local_38;
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = local_18;
        param_4[1] = local_14;
        param_4[2] = local_10;
        return;
      }
    }
  }
  else {
    *param_3 = local_3c;
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = local_24;
      param_4[1] = local_20;
      param_4[2] = local_1c;
      return;
    }
  }
  return;
}


