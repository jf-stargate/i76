/*
 * Program: i76.exe
 * Function: world_reader_record_table_context_helper_004b8980
 * Entry: 004b8980
 * Signature: undefined __stdcall world_reader_record_table_context_helper_004b8980(void)
 */


/* cgpt readability rename set E v17: Readability pass set E: world reader record table context
   helper based on adjacent named subsystem context. */

void world_reader_record_table_context_helper_004b8980(void)

{
  LPVOID pvVar1;
  
  while (DAT_005db988 != (LPVOID)0x0) {
    pvVar1 = *(LPVOID *)((int)DAT_005db988 + 4);
    xfree_global_heap(DAT_005db988);
    DAT_005db988 = pvVar1;
  }
  DAT_005db988 = (LPVOID)0x0;
  return;
}


