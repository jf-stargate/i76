/*
 * Program: i76.exe
 * Function: select_compatible_d3d_device_driver
 * Entry: 004339e0
 * Signature: undefined4 __cdecl select_compatible_d3d_device_driver(int * param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: selected D3D driver compatibility errors
    */

undefined4 __cdecl select_compatible_d3d_device_driver(int *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  int local_8;
  int local_4;
  
  local_4 = *param_2;
  local_8 = *param_1;
  if ((local_4 == -0x18) && (DAT_006080bc == 0)) {
    set_directdraw_error_message(s_Cannot_render_to_a_window_when_t_004f14bc);
    return 0;
  }
  if (local_8 == -0x19) {
    if (local_4 == -0x18) {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask(DAT_0060841c);
      iVar2 = select_best_display_driver_for_caps_mask(&local_8,uVar1);
      if (iVar2 == 0) {
        return 0;
      }
      if (local_8 == -100) {
        set_directdraw_error_message(s_Cannot_find_a_D3D_device_driver_w_004f1464);
        return 0;
      }
      goto LAB_00433c7d;
    }
    if (local_4 != -0x19) {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask((&DAT_006080e8)[local_4 * 4]);
      iVar2 = select_best_display_driver_for_caps_mask(&local_8,uVar1);
      if (iVar2 == 0) {
        return 0;
      }
      if (local_8 == -100) {
        set_directdraw_error_message(s_Cannot_find_a_D3D_device_driver_w_004f1390);
        return 0;
      }
      goto LAB_00433c7d;
    }
    if (DAT_006080bc == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask(DAT_0060841c);
    }
    iVar2 = 0;
    if (0 < DAT_006080d8) {
      puVar4 = &DAT_006080e8;
      do {
        uVar3 = map_display_bit_depth_to_ddraw_caps_mask(*puVar4);
        uVar1 = uVar1 | uVar3;
        iVar2 = iVar2 + 1;
        puVar4 = puVar4 + 4;
      } while (iVar2 < DAT_006080d8);
    }
    iVar2 = select_best_display_driver_for_caps_mask(&local_8,uVar1);
    if (iVar2 == 0) {
      return 0;
    }
    if (local_8 == -100) {
      set_directdraw_error_message(s_Cannot_find_a_D3D_device_driver_w_004f13ec);
      return 0;
    }
  }
  if (local_4 == -0x19) {
    if ((DAT_006080bc == 0) ||
       (uVar1 = map_display_bit_depth_to_ddraw_caps_mask(DAT_0060841c),
       ((&DAT_005fdf44)[local_8 * 0x4f] & uVar1) == 0)) {
      iVar2 = choose_display_mode_matching_caps(&local_4,(&DAT_005fdf44)[local_8 * 0x4f]);
      if (iVar2 == 0) {
        return 0;
      }
      if (local_4 == -100) {
        set_directdraw_error_message(s_The_selected_D3D_device_driver_i_004f131c);
        return 0;
      }
    }
    else {
      local_4 = -0x18;
    }
  }
  else {
    if (local_4 == -0x18) {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask(DAT_0060841c);
      if (((&DAT_005fdf44)[local_8 * 0x4f] & uVar1) != 0) goto LAB_00433c7d;
      local_4 = -0x19;
      iVar2 = select_compatible_d3d_device_driver(&local_8,&local_4);
    }
    else {
      uVar1 = map_display_bit_depth_to_ddraw_caps_mask((&DAT_006080e8)[local_4 * 4]);
      if (((&DAT_005fdf44)[local_8 * 0x4f] & uVar1) != 0) goto LAB_00433c7d;
      local_4 = -0x19;
      iVar2 = select_compatible_d3d_device_driver(&local_8,&local_4);
    }
    if ((iVar2 == 0) || (local_8 == -100)) {
      return 0;
    }
  }
LAB_00433c7d:
  *param_1 = local_8;
  *param_2 = local_4;
  return 1;
}


