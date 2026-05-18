/*
 * Program: i76.exe
 * Function: vehicle_effect_runtime_shutdown_helper_00443c50
 * Entry: 00443c50
 * Signature: undefined __stdcall vehicle_effect_runtime_shutdown_helper_00443c50(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: vehicle effect runtime shutdown helper
   based on prior focused closure context. */

void vehicle_effect_runtime_shutdown_helper_00443c50(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = DAT_0052bb90;
  if (DAT_0052bb90 != (undefined4 *)0x0) {
    do {
      puVar2 = DAT_0052bb90;
      DAT_0052bb90 = (undefined4 *)*DAT_0052bb90;
      xfree_global_heap(puVar2);
    } while (DAT_0052bb90 != puVar1);
  }
  DAT_0052bb90 = (undefined4 *)0x0;
  return;
}


