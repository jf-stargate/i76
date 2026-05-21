/*
 * Program: i76shell.dll
 * Function: is_special_equipment_part_type
 * Entry: 100342f0
 * Signature: undefined4 __cdecl is_special_equipment_part_type(int param_1)
 */


undefined4 __cdecl is_special_equipment_part_type(int param_1)

{
  if ((((param_1 != 0xb) && (param_1 != 8)) && (param_1 != 6)) && (param_1 != 7)) {
    return 0;
  }
  return 1;
}


