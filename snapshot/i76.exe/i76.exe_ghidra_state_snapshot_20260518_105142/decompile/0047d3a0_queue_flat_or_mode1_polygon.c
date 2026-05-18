/*
 * Program: i76.exe
 * Function: queue_flat_or_mode1_polygon
 * Entry: 0047d3a0
 * Signature: undefined __cdecl queue_flat_or_mode1_polygon(int param_1, float * param_2, int param_3, undefined4 param_4)
 */


/* [cgpt i76.exe geo raster span family renames v38; confidence=medium-high] Queues flat/mode1
   polygon command with simpler span callback and no texture gradients. */

void __cdecl queue_flat_or_mode1_polygon(int param_1,float *param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 local_18 [3];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbb6b;
  local_c = ExceptionList;
  if (0 < param_3) {
    DAT_004f9d80 = (void *)((int)DAT_004f9d80 - 0x60);
    ExceptionList = &local_c;
    if (DAT_004f9d80 < DAT_004f9d7c) {
      ExceptionList = &local_c;
      ensure_raster_scratch_arena();
      DAT_004f9d80 = (void *)((int)DAT_004f9d80 - 0x60);
    }
    local_4 = 0;
    if (DAT_004f9d80 == (void *)0x0) {
      uVar1 = 0;
    }
    else {
      uVar1 = initialize_raster_command_record
                        (DAT_004f9d80,param_4,1,raster_emit_span_callback_mode1_flat);
    }
    local_4 = 0xffffffff;
    build_projected_polygon_scanline_spans(param_1,uVar1,param_2,param_3,local_18);
  }
  ExceptionList = local_c;
  return;
}


