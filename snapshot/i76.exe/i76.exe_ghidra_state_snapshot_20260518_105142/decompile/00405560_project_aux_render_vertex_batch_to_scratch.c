/*
 * Program: i76.exe
 * Function: project_aux_render_vertex_batch_to_scratch
 * Entry: 00405560
 * Signature: int __cdecl project_aux_render_vertex_batch_to_scratch(undefined4 * param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Projects/transforms auxiliary render vertices into a scratch
   buffer for the dynamic render pass. */

int __cdecl project_aux_render_vertex_batch_to_scratch(undefined4 *param_1,int param_2)

{
  float fVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  fVar1 = _DAT_004bc504;
  if (DAT_00507cd4 <= DAT_00507cf8) {
    DAT_00507cf8 = 0;
    DAT_00507cf4 = 0;
    DAT_00507cf0 = 0;
    return -1;
  }
  if (DAT_00507cf8 == DAT_00507cd4 + -1) {
    if (DAT_00507cf4 == DAT_00507cf8 + -1) {
      puVar5 = &DAT_00506460 + (DAT_00507cf4 - DAT_00504c40) * 6;
      puVar6 = param_1;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = &DAT_00506448 + DAT_00507cf4 * 6;
      puVar6 = param_1 + 6;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
      puVar6 = param_1 + 0xc;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar2 = 3;
      DAT_00507cf8 = DAT_00507cf8 + 1;
    }
    else {
      puVar5 = &DAT_00506460 + DAT_00507cf4 * 6;
      puVar6 = param_1;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = &DAT_00506448 + DAT_00507cf4 * 6;
      puVar6 = param_1 + 6;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
      puVar6 = param_1 + 0xc;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      iVar2 = 3;
      DAT_00507cf4 = DAT_00507cf4 + 1;
    }
    goto LAB_0040586b;
  }
  if ((DAT_00507cf4 == 0) && (DAT_00507cf8 == 0)) {
    puVar5 = &DAT_00506448;
    puVar6 = param_1;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    DAT_00507cf8 = 1;
    puVar5 = &DAT_00506460;
    puVar6 = param_1 + 6;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  else {
    if (DAT_00507cf0 != 0) {
      puVar5 = &DAT_00506448 + DAT_00507cf4 * 6;
      puVar6 = param_1;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
      puVar6 = param_1 + 6;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      if ((float)(&DAT_00504c4c)[DAT_00507cf4 * 6] - (float)(&DAT_00504c64)[DAT_00507cf4 * 6] <=
          _DAT_004bc4dc) {
        DAT_00507cf4 = DAT_00507cf4 + 1;
        DAT_00507cf8 = DAT_00507cf8 + 1;
        puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
        puVar6 = param_1 + 0xc;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar5 = &DAT_00506448 + DAT_00507cf4 * 6;
        puVar6 = param_1 + 0x12;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
      }
      else {
        puVar5 = &DAT_00506448 + (DAT_00504c40 + DAT_00507cf0) * 6;
        puVar6 = param_1 + 0xc;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        puVar5 = &DAT_00506448 + DAT_00507cf0 * 6;
        puVar6 = param_1 + 0x12;
        for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar6 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar6 = puVar6 + 1;
        }
        DAT_00507cf0 = DAT_00507cf0 + DAT_00504c40;
        DAT_00507cf8 = DAT_00507cf0 + DAT_00504c40;
        DAT_00507cf4 = DAT_00507cf0;
      }
      iVar2 = 4;
      goto LAB_0040586b;
    }
    puVar5 = &DAT_00506448;
    puVar6 = param_1;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
    puVar6 = param_1 + 6;
    for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    if (_DAT_004bc4dc <
        (float)(&DAT_00504c4c)[DAT_00507cf8 * 6] - (float)(&DAT_00504c64)[DAT_00507cf8 * 6]) {
      puVar5 = &DAT_00506460;
      puVar6 = param_1 + 0xc;
      for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      DAT_00507cf0 = DAT_00507cf0 + 1;
      iVar2 = 3;
      DAT_00507cf8 = DAT_00507cf0 + DAT_00504c40;
      DAT_00507cf4 = DAT_00507cf0;
      goto LAB_0040586b;
    }
  }
  DAT_00507cf8 = DAT_00507cf8 + 1;
  puVar5 = &DAT_00506448 + DAT_00507cf8 * 6;
  puVar6 = param_1 + 0xc;
  for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  iVar2 = 3;
LAB_0040586b:
  if (iVar2 != 0) {
    pfVar3 = (float *)(param_1 + 2);
    iVar4 = iVar2;
    do {
      if (fVar1 < *pfVar3) {
        fVar1 = *pfVar3;
      }
      pfVar3 = pfVar3 + 6;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (fVar1 <= *(float *)(param_2 + 0x108)) {
    return 0;
  }
  return iVar2;
}


