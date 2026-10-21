/* Decompiled retail i76.exe, Ghidra v97; 00409740 load_fsm_chunk_from_bwd2_descriptor */

/* cgpt rename v3: Creates the FSM runtime heap, parses serialized FSM table data, and initializes
   FSM command/runtime tables.
   
   I76 rename v43: initialize_fsm_runtime_heap_and_tables
   ADEF/FSM top-level heap/table bootstrap.
   [I76 FSM v58] FSM container callback: descriptor+0x4 length, descriptor+0x8 payload, forwards to
   00410720 then 004125C0.
   [FSM v59 verified] FSM chunk reader: payload = descriptor+8, length = descriptor+4 minus 8;
   actual source: loose miss8/miss16/*.MSN BWD2 chunk.
   [I76 v64B] v58: FSM chunk callback forwards payload to 00410720 and 004125C0 */

undefined4 __cdecl load_fsm_chunk_from_bwd2_descriptor(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_1c = 0;
  iVar1 = *(int *)(param_1 + 4) + -8;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  puVar2 = (undefined4 *)(param_1 + 8);
  if (iVar1 == 0) {
    puVar2 = &local_1c;
  }
  g_fsm_runtime_heap_handle = HeapCreate(0,0,0);
  load_serialized_fsm_runtime_tables
            (iVar1,(int)puVar2,(int *)&g_fsm_host_command_records,&g_fsm_host_command_record_count,
             (int *)&g_fsm_media_records,&g_fsm_media_record_count,&g_fsm_named_position_records,
             &g_fsm_named_position_record_count,(int *)&g_fsm_mission_actor_records,
             &g_fsm_mission_actor_record_count,&g_fsm_pending_vm_node_head,
             &g_fsm_pending_vm_node_count,&g_fsm_vm_initial_word_array,&g_fsm_vm_initial_word_count,
             &g_fsm_vm_token_array,&g_fsm_vm_token_count,g_fsm_runtime_heap_handle);
  finalize_loaded_fsm_runtime_tables
            (g_fsm_host_command_records,g_fsm_host_command_record_count,g_fsm_media_records,
             g_fsm_media_record_count,g_fsm_named_position_records,g_fsm_named_position_record_count
             ,g_fsm_mission_actor_records,g_fsm_mission_actor_record_count,
             g_fsm_pending_vm_node_head,g_fsm_pending_vm_node_count,g_fsm_vm_initial_word_array,
             g_fsm_vm_initial_word_count,g_fsm_vm_token_array);
  return 1;
}


