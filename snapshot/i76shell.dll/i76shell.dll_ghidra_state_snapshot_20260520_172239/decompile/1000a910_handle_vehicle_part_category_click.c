/*
 * Program: i76shell.dll
 * Function: handle_vehicle_part_category_click
 * Entry: 1000a910
 * Signature: undefined __cdecl handle_vehicle_part_category_click(int param_1, int param_2, int param_3)
 */


void __cdecl handle_vehicle_part_category_click(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xc) + -0xc < param_2) {
    iVar1 = (param_3 - *(int *)(param_1 + 0x10)) / DAT_10051cd0;
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        open_vehicle_part_selection_list_dialog
                  (g_shell_ui_image_record_ptr_100f4f90,1,DAT_100d1dc0,(int *)&DAT_10044090,
                   0x100440a0,&LAB_100092d0);
        return;
      }
      if (iVar1 != 2) {
        open_vehicle_part_inventory_choice_dialog(iVar1);
        return;
      }
      open_vehicle_part_selection_list_dialog
                (g_shell_ui_image_record_ptr_100f4f90,2,DAT_100d1dbc,(int *)&DAT_10044070,0x10044080
                 ,&LAB_100092d0);
      return;
    }
    open_vehicle_part_selection_list_dialog
              (g_shell_ui_image_record_ptr_100f4f90,0,DAT_100d1dac,(int *)&DAT_10044010,0x10044020,
               &LAB_100092d0);
  }
  return;
}


