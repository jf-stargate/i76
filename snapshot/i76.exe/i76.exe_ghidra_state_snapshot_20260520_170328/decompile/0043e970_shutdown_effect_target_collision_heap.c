/*
 * Program: i76.exe
 * Function: shutdown_effect_target_collision_heap
 * Entry: 0043e970
 * Signature: undefined __stdcall shutdown_effect_target_collision_heap(void)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Destroys the effect-target
   collision/link payload heap and clears the heap handle. */

void shutdown_effect_target_collision_heap(void)

{
  HeapDestroy(DAT_00608be8);
  DAT_00608be8 = (HANDLE)0x0;
  return;
}


