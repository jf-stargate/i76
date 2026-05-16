/*
 * Program: i76.exe
 * Function: astar_report_path_too_long
 * Entry: 0040d8f0
 * Signature: undefined __cdecl astar_report_path_too_long(float * param_1, int param_2, int * param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Astar ran out of memory - path to long */

void __cdecl astar_report_path_too_long(float *param_1,int param_2,int *param_3,int *param_4)

{
  float *pfVar1;
  int *piVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  int local_2c;
  int *local_28;
  int *local_24;
  int *local_20;
  int local_1c;
  float local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  float local_4;
  
  piVar2 = param_3;
  local_1c = param_2 + -1;
  iVar5 = 0;
  local_2c = 0;
  pfVar6 = param_1;
  pfVar1 = param_1;
  if (0 < local_1c) {
    do {
      pfVar4 = pfVar1 + 3;
      if (pfVar6[2] == (float)_DAT_004bc670) {
        if (pfVar6[5] == (float)_DAT_004bc670) {
          local_18 = *pfVar6;
          local_10 = pfVar6[1];
          project_point_to_path_segment_context_helper_0048e700
                    (local_18,local_14,local_10,(int *)&local_28,(int *)&local_20);
          local_c = *pfVar4;
          local_4 = pfVar6[4];
          project_point_to_path_segment_context_helper_0048e700
                    (local_c,local_8,local_4,(int *)&param_3,(int *)&local_24);
          iVar3 = path_records_share_same_route_object(local_28,param_3);
          if (iVar3 != 0) {
            build_roadwar_path_waypoints_between_nodes
                      (local_28,local_20,param_3,local_24,piVar2,&local_2c);
            iVar5 = iVar5 + 1;
            pfVar4 = pfVar1 + 6;
            pfVar6 = pfVar6 + 3;
            goto LAB_0040da5e;
          }
        }
        piVar2[local_2c * 3] = (int)*pfVar6;
        piVar2[local_2c * 3 + 1] = (int)pfVar6[1];
        piVar2[local_2c * 3 + 2] = 0x3f800000;
        local_2c = local_2c + 1;
      }
      else {
        piVar2[local_2c * 3] = (int)*pfVar6;
        piVar2[local_2c * 3 + 1] = (int)pfVar6[1];
        piVar2[local_2c * 3 + 2] = (int)pfVar6[2];
        local_2c = local_2c + 1;
      }
LAB_0040da5e:
      iVar5 = iVar5 + 1;
      pfVar6 = pfVar6 + 3;
      pfVar1 = pfVar4;
    } while (iVar5 < local_1c);
  }
  piVar2[local_2c * 3] = (int)param_1[param_2 * 3 + -3];
  piVar2[local_2c * 3 + 1] = (int)param_1[param_2 * 3 + -2];
  piVar2[local_2c * 3 + 2] = (int)param_1[param_2 * 3 + -1];
  local_2c = local_2c + 1;
  if (1999 < local_2c) {
    report_chunk_parse_error();
  }
  *param_4 = local_2c;
  return;
}


