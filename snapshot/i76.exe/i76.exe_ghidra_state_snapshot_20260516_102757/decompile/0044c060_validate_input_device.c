/*
 * Program: i76.exe
 * Function: validate_input_device
 * Entry: 0044c060
 * Signature: int __cdecl validate_input_device(char * param_1)
 */


/* i76 second-pass rename
   old_name: FUN_0044c060
   suggested_name: validate_input_device
   basis: Reports missing/misconfigured input device and prompts user to continue/abort. */

int __cdecl validate_input_device(char *param_1)

{
  char cVar1;
  undefined *puVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined **ppuVar11;
  char *pcVar12;
  int local_8;
  
  local_8 = 0;
  ppuVar11 = &PTR_PTR_004f2850;
  do {
    if ((undefined4 *)*ppuVar11 != (undefined4 *)0x0) {
      iVar5 = (**(code **)*ppuVar11)();
      if ((iVar5 != 0) && (iVar10 = 0, 0 < iVar5)) {
        do {
          iVar4 = g_input_device_context_count;
          if (4 < g_input_device_context_count) {
            report_chunk_parse_error();
            return -1;
          }
          pcVar7 = (char *)(&DAT_00536380 + g_input_device_context_count * 0x1d);
          iVar6 = (**(code **)(*ppuVar11 + 4))(iVar10,pcVar7);
          if (iVar6 == 0) {
            iVar6 = _stricmp(pcVar7,param_1);
            if (iVar6 == 0) {
              uVar8 = 0xffffffff;
              goto code_r0x0044c1a7;
            }
            (**(code **)(*ppuVar11 + 0xc))(pcVar7);
          }
          iVar10 = iVar10 + 1;
        } while (iVar10 < iVar5);
      }
    }
    iVar5 = g_input_device_context_count;
    ppuVar11 = ppuVar11 + 1;
    local_8 = local_8 + 1;
  } while ((int)ppuVar11 < 0x4f285c);
  uVar8 = 0xffffffff;
  pcVar7 = param_1;
  do {
    pcVar12 = pcVar7;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar12;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  pcVar7 = pcVar12 + -uVar8;
  pcVar12 = (char *)(&DAT_0053da68 + g_input_device_context_count * 10);
  g_input_device_context_count = g_input_device_context_count + 1;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; pcVar3 = StrLookup_Global_Object_exref, uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar12 = pcVar12 + 1;
  }
  (&DAT_0053da50)[iVar5] = 0;
  pcVar7 = (char *)StrLookupFind(*(undefined4 *)pcVar3,s_The___s__input_device_does_not_e_004f4764,
                                 param_1,param_1);
  sprintf(&DAT_00535f80,pcVar7);
  release_and_show_mouse_cursor();
  report_chunk_parse_error();
  return -1;
  while( true ) {
    uVar8 = uVar8 - 1;
    pcVar7 = param_1 + 1;
    cVar1 = *param_1;
    param_1 = pcVar7;
    if (cVar1 == '\0') break;
code_r0x0044c1a7:
    pcVar7 = param_1;
    if (uVar8 == 0) break;
  }
  uVar8 = ~uVar8;
  pcVar7 = pcVar7 + -uVar8;
  pcVar12 = (char *)(&DAT_0053da68 + iVar4 * 10);
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar12 = pcVar12 + 4;
  }
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar12 = pcVar12 + 1;
  }
  g_input_device_context_count = g_input_device_context_count + 1;
  puVar2 = (&PTR_PTR_004f2850)[local_8];
  (&g_input_device_callback_table)[iVar4] = puVar2;
  iVar5 = (**(code **)(puVar2 + 8))(&DAT_00536380 + iVar4 * 0x1d);
  if (iVar5 != 0) {
    pcVar7 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                   s_The___s__input_device_is_not_con_004f45e0,
                                   &DAT_0053638c + iVar4 * 0x74,&DAT_0053638c + iVar4 * 0x74);
    sprintf(&DAT_00535f80,pcVar7);
    release_and_show_mouse_cursor();
    report_chunk_parse_error();
    (&DAT_0053da50)[iVar4] = 0;
    return -1;
  }
  (&DAT_0053da50)[iVar4] = 1;
  return iVar4;
}


