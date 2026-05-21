/*
 * Program: i76.exe
 * Function: extract_engine_or_suspension_state_pair
 * Entry: 0046a9f0
 * Signature: undefined __cdecl extract_engine_or_suspension_state_pair(int param_1, undefined4 * param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=medium-high] Extracts two dword
   state values from engine/suspension component runtime, defaulting to 300/300. */

void __cdecl
extract_engine_or_suspension_state_pair(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  
  if (param_1 != 0) {
    puVar1 = *(undefined4 **)(param_1 + 0x70);
    if (puVar1 != (undefined4 *)0x0) {
      *param_2 = *puVar1;
      *param_3 = puVar1[1];
      return;
    }
    *param_2 = 300;
    *param_3 = 300;
  }
  return;
}


