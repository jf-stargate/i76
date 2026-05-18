/*
 * Program: i76.exe
 * Function: queue_affine_textured_polygon_variant_00489860
 * Entry: 00489860
 * Signature: undefined __cdecl queue_affine_textured_polygon_variant_00489860(int param_1, float * param_2, int param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe GEO raster span renames v37; confidence=medium] Draw-table variant from
   high-frequency mode family; exact raster state still under investigation. */

void __cdecl
queue_affine_textured_polygon_variant_00489860
          (int param_1,float *param_2,int param_3,undefined4 param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined4 *puVar6;
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
  puStack_8 = &LAB_004bbdcb;
  local_c = ExceptionList;
  puVar6 = (undefined4 *)0x0;
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
      puVar6 = (undefined4 *)
               initialize_raster_command_record
                         (DAT_004f9d80,param_4,0,raster_emit_span_callback_mode_00488e40);
    }
    local_4 = 0xffffffff;
    iVar5 = build_projected_polygon_scanline_spans(param_1,(uint)puVar6,param_2,param_3,&local_3c);
    if (iVar5 != 0) {
      compute_projected_triangle_barycentric_matrix(&local_3c,&local_30);
      fVar2 = (float)*(int *)*puVar6 * _DAT_004be77c;
      fVar1 = *(float *)(local_38 + 0xc) * fVar2;
      fVar3 = *(float *)(local_34 + 0xc) * fVar2;
      fVar2 = *(float *)(local_3c + 0xc) * fVar2;
      puVar6[3] = fVar2 * local_30 + fVar1 * local_24 + fVar3 * local_18;
      puVar6[0x10] = fVar2 * local_2c + fVar1 * local_20 + fVar3 * local_14;
      puVar6[0x11] = fVar2 * local_28 + fVar1 * local_1c + fVar3 * local_10;
      fVar3 = (float)((((int *)*puVar6)[1] << 3) >> 3) * _DAT_004be77c;
      fVar1 = *(float *)(local_38 + 0x10) * fVar3;
      fVar2 = *(float *)(local_34 + 0x10) * fVar3;
      fVar3 = *(float *)(local_3c + 0x10) * fVar3;
      puVar6[4] = fVar3 * local_30 + fVar1 * local_24 + fVar2 * local_18;
      puVar6[0x12] = fVar3 * local_2c + fVar1 * local_20 + fVar2 * local_14;
      fVar4 = _DAT_004be778;
      puVar6[0x13] = fVar3 * local_28 + fVar1 * local_1c + fVar2 * local_10;
      fVar1 = *(float *)(local_38 + 8);
      fVar2 = *(float *)(local_34 + 8);
      fVar3 = *(float *)(local_3c + 8);
      puVar6[5] = fVar3 * local_30 + fVar1 * local_24 + fVar2 * local_18;
      puVar6[0x14] = fVar3 * local_2c + fVar1 * local_20 + fVar2 * local_14;
      puVar6[0x15] = fVar3 * local_28 + fVar1 * local_1c + fVar2 * local_10;
      fVar1 = (fVar4 - *(float *)(local_3c + 0x14)) * _DAT_004fa48c;
      fVar3 = (fVar4 - *(float *)(local_34 + 0x14)) * _DAT_004fa48c;
      fVar2 = (fVar4 - *(float *)(local_38 + 0x14)) * _DAT_004fa48c;
      puVar6[6] = fVar2 * local_24 + fVar3 * local_18 + fVar1 * local_30;
      puVar6[0x16] = fVar2 * local_20 + fVar3 * local_14 + fVar1 * local_2c;
      puVar6[0x17] = fVar2 * local_1c + fVar3 * local_10 + fVar1 * local_28;
    }
  }
  ExceptionList = local_c;
  return;
}


