/*
 * Program: i76shell.dll
 * Function: init_shell_ui_state
 * Entry: 10007930
 * Signature: undefined __stdcall init_shell_ui_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76shell first-pass rename
   old_name: FUN_10007930
   suggested_name: init_shell_ui_state
   basis: Shell UI state/init candidate from ShellMain neighborhood. */

void init_shell_ui_state(void)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  char *pcVar10;
  byte *pbVar11;
  
  DAT_100520dc = *(int *)(DAT_100cc528 + 0x40c) + 2;
  DAT_100520d0 = 0;
  DAT_100520e0 = -DAT_100520dc;
  mpack_database_get_item(DAT_100cc53c,0x53,&DAT_1005216c,&DAT_100520d4);
  *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0xf;
  load_shell_rle_bitmap_surface_from_database_record(DAT_100cc518,(LPVOID)0xd);
  clear_text_rect(DAT_100cc518,0,0,0x280,0x1e0);
  DAT_100520d8 = 0x1e0;
  DAT_10052170 = create_pointer_list_with_capacity(500);
  if (DAT_100520d0 < DAT_100520d4) {
    do {
      piVar3 = HeapAlloc(DAT_10051c50,1,0x10);
      iVar2 = DAT_100520d4;
      iVar7 = 0;
      cVar1 = *DAT_1005216c;
      for (; (cVar1 != '\n' && (DAT_100520d0 < iVar2)); DAT_100520d0 = DAT_100520d0 + 1) {
        (&DAT_100520e8)[iVar7] = cVar1;
        iVar7 = iVar7 + 1;
        DAT_1005216c = DAT_1005216c + 1;
        cVar1 = *DAT_1005216c;
      }
      DAT_1005216c = DAT_1005216c + 1;
      DAT_100520d0 = DAT_100520d0 + 1;
      uVar5 = 0xffffffff;
      (&DAT_100520e8)[iVar7] = 0;
      pcVar9 = &DAT_100520e8;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      pbVar4 = HeapAlloc(DAT_10051c50,1,~uVar5 + 1);
      uVar5 = 0xffffffff;
      pcVar9 = &DAT_100520e8;
      do {
        pcVar10 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pbVar8 = (byte *)(pcVar10 + -uVar5);
      pbVar11 = pbVar4;
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pbVar11 = *(undefined4 *)pbVar8;
        pbVar8 = pbVar8 + 4;
        pbVar11 = pbVar11 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pbVar11 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        pbVar11 = pbVar11 + 1;
      }
      piVar3[3] = (int)pbVar4;
      iVar7 = measure_string_width_from_glyph_sheet(DAT_100cc530,pbVar4);
      piVar3[2] = iVar7;
      *piVar3 = 0x140 - iVar7 / 2;
      piVar3[1] = DAT_100520d8;
      DAT_100520d8 = DAT_100520d8 + DAT_100520dc;
      insert_pointer_list_item_sorted_or_append((int)DAT_10052170,(int)piVar3,(undefined *)0x0);
    } while (DAT_100520d0 < DAT_100520d4);
  }
  FUN_1001ed30(FUN_10007b20);
  (**(code **)(DAT_10058198 + 0x54))();
  (**(code **)(DAT_10058198 + 0x50))(8,0);
  _DAT_10052168 = timeGetTime();
  return;
}


