/*
 * Program: i76.exe
 * Function: matrix_transform_bounds_context_helper_00478c20
 * Entry: 00478c20
 * Signature: undefined __cdecl matrix_transform_bounds_context_helper_00478c20(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: matrix transform bounds context helper
   based on adjacent named subsystem context. */

void __cdecl matrix_transform_bounds_context_helper_00478c20(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  byte *pbVar7;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  int local_c;
  byte *local_8;
  float local_4;
  
  local_8 = (byte *)(param_1 + 0xe9);
  local_c = 0;
  do {
    local_24 = (float)local_8[-1] * _DAT_004be698;
    local_20 = (float)*local_8 * _DAT_004be698;
    local_1c = (float)local_8[1] * _DAT_004be698;
    local_28 = local_24;
    if (local_24 < local_20) {
      local_28 = local_20;
    }
    if (local_28 < local_1c) {
      local_28 = local_1c;
    }
    local_14 = local_24;
    if (local_20 < local_24) {
      local_14 = local_20;
    }
    if (local_1c < local_14) {
      local_14 = local_1c;
    }
    if (ABS(local_28) <= (float)_DAT_004be6a0) {
      local_10 = 0.0;
    }
    else {
      local_10 = (local_28 - local_14) / local_28;
    }
    local_14 = local_28 - local_14;
    if ((float)_DAT_004be6a0 <= ABS(local_10)) {
      if ((float)_DAT_004be6a0 <= ABS(local_24 - local_28)) {
        if ((float)_DAT_004be6a0 <= ABS(local_20 - local_28)) {
          local_14 = (local_24 - local_20) / local_14 - _DAT_004be6b4;
        }
        else {
          local_14 = (local_1c - local_24) / local_14 - _DAT_004be6b0;
        }
      }
      else {
        local_14 = (local_20 - local_1c) / local_14;
      }
      local_14 = local_14 * _DAT_004be6b8;
      if (local_14 < _DAT_004be6a8) {
        local_14 = local_14 - _DAT_004be6bc;
      }
    }
    else {
      local_14 = -1.0;
    }
    local_18 = local_28;
    local_4 = _DAT_004be6c0;
    if (_DAT_004be6c8 < local_28 - _DAT_004be6c4) {
      local_4 = _DAT_004be6c8 - local_28;
    }
    local_4 = local_4 * _DAT_004be6cc;
    iVar6 = 0x10;
    puVar5 = &DAT_00609fa0 + local_c;
    do {
      geometry_projection_context_helper_00479010
                (local_14,local_10,local_18,&local_24,&local_20,&local_1c);
      iVar2 = ftol();
      iVar3 = ftol();
      iVar4 = ftol();
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      else if (0xff < iVar2) {
        iVar2 = 0xff;
      }
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      else if (0xff < iVar3) {
        iVar3 = 0xff;
      }
      if (iVar4 < 0) {
        iVar4 = 0;
      }
      else if (0xff < iVar4) {
        iVar4 = 0xff;
      }
      uVar1 = cache_nearest_palette_cube_index(iVar2,iVar3,iVar4);
      local_18 = local_4 + local_18;
      *puVar5 = uVar1;
      puVar5 = puVar5 + 0x100;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    local_18 = local_18 - _DAT_004be6d4;
    if (local_18 < _DAT_004be6a8) {
      local_18 = 0.0;
    }
    geometry_projection_context_helper_00479010
              (local_14,local_10,local_18,&local_24,&local_20,&local_1c);
    iVar6 = ftol();
    iVar2 = ftol();
    iVar3 = ftol();
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    else if (0xff < iVar6) {
      iVar6 = 0xff;
    }
    if (iVar2 < 0) {
      iVar2 = 0;
    }
    else if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    else if (0xff < iVar3) {
      iVar3 = 0xff;
    }
    uVar1 = cache_nearest_palette_cube_index(iVar6,iVar2,iVar3);
    (&DAT_0061b1a0)[local_c] = uVar1;
    local_c = local_c + 1;
    local_8 = local_8 + 3;
  } while (local_c < 0x100);
  iVar6 = 0xe0;
  pbVar7 = (byte *)(param_1 + 0x389);
  do {
    uVar1 = cache_nearest_palette_cube_index((uint)pbVar7[-1],(uint)*pbVar7,(uint)pbVar7[1]);
    puVar5 = &DAT_00609fa0 + iVar6;
    iVar2 = 0x10;
    do {
      *puVar5 = uVar1;
      puVar5 = puVar5 + 0x100;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    iVar6 = iVar6 + 1;
    pbVar7 = pbVar7 + 3;
  } while (iVar6 < 0xf0);
  return;
}


