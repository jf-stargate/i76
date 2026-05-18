/*
 * Program: i76.exe
 * Function: initialize_specials_housing_display
 * Entry: 00467e30
 * Signature: undefined __cdecl initialize_specials_housing_display(int param_1)
 */


/* cgpt whole-binary semantic rename v1: strings housing/bracket/dymo */

void __cdecl initialize_specials_housing_display(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int *local_10;
  int *local_c;
  int local_8;
  
  piVar3 = (int *)(param_1 + 0x70);
  iVar4 = 0;
  if (*piVar3 != 0) {
    param_1 = 0;
    local_c = (int *)&DAT_004f8630;
    local_10 = (int *)&DAT_004f8600;
    piVar3 = (int *)(*piVar3 + 0x3ec);
    local_8 = 3;
    do {
      if (*piVar3 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = **(int **)(*piVar3 + 0x70);
      }
      rand();
      iVar1 = ftol();
      draw_texture_widget_to_hud_surface_and_bind_object
                (DAT_0054b9ec,(byte *)(s_zbks_320_map_004f8190 + DAT_004f863c * 0xd),
                 s_3sp_bracket_1_004f8490 + param_1 + DAT_004f863c,
                 s_3housing1_004f8440 + DAT_004f863c + iVar1 * 0x10,&DAT_0054b9b8,1);
      if (iVar5 != 0) {
        iVar1 = *(int *)(*piVar3 + 0x70);
        (&DAT_004f85f0)[iVar4] = 0xffffffff;
        initialize_specials_tire_cover_indicator(iVar1,iVar5,iVar4,1);
        (&DAT_004f85e0)[iVar4] = 0xffffffff;
        if ((*piVar3 == 0) || (iVar2 = *(int *)(*piVar3 + 0x70), *(int *)(iVar2 + 4) < 1)) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
        if ((iVar5 < 0xc) && (-1 < iVar5)) {
          if (iVar2 == 0) {
            pcVar6 = s_3sp_empty_off_004f81d0 + DAT_004f863c + iVar5 * 0x10;
          }
          else {
            pcVar6 = s_3sp_empty_on_004f8290 + DAT_004f863c + iVar5 * 0x10;
          }
        }
        else {
          pcVar6 = (char *)0x0;
        }
        if ((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) {
          draw_texture_widget_to_hud_surface_and_bind_object
                    (DAT_0054b9ec,(byte *)(s_zbks_320_map_004f8190 + DAT_004f863c * 0xd),
                     s_3sp_dymo_1_004f84f0 + param_1 + DAT_004f863c,pcVar6,&DAT_0054b9b8,1);
        }
        iVar5 = *(int *)(iVar1 + 4);
        *local_10 = iVar5 % 10;
        iVar5 = iVar5 / 10;
        (&DAT_004f8610)[iVar4] = iVar5 % 10;
        iVar5 = iVar5 / 10;
        (&DAT_004f8620)[iVar4] = iVar5 % 10;
        *local_c = (iVar5 / 10) % 10;
        initialize_specials_numeric_display(iVar1,iVar4,1);
      }
      piVar3 = piVar3 + 1;
      local_10 = local_10 + 1;
      local_c = local_c + 1;
      iVar4 = iVar4 + 1;
      param_1 = param_1 + 0x10;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  return;
}


