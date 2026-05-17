/*
 * Program: i76.exe
 * Function: test_gear_shift_curve_region
 * Entry: 0046a0c0
 * Signature: undefined4 __cdecl test_gear_shift_curve_region(float param_1, float param_2, float param_3, float param_4, float param_5, float param_6)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Tests whether a
   speed/load point lies within a gear shift curve region. */

undefined4 __cdecl
test_gear_shift_curve_region
          (float param_1,float param_2,float param_3,float param_4,float param_5,float param_6)

{
  if ((((param_3 <= param_1) && (param_1 <= param_5)) && (param_4 <= param_2)) &&
     (param_2 <= param_6)) {
    if ((((param_5 - param_3) * (param_2 - param_6)) / (param_6 - param_4)) * param_5 < param_1) {
      return 1;
    }
    return 0;
  }
  return 0xffffffff;
}


