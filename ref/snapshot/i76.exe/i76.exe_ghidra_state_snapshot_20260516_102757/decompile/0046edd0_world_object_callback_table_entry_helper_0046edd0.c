/*
 * Program: i76.exe
 * Function: world_object_callback_table_entry_helper_0046edd0
 * Entry: 0046edd0
 * Signature: undefined __stdcall world_object_callback_table_entry_helper_0046edd0(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object callback table entry
   helper based on adjacent named subsystem context. */

void world_object_callback_table_entry_helper_0046edd0(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = radar_context_helper_0045f3b0(0x50);
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = &DAT_004faed8;
    puVar4 = puVar1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
  }
  return;
}


