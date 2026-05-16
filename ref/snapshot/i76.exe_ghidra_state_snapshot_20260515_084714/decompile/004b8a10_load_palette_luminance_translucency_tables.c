/*
 * Program: i76.exe
 * Function: load_palette_luminance_translucency_tables
 * Entry: 004b8a10
 * Signature: undefined4 __cdecl load_palette_luminance_translucency_tables(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings palette/luminance/translucency table not found */

undefined4 __cdecl load_palette_luminance_translucency_tables(int param_1)

{
  char cVar1;
  uint *puVar2;
  uint *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint *puVar10;
  undefined4 *puVar11;
  char *pcVar12;
  uint *puVar13;
  char *pcVar14;
  
  set_cd_audio_runtime_enabled_flag(*(undefined4 *)(param_1 + 8));
  palette_dib_surface_update_helper_00477b00(*(int *)(param_1 + 0x9b));
  puVar2 = open_resource_file_into_memory((char *)(param_1 + 0x26));
  if (puVar2 == (uint *)0x0) {
    report_chunk_parse_error();
  }
  puVar3 = open_resource_file_into_memory((char *)(param_1 + 0x33));
  if (puVar3 == (uint *)0x0) {
    report_chunk_parse_error();
  }
  if (puVar2 != (uint *)0x0) {
    puVar10 = puVar2;
    puVar13 = &g_game_8bpp_palette_rgb_triplets;
    for (iVar6 = 0xc0; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar13 = *puVar10;
      puVar10 = puVar10 + 1;
      puVar13 = puVar13 + 1;
    }
    (*DAT_005dd2c4)(&DAT_005dcec0,0,0x100,puVar2,puVar3);
  }
  if (puVar3 != (uint *)0x0) {
    release_resource_file_reference((char *)(param_1 + 0x33));
  }
  if (puVar2 != (uint *)0x0) {
    release_resource_file_reference((char *)(param_1 + 0x26));
  }
  puVar2 = open_resource_file_into_memory((char *)(param_1 + 0x40));
  if (puVar2 == (uint *)0x0) {
    report_chunk_parse_error();
  }
  else {
    matrix_vector_projection_context_helper_00478b30();
    puVar3 = puVar2;
    puVar10 = &g_palette_blend_table_a;
    for (iVar6 = 0x4000; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar10 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar10 = puVar10 + 1;
    }
  }
  if (puVar2 != (uint *)0x0) {
    release_resource_file_reference((char *)(param_1 + 0x40));
  }
  matrix_rotation_context_helper_00479780(&DAT_005dcec0,0xff);
  puVar4 = &DAT_00644220;
  puVar9 = (undefined4 *)(param_1 + 0x9f);
  do {
    puVar5 = puVar4 + 5;
    puVar11 = puVar9;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar4 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar4 = puVar5;
    puVar9 = puVar9 + 5;
  } while ((int)puVar5 < 0x6442c0);
  uVar7 = 0xffffffff;
  pcVar12 = (char *)(param_1 + 0x5a);
  do {
    pcVar14 = pcVar12;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar12 + 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar12 = pcVar14 + -uVar7;
  pcVar14 = (char *)&DAT_005dce60;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar12 = (char *)(param_1 + 0x4d);
  do {
    pcVar14 = pcVar12;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar12 + 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar12 = pcVar14 + -uVar7;
  pcVar14 = (char *)&DAT_006094f0;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar12 = (char *)(param_1 + 0x81);
  do {
    pcVar14 = pcVar12;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar12 + 1;
    cVar1 = *pcVar12;
    pcVar12 = pcVar14;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  pcVar12 = pcVar14 + -uVar7;
  pcVar14 = (char *)&DAT_005a7ec8;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar12;
    pcVar12 = pcVar12 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar12;
    pcVar12 = pcVar12 + 1;
    pcVar14 = pcVar14 + 1;
  }
  initialize_mission_scrounge_state((char *)(param_1 + 0x67));
  load_terrain_texture_defaults((char *)(param_1 + 0x74));
  load_horizon_texture_manifest((char *)(param_1 + 0x8e));
  _DAT_005dd300 = *(undefined4 *)(param_1 + 0xc);
  _DAT_005dd304 = *(undefined4 *)(param_1 + 0x10);
  _DAT_005dd308 = *(undefined4 *)(param_1 + 0x14);
  DAT_005dd30c = *(undefined1 *)(param_1 + 0x18);
  _DAT_005dd310 = *(undefined4 *)(param_1 + 0x19);
  _DAT_005dd314 = *(undefined4 *)(param_1 + 0x1d);
  _DAT_005dd318 = *(undefined4 *)(param_1 + 0x21);
  DAT_005dd31c = *(undefined1 *)(param_1 + 0x25);
  DAT_004c271c = (float)*(int *)(param_1 + 0x13f);
  return 1;
}


