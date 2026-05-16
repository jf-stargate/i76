/*
 * Program: i76.exe
 * Function: enqueue_vehicle_steer_brake_input_sample
 * Entry: 0041f9c0
 * Signature: undefined __cdecl enqueue_vehicle_steer_brake_input_sample(int param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6, int * param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] FSM/control helper that
   validates steer/e-brake values and appends vehicle control samples into the runtime
   damage/control state block. */

void __cdecl
enqueue_vehicle_steer_brake_input_sample
          (int param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6,int *param_7
          )

{
  int iVar1;
  int iVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar2 = get_vehicle_damage_event_state_block(iVar1);
  iVar1 = *param_2;
  if ((iVar1 < -100) || (100 < iVar1)) {
    report_chunk_parse_error();
    *(undefined4 *)(iVar2 + 0x9d68 + *(int *)(iVar2 + 0xa6cc) * 0x18) = 0;
  }
  else {
    *(float *)(iVar2 + 0x9d68 + *(int *)(iVar2 + 0xa6cc) * 0x18) = (float)iVar1 * _DAT_004bcbac;
  }
  iVar1 = *param_3;
  if ((iVar1 < -100) || (100 < iVar1)) {
    report_chunk_parse_error();
    *(undefined4 *)(iVar2 + 0x9d6c + *(int *)(iVar2 + 0xa6cc) * 0x18) = 0;
  }
  else {
    *(float *)(iVar2 + 0x9d6c + *(int *)(iVar2 + 0xa6cc) * 0x18) = (float)iVar1 * _DAT_004bcbac;
  }
  iVar1 = *param_4;
  if ((iVar1 == 0) || (iVar1 == 1)) {
    *(int *)(iVar2 + 0x9d74 + *(int *)(iVar2 + 0xa6cc) * 0x18) = iVar1;
  }
  else {
    report_chunk_parse_error();
    *(undefined4 *)(iVar2 + 0x9d74 + *(int *)(iVar2 + 0xa6cc) * 0x18) = 0;
  }
  iVar1 = *param_5;
  if ((iVar1 == -1) || (iVar1 == 1)) {
    *(float *)(iVar2 + 0x9d70 + *(int *)(iVar2 + 0xa6cc) * 0x18) = (float)iVar1;
  }
  else {
    report_chunk_parse_error();
    *(undefined4 *)(iVar2 + 0x9d70 + *(int *)(iVar2 + 0xa6cc) * 0x18) = 0x3f800000;
  }
  iVar1 = *param_6;
  if ((-1 < iVar1) && (iVar1 < 0xb)) {
    *(int *)(iVar2 + 0x9d78 + *(int *)(iVar2 + 0xa6cc) * 0x18) = iVar1;
  }
  iVar1 = *param_7;
  if ((-1 < iVar1) && (iVar1 < 0xb)) {
    *(int *)(iVar2 + 0x9d7c + *(int *)(iVar2 + 0xa6cc) * 0x18) = iVar1;
  }
  iVar1 = *(int *)(iVar2 + 0xa6cc) + 1;
  *(int *)(iVar2 + 0xa6cc) = iVar1;
  if (iVar1 == 100) {
    *(undefined4 *)(iVar2 + 0xa6cc) = 0;
  }
  if (*(int *)(iVar2 + 0xa6cc) == *(int *)(iVar2 + 0xa6c8)) {
    report_chunk_parse_error();
  }
  *(undefined4 *)(iVar2 + 0xa6d0) = 0;
  return;
}


