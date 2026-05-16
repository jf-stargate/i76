/*
 * Program: i76.exe
 * Function: init_display_mode_shell_or_windowed_candidate
 * Entry: 00431980
 * Signature: undefined4 __cdecl init_display_mode_shell_or_windowed_candidate(uint param_1, HWND param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl
init_display_mode_shell_or_windowed_candidate
          (uint param_1,HWND param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
          undefined4 param_6)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  initialize_display_runtime_globals();
  if ((param_1 & 1) != 0) {
    DAT_00608440 = 1;
    DAT_00608444 = 1;
  }
  if ((param_1 & 2) != 0) {
    DAT_00608444 = 1;
  }
  iVar3 = init_directdraw(-(DAT_00608444 != 0) & 4);
  if (((iVar3 == 0) ||
      (iVar3 = enumerate_or_choose_directdraw_display_modes_candidate(), iVar3 == 0)) ||
     (iVar4 = create_primary_and_back_surfaces_candidate((uint)(DAT_00608444 == 0)),
     iVar3 = DAT_006080dc, iVar4 == 0)) goto LAB_00431b89;
  DAT_005fdc00 = param_5;
  _DAT_005fdc04 = param_6;
  DAT_005fcee8 = param_3;
  _DAT_005fde20 = param_4;
  DAT_005fde40 = param_2;
  update_window_client_screen_metrics(param_2);
  iVar1 = DAT_00608428;
  iVar4 = DAT_00608424;
  if (iVar3 == -0x18) {
    iVar3 = set_directdraw_cooperative_level_candidate(param_2,0);
    if ((iVar3 == 0) ||
       (iVar3 = create_directdraw_render_surfaces(param_2,iVar4,iVar1,0xffffff9c,0,DAT_005fc0a8),
       uVar2 = DAT_005fc068, iVar3 == 0)) goto LAB_00431b89;
    uVar5 = map_display_bit_depth_to_ddraw_caps_mask((&DAT_006080e8)[DAT_006080dc * 4]);
    if ((uVar2 & uVar5) == 0) {
      iVar3 = choose_display_mode_matching_caps(&DAT_006080dc,uVar2);
      goto joined_r0x00431acc;
    }
  }
  else {
    iVar4 = (&DAT_006080e0)[iVar3 * 4];
    iVar1 = (&DAT_006080e4)[iVar3 * 4];
    _DAT_005fdc18 = DAT_00608424;
    _DAT_005fdc1c = DAT_00608428;
    DAT_00608424 = iVar4;
    DAT_00608428 = iVar1;
    iVar6 = set_directdraw_cooperative_level_candidate(param_2,1);
    if ((iVar6 == 0) ||
       (iVar6 = set_directdraw_display_mode_candidate(iVar4,iVar1,(&DAT_006080e8)[iVar3 * 4]),
       iVar6 == 0)) goto LAB_00431b89;
    DAT_006080dc = iVar3;
    if (param_1 == 0) {
      iVar3 = create_directdraw_render_surfaces(param_2,iVar4,iVar1,(&DAT_006080e8)[iVar3 * 4],1,1);
    }
    else {
      iVar3 = create_directdraw_render_surfaces(param_2,iVar4,iVar1,(&DAT_006080e8)[iVar3 * 4],1,0);
    }
joined_r0x00431acc:
    if (iVar3 == 0) goto LAB_00431b89;
  }
  iVar3 = create_and_attach_directdraw_palette();
  if (iVar3 != 0) {
    if (param_1 == 0) {
      initialize_directdraw_surface_descriptor_block(param_2);
    }
    _DAT_005fceec = 1;
    DAT_0060844c = 1;
    return 1;
  }
LAB_00431b89:
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


