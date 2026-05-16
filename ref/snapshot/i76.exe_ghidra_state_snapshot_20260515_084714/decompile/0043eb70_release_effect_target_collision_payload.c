/*
 * Program: i76.exe
 * Function: release_effect_target_collision_payload
 * Entry: 0043eb70
 * Signature: undefined __cdecl release_effect_target_collision_payload(int param_1)
 */


/* cgpt rename v4: Frees the per-target collision link chain and payload block attached at target
   +0x80. */

void __cdecl release_effect_target_collision_payload(int param_1)

{
  LPVOID lpMem;
  LPVOID pvVar1;
  LPVOID lpMem_00;
  
  lpMem = *(LPVOID *)(param_1 + 0x80);
  if (lpMem != (LPVOID)0x0) {
    lpMem_00 = *(LPVOID *)((int)lpMem + 8);
    while (lpMem_00 != (LPVOID)0x0) {
      pvVar1 = *(LPVOID *)((int)lpMem_00 + 0x18);
      HeapFree(DAT_00608be8,0,lpMem_00);
      lpMem_00 = pvVar1;
    }
    HeapFree(DAT_00608be8,0,lpMem);
    *(undefined4 *)(param_1 + 0x80) = 0;
  }
  return;
}


