/*
 * Program: i76.exe
 * Function: initialize_runtime_node_sentinel_fields
 * Entry: 004620a0
 * Signature: undefined __cdecl initialize_runtime_node_sentinel_fields(int param_1)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium] Small class-descriptor predicate
   near damage dispatch path.
   [I76 v67] Writes -1 to node+68 and zero to node+70; does not test or return handler availability
    */

void __cdecl initialize_runtime_node_sentinel_fields(int param_1)

{
  *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x70) = 0;
  return;
}


