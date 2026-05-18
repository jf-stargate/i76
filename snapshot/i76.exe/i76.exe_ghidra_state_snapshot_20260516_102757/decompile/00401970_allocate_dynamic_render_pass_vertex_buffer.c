/*
 * Program: i76.exe
 * Function: allocate_dynamic_render_pass_vertex_buffer
 * Entry: 00401970
 * Signature: undefined4 __cdecl allocate_dynamic_render_pass_vertex_buffer(undefined4 * param_1, undefined4 param_2, int * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Allocates or returns scratch vertex/output storage for the
   dynamic render pass. */

undefined4 __cdecl
allocate_dynamic_render_pass_vertex_buffer(undefined4 *param_1,undefined4 param_2,int *param_3)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  bool bVar6;
  undefined3 extraout_var;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  if (DAT_005049c8 < DAT_00503034) {
    if (DAT_005049c4 == 0xf) {
      puVar9 = &DAT_00501990;
      puVar10 = param_1;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      puVar9 = &DAT_00501828 + DAT_005049c8 * 6;
      puVar10 = param_1 + 6;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      puVar9 = &DAT_005019a8;
      puVar10 = param_1 + 0xc;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      puVar9 = &DAT_00501828;
      puVar10 = param_1 + 0x12;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      DAT_005049c8 = DAT_005049c8 + 1;
    }
    else {
      if ((DAT_005049c4 == 0) && (DAT_005049c8 == 0)) {
        DAT_005049c8 = 0x10;
        puVar9 = &DAT_00501828;
        puVar10 = param_1;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        puVar9 = &DAT_00501828 + DAT_005049c8 * 6;
        puVar10 = param_1 + 6;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        DAT_005049c8 = DAT_005049c8 + 1;
        DAT_005049c4 = DAT_005049c4 + 1;
        puVar9 = &DAT_00501828 + DAT_005049c8 * 6;
        puVar10 = param_1 + 0xc;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
      }
      else {
        puVar9 = &DAT_00501828 + DAT_005049c4 * 6;
        puVar10 = param_1;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        puVar9 = &DAT_00501828 + DAT_005049c8 * 6;
        puVar10 = param_1 + 6;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
        DAT_005049c8 = DAT_005049c8 + 1;
        DAT_005049c4 = DAT_005049c4 + 1;
        puVar9 = &DAT_00501828 + DAT_005049c8 * 6;
        puVar10 = param_1 + 0xc;
        for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar10 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        }
      }
      puVar9 = &DAT_00501828 + DAT_005049c4 * 6;
      puVar10 = param_1 + 0x12;
      for (iVar8 = 6; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar10 = *puVar9;
        puVar9 = puVar9 + 1;
        puVar10 = puVar10 + 1;
      }
    }
    *param_3 = DAT_005049cc;
    DAT_005049cc = DAT_005049cc + 1;
    pfVar1 = (float *)(param_1 + 3);
    *pfVar1 = DAT_004fa8e8;
    param_1[4] = DAT_004fa8ec;
    param_1[5] = DAT_004fa8f0;
    pfVar2 = (float *)(param_1 + 9);
    *pfVar2 = DAT_004fa90c;
    fVar5 = *pfVar1 - _DAT_004bc444;
    param_1[10] = DAT_004fa910;
    param_1[0xb] = DAT_004fa914;
    pfVar3 = (float *)(param_1 + 0xf);
    *pfVar3 = DAT_004fa900;
    param_1[0x10] = DAT_004fa904;
    param_1[0x11] = DAT_004fa908;
    pfVar4 = (float *)(param_1 + 0x15);
    *pfVar4 = DAT_004fa8f4;
    param_1[0x16] = DAT_004fa8f8;
    uVar7 = DAT_004fa8fc;
    *pfVar1 = fVar5;
    fVar5 = *pfVar2 - _DAT_004bc444;
    param_1[0x17] = uVar7;
    *pfVar2 = fVar5;
    *pfVar3 = *pfVar3 - _DAT_004bc448;
    *pfVar4 = *pfVar4 - _DAT_004bc448;
    bVar6 = get_global_heap_handle();
    if (CONCAT31(extraout_var,bVar6) == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 0x3f4ccccd;
    }
    param_1[5] = uVar7;
    param_1[0xb] = uVar7;
    param_1[0x11] = uVar7;
    param_1[0x17] = uVar7;
    return 4;
  }
  DAT_005049c8 = 0;
  DAT_005049c4 = 0;
  DAT_005049cc = 0;
  return 0xffffffff;
}


