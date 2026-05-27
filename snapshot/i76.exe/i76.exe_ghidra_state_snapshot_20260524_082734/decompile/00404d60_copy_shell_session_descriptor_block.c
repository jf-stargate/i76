/*
 * Program: i76.exe
 * Function: copy_shell_session_descriptor_block
 * Entry: 00404d60
 * Signature: undefined __cdecl copy_shell_session_descriptor_block(undefined4 * param_1)
 */


/* [cgpt i76.exe mission/resource rename v13; confidence=high] Copies the 0x66-dword shell session
   descriptor block from global shell launch output. */

void __cdecl copy_shell_session_descriptor_block(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &g_shell_session_descriptor_block;
  for (iVar1 = 0x66; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


