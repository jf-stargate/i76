/*
 * Program: i76shell.dll
 * Function: open_equipped_vehicle_part_replacement_dialog
 * Entry: 1000b020
 * Signature: undefined __cdecl open_equipped_vehicle_part_replacement_dialog(int param_1, int param_2, int param_3)
 */


void __cdecl open_equipped_vehicle_part_replacement_dialog(int param_1,int param_2,int param_3)

{
  if (*(int *)(param_1 + 0xc) + -0xc < param_2) {
    open_vehicle_part_selection_list_dialog
              (g_shell_ui_image_record_ptr_100f4f90,5,DAT_100d1db0,(int *)&DAT_10044030,0x10044040,
               &LAB_1000ae10);
    *(int *)(DAT_100533b8 + 0x10) = (param_3 - *(int *)(param_1 + 0x10)) / DAT_10051cd0;
  }
  return;
}


