/*
 * Program: i76.exe
 * Function: enumerate_logical_drives
 * Entry: 00470cd0
 * Signature: undefined __stdcall enumerate_logical_drives(void)
 */


/* i76 first-pass rename
   old_name: FUN_00470cd0
   suggested_name: enumerate_logical_drives
   basis: Uses GetLogicalDrives/GetDriveTypeA to enumerate drives. */

void enumerate_logical_drives(void)

{
  DWORD DVar1;
  UINT UVar2;
  char cVar3;
  int iVar4;
  undefined *local_10 [4];
  
  local_10[0] = PTR_DAT_004f8bac;
  DVar1 = GetLogicalDrives();
  cVar3 = '\0';
  iVar4 = 0;
  do {
    if ((DVar1 & 1 << ((byte)iVar4 & 0x1f)) != 0) {
      local_10[0] = (undefined *)CONCAT31(local_10[0]._1_3_,cVar3 + 'A');
      UVar2 = GetDriveTypeA((LPCSTR)local_10);
      if (UVar2 == 5) {
        (&DAT_00609520)[iVar4] = 1;
      }
    }
    cVar3 = cVar3 + '\x01';
    iVar4 = iVar4 + 1;
  } while (cVar3 < '\x1a');
  return;
}


