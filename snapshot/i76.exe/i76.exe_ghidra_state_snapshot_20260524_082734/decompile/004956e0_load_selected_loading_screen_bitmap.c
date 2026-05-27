/*
 * Program: i76.exe
 * Function: load_selected_loading_screen_bitmap
 * Entry: 004956e0
 * Signature: undefined4 __cdecl load_selected_loading_screen_bitmap(undefined * param_1)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Loads bitmap resource named by
   selected loading-screen record, centers it, builds compatible surface/DC state, initializes
   per-entry UI callbacks. */

undefined4 __cdecl load_selected_loading_screen_bitmap(undefined *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined4 *puVar8;
  int iVar9;
  int local_34 [13];
  
  if (param_1 == (undefined *)0x0) {
    if (DAT_00654b18 == (code *)0x0) {
      return 0;
    }
    (*DAT_00654b18)();
    return 0;
  }
  do {
    if (DAT_00654a34 != (int *)0x0) {
      release_localized_texture_resource_variant((char *)&g_loading_screen_bitmap_resource_name,0,0)
      ;
      DAT_00654a34 = (int *)0x0;
    }
    release_bitmap_surface_context(&DAT_00654a6c);
    if (DAT_00654a68 != (HGDIOBJ)0x0) {
      DeleteObject(DAT_00654a68);
      DAT_00654a68 = (HGDIOBJ)0x0;
    }
    release_bitmap_surface_context(&DAT_00654aa0);
    uVar3 = 0xffffffff;
    pcVar6 = param_1 + 8;
    do {
      pcVar7 = pcVar6;
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar3 = ~uVar3;
    pcVar6 = pcVar7 + -uVar3;
    pcVar7 = (char *)&g_loading_screen_bitmap_resource_name;
    g_current_loading_screen_record = param_1;
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar7 = pcVar7 + 4;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *pcVar7 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    }
    DAT_00654a34 = (int *)load_localized_texture_resource_variant
                                    ((byte *)&g_loading_screen_bitmap_resource_name,0,0);
    if (DAT_00654a34 != (int *)0x0) {
      puVar2 = (undefined4 *)
               construct_bitmap_surface_context
                         (local_34,*DAT_00654a34,(DAT_00654a34[1] << 3) >> 3,(int)(DAT_00654a34 + 2)
                          ,0);
      puVar8 = &DAT_00654a6c;
      for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar8 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar8 = puVar8 + 1;
      }
      if (DAT_00654a80 != 0) {
        *(undefined4 *)(param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 0x28) = 0;
        *(uint *)(param_1 + 0x30) = *DAT_00654a34 + 3U & 0xfffffffc;
        *(int *)(param_1 + 0x34) = (DAT_00654a34[1] << 3) >> 3;
        DAT_00654a40 = (((DAT_005dcee8 - ((DAT_00654a34[1] << 3) >> 3)) - DAT_005dcee0) + 1) / 2;
        DAT_00654a3c = (((DAT_005dcee4 - DAT_005dcedc) - *DAT_00654a34) + 1) / 2;
        DAT_00654a44 = DAT_00654a3c + *(int *)(param_1 + 0x30);
        DAT_00654a48 = DAT_00654a40 + *(int *)(param_1 + 0x34);
        puVar2 = (undefined4 *)
                 create_dibsection_8bpp_surface_context_with_game_palette
                           (local_34,g_loading_screen_hdc,*(int *)(param_1 + 0x30),
                            *(uint *)(param_1 + 0x34),&DAT_00654a68);
        puVar8 = &DAT_00654aa0;
        for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar8 = *puVar2;
          puVar2 = puVar2 + 1;
          puVar8 = puVar8 + 1;
        }
        if (DAT_00654a68 == (HGDIOBJ)0x0) {
          report_error();
          return 0;
        }
        iVar5 = *(int *)(param_1 + 0x18);
        iVar9 = 0;
        if (0 < *(int *)(param_1 + 0x1c)) {
          do {
            if (*(code **)(iVar5 + 8) != (code *)0x0) {
              (**(code **)(iVar5 + 8))(iVar5,6);
            }
            iVar9 = iVar9 + 1;
            iVar5 = iVar5 + 0x3c;
          } while (iVar9 < *(int *)(param_1 + 0x1c));
        }
        (*DAT_005dd2e8)(&DAT_005dcec0);
        redraw_mission_loading_screen();
        DAT_005a6154 = 1;
        DAT_00654b1c = 0;
        return 1;
      }
      report_error();
      return 0;
    }
    report_error();
    param_1 = &DAT_004fc0a0;
  } while( true );
}


