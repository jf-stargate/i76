/*
 * Program: i76shell.dll
 * Function: write_multicar_vehicle_definition_file
 * Entry: 10009010
 * Signature: undefined4 __cdecl write_multicar_vehicle_definition_file(int param_1, int param_2)
 */


undefined4 __cdecl write_multicar_vehicle_definition_file(int param_1,int param_2)

{
  FILE *_File;
  int iVar1;
  byte *pbVar2;
  int local_ec [59];
  
  _File = fopen(s_multicar_def_10043ffc,s_wb_10043ff8);
  if (_File != (FILE *)0x0) {
    param_2 = param_2 + -1;
    fwrite(&param_2,4,1,_File);
    iVar1 = 0;
    if (0 < param_2) {
      pbVar2 = (byte *)(param_1 + 0x914);
      do {
        FUN_10008d50(local_ec,pbVar2);
        fwrite(local_ec,0xeb,1,_File);
        iVar1 = iVar1 + 1;
        pbVar2 = pbVar2 + 0x8ec;
      } while (iVar1 < param_2);
    }
    fclose(_File);
    return 1;
  }
  return 0;
}


