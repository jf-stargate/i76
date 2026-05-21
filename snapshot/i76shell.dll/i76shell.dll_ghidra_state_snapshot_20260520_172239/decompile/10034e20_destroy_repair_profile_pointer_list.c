/*
 * Program: i76shell.dll
 * Function: destroy_repair_profile_pointer_list
 * Entry: 10034e20
 * Signature: undefined __stdcall destroy_repair_profile_pointer_list(void)
 */


void destroy_repair_profile_pointer_list(void)

{
  if (DAT_100f5308 != (LPVOID)0x0) {
    destroy_pointer_list_with_optional_item_destructor(DAT_100f5308,&LAB_10034de0);
    DAT_100f5308 = (LPVOID)0x0;
  }
  return;
}


