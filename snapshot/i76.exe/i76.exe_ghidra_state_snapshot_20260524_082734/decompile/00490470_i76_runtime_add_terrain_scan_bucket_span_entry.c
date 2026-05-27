/*
 * Program: i76.exe
 * Function: i76_runtime_add_terrain_scan_bucket_span_entry
 * Entry: 00490470
 * Signature: undefined __cdecl i76_runtime_add_terrain_scan_bucket_span_entry(undefined4 param_1, float param_2, float param_3, undefined4 param_4, undefined4 param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490470. Remove
   duplicated terrain wording.
   
   [cgpt_i76exe_terrain_runtime_structs_v10]
   proposed=i76_runtime_add_terrain_primitive_to_scan_buckets :: Adds terrain primitive span/range
   entry into scan bucket list.
   
   [cgpt_i76exe_terrain_runtime_structs_v11] proposed=i76_runtime_add_terrain_scan_bucket_span_entry
   :: Adds one terrain span-bucket entry to DAT_00654388/DAT_006543b8 structures.
   
   [cgpt_i76exe_terrain_runtime_structs_v12] proposed=i76_runtime_add_terrain_scan_bucket_span_entry
   :: Adds 0x10-byte span entries into all covered scan/depth buckets.
   [cgpt-i76-v36 medium] Adds terrain span entry to scan bucket. */

void __cdecl
i76_runtime_add_terrain_scan_bucket_span_entry
          (undefined4 param_1,float param_2,float param_3,undefined4 param_4,undefined4 param_5)

{
  float fVar1;
  int local_10;
  int local_8;
  
  fVar1 = param_2 - g_runtime_terrain_render_min_or_near_bound;
  if (param_3 < fVar1) {
    return;
  }
  local_10 = SUB84((double)((param_3 - fVar1) + (float)_DAT_004faf18),0);
  if (0 < local_10) {
    local_8 = SUB84((double)(fVar1 + (float)_DAT_004faf18),0);
    local_8 = local_8 * 0xc;
    do {
      DAT_006543a8 = (int *)(g_runtime_terrain_scan_bucket_table + local_8);
      if (*DAT_006543a8 == 0) {
        *DAT_006543a8 = (int)g_runtime_terrain_scan_bucket_span_cursor;
        g_runtime_terrain_scan_bucket_span_cursor[1] = param_5;
        *g_runtime_terrain_scan_bucket_span_cursor = param_4;
        g_runtime_terrain_scan_bucket_span_cursor[3] = 0;
      }
      else {
        *(undefined4 **)(DAT_006543a8[1] + 0xc) = g_runtime_terrain_scan_bucket_span_cursor;
        g_runtime_terrain_scan_bucket_span_cursor[1] = param_5;
        *g_runtime_terrain_scan_bucket_span_cursor = param_4;
        g_runtime_terrain_scan_bucket_span_cursor[3] = 0;
        DAT_006543a8[1] = (int)g_runtime_terrain_scan_bucket_span_cursor;
      }
      local_8 = local_8 + 0xc;
      g_runtime_terrain_scan_bucket_span_cursor[2] = param_1;
      DAT_006543a8[1] = (int)g_runtime_terrain_scan_bucket_span_cursor;
      g_runtime_terrain_scan_bucket_span_cursor = g_runtime_terrain_scan_bucket_span_cursor + 4;
      local_10 = local_10 + -1;
      DAT_006543a8[2] = DAT_006543a8[2] + 1;
    } while (local_10 != 0);
  }
  DAT_0059c498 = 1;
  return;
}


