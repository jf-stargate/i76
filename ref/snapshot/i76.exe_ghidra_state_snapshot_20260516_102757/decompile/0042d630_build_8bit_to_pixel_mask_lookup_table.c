/*
 * Program: i76.exe
 * Function: build_8bit_to_pixel_mask_lookup_table
 * Entry: 0042d630
 * Signature: undefined __cdecl build_8bit_to_pixel_mask_lookup_table(uint param_1, int * param_2)
 */


/* cgpt rename v8 display/d3d cluster: Builds a 256-entry lookup table that maps 8-bit channel
   values into a destination pixel-format mask/bitfield. */

void __cdecl build_8bit_to_pixel_mask_lookup_table(uint param_1,int *param_2)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  
  bVar3 = 0;
  for (; (param_1 & 1) == 0; param_1 = (int)param_1 >> 1) {
    bVar3 = bVar3 + 1;
  }
  bVar2 = 0;
  for (; param_1 != 0; param_1 = (int)param_1 >> 1) {
    bVar2 = bVar2 + 1;
  }
  uVar1 = 0;
  iVar4 = 0;
  param_1 = 0x100;
  do {
    uVar1 = uVar1 + (1 << (bVar2 & 0x1f));
    *param_2 = iVar4 << (bVar3 & 0x1f);
    if (0xff < uVar1) {
      uVar1 = uVar1 - 0x100;
      iVar4 = iVar4 + 1;
    }
    param_2 = param_2 + 1;
    param_1 = param_1 - 1;
  } while (param_1 != 0);
  return;
}


