/*
 * Program: i76.exe
 * Function: copy_wloc_six_wheel_transform_table
 * Entry: 004ae5a0
 * Signature: undefined4 __cdecl copy_wloc_six_wheel_transform_table(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] WLOC callback: copies six 0x38-byte
   wheel transform records into the vehicle runtime wheel-location table at +0x168. */

undefined4 __cdecl copy_wloc_six_wheel_transform_table(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  iVar4 = 6;
  puVar1 = (undefined4 *)(param_1 + 8);
  puVar3 = (undefined4 *)(*(int *)(param_2 + 4) + 0x168);
  do {
    iVar4 = iVar4 + -1;
    puVar5 = puVar1;
    puVar6 = puVar3;
    for (iVar2 = 0xe; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar1 = puVar1 + 0xe;
    puVar3 = puVar3 + 0xe;
  } while (iVar4 != 0);
  return 1;
}


