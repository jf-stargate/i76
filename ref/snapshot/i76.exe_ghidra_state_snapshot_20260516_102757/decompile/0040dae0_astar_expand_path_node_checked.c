/*
 * Program: i76.exe
 * Function: astar_expand_path_node_checked
 * Entry: 0040dae0
 * Signature: undefined __cdecl astar_expand_path_node_checked(int * param_1, int param_2, int * param_3)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Astar ran out of memory - path to long */

void __cdecl astar_expand_path_node_checked(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int local_18;
  int local_14;
  int local_10;
  
  local_18 = -1;
  local_14 = -1;
  local_10 = -1;
  piVar6 = param_1 + 0xe;
  *param_3 = 0;
  iVar1 = *piVar6;
  while (iVar1 != 0) {
    iVar2 = param_1[4];
    iVar3 = param_1[5];
    piVar4 = (int *)*piVar6;
    iVar1 = *param_1;
    iVar7 = param_1[1];
    iVar5 = piVar4[1];
    if (iVar1 < *piVar4) {
      if (iVar7 < iVar5) {
        iVar7 = 1;
      }
      else {
        iVar7 = ((iVar7 <= iVar5) - 1 & 0xfffffffe) + 6;
      }
    }
    else if (*piVar4 < iVar1) {
      if (iVar7 < iVar5) {
        iVar7 = 2;
      }
      else {
        iVar7 = ((iVar7 <= iVar5) - 1 & 0xfffffffe) + 7;
      }
    }
    else {
      iVar7 = ((iVar5 <= iVar7) - 1 & 0xfffffffd) + 3;
    }
    if ((((local_10 != iVar7) || (iVar2 != local_18)) || (piVar4[4] != iVar2)) ||
       ((iVar3 != local_14 || (piVar4[5] != iVar3)))) {
      *(float *)(param_2 + *param_3 * 0xc) = (float)iVar1;
      *(float *)(param_2 + 4 + *param_3 * 0xc) = (float)param_1[1];
      if (param_1[5] == 0) {
        if (param_1[4] == 0) {
          *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0;
        }
        else {
          *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0x3f800000;
        }
      }
      else {
        *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0x40000000;
      }
      iVar1 = *param_3;
      *param_3 = iVar1 + 1;
      if (1999 < iVar1 + 1) {
        report_chunk_parse_error();
      }
    }
    param_1 = (int *)*piVar6;
    piVar6 = param_1 + 0xe;
    local_18 = iVar2;
    local_14 = iVar3;
    local_10 = iVar7;
    iVar1 = param_1[0xe];
  }
  *(float *)(param_2 + *param_3 * 0xc) = (float)*param_1;
  *(float *)(param_2 + 4 + *param_3 * 0xc) = (float)param_1[1];
  if (param_1[5] == 0) {
    if (param_1[4] == 0) {
      *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0;
    }
    else {
      *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0x3f800000;
    }
  }
  else {
    *(undefined4 *)(param_2 + 8 + *param_3 * 0xc) = 0x40000000;
  }
  iVar1 = *param_3;
  *param_3 = iVar1 + 1;
  if (1999 < iVar1 + 1) {
    report_chunk_parse_error();
  }
  return;
}


