/*
 * Program: i76shell.dll
 * Function: cache_system_palette_reserved_entries
 * Entry: 10022730
 * Signature: undefined __stdcall cache_system_palette_reserved_entries(void)
 */


void cache_system_palette_reserved_entries(void)

{
  UINT UVar1;
  int iVar2;
  undefined1 *puVar3;
  
  DAT_100f60cc = GetDeviceCaps(DAT_100d3120,0x18);
  if (0 < (int)DAT_100f60cc) {
    DAT_100f60cc = (int)DAT_100f60cc >> 1;
    GetSystemPaletteEntries(DAT_100d3120,0,DAT_100f60cc,(LPPALETTEENTRY)&DAT_1004aa8c);
    GetSystemPaletteEntries
              (DAT_100d3120,0x100 - DAT_100f60cc,DAT_100f60cc,
               (LPPALETTEENTRY)(&DAT_1004ae8c + DAT_100f60cc * -4));
    UVar1 = DAT_100f60cc;
    iVar2 = 0;
    if (0 < (int)DAT_100f60cc) {
      puVar3 = &DAT_1004aa8d;
      do {
        (&DAT_100d312a)[iVar2 * 4] = (&DAT_1004aa8c)[iVar2 * 4];
        (&DAT_100d3129)[iVar2 * 4] = *puVar3;
        (&DAT_100d3128)[iVar2 * 4] = (&DAT_1004aa8e)[iVar2 * 4];
        (&DAT_1004aa8f)[iVar2 * 4] = 0;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 4;
      } while (iVar2 < (int)UVar1);
    }
    iVar2 = 0x100 - UVar1;
    if (iVar2 < 0x100) {
      iVar2 = iVar2 * 4;
      do {
        (&DAT_100d312a)[iVar2] = (&DAT_1004aa8c)[iVar2];
        (&DAT_100d3129)[iVar2] = (&DAT_1004aa8d)[iVar2];
        (&DAT_100d3128)[iVar2] = (&DAT_1004aa8e)[iVar2];
        (&DAT_1004aa8f)[iVar2] = 0;
        iVar2 = iVar2 + 4;
      } while (iVar2 < 0x400);
    }
  }
  return;
}


