/*
 * Program: i76shell.dll
 * Function: shutdown_directplay_session_and_thread
 * Entry: 1002e9b7
 * Signature: undefined __stdcall shutdown_directplay_session_and_thread(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void shutdown_directplay_session_and_thread(void)

{
  int iVar1;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 *puVar2;
  double dVar3;
  undefined4 local_420;
  undefined4 local_41c;
  undefined1 local_416 [2];
  undefined4 local_414;
  undefined1 local_40e [2];
  undefined1 local_40c [1036];
  
  if (DAT_100f3548 != (HANDLE)0x0) {
    WaitForSingleObject(DAT_100f3548,0xffffffff);
    CloseHandle(DAT_100f3548);
    DAT_100f3548 = (HANDLE)0x0;
  }
  if (DAT_100f4ee8 != 0) {
    dpClose(DAT_100f4ee8);
    dpSetGameServer(DAT_100f4ee8,0);
    time((time_t *)&local_41c);
    do {
      local_420 = 0x400;
      dpReceive(DAT_100f4ee8,local_416,local_40e,0,local_40c,&local_420);
      time((time_t *)&local_414);
      dVar3 = difftime(CONCAT44(local_41c,local_414),CONCAT44(unaff_ESI,unaff_EDI));
    } while (dVar3 < _DAT_10041ea8);
    dpDestroy(DAT_100f4ee8,0);
    DAT_100f4ee8 = 0;
  }
  puVar2 = DAT_100f231c;
  for (iVar1 = 0x8c; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


