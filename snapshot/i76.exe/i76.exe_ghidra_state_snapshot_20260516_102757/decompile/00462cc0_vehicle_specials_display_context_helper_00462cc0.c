/*
 * Program: i76.exe
 * Function: vehicle_specials_display_context_helper_00462cc0
 * Entry: 00462cc0
 * Signature: int __cdecl vehicle_specials_display_context_helper_00462cc0(int param_1)
 */


/* cgpt label refinement v19: was
   radar_classifier_specials_vehicle_specials_display_helper_00462cc0. Shorten readability label. */

int __cdecl vehicle_specials_display_context_helper_00462cc0(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  float local_30;
  
  iVar7 = 0;
  local_30 = 3.4028235e+38;
  if (param_1 != 0) {
    if (0 < g_network_weapon_runtime_actor_count) {
      puVar5 = &g_network_weapon_runtime_actor_entries;
      iVar6 = g_network_weapon_runtime_actor_count;
      do {
        iVar1 = *(int *)*puVar5;
        if (((*(uint *)(iVar1 + 0x10) & 0x200) == 0) &&
           (fVar2 = (float)*(double *)(iVar1 + 0x40) - (float)*(double *)(param_1 + 0x40),
           fVar4 = (float)*(double *)(iVar1 + 0x48) - (float)*(double *)(param_1 + 0x48),
           fVar3 = (float)*(double *)(iVar1 + 0x50) - (float)*(double *)(param_1 + 0x50),
           fVar2 = fVar3 * fVar3 + fVar4 * fVar4 + fVar2 * fVar2, fVar2 < local_30)) {
          iVar7 = iVar1;
          local_30 = fVar2;
        }
        puVar5 = puVar5 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    return iVar7;
  }
  return 0;
}


