/*
 * Program: i76.exe
 * Function: parse_wdf_weapon_definition_into_vehicle_slot
 * Entry: 004ae780
 * Signature: undefined4 __cdecl parse_wdf_weapon_definition_into_vehicle_slot(byte * param_1, int param_2, int param_3)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=medium-high] Loads/parses a WDF weapon
   definition referenced from VCFC and installs the resulting weapon runtime slot data. */

undefined4 __cdecl
parse_wdf_weapon_definition_into_vehicle_slot(byte *param_1,int param_2,int param_3)

{
  bool bVar1;
  uint uVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int local_40 [2];
  char local_38 [56];
  
  iVar4 = *(int *)(param_2 + 4);
  piVar5 = local_40;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  piVar5 = (int *)0x0;
  local_40[0] = param_2;
  strncpy(local_38,(char *)param_1,8);
  uVar2 = 0;
  do {
    if (local_38[uVar2] == '.') {
      local_38[uVar2] = '\0';
      break;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 8);
  bVar1 = parse_bwd2_resource_with_descriptor_table
                    (param_1,&WDF_descriptor_table,3,(byte *)local_40);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    return 0;
  }
  if (param_3 == 0) {
    piVar5 = (int *)(iVar4 + 0x2b8);
  }
  else if (param_3 == 2) {
    piVar5 = (int *)(iVar4 + 0x2f8);
  }
  else if (param_3 == 4) {
    piVar5 = (int *)(iVar4 + 0x338);
  }
  if (piVar5 != (int *)0x0) {
    piVar6 = local_40;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar5 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar5 = piVar5 + 1;
    }
  }
  return 1;
}


