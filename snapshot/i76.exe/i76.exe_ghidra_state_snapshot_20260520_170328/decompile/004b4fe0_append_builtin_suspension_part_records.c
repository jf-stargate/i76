/*
 * Program: i76.exe
 * Function: append_builtin_suspension_part_records
 * Entry: 004b4fe0
 * Signature: undefined __cdecl append_builtin_suspension_part_records(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=medium-high] Calls
   load_component_definition(index,1,...) for four built-in component records and emits shell
   category 4. */

void __cdecl append_builtin_suspension_part_records(int param_1,int param_2)

{
  int iVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  byte *pbVar8;
  char *pcVar9;
  byte local_b0 [72];
  undefined4 local_68;
  undefined4 local_60;
  char local_5c [14];
  undefined1 local_4e [78];
  
  iVar7 = 0;
  if (0 < param_2) {
    do {
      pbVar8 = local_b0;
      for (iVar4 = 0x2c; iVar4 != 0; iVar4 = iVar4 + -1) {
        pbVar8[0] = 0;
        pbVar8[1] = 0;
        pbVar8[2] = 0;
        pbVar8[3] = 0;
        pbVar8 = pbVar8 + 4;
      }
      load_engine_brake_suspension_component_definition(iVar7,1,local_b0);
      pcVar3 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,local_4e);
      uVar5 = 0xffffffff;
      do {
        pcVar9 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar3 + 1;
        cVar2 = *pcVar3;
        pcVar3 = pcVar9;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar9 + -uVar5;
      pcVar9 = (char *)(param_1 + DAT_005db984 * 0x54);
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pcVar9 = pcVar9 + 1;
      }
      *(undefined4 *)(param_1 + 0x1e + DAT_005db984 * 0x54) = 4;
      iVar4 = 1;
      do {
        iVar1 = iVar4 + DAT_005db984 * 0x15;
        iVar4 = iVar4 + 1;
        *(undefined4 *)(param_1 + 0x1e + iVar1 * 4) = 0;
      } while (iVar4 < 4);
      uVar5 = 0xffffffff;
      pcVar3 = local_5c;
      do {
        pcVar9 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar3 + 1;
        cVar2 = *pcVar3;
        pcVar3 = pcVar9;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar9 + -uVar5;
      pcVar9 = (char *)(param_1 + 0x2e + DAT_005db984 * 0x54);
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar3 = local_5c;
      do {
        pcVar9 = pcVar3;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar9 = pcVar3 + 1;
        cVar2 = *pcVar3;
        pcVar3 = pcVar9;
      } while (cVar2 != '\0');
      uVar5 = ~uVar5;
      pcVar3 = pcVar9 + -uVar5;
      pcVar9 = (char *)(param_1 + 0x3b + DAT_005db984 * 0x54);
      for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar3;
        pcVar3 = pcVar3 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar3;
        pcVar3 = pcVar3 + 1;
        pcVar9 = pcVar9 + 1;
      }
      *(undefined4 *)(param_1 + 0x4c + DAT_005db984 * 0x54) = local_68;
      *(undefined4 *)(param_1 + 0x50 + DAT_005db984 * 0x54) = local_60;
      DAT_005db984 = DAT_005db984 + 1;
      iVar7 = iVar7 + 1;
    } while (iVar7 < param_2);
  }
  return;
}


