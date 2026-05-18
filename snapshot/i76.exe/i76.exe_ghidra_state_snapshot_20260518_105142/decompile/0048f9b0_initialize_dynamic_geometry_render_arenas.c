/*
 * Program: i76.exe
 * Function: initialize_dynamic_geometry_render_arenas
 * Entry: 0048f9b0
 * Signature: undefined4 __stdcall initialize_dynamic_geometry_render_arenas(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Allocates render scratch arenas and initializes dynamic geometry span/record
   arrays. */

undefined4 initialize_dynamic_geometry_render_arenas(void)

{
  int iVar1;
  
  DAT_00654398 = virtual_alloc_reserved_commit_region(370000,0x40000);
  g_runtime_terrain_polygon_work_record_active = DAT_00654398;
  g_runtime_terrain_polygon_work_record_cursor = DAT_00654398;
  _DAT_00654390 = virtual_alloc_reserved_commit_region(0x1f400,0x40000);
  g_runtime_terrain_scan_bucket_span_cursor = _DAT_00654390;
  DAT_006543bc = _DAT_00654390;
  DAT_00654384 = virtual_alloc_reserved_commit_region(0xc000,0x40000);
  DAT_006543b0 = DAT_00654384;
  g_runtime_terrain_scan_bucket_table = virtual_alloc_reserved_commit_region(0xc000,0x40000);
  DAT_006543a8 = g_runtime_terrain_scan_bucket_table;
  DAT_006543a0 = xalloc_global_heap(0xb40);
  DAT_006543b4 = DAT_006543a0;
  if (DAT_006543a0 == 0) {
    return 0;
  }
  DAT_0065438c = DAT_006543a0 + 0xb40;
  iVar1 = 0x1000;
  do {
    DAT_00654384[2] = 0;
    DAT_00654384[1] = 0;
    *DAT_00654384 = 0;
    DAT_006543a8[2] = 0;
    *DAT_006543a8 = 0;
    DAT_00654384 = DAT_00654384 + 3;
    DAT_006543a8 = DAT_006543a8 + 3;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_0059c540 = 0;
  return 1;
}


