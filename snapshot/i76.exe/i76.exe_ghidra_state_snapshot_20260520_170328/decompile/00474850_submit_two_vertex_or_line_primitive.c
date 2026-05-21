/*
 * Program: i76.exe
 * Function: submit_two_vertex_or_line_primitive
 * Entry: 00474850
 * Signature: undefined __cdecl submit_two_vertex_or_line_primitive(float * param_1, float * param_2, float * param_3, undefined4 param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium-high] Submits a
   two-vertex/line primitive into the software renderer path. */

void __cdecl
submit_two_vertex_or_line_primitive(float *param_1,float *param_2,float *param_3,undefined4 param_4)

{
  float fVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 *puVar4;
  uint uVar5;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbb16;
  local_c = ExceptionList;
  uVar5 = ((uint)(param_2[2] - param_1[0x42]) & 0xbfffffff | (uint)(param_3[2] - param_1[0x42]) >> 1
          ) >> 0x1e;
  if (uVar5 != 3) {
    ExceptionList = &local_c;
    if (uVar5 != 0) {
      fVar1 = (param_1[0x42] - param_2[2]) / (param_3[2] - param_2[2]);
      if (((uint)(param_2[2] - param_1[0x42]) & 0x80000000) == 0) {
        ExceptionList = &local_c;
        param_3[2] = param_1[0x42];
        *param_3 = (*param_3 - *param_2) * fVar1 + *param_2;
        param_3[1] = (param_3[1] - param_2[1]) * fVar1 + param_2[1];
      }
      else {
        ExceptionList = &local_c;
        param_2[2] = param_1[0x42];
        *param_2 = (*param_3 - *param_2) * fVar1 + *param_2;
        param_2[1] = (param_3[1] - param_2[1]) * fVar1 + param_2[1];
      }
    }
    fVar1 = param_1[0x4e] - param_2[2];
    uVar5 = ((uint)fVar1 & 0xbfffffff | (uint)(param_1[0x4e] - param_3[2]) >> 1) >> 0x1e;
    if (uVar5 != 3) {
      if (uVar5 != 0) {
        if (((uint)fVar1 & 0x80000000) == 0) {
          fVar1 = fVar1 / (param_3[2] - param_2[2]);
          param_3[2] = param_1[0x4e];
          *param_3 = (*param_3 - *param_2) * fVar1 + *param_2;
          param_3[1] = (param_3[1] - param_2[1]) * fVar1 + param_2[1];
        }
        else {
          fVar1 = fVar1 / (param_3[2] - param_2[2]);
          param_2[2] = param_1[0x4e];
          *param_2 = (*param_3 - *param_2) * fVar1 + *param_2;
          param_2[1] = (param_3[1] - param_2[1]) * fVar1 + param_2[1];
        }
      }
      _DAT_0058dab0 =
           (double)((_DAT_004be5f8 / param_2[2]) * *param_2 * param_1[2] + *param_1 +
                   (float)_DAT_004faf18);
      puVar4 = DAT_004f9d80 + -0x18;
      _DAT_0058da30 =
           (double)(param_2[1] * (_DAT_004be5f8 / param_2[2]) * param_1[3] + param_1[1] +
                   (float)_DAT_004faf18);
      _DAT_0058da38 =
           (double)((_DAT_004be5f8 / param_3[2]) * *param_3 * param_1[2] + *param_1 +
                   (float)_DAT_004faf18);
      _DAT_0058da28 =
           (double)(param_3[1] * (_DAT_004be5f8 / param_3[2]) * param_1[3] + param_1[1] +
                   (float)_DAT_004faf18);
      if (puVar4 < DAT_004f9d7c) {
        DAT_004f9d80 = puVar4;
        if (DAT_0058dabc == (int *)0x0) {
          piVar2 = operator_new(0xc);
          local_4 = 0;
          if (piVar2 == (int *)0x0) {
            piVar2 = (int *)0x0;
            DAT_0058dab8 = (int *)0x0;
          }
          else {
            *piVar2 = 0;
            pvVar3 = operator_new(0x10000);
            piVar2[1] = (int)pvVar3;
            piVar2[2] = 0x10000;
            DAT_0058dab8 = piVar2;
          }
        }
        else {
          if (*DAT_0058dabc == 0) {
            puVar4 = operator_new(0xc);
            local_4 = 1;
            if (puVar4 == (undefined4 *)0x0) {
              puVar4 = (undefined4 *)0x0;
            }
            else {
              *puVar4 = 0;
              pvVar3 = operator_new(0x10000);
              puVar4[1] = pvVar3;
              puVar4[2] = 0x10000;
            }
            *DAT_0058dabc = (int)puVar4;
          }
          piVar2 = (int *)*DAT_0058dabc;
        }
        DAT_004f9d7c = (undefined4 *)piVar2[1];
        puVar4 = (undefined4 *)((piVar2[2] + piVar2[1] & 0xffffffe0U) - 0x60);
        DAT_0058dabc = piVar2;
      }
      DAT_004f9d80 = puVar4;
      if (puVar4 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4[2] = &LAB_00474b60;
        *puVar4 = param_4;
        puVar4[10] = 0;
      }
      if (0x1e0 < DAT_005dcec0) {
        puVar4[2] = graphics_buffer_memory_error_context_helper_00474b90;
      }
      puVar4[0x10] = DAT_0058dab0;
      puVar4[0x11] = DAT_0058da30;
      puVar4[0x12] = DAT_0058da38;
      puVar4[0x13] = DAT_0058da28;
      *DAT_0058da98 = (uint)puVar4;
      DAT_0058da98 = puVar4 + 1;
    }
  }
  ExceptionList = local_c;
  return;
}


