/* Decompiled retail i76.exe, Ghidra v97; 004238e0 cb_voice_message_completion_callback */

undefined4 cb_voice_message_completion_callback(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  DWORD DVar4;
  int *piVar5;
  int iStack_48;
  undefined4 uStack_44;
  undefined4 auStack_2c [4];
  undefined4 uStack_1c;
  code *pcStack_4;
  
  pcVar2 = g_cb_voice_message_queue_head;
  do {
    do {
      if (pcVar2 == (char *)0x0) {
        g_cb_voice_message_queue_head = pcVar2;
        return 0;
      }
      pcVar1 = *(char **)(pcVar2 + 0x20);
      g_cb_voice_message_queue_head = pcVar2;
      iVar3 = world_object_has_optional_runtime_flag(*(int *)(pcVar2 + 0x10));
      if ((iVar3 != 0) && (iVar3 = cockpit_gauge_context_helper_00459d90(), iVar3 != 0)) {
        cockpit_hud_texture_context_helper_00459d60();
      }
      if (*(undefined4 **)(pcVar2 + 0x14) != (undefined4 *)0x0) {
        release_audio_object_if_present(*(undefined4 **)(pcVar2 + 0x14));
      }
      xfree_global_heap(pcVar2);
      pcVar2 = pcVar1;
    } while ((pcVar1 == (char *)0x0) ||
            ((*(int *)(pcVar1 + 0x10) != 0 &&
             ((*(uint *)(*(int *)(pcVar1 + 0x10) + 0x10) & 0x200) != 0))));
    g_cb_voice_message_queue_head = pcVar1;
    if ((*(int *)(pcVar1 + 0x18) == 4) &&
       (DVar4 = GetTickCount(), 10000 < DVar4 - *(int *)(pcVar1 + 0x1c))) {
      piVar5 = (int *)0x0;
    }
    else {
      initialize_audio_distance_params_defaults(auStack_2c);
      initialize_audio_gate_params_defaults(&iStack_48);
      pcStack_4 = cb_voice_message_completion_callback;
      uStack_1c = 5;
      uStack_44 = 10000;
      piVar5 = create_or_queue_positional_audio_object(pcVar1,0,auStack_2c,&iStack_48);
      if ((((piVar5 != (int *)0x0) &&
           (iVar3 = world_object_has_optional_runtime_flag(*(int *)(pcVar1 + 0x10)), iVar3 != 0)) &&
          (iVar3 = weapon_hud_display_context_helper_004621a0(), iVar3 == 0)) &&
         (iVar3 = cockpit_gauge_context_helper_00459d90(), iVar3 == 0)) {
        cockpit_hud_texture_context_helper_00459d60();
      }
    }
    *(int **)(g_cb_voice_message_queue_head + 0x14) = piVar5;
    pcVar2 = g_cb_voice_message_queue_head;
  } while (*(int *)(g_cb_voice_message_queue_head + 0x14) == 0);
  return 0;
}


