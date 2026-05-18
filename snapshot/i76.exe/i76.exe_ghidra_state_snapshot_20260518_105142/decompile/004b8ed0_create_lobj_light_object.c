/*
 * Program: i76.exe
 * Function: create_lobj_light_object
 * Entry: 004b8ed0
 * Signature: undefined4 __cdecl create_lobj_light_object(int param_1, int * param_2)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium-high] LOBJ callback. Creates a
   light/object record from position/vector/intensity fields and marks the parent object with a
   light-present flag. */

undefined4 __cdecl create_lobj_light_object(int param_1,int *param_2)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  float local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = *(float *)(param_1 + 0x24);
  local_8 = *(undefined4 *)(param_1 + 0x28);
  local_4 = *(undefined4 *)(param_1 + 0x2c);
  local_18 = *(undefined4 *)(param_1 + 0x30);
  local_14 = *(undefined4 *)(param_1 + 0x34);
  local_10 = *(undefined4 *)(param_1 + 0x38);
  create_lobj_light_runtime_entry
            (*param_2,*(int *)(param_1 + 8),*(float *)(param_1 + 0x48),*(float *)(param_1 + 0x44),
             &local_c,&local_18);
  *(uint *)(*param_2 + 0x10) = *(uint *)(*param_2 + 0x10) | 0x800;
  return 1;
}


