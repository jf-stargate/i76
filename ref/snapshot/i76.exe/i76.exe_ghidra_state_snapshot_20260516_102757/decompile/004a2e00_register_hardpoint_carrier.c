/*
 * Program: i76.exe
 * Function: register_hardpoint_carrier
 * Entry: 004a2e00
 * Signature: undefined __cdecl register_hardpoint_carrier(int * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence hardpoint system max carriers */

void __cdecl register_hardpoint_carrier(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar3 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar3 == *param_1) goto LAB_004a2e2e;
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a2e2e:
  if (iVar1 == -1) {
    if (g_loaded_vehicle_runtime_count < 0x96) {
      iVar5 = 7;
      iVar1 = g_loaded_vehicle_runtime_count * 0x2c8;
      (&g_loaded_vehicle_runtime_table)[g_loaded_vehicle_runtime_count * 0xb2] = *param_1;
      *(undefined4 *)(&DAT_005be528 + iVar1) = 0;
      *(undefined4 *)(&DAT_005be4fc + iVar1) = 0xffffffff;
      puVar2 = (undefined4 *)(&DAT_005be530 + iVar1);
      puVar4 = &DAT_005be4dc + g_loaded_vehicle_runtime_count * 0xb2;
      do {
        *puVar4 = 0xffffffff;
        puVar2[0x14] = 0xffffffff;
        *puVar2 = 0xffffffff;
        puVar4 = puVar4 + 1;
        puVar2 = puVar2 + 0x16;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      *(undefined4 *)(&DAT_005be4f8 + iVar1) = 0xffffffff;
      *(undefined4 *)(&DAT_005be798 + iVar1) = 0;
      puVar2 = (undefined4 *)(&DAT_005be514 + iVar1);
      iVar1 = 5;
      do {
        puVar2[-5] = 0;
        *puVar2 = 0xffffffff;
        puVar2 = puVar2 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
      g_loaded_vehicle_runtime_count = g_loaded_vehicle_runtime_count + 1;
    }
    else {
      report_chunk_parse_error();
    }
    puVar2 = &DAT_005be210 + g_loaded_vehicle_runtime_count * 0xb2;
  }
  else {
    puVar2 = &g_loaded_vehicle_runtime_table + iVar1 * 0xb2;
  }
  DAT_005da754 = puVar2;
  if ((int)puVar2[0x14] < 7) {
    iVar1 = param_1[0x14];
    if (4 < iVar1) {
      piVar3 = puVar2 + (iVar1 + 1) * 0x16;
      *piVar3 = iVar1;
      piVar3[1] = param_1[1];
      piVar3[2] = param_1[0x12];
      piVar3[3] = param_1[0x13];
      piVar6 = param_1 + 2;
      piVar7 = piVar3 + 4;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *piVar7 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar7 = piVar7 + 1;
      }
      piVar3[0x14] = -1;
      return;
    }
    piVar3 = puVar2 + (puVar2[0x14] + 1) * 0x16;
    *piVar3 = iVar1;
    piVar3[1] = param_1[1];
    piVar3[2] = param_1[0x12];
    piVar3[3] = param_1[0x13];
    piVar6 = param_1 + 2;
    piVar7 = piVar3 + 4;
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar7 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar7 = piVar7 + 1;
    }
    piVar3[0x14] = -1;
    if (0 < (int)puVar2[0x14]) {
      qsort(puVar2 + 0x16,puVar2[0x14] + 1,0x58,weapon_instance_context_helper_004a51a0);
      iVar1 = 0;
      if (-1 < (int)puVar2[0x14]) {
        piVar3 = puVar2 + 0x2a;
        do {
          iVar5 = *piVar3;
          if ((iVar5 != -1) && ((&DAT_005aab24)[iVar5 * 0x13] != iVar1)) {
            (&DAT_005aab24)[iVar5 * 0x13] = iVar1;
          }
          iVar1 = iVar1 + 1;
          piVar3 = piVar3 + 0x16;
        } while (iVar1 <= (int)puVar2[0x14]);
      }
    }
    puVar2[0x14] = puVar2[0x14] + 1;
  }
  return;
}


