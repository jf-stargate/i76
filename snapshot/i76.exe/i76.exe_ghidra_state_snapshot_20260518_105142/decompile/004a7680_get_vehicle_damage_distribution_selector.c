/*
 * Program: i76.exe
 * Function: get_vehicle_damage_distribution_selector
 * Entry: 004a7680
 * Signature: undefined4 __cdecl get_vehicle_damage_distribution_selector(int param_1)
 */


/* [cgpt i76.exe damage dispatch rename v19; confidence=HIGH] Returns the first dword selector from
   object runtime data at +0x70, or zero when missing. */

undefined4 __cdecl get_vehicle_damage_distribution_selector(int param_1)

{
  if (*(undefined4 **)(param_1 + 0x70) != (undefined4 *)0x0) {
    return **(undefined4 **)(param_1 + 0x70);
  }
  return 0;
}


