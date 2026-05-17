/*
 * Program: i76.exe
 * Function: mark_vehicle_runtime_state_dirty
 * Entry: 00466e80
 * Signature: undefined __cdecl mark_vehicle_runtime_state_dirty(int param_1)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=medium-high] Sets vehicle runtime
   dirty/refresh flags around offsets +0x450/+0x454. */

void __cdecl mark_vehicle_runtime_state_dirty(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x6c) == 1) {
    iVar1 = *(int *)(param_1 + 0x70);
    *(undefined4 *)(iVar1 + 0x450) = 0x40000000;
    *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x80000400;
  }
  return;
}


