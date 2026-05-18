/*
 * Program: i76.exe
 * Function: special_equipment_state_context_helper_00468040
 * Entry: 00468040
 * Signature: undefined __stdcall special_equipment_state_context_helper_00468040(void)
 */


/* cgpt label refinement v19: was vehicle_specials_runtime_special_equipment_state_helper_00468040.
   Shorten readability label. */

void special_equipment_state_context_helper_00468040(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0054b9f0;
  for (iVar1 = 0x9c7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &DAT_0054fa10;
  for (iVar1 = 0x71; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0xffffffff;
    puVar2 = puVar2 + 1;
  }
  if (DAT_00588df0 < DAT_00588de8) {
    DAT_00588df0 = DAT_00588de8;
  }
  if (DAT_00588df4 < DAT_00588dec) {
    DAT_00588df4 = DAT_00588dec;
  }
  DAT_00588de8 = 0;
  DAT_00588dec = 0;
  return;
}


