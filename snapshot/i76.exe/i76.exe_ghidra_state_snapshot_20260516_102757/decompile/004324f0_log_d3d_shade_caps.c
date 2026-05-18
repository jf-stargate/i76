/*
 * Program: i76.exe
 * Function: log_d3d_shade_caps
 * Entry: 004324f0
 * Signature: undefined __cdecl log_d3d_shade_caps(FILE * param_1, uint param_2)
 */


/* cgpt whole-binary semantic rename v1: string table: Shade Caps / D3DPSHADECAPS_* */

void __cdecl log_d3d_shade_caps(FILE *param_1,uint param_2)

{
  fprintf(param_1,s_Shade_Caps_004f0a64);
  if (param_2 == 0) {
    fprintf(param_1,s_None_004f061c);
    return;
  }
  if ((param_2 & 1) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORFLATMONO_004f0a3c);
  }
  if ((param_2 & 2) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORFLATRGB_004f0a14);
  }
  if ((param_2 & 4) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORGOURAUDMONO_004f09ec);
  }
  if ((param_2 & 8) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORGOURAUDRGB_004f09c4);
  }
  if ((param_2 & 0x10) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORPHONGMONO_004f099c);
  }
  if ((param_2 & 0x20) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_COLORPHONGRGB_004f0974);
  }
  if ((param_2 & 0x40) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARFLATMONO_004f094c);
  }
  if ((param_2 & 0x80) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARFLATRGB_004f0924);
  }
  if ((param_2 & 0x100) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARGOURAUDMON_004f08fc);
  }
  if ((param_2 & 0x200) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARGOURAUDRGB_004f08d4);
  }
  if ((param_2 & 0x400) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARPHONGMONO_004f08ac);
  }
  if ((param_2 & 0x800) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_SPECULARPHONGRGB_004f0884);
  }
  if ((param_2 & 0x1000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAFLATBLEND_004f085c);
  }
  if ((param_2 & 0x2000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAFLATSTIPPLED_004f0834);
  }
  if ((param_2 & 0x4000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAGOURAUDBLEND_004f080c);
  }
  if ((param_2 & 0x8000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAGOURAUDSTIPPL_004f07e4);
  }
  if ((param_2 & 0x10000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAPHONGBLEND_004f07bc);
  }
  if ((param_2 & 0x20000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_ALPHAPHONGSTIPPLED_004f0794);
  }
  if ((param_2 & 0x40000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_FOGFLAT_004f076c);
  }
  if ((param_2 & 0x80000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_FOGGOURAUD_004f0744);
  }
  if ((param_2 & 0x100000) != 0) {
    fprintf(param_1,s_D3DPSHADECAPS_FOGPHONG_004f071c);
  }
  return;
}


