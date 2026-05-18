/*
 * Program: i76.exe
 * Function: terrain_map_log_tag
 * Entry: 004926c0
 * Signature: undefined __stdcall terrain_map_log_tag(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence termap */

void terrain_map_log_tag(void)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  
  pvVar2 = DAT_00644200;
  while (pvVar2 != (LPVOID)0x0) {
    pvVar1 = *(LPVOID *)((int)pvVar2 + 0x60);
    unlink_and_release_world_object_node_refcounted(pvVar2,s_termap_004fae0c);
    pvVar2 = pvVar1;
  }
  DAT_00644200 = (LPVOID)0x0;
  return;
}


