/*
 * Program: i76.exe
 * Function: set_damageable_part_state_pair
 * Entry: 0046da30
 * Signature: undefined __cdecl set_damageable_part_state_pair(int param_1, undefined4 param_2, undefined4 param_3)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Writes two state/damage
   fields to class 0x1e damageable part runtime data. */

void __cdecl set_damageable_part_state_pair(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x6c) == 0x1e)) &&
     (iVar1 = *(int *)(param_1 + 0x70), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 4) = param_2;
    *(undefined4 *)(iVar1 + 8) = param_3;
  }
  return;
}


