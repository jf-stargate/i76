/*
 * Program: i76.exe
 * Function: weapon_mount_context_helper_004a3280
 * Entry: 004a3280
 * Signature: undefined4 __cdecl weapon_mount_context_helper_004a3280(int param_1)
 */


/* cgpt label refinement v20: was weapon_hardpoint_mount_context_helper_004a3280. Shorten
   readability label. */

undefined4 __cdecl weapon_mount_context_helper_004a3280(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar2 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar2 == param_1) goto LAB_004a32a8;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a32a8:
  return *(undefined4 *)(&DAT_005be798 + iVar1 * 0x2c8);
}


