/*
 * Program: i76.exe
 * Function: log_d3d_misc_caps
 * Entry: 00432690
 * Signature: undefined __cdecl log_d3d_misc_caps(FILE * param_1, uint param_2)
 */


/* cgpt whole-binary semantic rename v1: string table: Misc Caps / D3DPMISCCAPS_* */

void __cdecl log_d3d_misc_caps(FILE *param_1,uint param_2)

{
  fprintf(param_1,s_Misc_Caps_004f0b50);
  if (param_2 == 0) {
    fprintf(param_1,s_None_004f061c);
    return;
  }
  if ((param_2 & 1) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_MASKPLANES_004f0b30);
  }
  if ((param_2 & 2) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_MASKZ_004f0b10);
  }
  if ((param_2 & 4) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_LINEPATTERNREP_004f0af0);
  }
  if ((param_2 & 8) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_CONFORMANT_004f0ad0);
  }
  if ((param_2 & 0x10) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_CULLNONE_004f0ab0);
  }
  if ((param_2 & 0x20) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_CULLCW_004f0a90);
  }
  if ((param_2 & 0x40) != 0) {
    fprintf(param_1,s_D3DPMISCCAPS_CULLCCW_004f0a70);
  }
  return;
}


