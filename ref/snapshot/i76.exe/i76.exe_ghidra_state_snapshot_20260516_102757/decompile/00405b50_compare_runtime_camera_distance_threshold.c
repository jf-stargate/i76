/*
 * Program: i76.exe
 * Function: compare_runtime_camera_distance_threshold
 * Entry: 00405b50
 * Signature: ushort __cdecl compare_runtime_camera_distance_threshold(float param_1)
 */


/* cgpt readability rename v13 set A: Compares DAT_004c2970 against a supplied float and returns a
   16-bit comparison code. */

ushort __cdecl compare_runtime_camera_distance_threshold(float param_1)

{
  ushort uVar1;
  
  if (DAT_004c2970 < param_1) {
    return 0xffff;
  }
  if (DAT_004c2970 == param_1) {
    return 0;
  }
  uVar1 = (ushort)(DAT_004c2970 < param_1) << 8 | (ushort)(NAN(DAT_004c2970) || NAN(param_1)) << 10
          | (ushort)(DAT_004c2970 == param_1) << 0xe;
  if (DAT_004c2970 >= param_1 && (DAT_004c2970 == param_1) == 0) {
    uVar1 = 1;
  }
  return uVar1;
}


