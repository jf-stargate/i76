/*
 * Program: i76.exe
 * Function: ordnance_instance_runtime_context_helper_0049fb10
 * Entry: 0049fb10
 * Signature: undefined8 __cdecl ordnance_instance_runtime_context_helper_0049fb10(int param_1)
 */


/* cgpt label refinement v20: was ordnance_instance_context_helper_0049fb10. Clarify runtime
   ordnance instance context. */

undefined8 __cdecl ordnance_instance_runtime_context_helper_0049fb10(int param_1)

{
  int iVar1;
  
  iVar1 = find_selected_mission_runtime_index(param_1);
  return CONCAT44((&DAT_006552e8)[iVar1 * 0x34],(&DAT_006552b4)[iVar1 * 0x34]);
}


