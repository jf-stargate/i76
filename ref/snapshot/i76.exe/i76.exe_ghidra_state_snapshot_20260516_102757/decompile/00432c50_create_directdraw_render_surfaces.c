/*
 * Program: i76.exe
 * Function: create_directdraw_render_surfaces
 * Entry: 00432c50
 * Signature: undefined4 __cdecl create_directdraw_render_surfaces(undefined4 param_1, int param_2, int param_3, undefined4 param_4, int param_5, int param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: creates fullscreen/window front/back buffers and clipper */

undefined4 __cdecl
create_directdraw_render_surfaces
          (undefined4 param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int *piStack_80;
  undefined4 auStack_6c [5];
  undefined4 uStack_58;
  uint uStack_14;
  undefined4 uStack_c;
  uint uStack_4;
  
  if (DAT_005fd0e8 != (int *)0x0) {
    piStack_80 = DAT_005fd0e8;
    (**(code **)(*DAT_005fd0e8 + 8))();
    DAT_005fd0e8 = (int *)0x0;
  }
  if (DAT_006080c4 != (int *)0x0) {
    piStack_80 = DAT_006080c4;
    (**(code **)(*DAT_006080c4 + 8))();
    DAT_006080c4 = (int *)0x0;
  }
  if (DAT_006080c0 != (int *)0x0) {
    piStack_80 = DAT_006080c0;
    (**(code **)(*DAT_006080c0 + 8))();
    DAT_006080c0 = (int *)0x0;
  }
  _DAT_005fcee0 = param_2;
  if (param_2 < 0x32) {
    _DAT_005fcee0 = 0x32;
  }
  if (param_3 < 0x32) {
    param_3 = 0x32;
  }
  iVar1 = 0x1b;
  _DAT_005fcee4 = param_3;
  if (param_5 == 0) {
    puVar2 = auStack_6c;
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    piStack_80 = (int *)0x0;
    auStack_6c[0] = 0x6c;
    auStack_6c[1] = 1;
    uStack_4 = 0x200;
    DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x18))(DAT_006080b8,auStack_6c,&DAT_006080c0);
    if (DAT_005fdc0c == 0) {
      uStack_14 = (-(uint)(param_2 != 0) & 0x3800) + 0x2840;
      if (DAT_00608440 != 0) {
        uStack_14 = uStack_14 | 0x800;
      }
      DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x18))
                               (DAT_006080b8,&stack0xffffff84,&DAT_006080c4,0);
      if (DAT_005fdc0c == 0) {
        puVar2 = (undefined4 *)&stack0xffffff84;
        for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar2 = 0;
          puVar2 = puVar2 + 1;
        }
        DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x58))(DAT_006080c4,&stack0xffffff84);
        if (DAT_005fdc0c == 0) {
          DAT_006080d0 = uStack_14 >> 0xe & 1;
          DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x10))(DAT_006080b8,0,&DAT_005fd0e8,0);
          if (DAT_005fdc0c == 0) {
            DAT_005fdc0c = (**(code **)(*DAT_005fd0e8 + 0x20))(DAT_005fd0e8,0,uStack_c);
            if (DAT_005fdc0c == 0) {
              DAT_005fdc0c = (**(code **)(*DAT_006080c0 + 0x70))(DAT_006080c0,DAT_005fd0e8);
              if (DAT_005fdc0c == 0) {
                clear_directdraw_front_back_buffers();
                return 1;
              }
              directdraw_error_to_string(DAT_005fdc0c);
              pcVar3 = s_Attaching_clipper_to_front_buffe_004f0d84;
            }
            else {
              directdraw_error_to_string(DAT_005fdc0c);
              pcVar3 = s_Attaching_clipper_to_window_fail_004f0db4;
            }
          }
          else {
            directdraw_error_to_string(DAT_005fdc0c);
            pcVar3 = s_CreateClipper_failed___s_004f0ddc;
          }
        }
        else {
          directdraw_error_to_string(DAT_005fdc0c);
          pcVar3 = s_Failed_to_get_surface_descriptio_004f0df8;
        }
      }
      else {
        if ((DAT_005fdc0c == -0x7ff8fff2) || (DAT_005fdc0c == -0x7789fe84)) goto LAB_00432f00;
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar3 = s_CreateSurface_for_window_back_bu_004f0f14;
      }
    }
    else {
      if ((DAT_005fdc0c == -0x7ff8fff2) || (DAT_005fdc0c == -0x7789fe84)) {
LAB_00432f00:
        set_directdraw_error_message(s_There_was_not_enough_video_memor_004f0e30);
        goto LAB_00432ff4;
      }
      directdraw_error_to_string(DAT_005fdc0c);
      pcVar3 = s_CreateSurface_for_window_front_b_004f0f44;
    }
  }
  else {
    puVar2 = auStack_6c;
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
    auStack_6c[0] = 0x6c;
    auStack_6c[1] = 0x21;
    uStack_4 = 0x2218;
    uStack_58 = 1;
    if (param_6 != 0) {
      uStack_4 = 0x6218;
    }
    if (DAT_00608440 != 0) {
      uStack_4 = uStack_4 | 0x800;
    }
    piStack_80 = (int *)0x0;
    DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x18))(DAT_006080b8,auStack_6c,&DAT_006080c0);
    if (DAT_005fdc0c == 0) {
      piStack_80 = (int *)0x4;
      DAT_005fdc0c = (**(code **)(*DAT_006080c0 + 0x30))(DAT_006080c0,&piStack_80,&DAT_006080c4);
      if (DAT_005fdc0c == 0) {
        puVar2 = (undefined4 *)&stack0xffffff84;
        for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar2 = 0;
          puVar2 = puVar2 + 1;
        }
        DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x58))(DAT_006080c4,&stack0xffffff84);
        if (DAT_005fdc0c == 0) {
          DAT_006080d0 = uStack_14 >> 0xe & 1;
          clear_directdraw_front_back_buffers();
          return 1;
        }
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar3 = s_Failed_to_get_surface_descriptio_004f0f78;
      }
      else {
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar3 = s_GetAttachedSurface_failed_to_get_004f0fb0;
      }
    }
    else {
      if ((DAT_005fdc0c == -0x7ff8fff2) || (DAT_005fdc0c == -0x7789fe84)) {
        set_directdraw_error_message(s_There_was_not_enough_video_memor_004f0fe4);
        goto LAB_00432ff4;
      }
      directdraw_error_to_string(DAT_005fdc0c);
      pcVar3 = s_CreateSurface_for_fullscreen_fli_004f108c;
    }
  }
  set_directdraw_error_message(pcVar3);
LAB_00432ff4:
  if (DAT_006080c0 != (int *)0x0) {
    (**(code **)(*DAT_006080c0 + 8))(DAT_006080c0);
    DAT_006080c0 = (int *)0x0;
  }
  if (DAT_006080c4 != (int *)0x0) {
    (**(code **)(*DAT_006080c4 + 8))(DAT_006080c4);
    DAT_006080c4 = (int *)0x0;
  }
  if (DAT_005fd0e8 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e8 + 8))(DAT_005fd0e8);
    DAT_005fd0e8 = (int *)0x0;
  }
  return 0;
}


