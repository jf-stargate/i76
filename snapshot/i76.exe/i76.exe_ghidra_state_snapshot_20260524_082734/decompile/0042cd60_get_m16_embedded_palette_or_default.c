/*
 * Program: i76.exe
 * Function: get_m16_embedded_palette_or_default
 * Entry: 0042cd60
 * Signature: int __cdecl get_m16_embedded_palette_or_default(int * param_1)
 */


/* cgpt rename v8 display/d3d cluster: Returns the embedded trailing palette pointer for an M16-like
   texture when present, otherwise returns the global/default palette pointer. */

int __cdecl get_m16_embedded_palette_or_default(int *param_1)

{
  int iVar1;
  
  if ((param_1[1] & 0x80000000U) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = ((param_1[1] << 3) >> 3) * *param_1 + 8 + (int)param_1;
  }
  if (iVar1 == 0) {
    iVar1 = DAT_0052b91c;
  }
  return iVar1;
}


