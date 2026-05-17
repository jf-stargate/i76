/*
 * Program: i76.exe
 * Function: select_recommended_performance_option_value
 * Entry: 00499920
 * Signature: undefined * __cdecl select_recommended_performance_option_value(undefined4 param_1, undefined4 param_2)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=medium-high] Stores one of two recommended
   performance option values depending on global mode/state DAT_006547e0 == 3. */

undefined * __cdecl
select_recommended_performance_option_value(undefined4 param_1,undefined4 param_2)

{
  if (DAT_006547e0 != 3) {
    *(undefined4 *)(PTR_DAT_004fe194 + 0x10) = param_1;
    return PTR_DAT_004fe194;
  }
  *(undefined4 *)(PTR_DAT_004fe194 + 0x10) = param_2;
  return PTR_DAT_004fe194;
}


