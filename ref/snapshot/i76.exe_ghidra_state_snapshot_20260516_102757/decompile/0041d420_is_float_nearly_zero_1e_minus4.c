/*
 * Program: i76.exe
 * Function: is_float_nearly_zero_1e_minus4
 * Entry: 0041d420
 * Signature: undefined4 __cdecl is_float_nearly_zero_1e_minus4(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Returns true when a float is within +/-0.0001. */

undefined4 __cdecl is_float_nearly_zero_1e_minus4(float param_1)

{
  if ((_DAT_004bcb20 < param_1) && (param_1 < _DAT_004bcb24)) {
    return 1;
  }
  return 0;
}


