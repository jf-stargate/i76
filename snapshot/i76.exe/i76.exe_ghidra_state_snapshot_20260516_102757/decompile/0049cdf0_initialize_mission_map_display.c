/*
 * Program: i76.exe
 * Function: initialize_mission_map_display
 * Entry: 0049cdf0
 * Signature: undefined __stdcall initialize_mission_map_display(void)
 */


/* cgpt whole-binary semantic rename v1: strings cmap/gdsgc map unavailable */

void initialize_mission_map_display(void)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint local_38;
  int local_34 [13];
  
  if (g_runtime_display_input_mode == 4) {
    piVar1 = find_audio_object_by_name_and_world_object(s_cmap2_wav_004fe5e0,0);
    release_audio_object_if_present(piVar1);
    piVar1 = find_audio_object_by_name_and_world_object(s_gdsgc26_wav_004fe5d4,0);
    release_audio_object_if_present(piVar1);
    release_bitmap_surface_context(&DAT_005a7e90);
    if (DAT_005a7e88 != (LPVOID)0x0) {
      xfree_global_heap(DAT_005a7e88);
      DAT_005a7e88 = (LPVOID)0x0;
    }
    start_pending_audio_objects();
    g_runtime_display_input_mode = 1;
    force_feedback_runtime_helper_00445b40();
    return;
  }
  if ((char)DAT_005a7ec8 != '\0') {
    local_38 = 0;
    load_localized_texture_or_vqm_to_buffer((char *)&DAT_005a7ec8,1,4,(uint *)0x0,&local_38);
    DAT_005a7e88 = (uint *)xalloc_global_heap(local_38);
    if ((DAT_005a7e88 == (uint *)0x0) ||
       (iVar2 = load_localized_texture_or_vqm_to_buffer
                          ((char *)&DAT_005a7ec8,1,4,DAT_005a7e88,&local_38), iVar2 == 0)) {
      report_chunk_parse_error();
      release_bitmap_surface_context(&DAT_005a7e90);
      if (DAT_005a7e88 != (uint *)0x0) {
        xfree_global_heap(DAT_005a7e88);
        DAT_005a7e88 = (uint *)0x0;
        return;
      }
    }
    else {
      puVar3 = (undefined4 *)
               construct_bitmap_surface_context
                         (local_34,*DAT_005a7e88,(int)(DAT_005a7e88[1] << 3) >> 3,
                          (int)(DAT_005a7e88 + 2),0);
      puVar4 = &DAT_005a7e90;
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      if ((DAT_005a7ea4 == 0) ||
         (iVar2 = mission_objective_notepad_context_helper_0045e190(&DAT_005a7e90), iVar2 == 0)) {
        report_chunk_parse_error();
        release_bitmap_surface_context(&DAT_005a7e90);
        if (DAT_005a7e88 != (uint *)0x0) {
          xfree_global_heap(DAT_005a7e88);
          DAT_005a7e88 = (uint *)0x0;
          return;
        }
      }
      else {
        force_feedback_runtime_helper_00445b60();
        update_audio_object_lists_and_release_finished();
        create_or_queue_positional_audio_object(s_cmap2_wav_004fe5e0,0,(undefined4 *)0x0,(int *)0x0)
        ;
        create_or_queue_positional_audio_object
                  (s_gdsgc26_wav_004fe5d4,0,(undefined4 *)0x0,(int *)0x0);
        g_runtime_display_input_mode = (-(uint)(g_runtime_display_input_mode != 4) & 3) + 1;
      }
    }
    return;
  }
  report_chunk_parse_error();
  return;
}


