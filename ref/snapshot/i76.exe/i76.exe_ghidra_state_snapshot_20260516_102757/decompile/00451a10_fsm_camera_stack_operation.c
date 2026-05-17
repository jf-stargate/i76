/*
 * Program: i76.exe
 * Function: fsm_camera_stack_operation
 * Entry: 00451a10
 * Signature: undefined __cdecl fsm_camera_stack_operation(int * param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00451a10
   suggested_name: fsm_camera_stack_operation
   basis: FSM camera stack diagnostics mention underflow/overflow. */

void __cdecl fsm_camera_stack_operation(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = is_vehicle_or_actor_runtime_world_object(*param_1);
  if (iVar1 != 0) {
    iVar1 = 0;
    if (0 < DAT_0053fd78) {
      piVar2 = &DAT_0053fcb0;
      do {
        if (*piVar2 == 0) {
          (&DAT_0053fcb0)[iVar1] = param_1;
          return;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 1;
      } while (iVar1 < DAT_0053fd78);
    }
    if (DAT_0053fd78 < 0x32) {
      (&DAT_0053fcb0)[DAT_0053fd78] = param_1;
      DAT_0053fd78 = DAT_0053fd78 + 1;
      return;
    }
    report_chunk_parse_error();
  }
  return;
}


