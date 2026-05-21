/*
 * Program: i76shell.dll
 * Function: find_current_directplay_session_desc
 * Entry: 10030748
 * Signature: undefined4 * __stdcall find_current_directplay_session_desc(void)
 */


undefined4 * find_current_directplay_session_desc(void)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  
  iVar1 = 0;
  if (DAT_100f224c < 1) {
    return (undefined4 *)0x0;
  }
  pcVar3 = &DAT_100f2357;
  do {
    iVar2 = 2;
    bVar6 = true;
    pcVar4 = &stack0x00000013;
    pcVar5 = pcVar3;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar6 = *pcVar4 == *pcVar5;
      pcVar4 = pcVar4 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar6);
    if (bVar6) {
      return &DAT_100f2328 + iVar1 * 0x24;
    }
    iVar1 = iVar1 + 1;
    pcVar3 = pcVar3 + 0x90;
    if (DAT_100f224c <= iVar1) {
      return (undefined4 *)0x0;
    }
  } while( true );
}


