/*
 * Program: i76.exe
 * Function: start_ai_vehicle_targeted_forward_burst_state
 * Entry: 0041c9d0
 * Signature: undefined __cdecl start_ai_vehicle_targeted_forward_burst_state(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v6 ai vehicle behavior cluster: Sets a short forward burst timer, optionally stores
   target id, and enters drive mode 3. */

void __cdecl start_ai_vehicle_targeted_forward_burst_state(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  float10 fVar5;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  iVar3 = *(int *)(iVar1 + 0x108);
  uVar2 = rand();
  uVar4 = (int)uVar2 >> 0x1f;
  if ((int)(((uVar2 ^ uVar4) - uVar4 & 3 ^ uVar4) - uVar4) < *(int *)(iVar3 + 0xa818)) {
    *(int *)(*(int *)(iVar1 + 0x108) + 0xa998) = param_2;
  }
  else {
    *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0xa998) = 0;
  }
  iVar3 = is_vehicle_or_actor_runtime_world_object(param_2);
  if (iVar3 == 0) {
    fVar5 = get_gameplay_runtime_seconds();
    *(float *)(*(int *)(iVar1 + 0x108) + 0xa82c) = (float)(fVar5 + (float10)_DAT_004bcad4);
  }
  else {
    fVar5 = get_gameplay_runtime_seconds();
    *(float *)(*(int *)(iVar1 + 0x108) + 0xa82c) =
         (float)((float10)*(int *)(*(int *)(iVar1 + 0x108) + 0xa818) * (float10)_DAT_004bcadc +
                fVar5 + (float10)_DAT_004bcad8);
  }
  *(undefined4 *)(iVar1 + 0xf0) = 0;
  vehicle_specials_state_getter_helper_00467370(param_1,3);
  *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
  *(undefined4 *)(*(int *)(iVar1 + 0x108) + 0x80) = 0x420c0000;
  return;
}


