/*
 * Program: i76.exe
 * Function: fsm_query_is_grooves_fault
 * Entry: 0040b860
 * Signature: undefined4 __cdecl fsm_query_is_grooves_fault(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: isGroovesFault validation */

undefined4 __cdecl fsm_query_is_grooves_fault(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    report_chunk_parse_error();
  }
  iVar1 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar1 != 0) {
    return *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x70) + 0x108) + 0xa6e0);
  }
  uVar2 = report_chunk_parse_error();
  return uVar2;
}


