/*
 * Program: i76.exe
 * Function: finalize_loaded_fsm_runtime_tables
 * Entry: 004125c0
 * Signature: undefined __cdecl finalize_loaded_fsm_runtime_tables(byte * param_1, int param_2, char * param_3, int param_4, undefined4 param_5, undefined4 param_6, byte * param_7, int param_8, int * param_9, int param_10, int param_11, undefined4 param_12, int param_13)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Finalizes loaded FSM runtime tables by initializing
   command names, registering instance ids, validating media lists, and relocating command-table
   pointers. */

void __cdecl
finalize_loaded_fsm_runtime_tables
          (byte *param_1,int param_2,char *param_3,int param_4,undefined4 param_5,undefined4 param_6
          ,byte *param_7,int param_8,int *param_9,int param_10,int param_11,undefined4 param_12,
          int param_13)

{
  undefined4 uVar1;
  
  if (0 < param_2) {
    do {
      uVar1 = initialize_fsm_command_name_table(param_1);
      *(undefined4 *)(param_1 + 0x50) = uVar1;
      param_1 = param_1 + 0x54;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  register_fsm_instance_ids_from_mission(param_7,param_8);
  validate_project_wav_smk_resource_list(param_3,param_4);
  relocate_fsm_command_table_internal_pointers(param_9,param_10,param_13,param_11);
  return;
}


