/*
 * Program: i76.exe
 * Function: load_or_create_player_definition
 * Entry: 004970f0
 * Signature: undefined __stdcall load_or_create_player_definition(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_004970f0
   suggested_name: load_or_create_player_definition
   basis: Reads/writes I76PLYR.DEF.
   
   [cgpt_i76exe_render_mode_v13] proposed=load_or_create_player_display_options :: Loads I76PLYR.DEF
   display/performance options. If high-color/miss16 or hardware renderer is active, forces related
   option bytes including terrain callback selector. */

void load_or_create_player_definition(void)

{
  bool bVar1;
  uint *puVar2;
  FILE *pFVar3;
  int *piVar4;
  undefined3 extraout_var;
  char cVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 local_10 [4];
  
  puVar7 = &g_player_display_options_block;
  for (iVar6 = 0x18; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  puVar7 = &DAT_005dce80;
  puVar8 = &g_player_display_options_block;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  puVar2 = (uint *)fill_recommended_performance_options(local_10);
  _g_display_mode_variant_index = *puVar2;
  _DAT_00654b84 = puVar2[1];
  _DAT_00654b88 = puVar2[2];
  DAT_00654b8c = puVar2[3];
  DAT_00654b90._0_1_ = 3;
  DAT_00654b90._1_1_ = 4;
  DAT_00654b90._2_1_ = 10;
  DAT_00654b90._3_1_ = 8;
  DAT_00654b94 = 1;
  DAT_00654b95 = 0;
  pFVar3 = fopen(s_I76PLYR_DEF_004fd7dc,&DAT_004c2098);
  if (pFVar3 != (FILE *)0x0) {
    fread(&g_player_display_options_block,1,0x60,pFVar3);
    fclose(pFVar3);
  }
  if ((&DAT_004f9e08)[(_g_display_mode_variant_index & 0xff) * 7] == 0) {
    cVar5 = '\x01';
    piVar4 = &DAT_004f9e24;
    do {
      if (*piVar4 == 1) {
        _g_display_mode_variant_index = CONCAT31(_g_player_options_force_high_color_byte,cVar5);
        break;
      }
      piVar4 = piVar4 + 7;
      cVar5 = cVar5 + '\x01';
    } while ((int)piVar4 < 0x4f9ee8);
  }
  bVar1 = is_miss16_high_color_resource_mode();
  if ((CONCAT31(extraout_var,bVar1) != 0) || (g_cmdline_hardware_raster_requested != 0)) {
    _g_display_mode_variant_index = CONCAT11(1,g_display_mode_variant_index);
    DAT_00654b8c = CONCAT13(1,(undefined3)DAT_00654b8c);
    _DAT_00654b88 = CONCAT13(1,_DAT_00654b88);
  }
  if ((DAT_004fcf58 != 0) &&
     (pFVar3 = fopen(s_I76PLYR_DEF_004fd7dc,s_wb_004edf28), pFVar3 != (FILE *)0x0)) {
    fwrite(&g_player_display_options_block,1,0x60,pFVar3);
    fclose(pFVar3);
  }
  if (((byte)DAT_00654b98 & 0x1c) != 0) {
    DAT_00535f78 = 1;
  }
  trim_audio_object_list_to_priority_limit((uint)DAT_00654b90._3_1_);
  set_audio_runtime_category_enable_mask(0xffffffff,0xffffffff,0xffffffff);
  DAT_004fcf58 = 0;
  return;
}


