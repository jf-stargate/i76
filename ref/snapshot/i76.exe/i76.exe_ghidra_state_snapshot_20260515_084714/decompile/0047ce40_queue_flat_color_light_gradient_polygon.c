/*
 * Program: i76.exe
 * Function: queue_flat_color_light_gradient_polygon
 * Entry: 0047ce40
 * Signature: undefined __cdecl queue_flat_color_light_gradient_polygon(int param_1, float * param_2, int param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=high] Queues flat-color polygon
   command with interpolated light/shade gradient; callback raster_emit_flat_shaded_gradient_spans.
    */

void __cdecl
queue_flat_color_light_gradient_polygon(int param_1,float *param_2,int param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int local_3c;
  int local_38;
  int local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  void *local_c;
  undefined *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &DAT_004bbb2b;
  local_c = ExceptionList;
  uVar5 = 0;
  if (0 < param_3) {
    DAT_004f9d80 = (void *)((int)DAT_004f9d80 - 0x60);
    ExceptionList = &local_c;
    if (DAT_004f9d80 < DAT_004f9d7c) {
      ExceptionList = &local_c;
      ensure_raster_scratch_arena();
      DAT_004f9d80 = (void *)((int)DAT_004f9d80 - 0x60);
    }
    local_4 = 0;
    if (DAT_004f9d80 != (void *)0x0) {
      uVar5 = initialize_raster_command_record
                        (DAT_004f9d80,param_4,0,raster_emit_flat_shaded_gradient_spans);
    }
    local_4 = 0xffffffff;
    iVar4 = build_projected_polygon_scanline_spans(param_1,uVar5,param_2,param_3,&local_3c);
    if (iVar4 != 0) {
      compute_projected_triangle_barycentric_matrix(&local_3c,&local_30);
      fVar3 = (_DAT_004be778 - *(float *)(local_38 + 0x14)) * _DAT_004fa48c;
      fVar1 = (_DAT_004be778 - *(float *)(local_34 + 0x14)) * _DAT_004fa48c;
      fVar2 = (_DAT_004be778 - *(float *)(local_3c + 0x14)) * _DAT_004fa48c;
      *(float *)(uVar5 + 0x18) = fVar2 * local_30 + fVar3 * local_24 + fVar1 * local_18;
      *(float *)(uVar5 + 0x58) = fVar2 * local_2c + fVar3 * local_20 + fVar1 * local_14;
      *(float *)(uVar5 + 0x5c) = fVar2 * local_28 + fVar3 * local_1c + fVar1 * local_10;
    }
  }
  ExceptionList = local_c;
  return;
}


