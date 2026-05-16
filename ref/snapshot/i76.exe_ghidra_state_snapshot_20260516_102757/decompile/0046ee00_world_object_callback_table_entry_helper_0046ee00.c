/*
 * Program: i76.exe
 * Function: world_object_callback_table_entry_helper_0046ee00
 * Entry: 0046ee00
 * Signature: undefined __cdecl world_object_callback_table_entry_helper_0046ee00(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object callback table entry
   helper based on adjacent named subsystem context. */

void __cdecl world_object_callback_table_entry_helper_0046ee00(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar1 = *(undefined4 **)(param_1 + 0x70);
  if (puVar1 != (undefined4 *)0x0) {
    puVar4 = (undefined4 *)(param_1 + 0x18);
    puVar5 = puVar1;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    uVar2 = get_root_ancestor_world_object(param_1);
    puVar1[0x12] = uVar2;
  }
  return;
}


