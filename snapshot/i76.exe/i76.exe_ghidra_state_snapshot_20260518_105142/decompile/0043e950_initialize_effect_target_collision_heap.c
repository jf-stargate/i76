/*
 * Program: i76.exe
 * Function: initialize_effect_target_collision_heap
 * Entry: 0043e950
 * Signature: undefined __stdcall initialize_effect_target_collision_heap(void)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Creates the heap used for effect-target
   collision/link payload allocations. */

void initialize_effect_target_collision_heap(void)

{
  DAT_00608be8 = HeapCreate(0,0,0);
  return;
}


