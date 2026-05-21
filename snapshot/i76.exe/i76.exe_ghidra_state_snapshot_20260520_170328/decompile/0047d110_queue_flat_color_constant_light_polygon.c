/*
 * Program: i76.exe
 * Function: queue_flat_color_constant_light_polygon
 * Entry: 0047d110
 * Signature: undefined __cdecl queue_flat_color_constant_light_polygon(int param_1, float * param_2, int param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Queues flat-color polygon
   command with constant light/shade value; callback raster_emit_flat_shaded_constant_spans. */

void __cdecl
queue_flat_color_constant_light_polygon(int param_1,float *param_2,int param_3,undefined4 param_4)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_18 [3];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbb4b;
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
      uVar2 = 0;
    }
    else {
      uVar2 = initialize_raster_command_record
                        (DAT_004f9d80,param_4,0,raster_emit_flat_shaded_constant_spans);
    }
    local_4 = 0xffffffff;
    iVar3 = build_projected_polygon_scanline_spans(param_1,uVar2,param_2,param_3,local_18);
    if (iVar3 != 0) {
      fVar1 = (_DAT_004be778 - param_2[5]) * _DAT_004fa48c;
      *(undefined4 *)(uVar2 + 0x58) = 0;
      *(undefined4 *)(uVar2 + 0x5c) = 0;
      *(float *)(uVar2 + 0x18) = fVar1;
    }
  }
  ExceptionList = local_c;
  return;
}


