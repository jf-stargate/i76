/*
 * Program: i76.exe
 * Function: graphics_error_ui_graphics_error_dialog_helper_00471400
 * Entry: 00471400
 * Signature: undefined __cdecl graphics_error_ui_graphics_error_dialog_helper_00471400(undefined4 * param_1, char * param_2, char * param_3)
 */


/* cgpt readability rename set C v15: Readability pass set C: likely graphics_error_ui /
   graphics_error_dialog_helper based on address neighborhood and previously named adjacent systems.
    */

void __cdecl
graphics_error_ui_graphics_error_dialog_helper_00471400
          (undefined4 *param_1,char *param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  HANDLE hFile;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  HANDLE local_8c;
  LPCVOID local_88;
  char local_80 [128];
  
  bVar2 = false;
  local_8c = (HANDLE)0x0;
  local_88 = (LPCVOID)0x0;
  if (param_3 == (char *)0x0) {
    local_80[0] = '\0';
  }
  else {
    uVar3 = 0xffffffff;
    do {
      pcVar6 = param_3;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar6 = param_3 + 1;
      cVar1 = *param_3;
      param_3 = pcVar6;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar6 + -uVar3;
    pcVar8 = local_80;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  uVar3 = 0xffffffff;
  do {
    pcVar6 = param_2;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = param_2 + 1;
    cVar1 = *param_2;
    param_2 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar8 = local_80;
  do {
    pcVar7 = pcVar8;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar7 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar7;
  } while (cVar1 != '\0');
  pcVar6 = pcVar6 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  hFile = CreateFileA(local_80,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (((hFile != (HANDLE)0xffffffff) &&
      (local_8c = CreateFileMappingA(hFile,(LPSECURITY_ATTRIBUTES)0x0,2,0,0,(LPCSTR)0x0),
      local_8c != (HANDLE)0x0)) &&
     (local_88 = MapViewOfFile(local_8c,4,0,0,0), local_88 != (LPVOID)0x0)) {
    bVar2 = true;
  }
  if (!bVar2) {
    if (local_88 != (LPCVOID)0x0) {
      UnmapViewOfFile(local_88);
    }
    if (local_8c != (HANDLE)0x0) {
      CloseHandle(local_8c);
    }
    if (hFile != (HANDLE)0xffffffff) {
      CloseHandle(hFile);
    }
  }
  *param_1 = hFile;
  param_1[1] = local_8c;
  param_1[2] = local_88;
  return;
}


