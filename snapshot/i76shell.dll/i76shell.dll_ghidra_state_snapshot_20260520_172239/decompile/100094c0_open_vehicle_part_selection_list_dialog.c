/*
 * Program: i76shell.dll
 * Function: open_vehicle_part_selection_list_dialog
 * Entry: 100094c0
 * Signature: undefined __cdecl open_vehicle_part_selection_list_dialog(int param_1, int param_2, int param_3, int * param_4, int param_5, undefined4 param_6)
 */


void __cdecl
open_vehicle_part_selection_list_dialog
          (int param_1,int param_2,int param_3,int *param_4,int param_5,undefined4 param_6)

{
  int iVar1;
  byte *pbVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte *pbVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  bool bVar13;
  char *pcVar14;
  byte local_20 [32];
  
  DAT_100533b8 = (int *)allocate_shell_ui_object_0x20();
  *DAT_100533b8 = 0xea;
  DAT_100533b8[1] = 0xf0 - *(int *)(&DAT_100440b0 + param_2 * 4) / 2;
  DAT_100533b8[2] = 0xac;
  DAT_100533b8[3] = *(int *)(&DAT_100440b0 + param_2 * 4);
  DAT_100533b8[4] = param_2;
  DAT_100533b8[5] = param_3;
  DAT_100533b8[7] = (int)redraw_vehicle_config_screen;
  piVar3 = create_pointer_list_with_capacity(2);
  DAT_100533b8[6] = (int)piVar3;
  insert_pointer_list_item_sorted_or_append(DAT_100533b8[6],(int)param_4,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append(DAT_100533b8[6],param_5,(undefined *)0x0);
  iVar1 = DAT_100533b8[2];
  iVar7 = DAT_100533b8[3];
  iVar8 = DAT_100533b8[1];
  iVar6 = *DAT_100533b8;
  uVar9 = iVar1 * 6;
  puVar4 = HeapAlloc(DAT_10051c50,1,uVar9);
  if (puVar4 != (undefined4 *)0x0) {
    puVar11 = puVar4;
    for (uVar5 = uVar9 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar11 = 0xf0f0f0f;
      puVar11 = puVar11 + 1;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined1 *)puVar11 = 0xf;
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar4,iVar6 + 6,iVar7 + iVar8,iVar1,6);
    HeapFree(DAT_10051c50,1,puVar4);
  }
  uVar9 = iVar7 * 6;
  puVar4 = HeapAlloc(DAT_10051c50,1,uVar9);
  if (puVar4 != (undefined4 *)0x0) {
    puVar11 = puVar4;
    for (uVar5 = uVar9 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar11 = 0xf0f0f0f;
      puVar11 = puVar11 + 1;
    }
    for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined1 *)puVar11 = 0xf;
      puVar11 = (undefined4 *)((int)puVar11 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar4,iVar1 + iVar6,iVar8 + 6,6,iVar7);
    HeapFree(DAT_10051c50,1,puVar4);
  }
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,param_1,param_2,*DAT_100533b8,DAT_100533b8[1],DAT_100533b8[2],
             DAT_100533b8[3]);
  iVar1 = *param_4 + 3 + *DAT_100533b8;
  iVar7 = param_4[2] + 1 + DAT_100533b8[1];
  if (DAT_10051dc0 == 0) {
    iVar8 = 0;
    if (0 < *(int *)(param_3 + 4)) {
      do {
        piVar3 = *(int **)(*(int *)(param_3 + 8) + iVar8 * 4);
        draw_vehicle_part_damage_indicator(piVar3,iVar1,iVar7);
        iVar6 = piVar3[4];
        if (iVar6 == 1) {
          iVar6 = *piVar3;
          pcVar14 = s____s_10044280;
LAB_1000977e:
          wsprintfA((LPSTR)local_20,pcVar14,iVar6);
        }
        else {
          if (iVar6 == 2) {
            iVar6 = *piVar3;
            pcVar14 = s____s_10044288;
            goto LAB_1000977e;
          }
          if (iVar6 == 3) {
            iVar6 = *piVar3;
            pcVar14 = s____s_10044290;
            goto LAB_1000977e;
          }
        }
        measure_and_draw_string_from_glyph_sheet
                  (DAT_100cc518,iVar1,iVar7,*(int *)(DAT_100cc52c + 0x408),local_20,(undefined *)0x0
                  );
        iVar7 = iVar7 + DAT_10051cd0;
        iVar8 = iVar8 + 1;
      } while (iVar8 < *(int *)(param_3 + 4));
    }
  }
  else {
    iVar8 = 0;
    if (0 < *(int *)(param_3 + 4)) {
      do {
        puVar4 = *(undefined4 **)(*(int *)(param_3 + 8) + iVar8 * 4);
        if (puVar4 != (undefined4 *)0x0) {
          pbVar2 = (byte *)*puVar4;
          iVar6 = 6;
          bVar13 = true;
          pbVar10 = pbVar2;
          pbVar12 = (byte *)s_Empty_10044278;
          do {
            if (iVar6 == 0) break;
            iVar6 = iVar6 + -1;
            bVar13 = *pbVar10 == *pbVar12;
            pbVar10 = pbVar10 + 1;
            pbVar12 = pbVar12 + 1;
          } while (bVar13);
          if (!bVar13) {
            measure_and_draw_string_from_glyph_sheet
                      (DAT_100cc518,iVar1,iVar7,*(int *)(DAT_100cc52c + 0x408),pbVar2,
                       (undefined *)0x0);
          }
        }
        iVar7 = iVar7 + DAT_10051cd0;
        iVar8 = iVar8 + 1;
        if (*(int *)(param_3 + 4) <= iVar8) {
          DAT_100d21a4 = param_6;
          return;
        }
      } while( true );
    }
  }
  DAT_100d21a4 = param_6;
  return;
}


