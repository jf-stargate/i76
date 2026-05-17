/*
 * Program: i76.exe
 * Function: weapon_instance_context_helper_004a51a0
 * Entry: 004a51a0
 * Signature: undefined4 __cdecl weapon_instance_context_helper_004a51a0(int * param_1, int * param_2)
 */


/* cgpt label refinement v20: was weapon_instance_registration_context_helper_004a51a0. Shorten
   readability label. */

undefined4 __cdecl weapon_instance_context_helper_004a51a0(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_90 [36];
  
  local_90[0] = 9;
  local_90[1] = 9;
  local_90[2] = 9;
  local_90[3] = 9;
  local_90[4] = 9;
  local_90[5] = 9;
  local_90[7] = 9;
  local_90[8] = 9;
  local_90[9] = 9;
  local_90[10] = 9;
  local_90[0xd] = 9;
  local_90[0xe] = 9;
  local_90[0xf] = 9;
  local_90[0x11] = 9;
  local_90[0x12] = 9;
  local_90[0x13] = 9;
  local_90[0x14] = 9;
  local_90[0x15] = 9;
  local_90[0x17] = 9;
  local_90[0x18] = 9;
  local_90[0x19] = 9;
  local_90[0x1c] = 9;
  local_90[0x1d] = 9;
  local_90[0x1e] = 9;
  local_90[0x1f] = 9;
  local_90[0x20] = 9;
  local_90[0x21] = 9;
  local_90[0x22] = 9;
  local_90[0xc] = 3;
  local_90[0x1b] = 3;
  local_90[6] = 2;
  local_90[0xb] = 1;
  local_90[0x10] = 2;
  local_90[0x16] = 4;
  local_90[0x1a] = 1;
  iVar1 = local_90[param_1[3] * 5 + param_1[2]];
  iVar2 = local_90[param_2[3] * 5 + param_2[2]];
  if (iVar1 < iVar2) {
    iVar3 = 0xffffffff;
  }
  else if (iVar1 == iVar2) {
    iVar3 = 0;
  }
  else {
    iVar3 = 1;
    if (iVar1 <= iVar2) {
      iVar3 = local_90[0x23];
    }
  }
  if (iVar1 == iVar2) {
    if (*param_1 < *param_2) {
      return 0xffffffff;
    }
    if (*param_2 < *param_1) {
      iVar3 = 1;
    }
  }
  return iVar3;
}


