/*
 * Program: i76shell.dll
 * Function: write_vehicle_scene_config_file
 * Entry: 10032980
 * Signature: undefined4 __cdecl write_vehicle_scene_config_file(char * param_1)
 */


undefined4 __cdecl write_vehicle_scene_config_file(char *param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  FILE *_File;
  undefined4 *puVar4;
  int local_4;
  
  bVar2 = false;
  bVar1 = false;
  local_4 = 0;
  puVar4 = DAT_100cc500;
  while (((puVar4 != (undefined4 *)0x0 && (puVar4 != DAT_100cc500)) || (!bVar1))) {
    bVar1 = true;
    iVar3 = _stricmp((char *)*puVar4,s_EMPTY_1004ccd0);
    if (iVar3 == 0) {
      puVar4 = (undefined4 *)puVar4[1];
    }
    else {
      local_4 = local_4 + 1;
      puVar4 = (undefined4 *)puVar4[1];
    }
  }
  _File = fopen(param_1,s_wb_1004ccd8);
  if (_File != (FILE *)0x0) {
    fwrite(&DAT_100581a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231,0x8c4,1,_File);
    if (DAT_100f5308 != 0) {
      local_4 = local_4 + *(int *)(DAT_100f5308 + 4);
    }
    fwrite(&local_4,4,1,_File);
    puVar4 = DAT_100cc500;
    while (((puVar4 != (undefined4 *)0x0 && (puVar4 != DAT_100cc500)) || (!bVar2))) {
      bVar2 = true;
      iVar3 = _stricmp((char *)*puVar4,s_EMPTY_1004ccdc);
      if (iVar3 == 0) {
        puVar4 = (undefined4 *)puVar4[1];
      }
      else {
        fwrite(puVar4,0x20,1,_File);
        fwrite((void *)*puVar4,0x54,1,_File);
        puVar4 = (undefined4 *)puVar4[1];
      }
    }
    if ((DAT_100f5308 != 0) && (iVar3 = 0, 0 < *(int *)(DAT_100f5308 + 4))) {
      do {
        puVar4 = *(undefined4 **)(*(int *)(DAT_100f5308 + 8) + iVar3 * 4);
        fwrite(puVar4,0x20,1,_File);
        fwrite((void *)*puVar4,0x54,1,_File);
        iVar3 = iVar3 + 1;
      } while (iVar3 < *(int *)(DAT_100f5308 + 4));
    }
    if (DAT_100520a0 == 0) {
      local_4 = 0;
      fwrite(&local_4,4,1,_File);
    }
    else {
      fwrite((void *)(DAT_100520a0 + 4),4,1,_File);
      iVar3 = 0;
      if (0 < *(int *)(DAT_100520a0 + 4)) {
        do {
          puVar4 = *(undefined4 **)(*(int *)(DAT_100520a0 + 8) + iVar3 * 4);
          fwrite(puVar4,0x20,1,_File);
          fwrite((void *)*puVar4,0x54,1,_File);
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(DAT_100520a0 + 4));
        fclose(_File);
        return 1;
      }
    }
    fclose(_File);
    return 1;
  }
  return 0;
}


