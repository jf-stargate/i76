/*
 * Program: i76.exe
 * Function: registered_resource_key_exists
 * Entry: 004b34f0
 * Signature: bool __cdecl registered_resource_key_exists(undefined4 * param_1)
 */


/* [cgpt i76.exe resource/archive rename v11; confidence=high] Binary-searches the registered
   0x30-byte resource-key table. */

bool __cdecl registered_resource_key_exists(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_30 = *param_1;
  local_2c = param_1[1];
  local_28 = param_1[2];
  local_24 = param_1[3];
  pvVar1 = bsearch(&local_30,g_registered_resource_records,g_registered_resource_record_count,0x30,
                   (_PtFuncCompare *)&compare_resource_record_16byte_key);
  return pvVar1 != (void *)0x0;
}


