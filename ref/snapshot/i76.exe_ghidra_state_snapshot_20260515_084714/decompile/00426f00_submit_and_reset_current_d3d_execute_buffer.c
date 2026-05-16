/*
 * Program: i76.exe
 * Function: submit_and_reset_current_d3d_execute_buffer
 * Entry: 00426f00
 * Signature: undefined4 __stdcall submit_and_reset_current_d3d_execute_buffer(void)
 */


/* cgpt rename v8 display/d3d cluster: Finalizes the current execute buffer, submits it through the
   Direct3D device, resets the active buffer index, and begins a new command buffer. */

undefined4 submit_and_reset_current_d3d_execute_buffer(void)

{
  int iVar1;
  
  iVar1 = finalize_d3d_execute_buffer_and_set_execute_data(&DAT_00524768 + DAT_00526770 * 8);
  if (iVar1 != 0) {
    (**(code **)(*DAT_005fde48 + 0x20))
              (DAT_005fde48,(&DAT_00524768)[DAT_00526770 * 8],DAT_005fde4c,1);
  }
  DAT_0052689c = 1;
  DAT_00526770 = 0;
  lock_and_begin_d3d_execute_buffer_batch(&DAT_00524768);
  return 1;
}


