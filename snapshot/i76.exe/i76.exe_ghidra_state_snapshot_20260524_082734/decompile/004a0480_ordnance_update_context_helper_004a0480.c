/*
 * Program: i76.exe
 * Function: ordnance_update_context_helper_004a0480
 * Entry: 004a0480
 * Signature: undefined __cdecl ordnance_update_context_helper_004a0480(float * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was ordnance_state_update_context_helper_004a0480. Shorten readability
   label. */

void __cdecl ordnance_update_context_helper_004a0480(float *param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  float local_3c [4];
  undefined4 local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar1 = *(int *)(param_2 + 0x70);
  if (iVar1 == 0) {
    effect_target_list_scan_context_helper_004382e0(local_3c);
  }
  else {
    pfVar2 = (float *)(iVar1 + 0x14);
    local_3c[0] = _DAT_004bea5c;
    local_24 = *(float *)(param_2 + 0x18) * *pfVar2 +
               *(float *)(param_2 + 0x30) * *(float *)(iVar1 + 0x1c) +
               *(float *)(param_2 + 0x24) * *(float *)(iVar1 + 0x18);
    local_20 = *(float *)(param_2 + 0x1c) * *pfVar2 +
               *(float *)(param_2 + 0x34) * *(float *)(iVar1 + 0x1c) +
               *(float *)(param_2 + 0x28) * *(float *)(iVar1 + 0x18);
    local_1c = *(float *)(param_2 + 0x20) * *pfVar2 +
               *(float *)(param_2 + 0x2c) * *(float *)(iVar1 + 0x18) +
               *(float *)(param_2 + 0x38) * *(float *)(iVar1 + 0x1c);
    local_2c = _DAT_004bea34;
    local_28 = _DAT_004bea34;
    local_3c[2] = SQRT(local_1c * local_1c + local_20 * local_20 + local_24 * local_24);
    local_18 = *(undefined4 *)(iVar1 + 0x2c);
    local_14 = *(undefined4 *)(iVar1 + 0x30);
    local_10 = *(undefined4 *)(iVar1 + 0x34);
  }
  pfVar2 = local_3c;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


