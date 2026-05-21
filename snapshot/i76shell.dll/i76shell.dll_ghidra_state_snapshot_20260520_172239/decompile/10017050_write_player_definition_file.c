/*
 * Program: i76shell.dll
 * Function: write_player_definition_file
 * Entry: 10017050
 * Signature: undefined __cdecl write_player_definition_file(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl write_player_definition_file(undefined4 *param_1)

{
  FILE *_File;
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_60 [16];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar2 = local_60;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *param_1;
      param_1 = param_1 + 1;
      puVar2 = puVar2 + 1;
    }
  }
  local_20 = DAT_100477a0;
  local_1c = DAT_100477a4;
  local_18 = DAT_100477a8;
  local_14 = DAT_100477ac;
  local_10 = DAT_100477b0;
  local_c = DAT_100477b4;
  local_8 = _DAT_100cc858;
  local_4 = DAT_100477b8;
  _File = fopen(s_I76PLYR_DEF_100479b0,s_wb_100479ac);
  if (_File != (FILE *)0x0) {
    fwrite(local_60,0x60,1,_File);
    fclose(_File);
  }
  return;
}


