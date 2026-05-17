/*
 * Program: i76.exe
 * Function: dispatch_runtime_camera_mode_activation_by_id
 * Entry: 004096c0
 * Signature: undefined __cdecl dispatch_runtime_camera_mode_activation_by_id(undefined4 param_1, int param_2)
 */


/* cgpt rename v5 runtime camera cluster: Dispatches runtime camera/view mode activation through the
   id->function table at 004c2990 and resets projection state after transitions. */

void __cdecl dispatch_runtime_camera_mode_activation_by_id(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if ((g_runtime_display_mode_state != 5) && (g_runtime_display_mode_state != 9)) {
    iVar2 = 0;
    piVar1 = &DAT_004c2990;
    while (*piVar1 != param_2) {
      piVar1 = piVar1 + 2;
      iVar2 = iVar2 + 1;
      if ((int *)0x4c2a0f < piVar1) {
        return;
      }
    }
    (**(code **)(iVar2 * 8 + 0x4c2994))(param_1);
    if (g_runtime_display_mode_state != 2) {
      weapon_hud_display_context_helper_004621b0();
      software_raster_command_context_helper_00472400((float *)&DAT_004c2730,1.0);
    }
  }
  return;
}


