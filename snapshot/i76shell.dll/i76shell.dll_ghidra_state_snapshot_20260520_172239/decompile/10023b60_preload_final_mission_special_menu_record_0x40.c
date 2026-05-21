/*
 * Program: i76shell.dll
 * Function: preload_final_mission_special_menu_record_0x40
 * Entry: 10023b60
 * Signature: undefined __cdecl preload_final_mission_special_menu_record_0x40(void * param_1)
 */


void __cdecl preload_final_mission_special_menu_record_0x40(void *param_1)

{
  long local_4;
  
  DAT_100d3964 = (int *)0x0;
  DAT_100d21a8 = 0;
  if (DAT_100d3968 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x40,&DAT_100d3968,&local_4);
  }
  load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,(LPVOID)0x1b);
  DAT_100d3964 = create_pointer_list_default_16();
  insert_pointer_list_item_sorted_or_append((int)DAT_100d3964,0x1004b000,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100d3964,0x1004b014,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100d3964,0x1004b028,(undefined *)0x0);
  insert_pointer_list_item_sorted_or_append((int)DAT_100d3964,0x1004b03c,(undefined *)0x0);
  FUN_1001eca0(&LAB_10023c20);
  DAT_100d3960 = 0xffffffff;
  return;
}


