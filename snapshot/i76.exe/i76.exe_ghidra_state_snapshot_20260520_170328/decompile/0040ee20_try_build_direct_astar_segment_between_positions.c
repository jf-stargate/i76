/*
 * Program: i76.exe
 * Function: try_build_direct_astar_segment_between_positions
 * Entry: 0040ee20
 * Signature: undefined4 __cdecl try_build_direct_astar_segment_between_positions(int * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int * param_5, int param_6, int param_7, int param_8, float param_9, undefined4 param_10, undefined4 param_11, undefined4 param_12, undefined4 param_13, undefined4 param_14)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Attempts to build a two-point direct A* path segment
   between two world positions when both positions lie near known path segments. */

undefined4 __cdecl
try_build_direct_astar_segment_between_positions
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5,
          int param_6,int param_7,int param_8,float param_9,undefined4 param_10,undefined4 param_11,
          undefined4 param_12,undefined4 param_13,undefined4 param_14)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  float in_stack_0000bba8;
  float in_stack_0000bbac;
  float in_stack_0000bbb0;
  float in_stack_0000bbb4;
  int in_stack_0000bbb8;
  
  zfsf_error_context_helper_004ba0a0();
  uVar6 = param_3;
  project_point_to_path_segment_context_helper_0048e700
            (in_stack_0000bba8,param_3,in_stack_0000bbac,(int *)&param_1,&param_7);
  if (param_1 == (int *)0x0) {
    return 0;
  }
  iVar7 = param_1[10];
  fVar2 = in_stack_0000bba8 - *(float *)(iVar7 + 0xc + param_7 * 0x18);
  fVar3 = in_stack_0000bbac - *(float *)(iVar7 + 0x14 + param_7 * 0x18);
  pfVar1 = (float *)(iVar7 + param_7 * 0x18);
  fVar4 = in_stack_0000bba8 - *pfVar1;
  fVar5 = in_stack_0000bbac - pfVar1[2];
  if ((_DAT_004bc704 < fVar3 * fVar3 + fVar2 * fVar2) &&
     (_DAT_004bc704 < fVar5 * fVar5 + fVar4 * fVar4)) {
    return 0;
  }
  project_point_to_path_segment_context_helper_0048e700
            (in_stack_0000bbb0,uVar6,in_stack_0000bbb4,(int *)&param_5,&param_6);
  if (param_1 == (int *)0x0) {
    return 0;
  }
  iVar7 = param_5[10];
  fVar2 = in_stack_0000bbb0 - *(float *)(iVar7 + 0xc + param_6 * 0x18);
  fVar3 = in_stack_0000bbb4 - *(float *)(iVar7 + 0x14 + param_6 * 0x18);
  pfVar1 = (float *)(iVar7 + param_6 * 0x18);
  fVar4 = in_stack_0000bbb0 - *pfVar1;
  fVar5 = in_stack_0000bbb4 - pfVar1[2];
  if ((_DAT_004bc704 < fVar3 * fVar3 + fVar2 * fVar2) &&
     (_DAT_004bc704 < fVar5 * fVar5 + fVar4 * fVar4)) {
    return 0;
  }
  iVar7 = path_records_share_same_route_object(param_1,param_5);
  if (iVar7 != 0) {
    param_11 = 0x3f800000;
    param_14 = 0x3f800000;
    astar_report_path_too_long(&param_9,2,(int *)&stack0x00005de4,&param_8);
    copy_astar_path_points_to_ai_path_state(in_stack_0000bbb8,(int)&stack0x00005de4,param_8);
    return 1;
  }
  return 0;
}


