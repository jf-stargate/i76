/*
 * Program: i76.exe
 * Function: get_special_equipment_runtime_index
 * Entry: 00467790
 * Signature: undefined4 __cdecl get_special_equipment_runtime_index(int param_1)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Returns the special-equipment
   index stored at runtime component +0x70, or zero for a missing component. */

undefined4 __cdecl get_special_equipment_runtime_index(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return **(undefined4 **)(param_1 + 0x70);
}


