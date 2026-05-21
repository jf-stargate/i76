/*
 * Program: i76shell.dll
 * Function: release_directplay_interface
 * Entry: 10022d10
 * Signature: undefined __stdcall release_directplay_interface(undefined4 * param_1)
 */


void release_directplay_interface(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if ((undefined4 *)param_1[0x17] != (undefined4 *)0x0) {
    puVar2 = (undefined4 *)param_1[0x17];
    for (iVar1 = 0xb8; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }
  *(undefined4 *)param_1[0x16] = 0;
  dpEnumPlayers(*param_1,param_1 + 1,&LAB_10022e50,param_1,10000);
  return;
}


