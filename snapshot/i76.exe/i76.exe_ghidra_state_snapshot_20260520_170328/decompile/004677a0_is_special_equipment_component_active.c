/*
 * Program: i76.exe
 * Function: is_special_equipment_component_active
 * Entry: 004677a0
 * Signature: undefined4 __cdecl is_special_equipment_component_active(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Predicate for active
   special-equipment runtime component state. */

undefined4 __cdecl is_special_equipment_component_active(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  if ((*(int *)(*(int *)(param_1 + 0x70) + 4) < 1) &&
     (*(int *)(*(int *)(param_1 + 0x70) + 0x10) == 0)) {
    return 0;
  }
  return 1;
}


