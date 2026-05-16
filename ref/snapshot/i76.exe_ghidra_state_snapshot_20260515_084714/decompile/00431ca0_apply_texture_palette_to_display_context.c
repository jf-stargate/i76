/*
 * Program: i76.exe
 * Function: apply_texture_palette_to_display_context
 * Entry: 00431ca0
 * Signature: undefined __cdecl apply_texture_palette_to_display_context(int * param_1)
 */


/* cgpt readability rename v13 set A: Applies an M16/texture embedded palette or default palette
   into the current display/palette context. */

void __cdecl apply_texture_palette_to_display_context(int *param_1)

{
  int iVar1;
  int **ppiVar2;
  undefined4 uVar3;
  int *local_20 [2];
  int local_18;
  int local_14;
  int *local_10;
  undefined4 local_4;
  
  local_20[0] = &local_18;
  local_4 = 0;
  local_18 = *param_1;
  local_10 = param_1 + 2;
  local_14 = (param_1[1] << 3) >> 3;
  iVar1 = get_m16_embedded_palette_or_default(param_1);
  ppiVar2 = local_20;
  local_20[0][3] = iVar1;
  uVar3 = 1;
  local_20[0][4] = 0xff;
  (*DAT_00608be4)(ppiVar2,uVar3);
  return;
}


