/*
 * Program: i76.exe
 * Function: world_object_callback_table_entry_helper_0046ee40
 * Entry: 0046ee40
 * Signature: undefined __cdecl world_object_callback_table_entry_helper_0046ee40(int param_1, undefined4 * param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object callback table entry
   helper based on adjacent named subsystem context. */

void __cdecl world_object_callback_table_entry_helper_0046ee40(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (*(undefined4 **)(param_1 + 0x70) != (undefined4 *)0x0) {
    puVar2 = *(undefined4 **)(param_1 + 0x70);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_2;
      param_2 = param_2 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  return;
}


