/*
 * Program: i76.exe
 * Function: release_d3d_execute_buffer_pool
 * Entry: 00427300
 * Signature: undefined4 __stdcall release_d3d_execute_buffer_pool(void)
 */


/* cgpt rename v8 display/d3d cluster: Finalizes and releases all allocated Direct3D execute buffers
   in the pool and clears active buffer counters. */

undefined4 release_d3d_execute_buffer_pool(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  finalize_d3d_execute_buffer_and_set_execute_data(&DAT_00524768 + DAT_00526770 * 8);
  iVar3 = 0;
  if (0 < DAT_0052689c) {
    piVar2 = &DAT_00524768;
    do {
      piVar1 = (int *)*piVar2;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        *piVar2 = 0;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 8;
    } while (iVar3 < DAT_0052689c);
  }
  DAT_0052689c = 0;
  DAT_00526770 = 0;
  return 1;
}


