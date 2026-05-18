/*
 * Program: i76.exe
 * Function: create_wdf_weapon_mount_pair_and_copy_core
 * Entry: 004ae870
 * Signature: undefined4 __cdecl create_wdf_weapon_mount_pair_and_copy_core(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] WDFC callback: creates paired weapon
   world objects, sets class 0x1e, copies core WDF scalars, and contributes weapon mass/weight. */

undefined4 __cdecl create_wdf_weapon_mount_pair_and_copy_core(int param_1,undefined4 *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)*param_2;
  iVar3 = create_vehicle_child_object_and_copy_ids(*piVar1,param_2 + 2);
  param_2[5] = iVar3;
  if (iVar3 != 0) {
    iVar3 = create_vehicle_child_object_and_copy_ids(*piVar1,param_2 + 2);
    param_2[4] = iVar3;
    if (iVar3 != 0) {
      set_world_object_class_and_register_runtime(iVar3,0x1e);
      set_world_object_class_and_register_runtime(param_2[5],0x1e);
      uVar2 = *(undefined4 *)(param_1 + 0x30);
      iVar3 = *(int *)(param_2[4] + 0x70);
      *(undefined4 *)(iVar3 + 8) = uVar2;
      *(undefined4 *)(iVar3 + 4) = uVar2;
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_1 + 0x38);
      uVar2 = *(undefined4 *)(param_1 + 0x30);
      iVar3 = *(int *)(param_2[5] + 0x70);
      *(undefined4 *)(iVar3 + 8) = uVar2;
      *(undefined4 *)(iVar3 + 4) = uVar2;
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(param_1 + 0x38);
      *(float *)(*(int *)(*(int *)*param_2 + 0x70) + 0xa4) =
           *(float *)(param_1 + 0x34) + *(float *)(param_1 + 0x34) +
           *(float *)(*(int *)(*(int *)*param_2 + 0x70) + 0xa4);
      return 1;
    }
  }
  return 0;
}


