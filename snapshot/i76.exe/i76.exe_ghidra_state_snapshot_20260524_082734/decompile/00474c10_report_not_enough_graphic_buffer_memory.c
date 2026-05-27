/*
 * Program: i76.exe
 * Function: report_not_enough_graphic_buffer_memory
 * Entry: 00474c10
 * Signature: undefined __stdcall report_not_enough_graphic_buffer_memory(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence graphic buffers */

void report_not_enough_graphic_buffer_memory(void)

{
  DAT_0058dac8 = HeapCreate(0,0x60000,0);
  if (DAT_0058dac8 == (HANDLE)0x0) {
    report_error();
  }
  return;
}


