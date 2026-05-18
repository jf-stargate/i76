/*
 * Program: i76.exe
 * Function: switch_display_mode_and_recreate_surfaces_candidate
 * Entry: 00430950
 * Signature: undefined4 __thiscall switch_display_mode_and_recreate_surfaces_candidate(void * this, int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall switch_display_mode_and_recreate_surfaces_candidate(void *this,int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  void *pvStack_4;
  
  DAT_0060844c = 0;
  iVar3 = select_compatible_d3d_device_driver(&DAT_005fde54,&param_1);
  pvStack_4 = this;
  if (iVar3 != 0) {
    iVar3 = release_directdraw_surfaces_candidate();
    if (iVar3 != 0) {
      if (DAT_00608410 != (void *)0x0) {
        iVar3 = clear_directdraw_front_back_buffers();
        if (iVar3 == 0) goto LAB_00430ae4;
      }
      if (DAT_005fde48 != (int *)0x0) {
        (**(code **)(*DAT_005fde48 + 8))(DAT_005fde48);
        DAT_005fde48 = (int *)0x0;
      }
      if (DAT_005fd0e0 != (int *)0x0) {
        (**(code **)(*DAT_005fd0e0 + 8))(DAT_005fd0e0);
        DAT_005fd0e0 = (int *)0x0;
      }
      if (DAT_005fd0e8 != (int *)0x0) {
        (**(code **)(*DAT_005fd0e8 + 8))(DAT_005fd0e8);
        DAT_005fd0e8 = (int *)0x0;
      }
      if (DAT_006080c4 != (int *)0x0) {
        (**(code **)(*DAT_006080c4 + 8))(DAT_006080c4);
        DAT_006080c4 = (int *)0x0;
      }
      if (DAT_006080c0 != (int *)0x0) {
        (**(code **)(*DAT_006080c0 + 8))(DAT_006080c0);
        DAT_006080c0 = (int *)0x0;
      }
      pvStack_4 = DAT_00608410;
      iVar3 = (&DAT_006080e0)[param_1 * 4];
      iVar1 = (&DAT_006080e4)[param_1 * 4];
      uVar2 = (&DAT_006080e8)[param_1 * 4];
      if (DAT_00608410 == (void *)0x0) {
        _DAT_005fdc18 = DAT_00608424;
        _DAT_005fdc1c = DAT_00608428;
      }
      DAT_00608424 = iVar3;
      DAT_00608428 = iVar1;
      iVar4 = set_directdraw_cooperative_level_candidate(DAT_005fde40,1);
      if (iVar4 != 0) {
        iVar4 = set_directdraw_display_mode_candidate(iVar3,iVar1,uVar2);
        if (iVar4 != 0) {
          DAT_006080dc = param_1;
          iVar4 = create_directdraw_render_surfaces
                            (DAT_005fde40,iVar3,iVar1,uVar2,1,(&DAT_005fdf84)[DAT_005fde54 * 0x4f]);
          if (iVar4 != 0) {
            iVar4 = create_and_attach_directdraw_palette();
            if (iVar4 != 0) {
              iVar4 = create_selected_direct3d_device(DAT_005fde54);
              if (iVar4 != 0) {
                iVar3 = invoke_optional_raster_driver_callback(iVar3,iVar1);
                if (iVar3 != 0) {
                  iVar3 = d3d_error_to_string();
                  if (iVar3 != 0) {
                    DAT_006080dc = param_1;
                    reset_display_clip_rects_to_current_mode();
                    DAT_0060844c = 1;
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_00430ae4:
  release_directdraw_surfaces_candidate();
  if (DAT_005fde48 != (int *)0x0) {
    (**(code **)(*DAT_005fde48 + 8))(DAT_005fde48);
    DAT_005fde48 = (int *)0x0;
  }
  if (DAT_005fd0e0 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e0 + 8))(DAT_005fd0e0);
    DAT_005fd0e0 = (int *)0x0;
  }
  if (DAT_005fd0e8 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e8 + 8))(DAT_005fd0e8);
    DAT_005fd0e8 = (int *)0x0;
  }
  if (DAT_006080c4 != (int *)0x0) {
    (**(code **)(*DAT_006080c4 + 8))(DAT_006080c4);
    DAT_006080c4 = (int *)0x0;
  }
  if (DAT_006080c0 != (int *)0x0) {
    (**(code **)(*DAT_006080c0 + 8))(DAT_006080c0);
    DAT_006080c0 = (int *)0x0;
  }
  if (pvStack_4 == (void *)0x0) {
    restore_directdraw_display_mode();
    set_directdraw_cooperative_level_candidate(DAT_005fde40,0);
  }
  return 0;
}


