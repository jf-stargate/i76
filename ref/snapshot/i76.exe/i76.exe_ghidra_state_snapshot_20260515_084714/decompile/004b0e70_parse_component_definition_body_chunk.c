/*
 * Program: i76.exe
 * Function: parse_component_definition_body_chunk
 * Entry: 004b0e70
 * Signature: undefined4 __cdecl parse_component_definition_body_chunk(int * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] Shared callback
   used for ENGN/BRAK/SUSP component body chunks. */

undefined4 __cdecl parse_component_definition_body_chunk(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  piVar3 = param_1 + 2;
  iVar1 = *param_1;
  if (iVar1 == 0x4b415242) {
    iVar1 = *(int *)(param_2 + 0x44);
    if (*(int *)(param_2 + 0x3c) == iVar1) {
      piVar4 = (int *)(param_2 + 0x48);
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar4 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      }
      *(short *)piVar4 = (short)*piVar3;
      *(undefined4 *)(param_2 + 0x40) = 1;
    }
    *(int *)(param_2 + 0x44) = iVar1 + 1;
    return 1;
  }
  if (iVar1 != 0x4e474e45) {
    if (iVar1 != 0x50535553) {
      report_chunk_parse_error();
      return 0;
    }
    iVar1 = *(int *)(param_2 + 0x7c);
    if (*(int *)(param_2 + 0x74) == iVar1) {
      piVar4 = (int *)(param_2 + 0x80);
      for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar4 = *piVar3;
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
      }
      *(short *)piVar4 = (short)*piVar3;
      *(undefined4 *)(param_2 + 0x78) = 1;
    }
    *(int *)(param_2 + 0x7c) = iVar1 + 1;
    return 1;
  }
  iVar1 = *(int *)(param_2 + 0xc);
  iVar2 = parse_world_object_placement_field_helper_00469f10(*(int *)(param_2 + 4));
  if (iVar2 == iVar1) {
    piVar4 = (int *)(param_2 + 0x10);
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar4 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    }
    *(short *)piVar4 = (short)*piVar3;
    *(undefined4 *)(param_2 + 8) = 1;
  }
  *(int *)(param_2 + 0xc) = iVar1 + 1;
  return 1;
}


