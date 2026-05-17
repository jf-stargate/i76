/*
 * Program: i76.exe
 * Function: create_gdi_font_from_i76_font_descriptor
 * Entry: 004768f0
 * Signature: HFONT __cdecl create_gdi_font_from_i76_font_descriptor(undefined4 * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Creates a Win32 GDI HFONT from
   one of the game's display-mode-specific font descriptors. */

HFONT __cdecl create_gdi_font_from_i76_font_descriptor(undefined4 *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  HDC hdc;
  HFONT pHVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  CHAR *pCVar8;
  bool bVar9;
  DWORD flags;
  LOGFONTA local_3c;
  
  puVar2 = (undefined4 *)param_1[_g_display_mode_variant_index & 0xff];
  if (puVar2 == (undefined4 *)0x0) {
    return (HFONT)0x0;
  }
  pcVar6 = (char *)*puVar2;
  if (pcVar6 == (char *)0x0) {
    pcVar6 = (char *)*param_1;
  }
  local_3c.lfHeight = puVar2[1];
  uVar4 = 0xffffffff;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  local_3c.lfWidth = 0;
  local_3c.lfEscapement = 0;
  local_3c.lfOrientation = 0;
  local_3c.lfWeight = 100;
  local_3c.lfItalic = '\0';
  local_3c.lfUnderline = '\0';
  local_3c.lfStrikeOut = '\0';
  local_3c.lfCharSet = '\0';
  local_3c.lfOutPrecision = '\x04';
  local_3c.lfClipPrecision = '\0';
  local_3c.lfQuality = '\x02';
  local_3c.lfPitchAndFamily = '\0';
  pcVar6 = pcVar7 + -uVar4;
  pCVar8 = local_3c.lfFaceName;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pCVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pCVar8 = pCVar8 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pCVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pCVar8 = pCVar8 + 1;
  }
  if (PTR_DAT_004fe194 == (undefined *)0x0) {
    bVar9 = false;
  }
  else {
    bVar9 = *(int *)PTR_DAT_004fe194 == 3;
  }
  if (bVar9) {
    local_3c.lfCharSet = 0x80;
  }
  flags = 1;
  hdc = (HDC)(*DAT_005dd2d0)(&DAT_005dcec0);
  SetMapperFlags(hdc,flags);
  pHVar3 = CreateFontIndirectA(&local_3c);
  (*DAT_005dd2d4)(&DAT_005dcec0);
  return pHVar3;
}


