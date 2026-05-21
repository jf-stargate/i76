/*
 * Program: i76.exe
 * Function: draw_wrapped_text_to_hdc_with_optional_underline
 * Entry: 004994b0
 * Signature: int __cdecl draw_wrapped_text_to_hdc_with_optional_underline(HDC param_1, int * param_2, byte * param_3, int param_4, undefined4 param_5, int * param_6)
 */


/* WARNING: Removing unreachable block (ram,0x00499529) */
/* [cgpt i76.exe damage dispatch rename v19; confidence=MEDIUM-HIGH] Draws wrapped text via TextOutA
   and optionally draws underline/marker spans into a bitmap surface. */

int __cdecl
draw_wrapped_text_to_hdc_with_optional_underline
          (HDC param_1,int *param_2,byte *param_3,int param_4,undefined4 param_5,int *param_6)

{
  byte bVar1;
  HDC hdc;
  undefined1 uVar2;
  int nMaxExtent;
  int *piVar3;
  byte *pbVar4;
  uint uVar5;
  int iVar6;
  byte *lpString;
  int c;
  int iVar7;
  tagSIZE local_48;
  int local_40;
  int local_3c;
  byte *local_2c;
  int local_28 [3];
  int local_1c [3];
  int local_10;
  int local_c;
  int local_4;
  
  lpString = param_3;
  hdc = param_1;
  local_10 = *param_2;
  iVar7 = param_2[1];
  nMaxExtent = param_2[2] - local_10;
  local_4 = param_2[3];
  uVar5 = 0xffffffff;
  pbVar4 = param_3;
  do {
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
  } while (bVar1 != 0);
  local_c = iVar7;
  GetTextExtentExPointA
            (param_1,(LPCSTR)param_3,~uVar5 - 1,nMaxExtent,(LPINT)&param_1,(LPINT)0x0,&local_48);
  param_3 = (byte *)(local_48.cy / 2 + iVar7);
  while( true ) {
    c = 0;
    iVar7 = 0;
    if (*lpString != 0) {
      piVar3 = (int *)measure_text_prefix_to_fit_hdc_width(local_28,lpString,nMaxExtent,hdc);
      local_40 = *piVar3;
      local_3c = piVar3[1];
      pbVar4 = lpString;
      if (*(char *)piVar3[2] == '\0') {
        local_2c = (byte *)piVar3[2];
        iVar7 = *piVar3;
        c = piVar3[1];
      }
      else {
        while( true ) {
          piVar3 = (int *)parse_next_text_break_token(local_1c,pbVar4);
          if ((*piVar3 == 0) || (iVar6 = *piVar3 + iVar7, local_40 < iVar6)) break;
          c = c + piVar3[1];
          pbVar4 = (byte *)piVar3[2];
          iVar7 = iVar6;
          local_2c = (byte *)piVar3[2];
        }
      }
    }
    if (iVar7 == 0) break;
    TextOutA(hdc,local_10,local_c,(LPCSTR)lpString,c);
    piVar3 = param_6;
    if (param_6 != (int *)0x0) {
      GetTextExtentPoint32A(hdc,(LPCSTR)lpString,c,&local_48);
      iVar7 = 0;
      uVar2 = convert_rgb_floats_to_nearest_palette_index();
      draw_clipped_line_to_bitmap_surface
                (piVar3,local_10,(int)param_3,local_48.cx,(int)param_3,uVar2,iVar7);
    }
    local_c = local_c + param_4;
    param_3 = param_3 + param_4;
    lpString = local_2c;
  }
  return local_c - param_2[1];
}


