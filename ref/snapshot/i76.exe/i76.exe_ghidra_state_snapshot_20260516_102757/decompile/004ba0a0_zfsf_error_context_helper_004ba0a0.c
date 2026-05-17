/*
 * Program: i76.exe
 * Function: zfsf_error_context_helper_004ba0a0
 * Entry: 004ba0a0
 * Signature: undefined __stdcall zfsf_error_context_helper_004ba0a0(void)
 */


/* WARNING: Unable to track spacebase fully for stack */
/* cgpt label refinement v20: was zfsf_resource_error_context_helper_004ba0a0. Shorten readability
   label. */

void zfsf_error_context_helper_004ba0a0(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}


