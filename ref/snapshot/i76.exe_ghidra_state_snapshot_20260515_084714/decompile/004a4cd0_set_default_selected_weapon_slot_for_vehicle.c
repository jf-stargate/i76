/*
 * Program: i76.exe
 * Function: set_default_selected_weapon_slot_for_vehicle
 * Entry: 004a4cd0
 * Signature: undefined __cdecl set_default_selected_weapon_slot_for_vehicle(int param_1, int param_2)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=medium_high] Updates the loaded vehicle
   selected weapon slot: clears on false input or selects the first active slot with weapon
   class/type 3. */

void __cdecl set_default_selected_weapon_slot_for_vehicle(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar3 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar3 == param_1) goto LAB_004a4cf8;
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a4cf8:
  if (param_2 == 0) {
    (&DAT_005be4dc)[iVar1 * 0xb2] = 0xffffffff;
    return;
  }
  iVar2 = 0;
  piVar3 = (int *)(iVar1 * 0x2c8 + 0x5be53c);
  do {
    if (*piVar3 == 3) break;
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0x16;
  } while (iVar2 < 5);
  if ((iVar2 == 5) || (*(int *)(&DAT_005be580 + iVar2 * 0x58 + iVar1 * 0x2c8) == -1)) {
    iVar2 = -1;
  }
  (&DAT_005be4dc)[iVar1 * 0xb2] = iVar2;
  return;
}


