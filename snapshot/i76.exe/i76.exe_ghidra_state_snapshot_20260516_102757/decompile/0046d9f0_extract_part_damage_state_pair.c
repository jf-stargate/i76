/*
 * Program: i76.exe
 * Function: extract_part_damage_state_pair
 * Entry: 0046d9f0
 * Signature: undefined __cdecl extract_part_damage_state_pair(int param_1, undefined4 * param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=medium-high] Extracts damage/state
   pair from damageable part runtime, defaulting to 300/300. */

void __cdecl extract_part_damage_state_pair(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = *(int *)(param_1 + 0x70);
    if (iVar1 != 0) {
      *param_2 = *(undefined4 *)(iVar1 + 4);
      *param_3 = *(undefined4 *)(iVar1 + 8);
      return;
    }
    *param_2 = 300;
    *param_3 = 300;
  }
  return;
}


