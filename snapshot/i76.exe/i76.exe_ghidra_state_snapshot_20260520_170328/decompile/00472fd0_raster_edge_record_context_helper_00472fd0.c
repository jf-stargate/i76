/*
 * Program: i76.exe
 * Function: raster_edge_record_context_helper_00472fd0
 * Entry: 00472fd0
 * Signature: undefined __thiscall raster_edge_record_context_helper_00472fd0(void * this, uint param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster edge record context helper
   based on adjacent named subsystem context. */

void __thiscall raster_edge_record_context_helper_00472fd0(void *this,uint param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  bool bVar9;
  
  puVar2 = *(uint **)((int)this + 4);
  puVar1 = (uint *)((int)this + 0x20);
  if (puVar2 != puVar1) {
    uVar4 = puVar2[3];
    if (((byte)*(undefined4 *)(uVar4 + 0x34) & 3) == 1) {
      puVar7 = (uint *)puVar2[1];
      uVar6 = *puVar2 >> 0x15;
      uVar5 = uVar4;
      if (puVar7 != puVar1) {
        do {
          uVar3 = puVar7[3];
          if (uVar4 == uVar3) {
            uVar8 = *puVar7 >> 0x15;
            if (uVar6 < uVar8) {
              if ((*(uint *)(uVar4 + 0x28) & 0x3ff) == param_1) {
                *(uint *)(uVar4 + 0x28) =
                     ((*(uint *)(uVar4 + 0x28) >> 0x15) * 0x7ff + uVar8) * 0x400 + param_1;
              }
              else {
                **(undefined4 **)(uVar4 + 0x30) = *(undefined4 *)(uVar4 + 0x28);
                *(int *)(uVar4 + 0x30) = *(int *)(uVar4 + 0x30) + 4;
                *(uint *)(uVar4 + 0x28) = (uVar6 * 0x7ff + uVar8) * 0x400 + param_1;
              }
            }
            bVar9 = uVar5 == uVar4;
            uVar4 = uVar5;
            if (bVar9) {
              uVar4 = puVar7[4];
              uVar5 = uVar4;
            }
          }
          else {
            uVar8 = uVar6;
            if (uVar5 == puVar7[4]) {
              uVar5 = uVar3;
              if (uVar4 == 0) {
                uVar4 = uVar3;
                uVar8 = *puVar7 >> 0x15;
              }
            }
            else if (uVar5 == uVar3) {
              uVar5 = puVar7[4];
            }
          }
          puVar7 = (uint *)puVar7[1];
          uVar6 = uVar8;
        } while (puVar7 != puVar1);
        return;
      }
    }
    else {
      puVar1 = *(uint **)((int)this + 0x28);
      uVar6 = *puVar2 >> 0x15;
      for (puVar7 = (uint *)puVar2[1]; puVar7 != puVar1; puVar7 = (uint *)puVar7[1]) {
        if (uVar4 == puVar7[3]) {
          uVar5 = *puVar7 >> 0x15;
          if (uVar6 < uVar5) {
            if ((*(uint *)(uVar4 + 0x28) & 0x3ff) == param_1) {
              *(uint *)(uVar4 + 0x28) =
                   ((*(uint *)(uVar4 + 0x28) >> 0x15) * 0x7ff + uVar5) * 0x400 + param_1;
            }
            else {
              **(undefined4 **)(uVar4 + 0x30) = *(undefined4 *)(uVar4 + 0x28);
              *(int *)(uVar4 + 0x30) = *(int *)(uVar4 + 0x30) + 4;
              *(uint *)(uVar4 + 0x28) = (uVar6 * 0x7ff + uVar5) * 0x400 + param_1;
            }
          }
          puVar2 = (uint *)puVar7[1];
          uVar4 = puVar7[4];
          if (uVar4 == puVar2[4]) {
            uVar6 = *puVar2 >> 0x15;
            puVar7 = puVar2;
            if (((uVar5 != uVar6) && (uVar4 != 0)) && (uVar5 < uVar6)) {
              uVar3 = *(uint *)(uVar4 + 0x28);
              if ((uVar3 & 0x3ff) == param_1) {
                *(uint *)(uVar4 + 0x28) = ((uVar3 >> 0x15) * 0x7ff + uVar6) * 0x400 + param_1;
                uVar4 = puVar2[3];
                uVar5 = uVar6;
                goto LAB_004731ed;
              }
              **(uint **)(uVar4 + 0x30) = uVar3;
              *(int *)(uVar4 + 0x30) = *(int *)(uVar4 + 0x30) + 4;
              *(uint *)(uVar4 + 0x28) = (uVar5 * 0x7ff + uVar6) * 0x400 + param_1;
            }
            uVar4 = puVar2[3];
            uVar5 = uVar6;
          }
        }
        else {
          uVar5 = uVar6;
          if (uVar4 == puVar7[4]) {
            uVar5 = *puVar7 >> 0x15;
            if ((uVar4 != 0) && (uVar6 < uVar5)) {
              if ((*(uint *)(uVar4 + 0x28) & 0x3ff) == param_1) {
                *(uint *)(uVar4 + 0x28) =
                     ((*(uint *)(uVar4 + 0x28) >> 0x15) * 0x7ff + uVar5) * 0x400 + param_1;
              }
              else {
                **(undefined4 **)(uVar4 + 0x30) = *(undefined4 *)(uVar4 + 0x28);
                *(int *)(uVar4 + 0x30) = *(int *)(uVar4 + 0x30) + 4;
                *(uint *)(uVar4 + 0x28) = (uVar6 * 0x7ff + uVar5) * 0x400 + param_1;
              }
            }
            uVar4 = puVar7[3];
          }
        }
LAB_004731ed:
        uVar6 = uVar5;
      }
      uVar5 = *puVar7 >> 0x15;
      if (uVar6 < uVar5) {
        if ((*(uint *)(uVar4 + 0x28) & 0x3ff) == param_1) {
          *(uint *)(uVar4 + 0x28) =
               ((*(uint *)(uVar4 + 0x28) >> 0x15) * 0x7ff + uVar5) * 0x400 + param_1;
          return;
        }
        **(undefined4 **)(uVar4 + 0x30) = *(undefined4 *)(uVar4 + 0x28);
        *(int *)(uVar4 + 0x30) = *(int *)(uVar4 + 0x30) + 4;
        *(uint *)(uVar4 + 0x28) = (uVar6 * 0x7ff + uVar5) * 0x400 + param_1;
      }
    }
  }
  return;
}


