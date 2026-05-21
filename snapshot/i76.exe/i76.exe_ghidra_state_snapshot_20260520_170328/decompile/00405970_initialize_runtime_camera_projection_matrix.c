/*
 * Program: i76.exe
 * Function: initialize_runtime_camera_projection_matrix
 * Entry: 00405970
 * Signature: undefined __cdecl initialize_runtime_camera_projection_matrix(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Initializes runtime
   camera/projection matrix globals, view aspect, default camera mode state, and active camera mode
   callback. */

void __cdecl initialize_runtime_camera_projection_matrix(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  float local_1e0;
  float local_1dc;
  float local_1d8 [118];
  
  DAT_004c2718 = 1;
  if (g_runtime_high_color_resource_mode == 2) {
    local_1e0 = 1.0;
  }
  else {
    local_1e0 = ((float)((DAT_005dcee8 - DAT_005dcee0) + 1) * _DAT_004bc50c) /
                ((float)((DAT_005dcee4 - DAT_005dcedc) + 1) * _DAT_004bc510);
  }
  if (DAT_00654b8a == '\0') {
    local_1dc = 150.0;
  }
  else {
    local_1dc = DAT_004c271c;
  }
  puVar1 = (undefined4 *)
           software_raster_command_context_helper_00472220
                     (local_1d8,0x5dcec0,1.5707963,local_1e0,local_1dc,1.0);
  puVar5 = &DAT_004c2730;
  for (iVar3 = 0x76; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar5 = puVar5 + 1;
  }
  if (param_1 == 1) {
    DAT_004c2908 = 0;
    DAT_004c2724 = 1;
    g_runtime_display_mode_state = 0;
    _DAT_004c2964 = 0;
    DAT_004c2968 = 0;
    _DAT_004c296c = 0;
    DAT_004c2970 = 0;
    _DAT_004c2980 = 0;
    DAT_004c2918 = 0x3f060a92;
    DAT_004c2928 = 0x3f060a92;
    DAT_004c291c = 0;
    DAT_004c292c = 0;
    DAT_004c2924 = 0x40b00000;
    DAT_004c2934 = 0x40b00000;
    uVar2 = get_active_player_or_camera_world_object_entry();
    if ((g_runtime_display_mode_state != 5) && (g_runtime_display_mode_state != 9)) {
      iVar3 = 0;
      piVar4 = &DAT_004c2990;
      while (*piVar4 != 0x1a) {
        piVar4 = piVar4 + 2;
        iVar3 = iVar3 + 1;
        if ((int *)0x4c2a0f < piVar4) {
          return;
        }
      }
      (**(code **)(iVar3 * 8 + 0x4c2994))(uVar2);
      if (g_runtime_display_mode_state != 2) {
        weapon_hud_display_context_helper_004621b0();
        software_raster_command_context_helper_00472400((float *)&DAT_004c2730,1.0);
      }
    }
  }
  return;
}


