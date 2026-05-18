/*
 * Program: I76EDIT.EXE
 * Function: setSBCS
 * Entry: 00427fe0
 * Signature: undefined __cdecl setSBCS(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    _setSBCS
   
   Library: Visual Studio 1998 Release */

void __cdecl setSBCS(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00438a70;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)puVar2 = 0;
  DAT_00438b80 = 0;
  DAT_00438b74 = 0;
  _DAT_00438b78 = 0;
  DAT_00438b84 = 0;
  DAT_00438b88 = 0;
  return;
}


