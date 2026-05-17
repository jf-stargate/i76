/*
 * Program: i76.exe
 * Function: dispatch_pending_input_action_code
 * Entry: 0044dec0
 * Signature: undefined __stdcall dispatch_pending_input_action_code(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Dispatches the currently pending
   input action through binding/action handler records. */

void dispatch_pending_input_action_code(void)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  
                    /* I76 semantic baseline: dispatch_pending_input_action_code
                       Dispatches the pending one-shot gameplay action code. */
  DAT_004f4ca4 = DAT_005dd360;
  if (DAT_0053681c != 0) {
    DAT_004f4ca4 = DAT_005dd360;
    DAT_0053681c = 0;
    return;
  }
  iVar1 = get_pending_active_player_ai_control_change_flag();
  uVar3 = _g_pending_input_action_code;
  if (iVar1 != 0) {
    DAT_0053681c = 0;
    return;
  }
  register_default_input_action_names(_g_pending_input_action_code);
  puVar2 = ui_bitmap_region_context_helper_0049beb0();
  if ((puVar2 != (undefined4 *)0x0) &&
     (iVar1 = ui_bitmap_region_context_helper_0049bb40((int)puVar2,uVar3 & 0xffff), iVar1 != 0)) {
    if (iVar1 == 2) {
      ui_bitmap_region_context_helper_0049b9e0((int)puVar2,0);
    }
    keyboard_joystick_input_binding_context_helper_0044eca0();
    return;
  }
  uVar3 = input_action_state_setter_helper_0044de30((short)uVar3);
  if ((short)uVar3 != 0) {
    input_device_binding_input_action_state_helper_0044e030(uVar3 & 0xffff);
  }
  iVar1 = is_damage_side_effects_suppressed();
  if ((iVar1 != 0) && (iVar1 = get_active_player_or_camera_world_object_entry(), iVar1 == 0)) {
    DAT_00536818 = 0;
    return;
  }
  play_adwind_audio_clip();
  scoreboard_or_input_table_context_helper_0044f1c0();
  DAT_00536818 = 0;
  return;
}


