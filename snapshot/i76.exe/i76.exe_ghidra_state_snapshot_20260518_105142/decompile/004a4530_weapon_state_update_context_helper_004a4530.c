/*
 * Program: i76.exe
 * Function: weapon_state_update_context_helper_004a4530
 * Entry: 004a4530
 * Signature: undefined4 __cdecl weapon_state_update_context_helper_004a4530(int param_1, int param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: weapon state update context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl weapon_state_update_context_helper_004a4530(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;
  
  uVar3 = 0;
  iVar4 = 0;
  if (0 < g_weapon_runtime_slot_count) {
    puVar5 = &g_weapon_runtime_slot_table;
    do {
      if (puVar5[2] == param_1) goto LAB_004a455a;
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 0x13;
    } while (iVar4 < g_weapon_runtime_slot_count);
  }
  puVar5 = (undefined4 *)0x0;
LAB_004a455a:
  if (puVar5 == (undefined4 *)0x0) {
    return 0;
  }
  iVar4 = 0;
  puVar6 = (uint *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar4 & 0x1f)) != 0) {
      uVar1 = puVar5[3];
      uVar2 = *puVar6;
      if (uVar1 < uVar2) {
        uVar3 = 1;
        *puVar6 = uVar2 - uVar1;
        puVar5[3] = 0;
      }
      else {
        puVar5[3] = uVar1 - uVar2;
        *puVar6 = 0;
      }
    }
    iVar4 = iVar4 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar4 < 4);
  return uVar3;
}


