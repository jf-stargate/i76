/*
 * Program: i76.exe
 * Function: weapon_fire_request_context_helper_004a4c50
 * Entry: 004a4c50
 * Signature: undefined4 __cdecl weapon_fire_request_context_helper_004a4c50(int param_1)
 */


/* cgpt readability rename set D v16: Readability pass set D: weapon fire request context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl weapon_fire_request_context_helper_004a4c50(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  if (0 < g_weapon_runtime_slot_count) {
    puVar2 = &g_weapon_runtime_slot_table;
    do {
      if (puVar2[2] == param_1) goto LAB_004a4c75;
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x13;
    } while (iVar1 < g_weapon_runtime_slot_count);
  }
  puVar2 = (undefined4 *)0x0;
LAB_004a4c75:
  if (puVar2 == (undefined4 *)0x0) {
    return 0;
  }
  return puVar2[3];
}


