/*
 * Program: i76.exe
 * Function: world_reader_record_handler_context_helper_004b8e00
 * Entry: 004b8e00
 * Signature: undefined4 __cdecl world_reader_record_handler_context_helper_004b8e00(int param_1, int param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record handler context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl world_reader_record_handler_context_helper_004b8e00(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(param_2 + 0x14);
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 1;
}


