/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_zone_128x128_packed_height_surface
 * Entry: 0041aaa0
 * Signature: undefined __cdecl i76edit_export_runtime_zone_128x128_packed_height_surface(uint * param_1, uint * param_2, int param_3, undefined8 param_4, ushort * param_5, int param_6, undefined4 param_7, undefined4 param_8, int param_9, ushort * param_10, uint * param_11, uint * param_12, uint * param_13, uint param_14)
 */


/* [cgpt_i76edit_level_renames_v4:low] Large terrain/zone payload builder that allocates
   0x208/0x8000 working buffers and scans map arrays; used near export/zone paths. Name is
   intentionally provisional.
   
   [cgpt_i76edit_level_renames_v6:high] Builds and writes one 0x8000-byte runtime zone raster:
   128x128 uint16. Low 12 bits are height; high bits encode terrain/surface class from the surface
   plane, including special handling around surface ids 0x63/0x64. */

void __cdecl
i76edit_export_runtime_zone_128x128_packed_height_surface
          (uint *param_1,uint *param_2,int param_3,undefined8 param_4,ushort *param_5,int param_6,
          undefined4 param_7,undefined4 param_8,int param_9,ushort *param_10,uint *param_11,
          uint *param_12,uint *param_13,uint param_14)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint *puVar4;
  uint uVar5;
  ushort uVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  ushort *puVar10;
  int in_stack_00004044;
  int in_stack_00004048;
  
  FUN_004237d0();
  param_9 = 0;
  puVar9 = (undefined4 *)&stack0x00000040;
  for (iVar7 = 0x1000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  puVar2 = (ushort *)i76edit_get_terrain_plane_row_ptr(in_stack_00004044,0);
  puVar3 = (ushort *)i76edit_get_terrain_plane_row_ptr(in_stack_00004044,2);
  puVar4 = _malloc(0x208);
  param_11 = puVar4;
  param_1 = _malloc(0x208);
  param_12 = param_1;
  param_2 = _malloc(0x208);
  param_13 = param_2;
  param_5 = _malloc(0x8000);
  puVar10 = param_5;
  for (iVar7 = 0x2000; iVar7 != 0; iVar7 = iVar7 + -1) {
    puVar10[0] = 0;
    puVar10[1] = 0;
    puVar10 = puVar10 + 2;
  }
  param_7 = 0;
  param_8 = 0;
  param_6 = in_stack_00004044;
  param_10 = param_5;
  param_4 = i76edit_find_zone_cell_origin_by_zone_id(in_stack_00004044,0,0);
  puVar8 = puVar4;
  for (iVar7 = 0x82; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar8 = 0xffffffff;
    puVar8 = puVar8 + 1;
  }
  param_3 = -1;
  *param_1 = 0xffffffff;
  *param_2 = 0xffffffff;
  param_1[0x81] = 0xffffffff;
  param_2[0x81] = 0xffffffff;
  do {
    iVar7 = -1;
    param_14 = param_3 + param_4._4_4_;
    puVar8 = (&param_1)[param_3];
    do {
      uVar5 = (int)param_4 + iVar7;
      iVar7 = iVar7 + 1;
      uVar5 = i76edit_get_or_create_zone_surface_sample(uVar5,param_14,99);
      *puVar8 = uVar5;
      puVar8 = puVar8 + 1;
    } while (iVar7 < 0x81);
    param_3 = param_3 + 1;
  } while (param_3 < 2);
  param_7 = 0;
  param_8 = 1;
  param_4 = i76edit_find_zone_cell_origin_by_zone_id(param_6,0,1);
  param_6 = 0x80;
  do {
    puVar8 = param_1;
    iVar7 = 0x80;
    do {
      uVar6 = *puVar3;
      if (99 < uVar6) {
        param_9 = 1;
        uVar6 = uVar6 - 100;
      }
      uVar6 = uVar6 << 0xd;
      uVar1 = *puVar2;
      if (param_9 != 0) {
        param_9 = 0;
        uVar6 = uVar6 | 0x1000;
      }
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
      *param_10 = *param_10 | uVar6 | uVar1 & 0xfff;
      param_10 = param_10 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    iVar7 = -1;
    param_4 = CONCAT44(param_4._4_4_ + 1,(int)param_4);
    param_1 = param_2;
    param_2 = puVar4;
    do {
      uVar5 = (int)param_4 + iVar7;
      iVar7 = iVar7 + 1;
      uVar5 = i76edit_get_or_create_zone_surface_sample(uVar5,param_4._4_4_,99);
      *puVar4 = uVar5;
      puVar4 = puVar4 + 1;
    } while (iVar7 < 0x81);
    param_6 = param_6 + -1;
    puVar4 = puVar8;
  } while (param_6 != 0);
  __write(in_stack_00004048,param_5,0x8000);
  _free(param_5);
  _free(param_11);
  _free(param_12);
  _free(param_13);
  return;
}


