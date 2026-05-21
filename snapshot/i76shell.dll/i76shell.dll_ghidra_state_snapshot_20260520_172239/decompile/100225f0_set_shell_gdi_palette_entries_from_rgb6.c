/*
 * Program: i76shell.dll
 * Function: set_shell_gdi_palette_entries_from_rgb6
 * Entry: 100225f0
 * Signature: undefined4 __cdecl set_shell_gdi_palette_entries_from_rgb6(int param_1, int param_2, undefined2 * param_3)
 */


undefined4 __cdecl
set_shell_gdi_palette_entries_from_rgb6(int param_1,int param_2,undefined2 *param_3)

{
  char cVar1;
  int iVar2;
  undefined2 *puVar3;
  char *pcVar4;
  char *pcVar5;
  
  if ((((param_3 != (undefined2 *)0x0) && (-1 < param_1)) && (param_1 < 0x100)) &&
     ((0 < param_2 && (param_2 <= 0x100 - param_1)))) {
    if (0 < param_2) {
      puVar3 = (undefined2 *)((int)&DAT_100533f0 + param_1 * 3);
      do {
        param_2 = param_2 + -1;
        *puVar3 = *param_3;
        *(undefined1 *)(puVar3 + 1) = *(undefined1 *)(param_3 + 1);
        param_3 = (undefined2 *)((int)param_3 + 3);
        puVar3 = (undefined2 *)((int)puVar3 + 3);
      } while (param_2 != 0);
    }
    iVar2 = 0;
    pcVar4 = (char *)((int)&DAT_100533f0 + 1);
    do {
      cVar1 = pcVar4[-1];
      pcVar5 = pcVar4 + 3;
      (&DAT_100d312a)[iVar2] = cVar1 << 2;
      (&DAT_1004aa8c)[iVar2] = cVar1 << 2;
      cVar1 = *pcVar4;
      (&DAT_100d3129)[iVar2] = cVar1 << 2;
      (&DAT_1004aa8d)[iVar2] = cVar1 << 2;
      cVar1 = pcVar4[1];
      (&DAT_1004aa8e)[iVar2] = cVar1 << 2;
      (&DAT_100d3128)[iVar2] = cVar1 << 2;
      (&DAT_1004aa8f)[iVar2] = 4;
      iVar2 = iVar2 + 4;
      pcVar4 = pcVar5;
    } while ((int)pcVar5 < 0x100536f1);
    if (DAT_100d3124 == (HPALETTE)0x0) {
      DAT_100d3124 = CreatePalette((LOGPALETTE *)&DAT_1004aa88);
      DAT_100f60d0 = SelectPalette(DAT_100d3120,DAT_100d3124,0);
    }
    else {
      SetPaletteEntries(DAT_100d3124,0,0x100,(PALETTEENTRY *)&DAT_1004aa8c);
    }
    SetSystemPaletteUse(DAT_100d3120,2);
    SetSystemPaletteUse(DAT_100d3120,1);
    RealizePalette(DAT_100d3120);
    return 1;
  }
  return 0;
}


