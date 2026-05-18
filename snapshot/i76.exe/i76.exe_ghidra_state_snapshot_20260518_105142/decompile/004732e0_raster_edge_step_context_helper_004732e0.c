/*
 * Program: i76.exe
 * Function: raster_edge_step_context_helper_004732e0
 * Entry: 004732e0
 * Signature: undefined __thiscall raster_edge_step_context_helper_004732e0(void * this, uint * param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster edge step context helper based
   on adjacent named subsystem context. */

void __thiscall raster_edge_step_context_helper_004732e0(void *this,uint *param_1)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  while (param_1 != (uint *)0x0) {
    uVar2 = param_1[3];
    puVar3 = (uint *)param_1[1];
    iVar1 = *(int *)(uVar2 + 0x30) * 4 + 4;
    DAT_004f9d80 = DAT_004f9d80 - iVar1;
    if (DAT_004f9d80 < DAT_004f9d7c) {
      ensure_raster_scratch_arena();
      DAT_004f9d80 = DAT_004f9d80 - iVar1;
    }
    uVar5 = DAT_004f9d80;
    *(uint *)(uVar2 + 0x2c) = DAT_004f9d80;
    *(uint *)(uVar2 + 0x30) = uVar5;
    puVar4 = *(uint **)((int)this + 4);
    uVar7 = 0;
    uVar5 = *puVar4;
    while (uVar5 < *param_1) {
      uVar6 = puVar4[3];
      if ((uVar5 & 1) == 0) {
        if (uVar7 == uVar6) {
          uVar7 = puVar4[4];
        }
      }
      else if (((*param_1 < **(uint **)(uVar6 + 0x24)) &&
               (*(uint *)(uVar6 + 0x34) < *(uint *)(uVar2 + 0x34))) &&
              ((uVar7 == 0 || (*(uint *)(uVar7 + 0x34) < *(uint *)(uVar6 + 0x34))))) {
        uVar7 = uVar6;
      }
      puVar4 = (uint *)puVar4[1];
      uVar5 = *puVar4;
    }
    param_1[4] = uVar7;
    uVar5 = puVar4[2];
    param_1[1] = (uint)puVar4;
    param_1[2] = uVar5;
    puVar4[2] = (uint)param_1;
    *(uint **)(uVar5 + 4) = param_1;
    uVar5 = **(uint **)(uVar2 + 0x24);
    uVar6 = *puVar4;
    while (uVar6 < uVar5) {
      if (uVar7 == puVar4[4]) {
        if (((uVar6 & 1) == 0) ||
           (uVar8 = puVar4[3], *(uint *)(uVar2 + 0x34) <= *(uint *)(uVar8 + 0x34))) {
          puVar4[4] = uVar2;
          uVar8 = uVar7;
        }
      }
      else {
        uVar8 = uVar7;
        if (uVar7 == puVar4[3]) {
          uVar8 = puVar4[4];
        }
      }
      puVar4 = (uint *)puVar4[1];
      uVar7 = uVar8;
      uVar6 = *puVar4;
    }
    *(uint *)(*(int *)(uVar2 + 0x24) + 0x10) = uVar7;
    uVar2 = *(uint *)(uVar2 + 0x24);
    uVar5 = puVar4[2];
    *(uint **)(uVar2 + 4) = puVar4;
    *(uint *)(uVar2 + 8) = uVar5;
    puVar4[2] = uVar2;
    *(uint *)(uVar5 + 4) = uVar2;
    param_1 = puVar3;
  }
  return;
}


