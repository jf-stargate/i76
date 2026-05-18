/*
 * Program: i76.exe
 * Function: initialize_specials_empty_indicator
 * Entry: 00467850
 * Signature: undefined __cdecl initialize_specials_empty_indicator(int param_1)
 */


/* cgpt whole-binary semantic rename v1: strings sp_empty / carx1 */

void __cdecl initialize_specials_empty_indicator(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x70) != 0) {
    iVar7 = 0;
    piVar5 = &DAT_004f85e0;
    piVar4 = (int *)(*(int *)(param_1 + 0x70) + 0x3ec);
    iVar6 = DAT_004f863c;
    do {
      iVar3 = *piVar4;
      if (iVar3 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = **(int **)(iVar3 + 0x70);
      }
      if (iVar1 != 0) {
        if ((iVar3 == 0) || (*(int *)(*(int *)(iVar3 + 0x70) + 4) < 1)) {
          iVar3 = 0;
        }
        else {
          iVar3 = *(int *)(*(int *)(iVar3 + 0x70) + 0x10);
        }
        if (*piVar5 != iVar3) {
          *piVar5 = iVar3;
          if ((iVar1 < 0xc) && (-1 < iVar1)) {
            if (iVar3 == 0) {
              pcVar2 = s_3sp_empty_off_004f81d0 + iVar6 + iVar1 * 0x10;
            }
            else {
              pcVar2 = s_3sp_empty_on_004f8290 + iVar6 + iVar1 * 0x10;
            }
          }
          else {
            pcVar2 = (char *)0x0;
          }
          if ((pcVar2 != (char *)0x0) && (*pcVar2 != '\0')) {
            draw_texture_widget_to_hud_surface_and_bind_object
                      (DAT_0054b9ec,(byte *)(s_zbks_320_map_004f8190 + iVar6 * 0xd),
                       s_3sp_dymo_1_004f84f0 + iVar7 + iVar6,pcVar2,&DAT_0054b9b8,1);
            iVar6 = DAT_004f863c;
          }
        }
      }
      piVar5 = piVar5 + 1;
      piVar4 = piVar4 + 1;
      iVar7 = iVar7 + 0x10;
    } while ((int)piVar5 < 0x4f85e9);
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    iVar6 = 0x11;
    piVar4 = (int *)(*(int *)(param_1 + 0x70) + 0x3ec);
    do {
      iVar7 = *piVar4;
      if (iVar7 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = **(int **)(iVar7 + 0x70);
      }
      if (iVar3 != 0) {
        initialize_specials_tire_cover_indicator
                  (*(undefined4 *)(iVar7 + 0x70),iVar3,iVar6 + -0x11,0);
      }
      iVar6 = iVar6 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar6 < 0x14);
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    iVar6 = 0x11;
    piVar4 = (int *)(*(int *)(param_1 + 0x70) + 0x3ec);
    do {
      iVar7 = *piVar4;
      if (iVar7 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = **(int **)(iVar7 + 0x70);
      }
      if (iVar3 != 0) {
        initialize_specials_numeric_display(*(int *)(iVar7 + 0x70),iVar6 + -0x11,0);
      }
      iVar6 = iVar6 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar6 < 0x14);
  }
  return;
}


