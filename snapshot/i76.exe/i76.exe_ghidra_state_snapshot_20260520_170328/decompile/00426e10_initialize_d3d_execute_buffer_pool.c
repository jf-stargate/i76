/*
 * Program: i76.exe
 * Function: initialize_d3d_execute_buffer_pool
 * Entry: 00426e10
 * Signature: undefined4 __cdecl initialize_d3d_execute_buffer_pool(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v8 display/d3d cluster: Initializes the Direct3D execute-buffer pool/ring, creates
   the first execute buffer, and primes the current command buffer. */

undefined4 __cdecl initialize_d3d_execute_buffer_pool(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = &DAT_00524784;
  do {
    puVar1[-2] = 0;
    *puVar1 = 0xffffffff;
    puVar1 = puVar1 + 8;
  } while ((int)puVar1 < 0x526784);
  iVar2 = 0x2000;
  if (DAT_005fe578 != 0) {
    iVar2 = DAT_005fe578;
  }
  DAT_005268a0 = (uint)(iVar2 * 3) / 0xa0;
  if ((int)DAT_005fe57c < (int)DAT_005268a0) {
    DAT_005268a0 = DAT_005fe57c;
  }
  _DAT_00526780 = 0;
  DAT_00526768 = param_1;
  DAT_00526770 = 0;
  DAT_0052689c = 1;
  _DAT_00526788 = 0;
  _DAT_00526778 = 0x14;
  _DAT_0052677c = 1;
  _DAT_00526784 = 0x2000;
  if (DAT_005fe578 != 0) {
    _DAT_00526784 = DAT_005fe578;
  }
  iVar2 = (**(code **)(*param_1 + 0x18))(param_1,&DAT_00526778,&DAT_00524768,0);
  if (iVar2 == 0) {
    iVar2 = DAT_00526770 * 8;
    (&DAT_0052477c)[DAT_00526770 * 8] = 1;
    lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768 + iVar2);
  }
  return 1;
}


