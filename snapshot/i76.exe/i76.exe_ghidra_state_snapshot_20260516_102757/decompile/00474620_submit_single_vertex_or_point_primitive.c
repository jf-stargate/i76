/*
 * Program: i76.exe
 * Function: submit_single_vertex_or_point_primitive
 * Entry: 00474620
 * Signature: undefined __cdecl submit_single_vertex_or_point_primitive(float * param_1, float * param_2, undefined4 param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe geo raster span family renames v38; confidence=medium-high] Submits a
   single-vertex/point primitive into the software renderer path. */

void __cdecl
submit_single_vertex_or_point_primitive(float *param_1,float *param_2,undefined4 param_3)

{
  float fVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 *puVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_004bbaf6;
  local_c = ExceptionList;
  if (((param_1[0x42] <= param_2[2]) && (param_2[2] <= param_1[0x4e])) && (0x1e0 < DAT_005dcec0)) {
    _DAT_0058da48 =
         (double)(param_1[2] * (_DAT_004be5f8 / param_2[2]) * *param_2 + *param_1 +
                 (float)_DAT_004faf18);
    _DAT_0058da58 =
         (double)(param_2[1] * param_1[3] * (_DAT_004be5f8 / param_2[2]) + param_1[1] +
                 (float)_DAT_004faf18);
    fVar1 = param_1[0xf];
    if (((*(int *)((int)fVar1 + 0x1c) <= DAT_0058da48) &&
        (DAT_0058da48 < *(int *)((int)fVar1 + 0x24))) &&
       ((*(int *)((int)fVar1 + 0x20) <= DAT_0058da58 && (DAT_0058da58 < *(int *)((int)fVar1 + 0x28))
        ))) {
      puVar4 = DAT_004f9d80 + -0x18;
      if (puVar4 < DAT_004f9d7c) {
        DAT_004f9d80 = puVar4;
        if (DAT_0058dabc == (int *)0x0) {
          ExceptionList = &local_c;
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
            ExceptionList = &local_c;
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
        puVar4[2] = &LAB_00474820;
        *puVar4 = param_3;
        puVar4[10] = 0;
      }
      puVar4[0x10] = DAT_0058da48;
      puVar4[0x11] = DAT_0058da58;
      *DAT_0058da98 = (uint)puVar4;
      DAT_0058da98 = puVar4 + 1;
    }
  }
  ExceptionList = local_c;
  return;
}


