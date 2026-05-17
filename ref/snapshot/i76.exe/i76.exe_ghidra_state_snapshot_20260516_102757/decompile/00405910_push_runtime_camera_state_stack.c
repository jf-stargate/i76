/*
 * Program: i76.exe
 * Function: push_runtime_camera_state_stack
 * Entry: 00405910
 * Signature: undefined4 __stdcall push_runtime_camera_state_stack(void)
 */


/* cgpt readability rename v13 set A: Pushes the active runtime camera/view state onto an 8-entry
   stack and resumes classifier/display state if needed. */

undefined4 push_runtime_camera_state_stack(void)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (DAT_004c2988 < 8) {
    puVar3 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
    puVar4 = &g_runtime_display_mode_change_callback;
    DAT_004c2988 = DAT_004c2988 + 1;
    for (iVar2 = 0x9a; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    if ((g_runtime_display_mode_state == 2) &&
       (iVar2 = weapon_hud_display_context_helper_004621a0(), iVar2 == 0)) {
      uVar1 = reticle_crosshair_context_helper_00462130();
      while (uVar1 == 0) {
        uVar1 = reticle_crosshair_context_helper_00462130();
      }
    }
    return 1;
  }
  return 0;
}


