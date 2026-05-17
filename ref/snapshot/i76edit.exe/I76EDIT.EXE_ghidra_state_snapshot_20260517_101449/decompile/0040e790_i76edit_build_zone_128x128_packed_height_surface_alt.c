/*
 * Program: I76EDIT.EXE
 * Function: i76edit_build_zone_128x128_packed_height_surface_alt
 * Entry: 0040e790
 * Signature: undefined __cdecl i76edit_build_zone_128x128_packed_height_surface_alt(uint * param_1, uint * param_2, uint * param_3, ushort * param_4, uint * param_5, undefined4 param_6, undefined4 param_7, undefined8 param_8, ushort * param_9, uint * param_10, ushort * param_11, uint * param_12, ushort * param_13, ushort * param_14, ushort * param_15, ushort * param_16, uint * param_17, uint * param_18, uint * param_19)
 */


/* [cgpt_i76edit_level_renames_v4:low] Large terrain/zone payload builder similar to 0041aaa0, with
   0x208/0x8000 work buffers and map scans. Name is intentionally provisional.
   
   [cgpt_i76edit_level_renames_v6:medium] Alternate 128x128 zone raster builder. Shares the same
   terrain-plane access and 0x8000 work-buffer pattern as the runtime zone exporter, but includes an
   extra smoothing/sampling path. */

