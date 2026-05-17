/*
 * Program: i76.exe
 * Function: remove_loaded_vehicle_runtime_and_weapon_slots
 * Entry: 004a3580
 * Signature: undefined __cdecl remove_loaded_vehicle_runtime_and_weapon_slots(int param_1)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=high] Removes one loaded vehicle runtime
   record, compacts g_loaded_vehicle_runtime_table, compacts weapon runtime slots, and rebuilds slot
   back-pointers. */

void __cdecl remove_loaded_vehicle_runtime_and_weapon_slots(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  size_t _NumOfElements;
  size_t sVar6;
  int local_1c [7];
  
  if (param_1 != 0) {
    iVar2 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar1 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar1 == param_1) goto LAB_004a35b5;
        iVar2 = iVar2 + 1;
        piVar1 = piVar1 + 0xb2;
      } while (iVar2 < g_loaded_vehicle_runtime_count);
    }
    iVar2 = -1;
LAB_004a35b5:
    if ((iVar2 != -1) && (iVar2 < g_loaded_vehicle_runtime_count)) {
      _NumOfElements = 0;
      piVar3 = local_1c;
      iVar5 = 7;
      piVar1 = (int *)(&DAT_005be580 + iVar2 * 0x2c8);
      do {
        if (*piVar1 != -1) {
          *piVar3 = *piVar1;
          _NumOfElements = _NumOfElements + 1;
          piVar3 = piVar3 + 1;
        }
        piVar1 = piVar1 + 0x16;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      memmove(&g_loaded_vehicle_runtime_table + iVar2 * 0xb2,&DAT_005be7a0 + iVar2 * 0xb2,
              g_loaded_vehicle_runtime_count * 0x2c8 + iVar2 * -0x2c8);
      iVar2 = g_loaded_vehicle_runtime_count + -1;
      iVar5 = g_loaded_vehicle_runtime_count + -2;
      g_loaded_vehicle_runtime_count = iVar2;
      if (-1 < iVar5) {
        puVar4 = &g_loaded_vehicle_runtime_table + iVar5 * 0xb2;
        do {
          piVar1 = puVar4 + 0x2a;
          iVar5 = 7;
          do {
            if (*piVar1 != -1) {
              (&DAT_005aab20)[*piVar1 * 0x13] = puVar4;
            }
            piVar1 = piVar1 + 0x16;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
          puVar4 = puVar4 + -0xb2;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      if (1 < (int)_NumOfElements) {
        qsort(local_1c,_NumOfElements,4,(_PtFuncCompare *)&LAB_004a3730);
      }
      if (0 < (int)_NumOfElements) {
        piVar1 = local_1c;
        sVar6 = _NumOfElements;
        do {
          iVar2 = *piVar1;
          memmove(&g_weapon_runtime_slot_table + iVar2 * 0x13,&DAT_005aab54 + iVar2 * 0x4c,
                  g_weapon_runtime_slot_count * 0x4c + iVar2 * -0x4c);
          piVar1 = piVar1 + 1;
          sVar6 = sVar6 - 1;
        } while (sVar6 != 0);
      }
      g_weapon_runtime_slot_count = g_weapon_runtime_slot_count - _NumOfElements;
      if ((0 < (int)_NumOfElements) && (iVar2 = g_weapon_runtime_slot_count + -1, -1 < iVar2)) {
        piVar1 = &DAT_005aab24 + iVar2 * 0x13;
        do {
          *(int *)(piVar1[-1] + 0xa8 + *piVar1 * 0x58) = iVar2;
          piVar1[-7] = iVar2;
          iVar2 = iVar2 + -1;
          piVar1 = piVar1 + -0x13;
        } while (-1 < iVar2);
      }
      vehicle_specials_display_context_helper_00462a80();
      mark_active_vehicle_damage_textures_dirty();
    }
  }
  return;
}


