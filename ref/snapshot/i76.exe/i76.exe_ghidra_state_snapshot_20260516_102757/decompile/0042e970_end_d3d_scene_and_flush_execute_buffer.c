/*
 * Program: i76.exe
 * Function: end_d3d_scene_and_flush_execute_buffer
 * Entry: 0042e970
 * Signature: undefined4 __stdcall end_d3d_scene_and_flush_execute_buffer(void)
 */


/* cgpt rename v8 display/d3d cluster: Flushes the current execute buffer, calls the Direct3D device
   EndScene path, and releases video-memory texture cache records when flagged. */

undefined4 end_d3d_scene_and_flush_execute_buffer(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_005fde48;
  submit_and_reset_current_d3d_execute_buffer();
  iVar2 = (**(code **)(*piVar1 + 0x50))(piVar1);
  if (iVar2 != 0) {
    return 0;
  }
  if (DAT_005280d0 == 1) {
    release_all_video_memory_texture_cache_records();
  }
  DAT_005280d0 = 0;
  return 1;
}


