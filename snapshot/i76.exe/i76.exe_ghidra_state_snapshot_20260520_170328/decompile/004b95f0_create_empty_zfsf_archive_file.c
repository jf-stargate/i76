/*
 * Program: i76.exe
 * Function: create_empty_zfsf_archive_file
 * Entry: 004b95f0
 * Signature: undefined4 __cdecl create_empty_zfsf_archive_file(char * param_1, undefined4 param_2)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Creates a minimal empty ZFSF archive
   file: writes 0x1c-byte ZFSF header and one 0xe14-byte directory table. Used by
   open_zfsf_archive_file only when update/create mode is requested and the archive is missing. */

undefined4 __cdecl create_empty_zfsf_archive_file(char *param_1,undefined4 param_2)

{
  FILE *pFVar1;
  size_t sVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_e30;
  undefined1 local_e2f;
  undefined1 local_e2e;
  undefined1 local_e2d;
  undefined4 local_e2c;
  undefined4 local_e28;
  undefined4 local_e24;
  undefined4 local_e20;
  undefined4 local_e1c;
  undefined4 local_e18;
  undefined4 local_e14 [901];
  
  pFVar1 = fopen(param_1,&DAT_004c2098);
  if (pFVar1 != (FILE *)0x0) {
    fclose(pFVar1);
    sprintf(&g_resource_key_registration_error_buffer,s_File___s__already_exists_00500e50,param_1);
    return 0;
  }
  pFVar1 = fopen(param_1,s_wb_004edf28);
  if (pFVar1 == (FILE *)0x0) {
    sprintf(&g_resource_key_registration_error_buffer,s_Could_not_create_file___s__00500e34,param_1)
    ;
    return 0;
  }
  local_e2f = 0x46;
  local_e2d = 0x46;
  local_e1c = param_2;
  puVar4 = local_e14;
  for (iVar3 = 0x385; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  local_e30 = 0x5a;
  local_e2e = 0x53;
  local_e2c = 1;
  local_e28 = 0x10;
  local_e24 = 100;
  local_e20 = 0;
  local_e18 = 0x1c;
  sVar2 = fwrite(&local_e30,0x1c,1,pFVar1);
  if (sVar2 != 0) {
    sVar2 = fwrite(local_e14,0xe14,1,pFVar1);
    if (sVar2 != 0) {
      fclose(pFVar1);
      return 1;
    }
  }
  sprintf(&g_resource_key_registration_error_buffer,s_Error_writing_to_file___s__00500e18,param_1);
  fclose(pFVar1);
  return 0;
}


