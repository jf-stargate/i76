/*
 * Program: i76.exe
 * Function: weapon_mount_context_helper_004a3380
 * Entry: 004a3380
 * Signature: undefined4 __cdecl weapon_mount_context_helper_004a3380(int param_1, undefined4 * param_2)
 */


/* cgpt label refinement v20: was weapon_hardpoint_mount_context_helper_004a3380. Shorten
   readability label. */

undefined4 __cdecl weapon_mount_context_helper_004a3380(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = 0;
  if (0 < g_weapon_runtime_slot_count) {
    puVar3 = &g_weapon_runtime_slot_table;
    do {
      if (puVar3[2] == param_1) goto LAB_004a33a6;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 0x13;
    } while (iVar2 < g_weapon_runtime_slot_count);
  }
  puVar3 = (undefined4 *)0x0;
LAB_004a33a6:
  if (puVar3 == (undefined4 *)0x0) {
    return 3;
  }
  puVar1 = (undefined4 *)puVar3[6] + (puVar3[7] + 1) * 0x16;
  *param_2 = *(undefined4 *)puVar3[6];
  param_2[1] = puVar1[1];
  puVar3 = puVar1 + 4;
  puVar4 = param_2 + 2;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  param_2[0x12] = puVar1[2];
  param_2[0x13] = puVar1[3];
  param_2[0x14] = *puVar1;
  return 1;
}


