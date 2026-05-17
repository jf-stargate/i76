/*
 * Program: i76.exe
 * Function: log_d3d_blend_caps
 * Entry: 00432740
 * Signature: undefined __cdecl log_d3d_blend_caps(FILE * param_1, uint param_2)
 */


/* cgpt whole-binary semantic rename v1: string table: Blend Caps / D3DPBLENDCAPS_* */

void __cdecl log_d3d_blend_caps(FILE *param_1,uint param_2)

{
  fprintf(param_1,s_Blend_Caps_004f0cf8);
  if (param_2 == 0) {
    fprintf(param_1,s_None_004f061c);
    return;
  }
  if ((param_2 & 1) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_ZERO_004f0cdc);
  }
  if ((param_2 & 2) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_ONE_004f0cbc);
  }
  if ((param_2 & 4) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_SRCCOLOR_004f0c9c);
  }
  if ((param_2 & 8) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_INVSRCCOLOR_004f0c7c);
  }
  if ((param_2 & 0x10) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_SRCALPHA_004f0c5c);
  }
  if ((param_2 & 0x20) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_INVSRCALPHA_004f0c3c);
  }
  if ((param_2 & 0x40) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_DESTALPHA_004f0c1c);
  }
  if ((param_2 & 0x80) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_INVDESTALPHA_004f0bfc);
  }
  if ((param_2 & 0x100) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_DESTCOLOR_004f0bdc);
  }
  if ((param_2 & 0x200) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_INVDESTCOLOR_004f0bbc);
  }
  if ((param_2 & 0x400) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_SRCALPHASAT_004f0b9c);
  }
  if ((param_2 & 0x800) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_BOTHSRCALPHA_004f0b7c);
  }
  if ((param_2 & 0x1000) != 0) {
    fprintf(param_1,s_D3DPBLENDCAPS_BOTHINVSRCALPHA_004f0b5c);
  }
  return;
}


