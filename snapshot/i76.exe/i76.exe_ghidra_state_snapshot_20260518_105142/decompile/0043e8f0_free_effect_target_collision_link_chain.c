/*
 * Program: i76.exe
 * Function: free_effect_target_collision_link_chain
 * Entry: 0043e8f0
 * Signature: undefined __cdecl free_effect_target_collision_link_chain(int param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Frees a collision-link chain associated
   with an effect-target/collision payload. */

void __cdecl free_effect_target_collision_link_chain(int param_1)

{
  LPVOID pvVar1;
  LPVOID lpMem;
  
  lpMem = *(LPVOID *)(param_1 + 0x18);
  while (lpMem != (LPVOID)0x0) {
    pvVar1 = *(LPVOID *)((int)lpMem + 8);
    HeapFree(DAT_00608be8,0,lpMem);
    lpMem = pvVar1;
  }
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}


