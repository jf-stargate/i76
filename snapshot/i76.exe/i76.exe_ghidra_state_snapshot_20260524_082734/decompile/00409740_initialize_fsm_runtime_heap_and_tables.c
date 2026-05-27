/*
 * Program: i76.exe
 * Function: initialize_fsm_runtime_heap_and_tables
 * Entry: 00409740
 * Signature: undefined4 __cdecl initialize_fsm_runtime_heap_and_tables(int param_1)
 */


/* cgpt rename v3: Creates the FSM runtime heap, parses serialized FSM table data, and initializes
   FSM command/runtime tables.
   
   I76 rename v43: initialize_fsm_runtime_heap_and_tables
   ADEF/FSM top-level heap/table bootstrap. */

undefined4 __cdecl initialize_fsm_runtime_heap_and_tables(int param_1)

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
  g_fsm_runtime_global_cluster_begin = HeapCreate(0,0,0);
  load_serialized_fsm_runtime_tables
            (iVar1,(int)puVar2,(int *)&g_fsm_runtime_table_cluster,&DAT_0051f60c,
             (int *)&DAT_0051f610,&DAT_0051f614,&DAT_0051f618,&DAT_0051f61c,(int *)&DAT_0051f620,
             &DAT_0051f624,&DAT_0051f628,&DAT_0051f62c,&DAT_0051f630,&DAT_0051f634,&DAT_0051f638,
             &g_fsm_runtime_global_cluster_end,g_fsm_runtime_global_cluster_begin);
  finalize_loaded_fsm_runtime_tables
            (g_fsm_runtime_table_cluster,DAT_0051f60c,DAT_0051f610,DAT_0051f614,DAT_0051f618,
             DAT_0051f61c,DAT_0051f620,DAT_0051f624,DAT_0051f628,DAT_0051f62c,DAT_0051f630,
             DAT_0051f634,DAT_0051f638);
  return 1;
}


