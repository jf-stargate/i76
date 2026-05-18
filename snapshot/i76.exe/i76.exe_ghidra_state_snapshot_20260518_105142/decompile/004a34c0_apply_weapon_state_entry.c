/*
 * Program: i76.exe
 * Function: apply_weapon_state_entry
 * Entry: 004a34c0
 * Signature: undefined __cdecl apply_weapon_state_entry(int param_1, int param_2, int param_3, undefined4 param_4)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium] Helper used by WPST callback to
   apply a weapon state entry to a vehicle/world object.
   [cgpt i76.exe vehicle object rename v7; confidence=high] Finds a loaded vehicle and weapon slot,
   then writes WPST state into the global weapon runtime table; reports a chunk parse error on
   invalid mapping. */

void __cdecl apply_weapon_state_entry(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar3 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar3 == param_1) goto LAB_004a34e8;
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a34e8:
  iVar2 = 0;
  piVar3 = (int *)(&DAT_005be530 + iVar1 * 0x2c8);
  do {
    if (*piVar3 == param_2) goto LAB_004a3511;
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 0x16;
  } while (iVar2 < 7);
  iVar2 = -1;
LAB_004a3511:
  iVar1 = *(int *)(&DAT_005be580 + iVar2 * 0x58 + iVar1 * 0x2c8);
  if (iVar1 != -1) {
    (&DAT_005aab14)[iVar1 * 0x13] = param_4;
    if (param_3 != -1) {
      *(int *)(&DAT_005aab28 + iVar1 * 0x4c) = param_3;
    }
    return;
  }
  report_chunk_parse_error();
  return;
}


