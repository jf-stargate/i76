/*
 * Program: i76.exe
 * Function: force_feedback_effect_instance_helper_004456e0
 * Entry: 004456e0
 * Signature: undefined __stdcall force_feedback_effect_instance_helper_004456e0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: force feedback effect instance helper
   based on prior focused closure context. */

void force_feedback_effect_instance_helper_004456e0(void)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)get_active_player_or_camera_world_object_entry();
  if (((DAT_00654b8c._1_1_ == '\0') || (DAT_005280d4 != 0)) || (DAT_0054ac68 != 0)) {
    DAT_004f22f8 = 0;
  }
  else {
    DAT_004f22f8 = 1;
  }
  if (((piVar2 != (int *)0x0) && (*piVar2 != 0)) && (iVar1 = *(int *)(*piVar2 + 0x70), iVar1 != 0))
  {
    if (DAT_004f22f8 == 0) {
      get_world_object_class_id(*(int *)(iVar1 + 0x42c),1);
      return;
    }
    world_object_geometry_context_helper_00458860(*(int *)(iVar1 + 0x42c),1);
  }
  return;
}


