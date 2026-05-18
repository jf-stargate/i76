/*
 * Program: i76.exe
 * Function: parse_hloc_vehicle_hardpoint_location_chunk_validation
 * Entry: 004aea00
 * Signature: undefined4 __cdecl parse_hloc_vehicle_hardpoint_location_chunk_validation(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=medium] Validation-table HLOC callback entry;
   may be a thunk/interior label depending on function discovery, so this script labels only if no
   function starts here. */

undefined4 __cdecl parse_hloc_vehicle_hardpoint_location_chunk_validation(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = *(int *)(param_2 + 4);
  if (6 < *(int *)(iVar1 + 0xa60)) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 0x428 + *(int *)(iVar1 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(iVar1 + 0x430 + *(int *)(iVar1 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(iVar1 + 0x42c + *(int *)(iVar1 + 0xa60) * 0xfc) = *(undefined4 *)(param_1 + 0x1c);
  puVar3 = (undefined4 *)(param_1 + 0x24);
  puVar4 = (undefined4 *)(iVar1 + 0x434 + *(int *)(iVar1 + 0xa60) * 0xfc);
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(int *)(iVar1 + 0xa60) = *(int *)(iVar1 + 0xa60) + 1;
  return 1;
}


