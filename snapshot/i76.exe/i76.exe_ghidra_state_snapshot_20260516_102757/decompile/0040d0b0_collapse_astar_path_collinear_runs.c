/*
 * Program: i76.exe
 * Function: collapse_astar_path_collinear_runs
 * Entry: 0040d0b0
 * Signature: undefined __stdcall collapse_astar_path_collinear_runs(void)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Compacts/collapses path points with
   collinear/continuation flags into a simplified output path. */

void collapse_astar_path_collinear_runs(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  undefined4 *puVar7;
  float *pfVar8;
  int iVar9;
  int iStack00000004;
  int *piStack00000008;
  undefined4 in_stack_00000010;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000028;
  int in_stack_00003eb4;
  int in_stack_00003eb8;
  float *in_stack_00003ebc;
  int *in_stack_00003ec0;
  
  zfsf_error_context_helper_004ba0a0();
  iStack00000004 = 0;
  iVar9 = 0;
  if (0 < in_stack_00003eb8) {
    puVar7 = (undefined4 *)&stack0x00000030;
    for (iVar2 = in_stack_00003eb8; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    iVar2 = iVar9;
    if (0 < in_stack_00003eb8) {
      do {
        iVar1 = iStack00000004;
        pfVar5 = (float *)(in_stack_00003eb4 + iStack00000004 * 0xc);
        if ((*(int *)(in_stack_00003eb4 + 8 + iStack00000004 * 0xc) == 0x3f800000) &&
           (iVar4 = in_stack_00003eb8 + -1, iStack00000004 < iVar4)) {
          *in_stack_00003ebc = *pfVar5;
          in_stack_00003ebc[1] = pfVar5[1];
          in_stack_00003ebc[2] = pfVar5[2];
          iVar9 = iVar2 + 1;
          pfVar8 = in_stack_00003ebc + 3;
          if (pfVar5[5] != 1.0) goto LAB_0040d320;
          iVar6 = iStack00000004 + 1;
          if (iVar6 < iVar4) {
            piVar3 = (int *)(in_stack_00003eb4 + 0x14 + iVar6 * 0xc);
            do {
              if (*piVar3 != 0x3f800000) break;
              iVar6 = iVar6 + 1;
              piVar3 = piVar3 + 3;
            } while (iVar6 < iVar4);
          }
          piStack00000008 = (int *)(&stack0x00000030 + iStack00000004 * 4);
          if (*(int *)(&stack0x00000030 + iStack00000004 * 4) == 0) {
            project_point_to_path_segment_context_helper_0048e700
                      (*pfVar5,in_stack_00000010,pfVar5[1],piStack00000008,
                       (int *)(&stack0x00001f70 + iStack00000004 * 4));
          }
          if (*(int *)(&stack0x00000030 + iVar6 * 4) == 0) {
            project_point_to_path_segment_context_helper_0048e700
                      (*(float *)(in_stack_00003eb4 + iVar6 * 0xc),in_stack_00000028,
                       *(float *)(in_stack_00003eb4 + iVar6 * 0xc + 4),
                       (int *)(&stack0x00000030 + iVar6 * 4),(int *)(&stack0x00001f70 + iVar6 * 4));
          }
          iVar4 = path_records_share_same_route_object
                            ((int *)*piStack00000008,*(int **)(&stack0x00000030 + iVar6 * 4));
          if ((iVar4 == 0) && (iVar1 + 1 != iVar6)) {
            iVar6 = iVar6 + -1;
            if (iVar6 != iVar1) {
              pfVar5 = (float *)(in_stack_00003eb4 + iVar6 * 0xc);
              do {
                if (*(int *)(&stack0x00000030 + iVar6 * 4) == 0) {
                  project_point_to_path_segment_context_helper_0048e700
                            (*pfVar5,in_stack_0000001c,pfVar5[1],
                             (int *)(&stack0x00000030 + iVar6 * 4),
                             (int *)(&stack0x00001f70 + iVar6 * 4));
                }
                iVar1 = path_records_share_same_route_object
                                  ((int *)*piStack00000008,*(int **)(&stack0x00000030 + iVar6 * 4));
                if (iVar1 != 0) break;
                iVar6 = iVar6 + -1;
                pfVar5 = pfVar5 + -3;
              } while (iVar6 != iStack00000004);
              if (iVar6 != iStack00000004) {
                iVar1 = in_stack_00003eb4 + iVar6 * 0xc;
                *pfVar8 = *(float *)(in_stack_00003eb4 + iVar6 * 0xc);
                in_stack_00003ebc[4] = *(float *)(iVar1 + 4);
                iVar9 = iVar2 + 2;
                in_stack_00003ebc[5] = *(float *)(iVar1 + 8);
                pfVar8 = in_stack_00003ebc + 6;
              }
            }
            iStack00000004 = iVar6 + 1;
          }
          else {
            iStack00000004 = iVar6 + 1;
            iVar1 = in_stack_00003eb4 + iVar6 * 0xc;
            *pfVar8 = *(float *)(in_stack_00003eb4 + iVar6 * 0xc);
            in_stack_00003ebc[4] = *(float *)(iVar1 + 4);
            iVar9 = iVar2 + 2;
            in_stack_00003ebc[5] = *(float *)(iVar1 + 8);
            pfVar8 = in_stack_00003ebc + 6;
          }
        }
        else {
          *in_stack_00003ebc = *pfVar5;
          in_stack_00003ebc[1] = pfVar5[1];
          in_stack_00003ebc[2] = pfVar5[2];
LAB_0040d320:
          iVar9 = iVar2 + 1;
          pfVar8 = in_stack_00003ebc + 3;
          iStack00000004 = iStack00000004 + 1;
        }
        in_stack_00003ebc = pfVar8;
        iVar2 = iVar9;
      } while (iStack00000004 < in_stack_00003eb8);
    }
  }
  *in_stack_00003ec0 = iVar9;
  return;
}


