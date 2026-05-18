/*
 * Program: i76.exe
 * Function: test_bounds_overlap_xz_ranges
 * Entry: 00434b60
 * Signature: undefined4 __cdecl test_bounds_overlap_xz_ranges(float * param_1, int param_2)
 */


/* cgpt readability rename v13 set A: Tests overlap between two X/Z bounding ranges or effect-target
   bounds records. */

undefined4 __cdecl test_bounds_overlap_xz_ranges(float *param_1,int param_2)

{
  if (*(float *)(param_2 + 0x5c) < *param_1) {
    return 0;
  }
  if (param_1[3] < *(float *)(param_2 + 0x50)) {
    return 0;
  }
  if (*(float *)(param_2 + 100) < param_1[2]) {
    return 0;
  }
  if (param_1[5] < *(float *)(param_2 + 0x58)) {
    return 0;
  }
  return 1;
}


