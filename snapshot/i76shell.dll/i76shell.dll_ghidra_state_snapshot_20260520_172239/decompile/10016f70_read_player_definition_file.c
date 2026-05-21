/*
 * Program: i76shell.dll
 * Function: read_player_definition_file
 * Entry: 10016f70
 * Signature: undefined __cdecl read_player_definition_file(undefined4 param_1, undefined4 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl read_player_definition_file(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  FILE *_File;
  int iVar2;
  undefined1 local_70 [16];
  undefined4 auStack_60 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined2 uStack_c;
  undefined4 uStack_8;
  undefined1 uStack_4;
  
  puVar1 = (undefined4 *)(**(code **)(DAT_10058198 + 0x48))(local_70);
  DAT_100477a0 = *puVar1;
  DAT_100477a4 = puVar1[1];
  DAT_100477a8 = puVar1[2];
  DAT_100477ac = puVar1[3];
  _File = fopen(s_I76PLYR_DEF_100479a0,s_rb_1004799c);
  if (_File != (FILE *)0x0) {
    fread(auStack_60,0x60,1,_File);
    fclose(_File);
    if (param_2 != (undefined4 *)0x0) {
      puVar1 = auStack_60;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_2 = *puVar1;
        puVar1 = puVar1 + 1;
        param_2 = param_2 + 1;
      }
    }
    DAT_100477a0 = uStack_20;
    DAT_100477a4 = uStack_1c;
    DAT_100477a8 = uStack_18;
    DAT_100477ac = uStack_14;
    DAT_100477b0 = uStack_10;
    DAT_100477b4 = uStack_c;
    _DAT_100cc858 = uStack_8;
    DAT_100477b8 = uStack_4;
  }
  return;
}


