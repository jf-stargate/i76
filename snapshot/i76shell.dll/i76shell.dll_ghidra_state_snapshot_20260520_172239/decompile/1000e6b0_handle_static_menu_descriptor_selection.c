/*
 * Program: i76shell.dll
 * Function: handle_static_menu_descriptor_selection
 * Entry: 1000e6b0
 * Signature: undefined __cdecl handle_static_menu_descriptor_selection(int param_1)
 */


void __cdecl handle_static_menu_descriptor_selection(int param_1)

{
  void *pvVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  if (param_1 != 0) {
    iVar2 = FUN_1001fb10(DAT_100cc514);
    if (iVar2 == 1) {
      if (DAT_100d2168 == 0xc00e) {
        iVar2 = *(int *)(DAT_100cc514 + 0x30);
        iVar4 = *(int *)(DAT_100cc514 + 0x2c);
        piVar3 = (int *)&DAT_10044990;
      }
      else {
        iVar2 = *(int *)(DAT_100cc514 + 0x30);
        iVar4 = *(int *)(DAT_100cc514 + 0x2c);
        if (*(int *)(DAT_100c5ad8 + 0x20) == 2) {
          piVar3 = (int *)&DAT_10044780;
        }
        else {
          piVar3 = (int *)&DAT_10044b48;
        }
      }
      piVar3 = hit_test_static_ui_descriptor_table(piVar3,iVar4,iVar2);
      if ((piVar3 != (int *)0x0) && ((code *)piVar3[8] != (code *)0x0)) {
        (*(code *)piVar3[8])(piVar3);
        switch(DAT_10055d90) {
        case 1:
          DAT_100d21ac = 1;
          DAT_100d2194 = 4;
          break;
        case 2:
          DAT_100d21ac = 1;
          DAT_100d2194 = 5;
          break;
        case 3:
          DAT_100d21ac = 1;
          DAT_100d2194 = 6;
          break;
        case 4:
          DAT_100d21ac = 1;
          DAT_100d2194 = 7;
          break;
        case 5:
          DAT_100d21ac = 1;
          DAT_100d2194 = 0xb;
          break;
        case 6:
          DAT_100d21ac = 1;
          DAT_100d2194 = 1;
          break;
        case 7:
          DAT_100d21ac = 1;
          DAT_100d2194 = 2;
          break;
        case 9:
          *(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0xffffffff;
          destroy_vehicle_config_ui_lists();
          destroy_repair_profile_pointer_list();
          reset_shell_session_resource_globals();
          initialize_single_player_shell_session_defaults();
          DAT_100d21ac = 1;
          DAT_100d2194 = 10;
          break;
        case 10:
          DAT_100d21ac = 1;
          DAT_100d2194 = 9;
          break;
        case 0xb:
          DAT_100d21ac = 1;
          DAT_100d2194 = 3;
        }
      }
    }
    if (((param_1 != 0) && (DAT_10055d90 != 8)) &&
       (iVar2 = poll_keyboard_control_result(DAT_100cc50c), iVar2 != 3)) {
      return;
    }
  }
  FUN_1001ed40(0x1000e6b0);
  DAT_10051c48 = 0;
  if (DAT_100d2168 == 0xc00e) {
    piVar3 = (int *)&DAT_10044990;
  }
  else if ((DAT_100d2168 == 0xc017) || (DAT_100d2168 == 0xc00f)) {
    piVar3 = (int *)&DAT_10044780;
  }
  else {
    piVar3 = (int *)&DAT_10044b48;
  }
  destroy_static_ui_descriptor_widgets(piVar3);
  pvVar1 = DAT_10055d98;
  if (DAT_10055d98 != (void *)0x0) {
    FUN_10036620();
    operator_delete(pvVar1);
  }
  set_shell_surface_palette_from_rgb6(DAT_100cc518,(undefined4 *)&DAT_10055db0,1);
  if ((DAT_100d21ac == 0) &&
     (*(undefined4 *)((int)DAT_100cc518 + 0x3d0) = 0xffffffff, DAT_100d21a8 != (code *)0x0)) {
    flush_or_repaint_shell_surface_context((int)DAT_100cc518);
    (*DAT_100d21a8)();
  }
  return;
}


