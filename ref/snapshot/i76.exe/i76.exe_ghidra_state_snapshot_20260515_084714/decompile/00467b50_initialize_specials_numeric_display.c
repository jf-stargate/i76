/*
 * Program: i76.exe
 * Function: initialize_specials_numeric_display
 * Entry: 00467b50
 * Signature: undefined __cdecl initialize_specials_numeric_display(int param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings ones/tens/hunds/thous */

void __cdecl initialize_specials_numeric_display(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_34 [13];
  
  iVar4 = *(int *)(param_1 + 4) / 10;
  iVar1 = iVar4 / 10;
  if ((*(int *)(param_1 + 4) % 10 != *(int *)(&DAT_004f8600 + param_2 * 4)) || (param_3 != 0)) {
    if (param_3 == 0) {
      *(int *)(&DAT_004f8600 + param_2 * 4) = *(int *)(&DAT_004f8600 + param_2 * 4) + -1;
    }
    if (*(int *)(&DAT_004f8600 + param_2 * 4) == -1) {
      *(undefined4 *)(&DAT_004f8600 + param_2 * 4) = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,DAT_0054b9ec,s_zbks_320_map_004f8190 + DAT_004f863c * 0xd,
                        s_3sp_num_ones_1_004f8520 + DAT_004f863c + param_2 * 0x10,
                        s_3top_004f81b0 + DAT_004f863c,s_3bottom_004f81c0 + DAT_004f863c);
    puVar5 = &DAT_0054b9b8;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  if ((iVar4 % 10 != (&DAT_004f8610)[param_2]) || (param_3 != 0)) {
    if (param_3 == 0) {
      (&DAT_004f8610)[param_2] = (&DAT_004f8610)[param_2] + -1;
    }
    if ((&DAT_004f8610)[param_2] == -1) {
      (&DAT_004f8610)[param_2] = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,DAT_0054b9ec,s_zbks_320_map_004f8190 + DAT_004f863c * 0xd,
                        s_3sp_num_tens_1_004f8550 + DAT_004f863c + param_2 * 0x10,
                        s_3top_004f81b0 + DAT_004f863c,s_3bottom_004f81c0 + DAT_004f863c);
    puVar5 = &DAT_0054b9b8;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  if ((iVar1 % 10 != (&DAT_004f8620)[param_2]) || (param_3 != 0)) {
    if (param_3 == 0) {
      (&DAT_004f8620)[param_2] = (&DAT_004f8620)[param_2] + -1;
    }
    if ((&DAT_004f8620)[param_2] == -1) {
      (&DAT_004f8620)[param_2] = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,DAT_0054b9ec,s_zbks_320_map_004f8190 + DAT_004f863c * 0xd,
                        s_3sp_num_hunds_1_004f8580 + DAT_004f863c + param_2 * 0x10,
                        s_3top_004f81b0 + DAT_004f863c,s_3bottom_004f81c0 + DAT_004f863c);
    puVar5 = &DAT_0054b9b8;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  if (((iVar1 / 10) % 10 != *(int *)(&DAT_004f8630 + param_2 * 4)) || (param_3 != 0)) {
    if (param_3 == 0) {
      *(int *)(&DAT_004f8630 + param_2 * 4) = *(int *)(&DAT_004f8630 + param_2 * 4) + -1;
    }
    if (*(int *)(&DAT_004f8630 + param_2 * 4) == -1) {
      *(undefined4 *)(&DAT_004f8630 + param_2 * 4) = 9;
    }
    puVar2 = (undefined4 *)
             draw_scrolling_texture_widget_to_hud_surface
                       (local_34,DAT_0054b9ec,s_zbks_320_map_004f8190 + DAT_004f863c * 0xd,
                        s_3sp_num_thous_1_004f85b0 + DAT_004f863c + param_2 * 0x10,
                        s_3top_004f81b0 + DAT_004f863c,s_3bottom_004f81c0 + DAT_004f863c);
    puVar5 = &DAT_0054b9b8;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  return;
}


