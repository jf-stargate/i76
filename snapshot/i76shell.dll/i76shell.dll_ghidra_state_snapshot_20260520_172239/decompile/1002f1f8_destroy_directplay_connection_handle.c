/*
 * Program: i76shell.dll
 * Function: destroy_directplay_connection_handle
 * Entry: 1002f1f8
 * Signature: undefined __stdcall destroy_directplay_connection_handle(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void destroy_directplay_connection_handle(void)

{
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  double dVar1;
  undefined4 local_420;
  undefined4 local_41c;
  undefined1 local_416 [2];
  undefined4 local_414;
  undefined1 local_40e [2];
  undefined1 local_40c [1036];
  
  if (DAT_100f4ee8 != 0) {
    dpClose(DAT_100f4ee8);
    dpSetGameServer(DAT_100f4ee8,0);
    time((time_t *)&local_41c);
    do {
      local_420 = 0x400;
      dpReceive(DAT_100f4ee8,local_416,local_40e,0,local_40c,&local_420);
      time((time_t *)&local_414);
      dVar1 = difftime(CONCAT44(local_41c,local_414),CONCAT44(unaff_ESI,unaff_EBX));
    } while (dVar1 < _DAT_10041ea8);
    dpDestroy(DAT_100f4ee8,0);
    DAT_100f4ee8 = 0;
  }
  return;
}