void __cdecl
i76edit_build_zone_128x128_packed_height_surface_alt
          (uint *param_1,uint *param_2,uint *param_3,ushort *param_4,uint *param_5,
          undefined4 param_6,undefined4 param_7,undefined8 param_8,ushort *param_9,uint *param_10,
          ushort *param_11,uint *param_12,ushort *param_13,ushort *param_14,ushort *param_15,
          ushort *param_16,uint *param_17,uint *param_18,uint *param_19)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  ushort uVar8;
  uint *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  undefined4 *puVar13;
  int iVar14;
  uint *in_stack_00004058;
  
  FUN_004237d0();
  puVar13 = (undefined4 *)&stack0x00000054;
  for (iVar5 = 0x1000; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  param_9 = (ushort *)i76edit_get_terrain_plane_row_ptr((int)in_stack_00004058,0);
  param_16 = (ushort *)i76edit_get_terrain_plane_row_ptr((int)in_stack_00004058,2);
  puVar2 = _malloc(0x208);
  param_17 = puVar2;
  param_1 = _malloc(0x208);
  param_18 = param_1;
  param_2 = _malloc(0x208);
  param_19 = param_2;
  param_4 = _malloc(0x8000);
  puVar10 = param_4;
  for (iVar5 = 0x2000; iVar5 != 0; iVar5 = iVar5 + -1) {
    puVar10[0] = 0;
    puVar10[1] = 0;
    puVar10 = puVar10 + 2;
  }
  param_6 = 0;
  param_7 = 0;
  param_5 = in_stack_00004058;
  param_13 = param_4;
  param_8 = i76edit_find_zone_cell_origin_by_zone_id((int)in_stack_00004058,0,0);
  puVar9 = puVar2;
  for (iVar5 = 0x82; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = 0xffffffff;
    puVar9 = puVar9 + 1;
  }
  iVar14 = -1;
  iVar5 = (int)param_8;
  *param_1 = 0xffffffff;
  *param_2 = 0xffffffff;
  param_1[0x81] = 0xffffffff;
  param_2[0x81] = 0xffffffff;
  do {
    iVar6 = -1;
    param_3 = (uint *)(param_8._4_4_ + iVar14);
    puVar9 = (&param_1)[iVar14];
    do {
      uVar3 = iVar6 + iVar5;
      iVar6 = iVar6 + 1;
      uVar3 = i76edit_get_or_create_zone_surface_sample(uVar3,(uint)param_3,99);
      *puVar9 = uVar3;
      puVar9 = puVar9 + 1;
    } while (iVar6 < 0x81);
    iVar14 = iVar14 + 1;
  } while (iVar14 < 2);
  iVar5 = 0;
  param_6 = 0;
  param_7 = 1;
  param_8 = i76edit_find_zone_cell_origin_by_zone_id((int)param_5,0,1);
  param_15 = param_16;
  param_14 = param_9;
  param_11 = param_4 + -0x81;
  do {
    iVar14 = 0;
    param_10 = param_1;
    param_12 = param_2 + 1;
    puVar9 = puVar2;
    do {
      puVar7 = puVar9 + 1;
      uVar8 = *param_15;
      puVar4 = param_10 + 1;
      param_5 = param_10;
      param_3 = param_12 + -1;
      puVar1 = param_10 + 2;
      if (((((int)*puVar7 < 0) || ((int)puVar9[2] < 0)) || ((int)*puVar1 < 0)) ||
         (((param_9 = (ushort *)*param_10, (int)param_9 < 0 ||
           (param_3 = (uint *)*param_3, (int)param_3 < 0)) || ((int)*param_12 < 0)))) {
LAB_0040e9ba:
        param_10 = puVar4;
        if (uVar8 < 100) {
          uVar8 = uVar8 + 100;
        }
        if (0 < iVar5) {
          if ((0 < iVar14) && ((*param_11 & 0x1000) != 0)) {
            if (0 < iVar14) {
              *(undefined1 *)((int)&param_19 + iVar5 + iVar14 + 3) = 1;
            }
            if (iVar5 < 1) goto LAB_0040ea1b;
            (&stack0xffffffd4)[iVar5 + iVar14] = 1;
          }
          if (((0 < iVar5) && (iVar14 < 0x7f)) && ((*(byte *)((int)param_11 + 5) & 0x10) != 0)) {
            if (iVar14 < 0x7f) {
              (&stack0x00000055)[iVar5 + iVar14] = 1;
            }
            if (-1 < iVar14) {
              (&stack0xffffffd4)[iVar5 + iVar14] = 1;
            }
          }
        }
      }
      else {
        param_10 = puVar4;
        iVar6 = thunk_FUN_00411680((uint)(*param_14 & 0xfff),*puVar7,puVar9[2],*puVar1,(int)param_9,
                                   (int)param_3,*param_12);
        puVar4 = param_10;
        if (iVar6 != 0) goto LAB_0040e9ba;
      }
LAB_0040ea1b:
      puVar1 = param_1;
      *param_13 = *param_13 | uVar8;
      param_13 = param_13 + 1;
      param_11 = param_11 + 1;
      param_14 = param_14 + 1;
      param_12 = param_12 + 1;
      iVar14 = iVar14 + 1;
      param_15 = param_15 + 1;
      puVar9 = puVar7;
    } while (iVar14 < 0x80);
    iVar14 = -1;
    param_8 = CONCAT44(param_8._4_4_ + 1,(int)param_8);
    param_1 = param_2;
    param_2 = puVar2;
    do {
      uVar3 = (int)param_8 + iVar14;
      iVar14 = iVar14 + 1;
      uVar3 = i76edit_get_or_create_zone_surface_sample(uVar3,param_8._4_4_,99);
      *puVar2 = uVar3;
      puVar2 = puVar2 + 1;
    } while (iVar14 < 0x81);
    iVar5 = iVar5 + 0x80;
    puVar2 = puVar1;
    if (0x3fff < iVar5) {
      iVar5 = 0;
      puVar10 = param_16;
      puVar12 = param_4;
      do {
        iVar14 = 0;
        puVar11 = puVar10;
        do {
          if (((&stack0x00000054)[iVar5 + iVar14] != '\0') && (*puVar12 < 100)) {
            *puVar12 = *puVar12 + 100;
          }
          puVar10 = puVar11 + 1;
          *puVar11 = *puVar12;
          puVar12 = puVar12 + 1;
          iVar14 = iVar14 + 1;
          puVar11 = puVar10;
        } while (iVar14 < 0x80);
        iVar5 = iVar5 + 0x80;
      } while (iVar5 < 0x4000);
      _free(param_4);
      _free(param_17);
      _free(param_18);
      _free(param_19);
      return;
    }
  } while( true );
}


