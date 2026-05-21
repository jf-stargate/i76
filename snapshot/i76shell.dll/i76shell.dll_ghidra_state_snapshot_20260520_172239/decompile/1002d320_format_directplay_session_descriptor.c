/*
 * Program: i76shell.dll
 * Function: format_directplay_session_descriptor
 * Entry: 1002d320
 * Signature: undefined __cdecl format_directplay_session_descriptor(undefined4 * param_1)
 */


void __cdecl format_directplay_session_descriptor(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_100f1db8;
  for (iVar1 = 0x66; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


