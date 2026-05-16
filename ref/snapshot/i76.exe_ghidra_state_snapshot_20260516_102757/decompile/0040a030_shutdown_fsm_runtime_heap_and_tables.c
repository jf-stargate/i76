/*
 * Program: i76.exe
 * Function: shutdown_fsm_runtime_heap_and_tables
 * Entry: 0040a030
 * Signature: undefined __stdcall shutdown_fsm_runtime_heap_and_tables(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Destroys the FSM runtime heap, calls the no-op cleanup callback, and clears FSM
   runtime state. */

void shutdown_fsm_runtime_heap_and_tables(void)

{
  HeapDestroy(DAT_0051f5b4);
  noop_world_object_callback_stub();
  _DAT_0051f600 = 0;
  return;
}


