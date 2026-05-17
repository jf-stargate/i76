/*
 * Program: i76.exe
 * Function: open_zfsf_archive
 * Entry: 004b9800
 * Signature: char * __cdecl open_zfsf_archive(char * param_1, FILE * param_2)
 */


/* [cgpt i76.exe ZFSF format renames v13; confidence=high] Parses and validates an already-open ZFSF
   archive stream. Validates magic ZFSF, version 1, record-name size 0x10,
   records-per-directory-table 100; reads chained 0xe14-byte directory tables and filters inactive
   records. */

char * __cdecl open_zfsf_archive(char *param_1,FILE *param_2)

{
  char cVar1;
  int _Offset;
  size_t sVar2;
  LPVOID pvVar3;
  size_t sVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  undefined4 *puVar12;
  char *pcVar13;
  int local_e34;
  char local_e30;
  char local_e2f;
  char local_e2e;
  char local_e2d;
  int local_e2c;
  int local_e28;
  int local_e24;
  int local_e20;
  undefined4 local_e1c;
  long local_e18;
  int local_e14;
  char local_e10 [3600];
  
  fseek(param_2,0,0);
  sVar2 = fread(&local_e30,0x1c,1,param_2);
  if (sVar2 == 0) {
    pcVar13 = s_Could_not_read_header_of_file____00500f08;
LAB_004b9aab:
    sprintf(&g_resource_error_message,pcVar13,param_1);
    return (char *)0x0;
  }
  if ((((local_e30 != 'Z') || (local_e2f != 'F')) || (local_e2e != 'S')) ||
     (((local_e2d != 'F' || (local_e2c != 1)) || ((local_e28 != 0x10 || (local_e24 != 100)))))) {
    pcVar13 = s_Invalid_header_in_file___s__00500e8c;
    goto LAB_004b9aab;
  }
  pcVar13 = HeapAlloc(g_process_heap,0,0x2c);
  if (pcVar13 == (char *)0x0) {
    fatal_out_of_memory_message((LPCSTR)0x0);
  }
  uVar6 = 0xffffffff;
  do {
    pcVar10 = param_1;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar10 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar10;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar9 = pcVar10 + -uVar6;
  pcVar10 = pcVar13;
  for (uVar7 = uVar6 >> 2; pcVar10 = pcVar10 + 4, uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar10 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar10 = pcVar10 + 1;
  }
  *(FILE **)pcVar13 = param_2;
  *(int *)(pcVar13 + 0x14) = local_e20 / 100 + 1;
  *(int *)(pcVar13 + 0x18) = local_e20;
  *(int *)(pcVar13 + 0x20) = local_e20;
  *(undefined4 *)(pcVar13 + 0x1c) = local_e1c;
  pvVar3 = HeapAlloc(g_process_heap,0,*(int *)(pcVar13 + 0x14) << 2);
  *(LPVOID *)(pcVar13 + 0x24) = pvVar3;
  if (pvVar3 != (LPVOID)0x0) {
    pvVar3 = HeapAlloc(g_process_heap,0,local_e20 * 0x24);
    *(LPVOID *)(pcVar13 + 0x28) = pvVar3;
    if (pvVar3 != (LPVOID)0x0) goto LAB_004b9959;
  }
  fatal_out_of_memory_message((LPCSTR)0x0);
LAB_004b9959:
  sVar2 = 0;
  iVar11 = 0;
  fseek(*(FILE **)pcVar13,local_e18,0);
  sVar4 = fread(&local_e14,0xe14,1,*(FILE **)pcVar13);
  _Offset = local_e14;
  do {
    if (sVar4 == 0) {
      sprintf(&g_resource_error_message,s_Could_not_read_dtable__d_of_file_00500ee0,iVar11,
              pcVar13 + 4);
LAB_004b9a5f:
      HeapFree(g_process_heap,0,pcVar13);
      return (char *)0x0;
    }
    iVar11 = iVar11 + 1;
    local_e34 = 0;
    *(long *)(*(int *)(pcVar13 + 0x24) + -4 + iVar11 * 4) = local_e18;
    iVar5 = sVar2 * 0x24;
    pcVar10 = local_e10;
    do {
      if (*pcVar10 == '\0') break;
      if ((pcVar10[0x20] & 1U) == 0) {
        puVar12 = (undefined4 *)(*(int *)(pcVar13 + 0x28) + iVar5);
        sVar2 = sVar2 + 1;
        iVar5 = iVar5 + 0x24;
        pcVar9 = pcVar10;
        for (iVar8 = 9; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar12 = *(undefined4 *)pcVar9;
          pcVar9 = pcVar9 + 4;
          puVar12 = puVar12 + 1;
        }
      }
      pcVar10 = pcVar10 + 0x24;
      local_e34 = local_e34 + 1;
    } while (local_e34 < 100);
    if (_Offset == 0) {
      *(size_t *)(pcVar13 + 0x18) = sVar2;
      if (iVar11 == *(int *)(pcVar13 + 0x14)) {
        qsort(*(void **)(pcVar13 + 0x28),sVar2,0x24,compare_zfsf_record_name_cstring);
        return pcVar13;
      }
      sprintf(&g_resource_error_message,s_Header_has__d_dtables__actually___00500ea8,
              *(int *)(pcVar13 + 0x14),iVar11,pcVar13 + 4);
      goto LAB_004b9a5f;
    }
    local_e14 = _Offset;
    fseek(*(FILE **)pcVar13,_Offset,0);
    sVar4 = fread(&local_e14,0xe14,1,*(FILE **)pcVar13);
    local_e18 = _Offset;
    _Offset = local_e14;
  } while( true );
}


