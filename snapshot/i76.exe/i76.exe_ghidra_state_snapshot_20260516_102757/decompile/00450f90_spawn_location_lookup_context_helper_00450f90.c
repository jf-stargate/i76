/*
 * Program: i76.exe
 * Function: spawn_location_lookup_context_helper_00450f90
 * Entry: 00450f90
 * Signature: undefined __cdecl spawn_location_lookup_context_helper_00450f90(int param_1, int param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: spawn location lookup context helper
   based on prior focused closure context. */

void __cdecl spawn_location_lookup_context_helper_00450f90(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (param_2 == 0) {
    if (0x3f < DAT_00540d98) {
      return;
    }
    puVar1 = (undefined4 *)(&DAT_0053fd88 + DAT_00540d98 * 0x40);
    DAT_00540d98 = DAT_00540d98 + 1;
  }
  else {
    if (param_2 != 1) {
      return;
    }
    if (0x3f < DAT_00540d9c) {
      return;
    }
    puVar1 = (undefined4 *)(&DAT_0053ecb0 + DAT_00540d9c * 0x40);
    DAT_00540d9c = DAT_00540d9c + 1;
  }
  *puVar1 = *(undefined4 *)(param_1 + 8);
  puVar1[1] = *(undefined4 *)(param_1 + 0xc);
  puVar1[2] = *(undefined4 *)(param_1 + 0x10);
  puVar1[3] = *(undefined4 *)(param_1 + 0x14);
  puVar1[4] = *(undefined4 *)(param_1 + 0x18);
  puVar1[5] = *(undefined4 *)(param_1 + 0x1c);
  puVar1[6] = *(undefined4 *)(param_1 + 0x20);
  puVar1[7] = *(undefined4 *)(param_1 + 0x24);
  puVar1[8] = *(undefined4 *)(param_1 + 0x28);
  *(double *)(puVar1 + 10) = (double)*(float *)(param_1 + 0x2c);
  *(double *)(puVar1 + 0xc) = (double)*(float *)(param_1 + 0x30);
  *(double *)(puVar1 + 0xe) = (double)*(float *)(param_1 + 0x34);
  return;
}


