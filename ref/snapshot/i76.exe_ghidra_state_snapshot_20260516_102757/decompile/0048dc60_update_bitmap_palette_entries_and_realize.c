/*
 * Program: i76.exe
 * Function: update_bitmap_palette_entries_and_realize
 * Entry: 0048dc60
 * Signature: undefined4 __cdecl update_bitmap_palette_entries_and_realize(int param_1, int param_2, int param_3, int param_4, undefined4 * param_5)
 */


/* cgpt rename v2: Copies palette entries, rebuilds palette tables, creates/updates HPALETTE,
   realizes it, and refreshes the bitmap context. */

undefined4 __cdecl
update_bitmap_palette_entries_and_realize
          (int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  undefined4 *puVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  
  if (*(int *)(param_1 + 0xe0) == 0) {
    return 0;
  }
  memmove((void *)(param_1 + 0xe8 + param_2 * 3),(void *)(param_4 + param_2 * 3),param_3 * 3);
  puVar1 = (undefined4 *)(param_1 + 0xe8);
  *(undefined1 *)(param_1 + 0xea) = 0;
  *(undefined1 *)puVar1 = 0;
  *(undefined1 *)(param_1 + 0xe9) = 0;
  vec3_interpolate_context_helper_004795a0(puVar1);
  matrix_rotation_context_helper_004797f0((int)puVar1,param_2,param_3,0);
  puVar2 = &DAT_004fa4e5;
  puVar3 = (undefined1 *)(param_1 + 0xe9);
  do {
    puVar2[-1] = puVar3[-1];
    *puVar2 = *puVar3;
    puVar2[1] = puVar3[1];
    puVar2[2] = 4;
    puVar2 = puVar2 + 4;
    puVar3 = puVar3 + 3;
  } while ((int)puVar2 < 0x4fa8e5);
  if (DAT_0059c1b4 == (HPALETTE)0x0) {
    DAT_0059c1b4 = CreatePalette((LOGPALETTE *)&DAT_004fa4e0);
    DAT_0059c1b8 = SelectPalette(DAT_0059c1b0,DAT_0059c1b4,0);
  }
  else {
    SetPaletteEntries(DAT_0059c1b4,0,0x100,(PALETTEENTRY *)&DAT_004fa4e4);
  }
  RealizePalette(DAT_0059c1b0);
  geometry_projection_clip_context_helper_004791e0(param_1,param_5);
  return 1;
}


