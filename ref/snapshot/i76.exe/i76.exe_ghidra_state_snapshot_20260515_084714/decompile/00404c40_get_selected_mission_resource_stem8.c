/*
 * Program: i76.exe
 * Function: get_selected_mission_resource_stem8
 * Entry: 00404c40
 * Signature: undefined8 __stdcall get_selected_mission_resource_stem8(void)
 */


/* [cgpt i76.exe mission/runtime rename v14; confidence=high] Splits
   g_selected_mission_resource_path and returns/copies the first 8 bytes of the filename stem. */

undefined8 get_selected_mission_resource_stem8(void)

{
  undefined4 local_1c;
  undefined4 local_18;
  char local_14 [20];
  
  local_1c = 0;
  local_18 = 0;
  _splitpath((char *)&g_selected_mission_resource_path,(char *)0x0,(char *)0x0,local_14,(char *)0x0)
  ;
  strncpy((char *)&local_1c,local_14,8);
  return CONCAT44(local_18,local_1c);
}


