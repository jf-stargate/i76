/*
 * Program: i76.exe
 * Function: init_display_mode_full_setup_candidate
 * Entry: 004305e0
 * Signature: undefined4 __cdecl init_display_mode_full_setup_candidate(byte param_1, HWND param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
init_display_mode_full_setup_candidate
          (byte param_1,HWND param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int local_8;
  int local_4;
  
  initialize_display_runtime_globals();
  if ((param_1 & 1) != 0) {
    DAT_00608440 = 1;
    DAT_00608444 = 1;
  }
  if ((param_1 & 2) != 0) {
    DAT_00608444 = 1;
  }
  iVar2 = init_directdraw(-(DAT_00608444 != 0) & 4);
  if ((((iVar2 == 0) ||
       (iVar2 = enumerate_or_choose_directdraw_display_modes_candidate(), iVar2 == 0)) ||
      (iVar2 = create_primary_and_back_surfaces_candidate((uint)(DAT_00608444 == 0)), iVar2 == 0))
     || ((iVar2 = create_direct3d_interface(), iVar2 == 0 ||
         (iVar2 = enumerate_direct3d_drivers(), iVar2 == 0)))) goto LAB_004307d1;
  DAT_005fdc00 = param_5;
  DAT_005fcee8 = param_3;
  _DAT_005fde20 = param_4;
  _DAT_005fdc04 = param_6;
  DAT_005fde40 = param_2;
  local_8 = -0x19;
  local_4 = DAT_006080dc;
  iVar2 = select_compatible_d3d_device_driver(&local_8,&local_4);
  if (iVar2 == 0) goto LAB_004307d1;
  update_window_client_screen_metrics(param_2);
  iVar5 = DAT_00608428;
  iVar2 = DAT_00608424;
  if (local_4 == -0x18) {
    iVar3 = set_directdraw_cooperative_level_candidate(param_2,0);
    if ((iVar3 == 0) ||
       (iVar3 = create_directdraw_render_surfaces
                          (param_2,iVar2,iVar5,0xffffff9c,0,(&DAT_005fdf84)[local_8 * 0x4f]),
       iVar3 == 0)) goto LAB_004307d1;
    uVar1 = (&DAT_005fdf44)[local_8 * 0x4f];
    uVar4 = map_display_bit_depth_to_ddraw_caps_mask((&DAT_006080e8)[DAT_006080dc * 4]);
    if ((uVar1 & uVar4) == 0) {
      iVar3 = choose_display_mode_matching_caps(&DAT_006080dc,uVar1);
      goto joined_r0x00430942;
    }
  }
  else {
    iVar2 = (&DAT_006080e0)[local_4 * 4];
    iVar5 = (&DAT_006080e4)[local_4 * 4];
    _DAT_005fdc18 = DAT_00608424;
    _DAT_005fdc1c = DAT_00608428;
    DAT_00608424 = iVar2;
    DAT_00608428 = iVar5;
    iVar3 = set_directdraw_cooperative_level_candidate(param_2,1);
    if ((iVar3 == 0) ||
       (iVar3 = set_directdraw_display_mode_candidate(iVar2,iVar5,(&DAT_006080e8)[local_4 * 4]),
       iVar3 == 0)) goto LAB_004307d1;
    DAT_006080dc = local_4;
    iVar3 = create_directdraw_render_surfaces
                      (param_2,iVar2,iVar5,(&DAT_006080e8)[local_4 * 4],1,
                       (&DAT_005fdf84)[local_8 * 0x4f]);
joined_r0x00430942:
    if (iVar3 == 0) goto LAB_004307d1;
  }
  iVar3 = create_and_attach_directdraw_palette();
  if ((((iVar3 != 0) && (iVar3 = create_selected_direct3d_device(local_8), iVar3 != 0)) &&
      (iVar3 = update_supported_display_depth_flags_for_driver(local_8), iVar3 != 0)) &&
     ((iVar2 = invoke_optional_raster_driver_callback(iVar2,iVar5), iVar2 != 0 &&
      (iVar2 = d3d_error_to_string(), iVar2 != 0)))) {
    reset_display_clip_rects_to_current_mode();
    _DAT_005fceec = 1;
    DAT_0060844c = 1;
    return 1;
  }
LAB_004307d1:
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
  if (DAT_00608410 != 0) {
    restore_directdraw_display_mode();
    set_directdraw_cooperative_level_candidate(param_2,0);
  }
  if (DAT_005fde44 != (int *)0x0) {
    (**(code **)(*DAT_005fde44 + 8))(DAT_005fde44);
    DAT_005fde44 = (int *)0x0;
  }
  if (DAT_006080b8 != (int *)0x0) {
    (**(code **)(*DAT_006080b8 + 8))(DAT_006080b8);
    DAT_006080b8 = (int *)0x0;
  }
  return 0;
}


