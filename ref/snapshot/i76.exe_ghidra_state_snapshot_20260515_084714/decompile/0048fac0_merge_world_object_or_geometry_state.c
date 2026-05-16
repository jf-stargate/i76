/*
 * Program: i76.exe
 * Function: merge_world_object_or_geometry_state
 * Entry: 0048fac0
 * Signature: undefined __cdecl merge_world_object_or_geometry_state(float * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence merge */

void __cdecl merge_world_object_or_geometry_state(float *param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  float fVar3;
  undefined4 *puVar4;
  LPVOID pvVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int *piVar11;
  float fVar12;
  int local_1c;
  int local_14;
  int local_10;
  int local_8;
  
  if (_DAT_004be7c8 < _DAT_006543a4) {
    _DAT_006543a4 = 4096.0;
  }
  local_10 = SUB84((double)(_DAT_006543a4 + (float)_DAT_004faf18),0);
  fVar3 = DAT_006543ac + (float)_DAT_004faf18;
  DAT_00654384 = DAT_006543b0 + local_10 * 3;
  local_14 = local_10 + 1;
  if (0 < local_14) {
    local_1c = local_10;
    do {
      if (0 < (int)DAT_00654384[2]) {
        DAT_0065439c = (undefined4 *)*DAT_00654384;
        do {
          if (((int)DAT_0065439c[3] < 0xc) && (pfVar1 = (float *)*DAT_0065439c, (int)pfVar1 < 0x20))
          {
            puVar10 = (undefined4 *)DAT_0065439c[5];
            if (pfVar1 == (float *)0x0) {
              if (DAT_0065439c[3] == 6) {
                piVar11 = DAT_0065439c + 0xf;
                if (DAT_0065439c[0xf] == 0) {
                  for (piVar6 = DAT_006543b4; piVar6 < DAT_006543a0; piVar6 = piVar6 + 0x24) {
                    if (*piVar6 == DAT_0065439c[7]) {
                      piVar6[2] = local_1c;
                      goto LAB_0048fbe3;
                    }
                  }
                  piVar6 = (int *)0x0;
LAB_0048fbe3:
                  *piVar11 = (int)piVar6;
                  if (piVar6 != (int *)0x0) {
                    iVar9 = piVar6[3];
                    iVar2 = piVar6[2];
                    iVar8 = iVar2;
                    if (0 < iVar9) {
                      piVar6 = piVar6 + 7;
                      piVar7 = piVar6;
                      do {
                        if (*piVar7 < iVar8) {
                          iVar8 = *piVar6;
                        }
                        piVar7 = piVar7 + 4;
                        piVar6 = piVar6 + 4;
                        iVar9 = iVar9 + -1;
                      } while (iVar9 != 0);
                    }
                    if (iVar8 != iVar2) {
                      local_8 = SUB84((double)fVar3,0);
                      DAT_006543c0 = DAT_0065439c;
                      DAT_0065439c[6] = 0;
                      iVar8 = iVar8 + local_8;
                      DAT_006543c0[5] = 0;
                      puVar4 = DAT_00654384;
                      if (local_1c < iVar8) {
                        iVar8 = local_1c + -1;
                      }
                      fVar12 = (float)iVar8;
                      if ((float)iVar8 < DAT_006543ac) {
                        fVar12 = DAT_006543ac;
                      }
                      terrain_map_context_helper_0048fe10(fVar12);
                      DAT_00654384 = puVar4;
                      *(int *)(*piVar11 + 8) = iVar8;
                      goto LAB_0048fcec;
                    }
                  }
                  (*(code *)(&PTR_LAB_004faca8)[DAT_0065439c[3]])(DAT_0065439c,param_1);
                }
                else {
                  (*(code *)PTR_dispatch_world_object_geometry_render_pass_004facc0)
                            (DAT_0065439c,param_1);
                }
              }
              else {
                DAT_0065439c[0xf] = 0;
                (*(code *)(&PTR_LAB_004faca8)[DAT_0065439c[3]])(DAT_0065439c,param_1);
              }
            }
            else if (*(int *)((int)param_1[0xf] + 8) == 1) {
              log_cache_memory_status
                        (param_1,(float *)(DAT_0065439c + 7),pfVar1,(uint *)DAT_0065439c[1],
                         (float *)DAT_0065439c[2]);
            }
            else {
              submit_lit_textured_polygon_to_renderer
                        (param_1,(float *)(DAT_0065439c + 7),(int)pfVar1,(uint *)DAT_0065439c[1],
                         (uint)DAT_0065439c[2]);
            }
          }
          else {
            puVar10 = (undefined4 *)0x0;
          }
LAB_0048fcec:
          DAT_0065439c = puVar10;
        } while (puVar10 != (undefined4 *)0x0);
        DAT_00654384[2] = 0;
        DAT_00654384[1] = 0;
        *DAT_00654384 = 0;
      }
      local_1c = local_1c + -1;
      DAT_00654384 = DAT_00654384 + -3;
      local_14 = local_14 + -1;
    } while (local_14 != 0);
  }
  if (DAT_0059c498 != 0) {
    puVar10 = DAT_00654388;
    for (iVar8 = 0x3000; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    DAT_0059c498 = 0;
    DAT_006543b8 = DAT_006543bc;
  }
  puVar10 = DAT_006543b0;
  for (iVar8 = 0x3000; iVar8 != 0; iVar8 = iVar8 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  DAT_006543c0 = (undefined4 *)DAT_00654398;
  if (param_2 != 0) {
    iVar8 = 0;
    if (0 < DAT_0059c540) {
      puVar10 = &DAT_0059c4a4;
      do {
        pvVar5 = release_world_object_tree_reference(*(LPVOID *)*puVar10,s_merge_004fad14);
        if (pvVar5 != (LPVOID)0x0) {
          finalize_released_world_object_after_damage(pvVar5,s_merge_004fad14);
        }
        iVar8 = iVar8 + 1;
        puVar10 = puVar10 + 2;
      } while (iVar8 < DAT_0059c540);
    }
    DAT_006543a0 = DAT_006543b4;
    DAT_0059c540 = 0;
    piVar11 = DAT_006543b4;
    for (iVar8 = 0x2d0; iVar8 != 0; iVar8 = iVar8 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
  }
  DAT_006543ac = 1e+06;
  _DAT_006543a4 = -1e+06;
  return;
}


