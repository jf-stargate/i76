/*
 * Program: i76.exe
 * Function: parse_component_definition_reference_chunk
 * Entry: 004b0d00
 * Signature: undefined4 __cdecl parse_component_definition_reference_chunk(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] Shared callback
   used for ENGN/BRAK/SUSP chunks in one component descriptor table. */

undefined4 __cdecl parse_component_definition_reference_chunk(int *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  
  fVar3 = _DAT_004bec84;
  iVar4 = *param_1;
  if (iVar4 == 0x4b415242) {
    if (param_2[0xf] == param_2[0x11]) {
      iVar4 = param_1[2];
      iVar2 = *(int *)(*(int *)(*param_2 + 0x3cc) + 0x70);
      *(int *)(iVar2 + 8) = iVar4;
      *(int *)(iVar2 + 4) = iVar4;
      *(int *)(iVar2 + 0xc) = param_1[3];
      *(int *)(iVar2 + 0x14) = param_2[0xf];
      *(float *)(*param_2 + 0xa4) = (float)param_1[4] + *(float *)(*param_2 + 0xa4);
      param_2[0x10] = 1;
    }
    param_2[0x11] = param_2[0x11] + 1;
    return 1;
  }
  if (iVar4 != 0x4e474e45) {
    if (iVar4 != 0x50535553) {
      report_chunk_parse_error();
      return 0;
    }
    if (param_2[0x1d] == param_2[0x1f]) {
      iVar4 = param_1[2];
      piVar1 = *(int **)(*(int *)(*param_2 + 0x3c8) + 0x70);
      piVar1[1] = iVar4;
      *piVar1 = iVar4;
      piVar1[2] = param_2[0x1d];
      iVar4 = param_1[3];
      piVar1[6] = iVar4;
      piVar1[5] = iVar4;
      piVar1[7] = (int)((fVar3 - (float)param_1[4]) * _DAT_004bec88);
      *(float *)(*param_2 + 0xa4) = (float)param_1[5] + *(float *)(*param_2 + 0xa4);
      param_2[0x1e] = 1;
    }
    param_2[0x1f] = param_2[0x1f] + 1;
    return 1;
  }
  iVar4 = parse_world_object_placement_field_helper_00469f10(param_2[1]);
  if (iVar4 == param_2[3]) {
    iVar4 = param_1[2];
    piVar1 = *(int **)(*(int *)(*param_2 + 0x3c4) + 0x70);
    piVar1[1] = iVar4;
    *piVar1 = iVar4;
    piVar1[5] = param_1[3];
    world_object_placement_flags_helper_0046a060((int)piVar1,param_2[1]);
    *(float *)(*param_2 + 0xa4) = (float)param_1[4] + *(float *)(*param_2 + 0xa4);
    param_2[2] = 1;
  }
  param_2[3] = param_2[3] + 1;
  return 1;
}


