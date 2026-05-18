/*
 * Program: i76.exe
 * Function: queue_affine_textured_polygon_uv_variant_b
 * Entry: 0047f620
 * Signature: undefined __cdecl queue_affine_textured_polygon_uv_variant_b(int param_1, float * param_2, int param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium] Queues affine textured
   polygon variant with alternate UV coefficient ordering/callback. */

void __cdecl
queue_affine_textured_polygon_uv_variant_b
          (int param_1,float *param_2,int param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
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
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbbeb;
  local_c = ExceptionList;
  puVar5 = (undefined4 *)0x0;
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
      puVar5 = (undefined4 *)
               initialize_raster_command_record
                         (DAT_004f9d80,param_4,0,raster_emit_textured_spans_variant_b);
    }
    local_4 = 0xffffffff;
    iVar4 = build_projected_polygon_scanline_spans(param_1,(uint)puVar5,param_2,param_3,&local_3c);
    if (iVar4 != 0) {
      compute_projected_triangle_barycentric_matrix(&local_3c,&local_30);
      fVar2 = (float)*(int *)*puVar5 * _DAT_004be77c;
      fVar1 = *(float *)(local_38 + 0xc) * fVar2;
      fVar3 = *(float *)(local_34 + 0xc) * fVar2;
      fVar2 = *(float *)(local_3c + 0xc) * fVar2;
      puVar5[3] = fVar2 * local_30 + fVar1 * local_24 + fVar3 * local_18;
      puVar5[0x10] = fVar2 * local_2c + fVar1 * local_20 + fVar3 * local_14;
      puVar5[0x11] = fVar2 * local_28 + fVar1 * local_1c + fVar3 * local_10;
      fVar3 = (float)((((int *)*puVar5)[1] << 3) >> 3) * _DAT_004be77c;
      fVar1 = *(float *)(local_3c + 0x10) * fVar3;
      fVar2 = *(float *)(local_34 + 0x10) * fVar3;
      fVar3 = *(float *)(local_38 + 0x10) * fVar3;
      puVar5[4] = fVar3 * local_24 + fVar2 * local_18 + fVar1 * local_30;
      puVar5[0x12] = fVar3 * local_20 + fVar2 * local_14 + fVar1 * local_2c;
      puVar5[0x13] = fVar3 * local_1c + fVar2 * local_10 + fVar1 * local_28;
    }
  }
  ExceptionList = local_c;
  return;
}


