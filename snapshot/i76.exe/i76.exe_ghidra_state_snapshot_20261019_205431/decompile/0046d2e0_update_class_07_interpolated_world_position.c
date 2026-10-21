/*
 * Program: i76.exe
 * Function: update_class_07_interpolated_world_position
 * Entry: 0046d2e0
 * Signature: undefined __cdecl update_class_07_interpolated_world_position(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl update_class_07_interpolated_world_position(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;
  float10 fVar8;
  float local_24;
  float local_20;
  float local_1c;
  
  iVar4 = *(int *)(param_1 + 0x70);
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x90) == 0)) {
    fVar8 = get_runtime_frame_delta_seconds();
    pfVar1 = (float *)(iVar4 + 0x78);
    local_24 = *pfVar1;
    local_20 = *(float *)(iVar4 + 0x7c);
    fVar3 = (float)(fVar8 * (float10)*(float *)(iVar4 + 0x94));
    local_1c = *(float *)(iVar4 + 0x80);
    pfVar2 = (float *)(iVar4 + 0x84);
    if ((_DAT_004be378 <= fVar3) &&
       ((fVar3 <= _DAT_004be380 && (fVar7 = local_24 - *pfVar2, (float)_DAT_004be388 <= ABS(fVar7)))
       )) {
      local_24 = fVar3 * fVar7 + *pfVar2;
    }
    if (((_DAT_004be378 <= fVar3) && (fVar3 <= _DAT_004be380)) &&
       (fVar7 = local_20 - *(float *)(iVar4 + 0x88), (float)_DAT_004be388 <= ABS(fVar7))) {
      local_20 = fVar3 * fVar7 + *(float *)(iVar4 + 0x88);
    }
    if (((_DAT_004be378 <= fVar3) && (fVar3 <= _DAT_004be380)) &&
       (fVar7 = local_1c - *(float *)(iVar4 + 0x8c), (float)_DAT_004be388 <= ABS(fVar7))) {
      local_1c = fVar3 * fVar7 + *(float *)(iVar4 + 0x8c);
    }
    *pfVar2 = local_24;
    *(float *)(iVar4 + 0x88) = local_20;
    *(float *)(iVar4 + 0x8c) = local_1c;
    local_20 = *(float *)(iVar4 + 0x7c) - local_20;
    local_1c = *(float *)(iVar4 + 0x80) - local_1c;
    if (((_DAT_004be390 < *pfVar1 - local_24) && (*pfVar1 - local_24 < _DAT_004be394)) &&
       ((_DAT_004be390 < local_20 &&
        (((local_20 < _DAT_004be394 && (_DAT_004be390 < local_1c)) && (local_1c < _DAT_004be394)))))
       ) {
      *(undefined4 *)(iVar4 + 0x90) = 1;
      fVar3 = *(float *)(iVar4 + 0x6c);
      uVar5 = *(undefined4 *)(iVar4 + 0x70);
      uVar6 = *(undefined4 *)(iVar4 + 0x74);
      *pfVar2 = *pfVar1;
      *(undefined4 *)(iVar4 + 0x88) = *(undefined4 *)(iVar4 + 0x7c);
      *(undefined4 *)(iVar4 + 0x8c) = *(undefined4 *)(iVar4 + 0x80);
      *(float *)(iVar4 + 0x6c) = *pfVar1;
      *(undefined4 *)(iVar4 + 0x70) = *(undefined4 *)(iVar4 + 0x7c);
      *(undefined4 *)(iVar4 + 0x74) = *(undefined4 *)(iVar4 + 0x80);
      *pfVar1 = fVar3;
      *(undefined4 *)(iVar4 + 0x7c) = uVar5;
      *(undefined4 *)(iVar4 + 0x80) = uVar6;
    }
    *(double *)(param_1 + 0x40) = (double)*pfVar2;
    *(double *)(param_1 + 0x48) = (double)*(float *)(iVar4 + 0x88);
    *(double *)(param_1 + 0x50) = (double)*(float *)(iVar4 + 0x8c);
  }
  return;
}


