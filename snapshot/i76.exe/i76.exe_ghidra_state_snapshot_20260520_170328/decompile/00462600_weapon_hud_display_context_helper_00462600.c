/*
 * Program: i76.exe
 * Function: weapon_hud_display_context_helper_00462600
 * Entry: 00462600
 * Signature: undefined4 __cdecl weapon_hud_display_context_helper_00462600(int param_1)
 */


/* cgpt label refinement v19: was radar_classifier_specials_weapon_hud_display_helper_00462600.
   Shorten readability label. */

undefined4 __cdecl weapon_hud_display_context_helper_00462600(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  while( true ) {
    if (*(int *)(param_1 + 0x6c) == 0x32) {
      get_world_object_class_id(param_1,1);
      return 1;
    }
    if ((*(int *)(param_1 + 100) != 0) &&
       (iVar1 = weapon_hud_display_context_helper_00462600(*(int *)(param_1 + 100)), iVar1 == 1))
    break;
    param_1 = *(int *)(param_1 + 0x60);
    if (param_1 == 0) {
      return 0;
    }
  }
  return 1;
}


