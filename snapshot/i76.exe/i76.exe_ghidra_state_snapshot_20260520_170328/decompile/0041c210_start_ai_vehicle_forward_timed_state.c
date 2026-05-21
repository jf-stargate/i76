/*
 * Program: i76.exe
 * Function: start_ai_vehicle_forward_timed_state
 * Entry: 0041c210
 * Signature: undefined __cdecl start_ai_vehicle_forward_timed_state(int param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Sets a timed AI behavior state, stores a
   target/object id, clears brake override, enters drive mode 3, and sets speed limit 35. */

void __cdecl start_ai_vehicle_forward_timed_state(int param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  fVar2 = get_gameplay_runtime_seconds();
  *(float *)(*(int *)(iVar1 + 0x108) + 0xa82c) = (float)(fVar2 + (float10)_DAT_004bcab0);
  *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0xa998) = param_2;
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x80) = 0x420c0000;
  return;
}


