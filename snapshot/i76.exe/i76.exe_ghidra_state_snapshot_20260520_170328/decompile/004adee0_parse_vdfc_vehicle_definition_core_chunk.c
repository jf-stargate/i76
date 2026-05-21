/*
 * Program: i76.exe
 * Function: parse_vdfc_vehicle_definition_core_chunk
 * Entry: 004adee0
 * Signature: undefined __cdecl parse_vdfc_vehicle_definition_core_chunk(int param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=high] VDFC callback in the
   vehicle asset descriptor chain; copies core VDF vehicle definition fields. */

void __cdecl parse_vdfc_vehicle_definition_core_chunk(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  iVar1 = param_2[1];
  set_world_object_class_and_register_runtime(*param_2,*(int *)(param_1 + 0x1c));
  iVar2 = *(int *)(*param_2 + 0x70);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0xa4) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(iVar2 + 0x124) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(iVar2 + 0x120) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(iVar2 + 0x47c) = *(undefined4 *)(param_1 + 0x20);
    parse_labeled_data_record((char *)(param_1 + 0x48));
  }
  piVar3 = (int *)(param_1 + 0x24);
  piVar4 = param_2 + 0xf;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  param_2[0x14] = 1;
  *(undefined4 *)(iVar1 + 0xa5c) = *(undefined4 *)(param_1 + 0x44);
  return;
}


