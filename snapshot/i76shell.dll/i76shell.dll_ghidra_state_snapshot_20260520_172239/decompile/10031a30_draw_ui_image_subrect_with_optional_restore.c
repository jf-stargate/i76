/*
 * Program: i76shell.dll
 * Function: draw_ui_image_subrect_with_optional_restore
 * Entry: 10031a30
 * Signature: undefined __cdecl draw_ui_image_subrect_with_optional_restore(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


void __cdecl
draw_ui_image_subrect_with_optional_restore
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  undefined1 local_800 [2048];
  
  if (DAT_100f4f58 != 0) {
    uVar1 = lock_shell_surface_for_draw((int)DAT_100cc518);
    if ((char)uVar1 == '\0') {
      blit_mw2_image_subresource_transformed_or_masked
                ((int *)((int)DAT_100cc518 + 0x6c),param_1,param_2,param_5 + -4 + param_3,
                 param_6 + -1 + param_4,(int)local_800,0,-0x10000,-0x10000,0);
      unlock_shell_surface_after_draw((int)DAT_100cc518);
    }
    mark_shell_surface_dirty_rect(DAT_100cc518,param_3,param_4,param_5,param_6);
    return;
  }
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}


