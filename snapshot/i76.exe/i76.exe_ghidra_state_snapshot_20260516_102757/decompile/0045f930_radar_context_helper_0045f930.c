/*
 * Program: i76.exe
 * Function: radar_context_helper_0045f930
 * Entry: 0045f930
 * Signature: undefined __cdecl radar_context_helper_0045f930(int param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_radar_context_helper_0045f930. Shorten readability
   label. */

void __cdecl radar_context_helper_0045f930(int param_1)

{
  int iVar1;
  int *piVar2;
  char *pcVar3;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if (iVar1 != 0) {
    piVar2 = (int *)get_active_player_or_camera_world_object_entry();
    if ((piVar2 != (int *)0x0) && (*(int *)(iVar1 + 0x78) == *piVar2)) {
      pcVar3 = (char *)find_object_texture_slot_name(param_1,0);
      if ((pcVar3 != (char *)0x0) && (*pcVar3 != '\0')) {
        release_texture_animation_record(param_1,pcVar3);
      }
    }
  }
  return;
}


