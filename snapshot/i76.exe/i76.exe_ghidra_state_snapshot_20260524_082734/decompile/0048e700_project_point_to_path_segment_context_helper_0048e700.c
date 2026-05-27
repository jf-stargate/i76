/*
 * Program: i76.exe
 * Function: project_point_to_path_segment_context_helper_0048e700
 * Entry: 0048e700
 * Signature: undefined __cdecl project_point_to_path_segment_context_helper_0048e700(float param_1, undefined4 param_2, float param_3, int * param_4, int * param_5)
 */


/* cgpt readability rename set D v16: Readability pass set D: project point to path segment context
   helper based on adjacent named subsystem context. */

void __cdecl
project_point_to_path_segment_context_helper_0048e700
          (float param_1,undefined4 param_2,float param_3,int *param_4,int *param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  bool bVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  double *pdVar13;
  int iVar14;
  int *local_b8;
  int local_b4;
  double local_b0;
  int *local_9c;
  undefined8 local_88;
  int local_80 [2];
  undefined8 local_78;
  undefined4 local_70 [27];
  
  local_b4 = 0;
  local_b0 = 1e+30;
  local_b8 = (int *)0x0;
  iVar9 = world_reader_record_table_context_helper_004b8970();
  if (iVar9 != 0) {
    iVar9 = world_reader_record_table_context_helper_004b8970();
    if (iVar9 != 0) {
      piVar12 = local_80;
      local_9c = piVar12;
      do {
        fVar6 = param_1 - *(float *)(iVar9 + 0x18);
        fVar5 = param_3 - *(float *)(iVar9 + 0x20);
        fVar5 = fVar5 * fVar5 + fVar6 * fVar6;
        if (fVar5 <= (float)local_b0) {
          if (local_b4 < 8) {
            *(double *)(piVar12 + -2) = (double)fVar5;
            *piVar12 = iVar9;
            local_b4 = local_b4 + 1;
            local_9c = piVar12 + 4;
            local_b8 = (int *)local_b4;
          }
          else {
            local_88 = (double)fVar5;
            local_80[0] = iVar9;
          }
          do {
            bVar8 = false;
            if (1 < local_b4) {
              iVar10 = local_b4 + -1;
              pdVar13 = (double *)&local_78;
              do {
                if (pdVar13[-2] < *pdVar13) {
                  uVar1 = *(undefined4 *)pdVar13;
                  uVar2 = *(undefined4 *)((int)pdVar13 + 4);
                  uVar3 = *(undefined4 *)(pdVar13 + 1);
                  uVar4 = *(undefined4 *)((int)pdVar13 + 0xc);
                  *(undefined4 *)pdVar13 = *(undefined4 *)(pdVar13 + -2);
                  *(undefined4 *)((int)pdVar13 + 4) = *(undefined4 *)((int)pdVar13 + -0xc);
                  *(undefined4 *)(pdVar13 + 1) = *(undefined4 *)(pdVar13 + -1);
                  *(undefined4 *)((int)pdVar13 + 0xc) = *(undefined4 *)((int)pdVar13 + -4);
                  *(undefined4 *)(pdVar13 + -2) = uVar1;
                  *(undefined4 *)((int)pdVar13 + -0xc) = uVar2;
                  *(undefined4 *)(pdVar13 + -1) = uVar3;
                  *(undefined4 *)((int)pdVar13 + -4) = uVar4;
                  bVar8 = true;
                  local_b4 = (int)local_b8;
                }
                pdVar13 = pdVar13 + 2;
                iVar10 = iVar10 + -1;
              } while (iVar10 != 0);
            }
          } while (bVar8);
          local_b0 = local_88;
          piVar12 = local_9c;
        }
        iVar9 = *(int *)(iVar9 + 4);
      } while (iVar9 != 0);
    }
    fVar5 = 1e+30;
    if (0 < local_b4) {
      local_b8 = local_80;
      do {
        iVar10 = 0;
        iVar9 = *local_b8;
        if (0 < *(int *)(iVar9 + 0x14)) {
          iVar14 = 0;
          do {
            iVar11 = *(int *)(iVar9 + 0x28) + iVar14;
            fVar7 = *(float *)(iVar11 + 0xc) - param_1;
            fVar6 = *(float *)(iVar11 + 0x14) - param_3;
            fVar6 = fVar6 * fVar6 + fVar7 * fVar7;
            if (fVar6 <= fVar5) {
              *param_4 = iVar9;
              *param_5 = iVar10;
              fVar5 = fVar6;
            }
            iVar10 = iVar10 + 1;
            iVar14 = iVar14 + 0x18;
          } while (iVar10 < *(int *)(iVar9 + 0x14));
        }
        local_b8 = local_b8 + 4;
        local_b4 = local_b4 + -1;
      } while (local_b4 != 0);
    }
    return;
  }
  *param_4 = 0;
  return;
}


