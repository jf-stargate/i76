/*
 * Program: i76.exe
 * Function: muzzle_flash_log_tag
 * Entry: 0049f210
 * Signature: undefined4 __cdecl muzzle_flash_log_tag(undefined4 param_1, undefined4 param_2, int param_3, undefined4 param_4, undefined4 param_5)
 */


/* cgpt whole-binary semantic rename v1: string evidence mzlfls */

undefined4 __cdecl
muzzle_flash_log_tag
          (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  char *_Source;
  byte *_Dest;
  
  if (*(int *)(param_3 + 100) == 0) {
    return 1;
  }
  puVar1 = HeapAlloc(g_weapon_muzzle_flash_runtime_heap,0,0x30);
  puVar1[0xb] = g_weapon_muzzle_flash_runtime_list;
  g_weapon_muzzle_flash_runtime_list = puVar1;
  *puVar1 = param_1;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  increment_refcount_recursive_for_object_tree(param_3,s_mzlfls_004fe6e8);
  puVar1[3] = param_4;
  puVar1[6] = param_5;
  puVar1[4] = 0;
  puVar1[5] = 0;
  world_object_bounds_context_helper_00458790(*(int *)(param_3 + 100),1);
  _Source = (char *)find_object_texture_slot_name(*(int *)(param_3 + 100),0);
  if ((_Source != (char *)0x0) && (*_Source != '\0')) {
    _Dest = (byte *)(puVar1 + 7);
    strncpy((char *)_Dest,_Source,0x10);
    bind_texture_resource_to_object_slot(*(uint *)(param_3 + 100),_Dest,_Dest);
    return 1;
  }
  puVar1[7] = 0;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  return 1;
}


