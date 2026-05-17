/*
 * Program: i76.exe
 * Function: open_zfsf_archive_file
 * Entry: 004b9740
 * Signature: char * __cdecl open_zfsf_archive_file(char * param_1, int param_2)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Opens a ZFSF archive file by path. Second
   argument selects read-only mode versus create/update-capable rb+ mode. Retail resource callers
   observed passing 0 for read-only rb behavior. */

char * __cdecl open_zfsf_archive_file(char *param_1,int param_2)

{
  FILE *_File;
  int *piVar1;
  int iVar2;
  char *pcVar3;
  
  if (param_2 == 0) {
    _File = fopen(param_1,&DAT_004c2098);
    if (_File == (FILE *)0x0) goto LAB_004b97bb;
    setvbuf(_File,(char *)0x0,4,0);
  }
  else {
    _File = fopen(param_1,&DAT_00500e88);
    if (_File != (FILE *)0x0) goto LAB_004b97d5;
    piVar1 = _errno();
    if (*piVar1 == 2) {
      iVar2 = create_empty_zfsf_archive_file(param_1,0);
      if (iVar2 != 0) {
        _File = fopen(param_1,&DAT_00500e88);
      }
    }
  }
  if (_File != (FILE *)0x0) {
LAB_004b97d5:
    pcVar3 = open_zfsf_archive(param_1,_File);
    if (pcVar3 == (char *)0x0) {
      fclose(_File);
      pcVar3 = (char *)0x0;
    }
    return pcVar3;
  }
LAB_004b97bb:
  sprintf(&g_resource_error_message,s_Could_not_open_file___s__00500e6c,param_1);
  return (char *)0x0;
}


