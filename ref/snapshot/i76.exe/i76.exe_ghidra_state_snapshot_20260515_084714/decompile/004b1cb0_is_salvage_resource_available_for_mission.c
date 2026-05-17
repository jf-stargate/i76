/*
 * Program: i76.exe
 * Function: is_salvage_resource_available_for_mission
 * Entry: 004b1cb0
 * Signature: int __cdecl is_salvage_resource_available_for_mission(char * param_1, int param_2, int param_3, int param_4)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Checks/canonicalizes salvage
   resource tokens against mission family and mission-number availability tables. */

int __cdecl
is_salvage_resource_available_for_mission(char *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  
  iVar3 = param_2;
  iVar8 = 0;
  param_2 = 0;
  iVar1 = iVar3 * 0xc;
  if (0 < *(int *)(&g_salvage_availability_count_table + iVar1)) {
    do {
      if (param_2 != 0) {
        return param_2;
      }
      uVar5 = 0xffffffff;
      iVar7 = iVar8 * 0x1c;
      pcVar10 = (&g_salvage_availability_table_groups)[iVar3 * 3] + iVar7;
      pcVar11 = pcVar10;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar11;
        pcVar11 = pcVar11 + 1;
      } while (cVar2 != '\0');
      iVar4 = _strnicmp(param_1 + *(int *)(&g_salvage_availability_name_offset_table + iVar1),
                        pcVar10,~uVar5 - 1);
      iVar9 = iVar8;
      if (iVar4 == 0) {
        while ((-1 < iVar9 && (*(int *)(pcVar10 + 0x18) != 1))) {
          if (param_2 != 0) goto LAB_004b1d8a;
          if ((param_4 == 2) && (*(int *)(pcVar10 + 0x10) <= param_3)) {
            param_2 = 1;
          }
          else if ((param_4 == 3) && (*(int *)(pcVar10 + 0x14) <= param_3)) {
            param_2 = 1;
          }
          else {
            iVar7 = iVar7 + -0x1c;
            iVar9 = iVar9 + -1;
            pcVar10 = (&g_salvage_availability_table_groups)[iVar3 * 3] + iVar7;
          }
        }
        if ((param_2 != 0) || (param_2 = *(int *)(pcVar10 + 0x18), param_2 != 0)) {
LAB_004b1d8a:
          if (iVar8 != iVar9) {
            if (*(int *)(&g_salvage_availability_name_offset_table + iVar1) == 0) {
              uVar5 = 0xffffffff;
              do {
                pcVar11 = pcVar10;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar11 = pcVar10 + 1;
                cVar2 = *pcVar10;
                pcVar10 = pcVar11;
              } while (cVar2 != '\0');
              uVar5 = ~uVar5;
              pcVar10 = pcVar11 + -uVar5;
              pcVar11 = param_1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
                pcVar10 = pcVar10 + 4;
                pcVar11 = pcVar11 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar11 = *pcVar10;
                pcVar10 = pcVar10 + 1;
                pcVar11 = pcVar11 + 1;
              }
            }
            else {
              uVar5 = 0xffffffff;
              pcVar11 = pcVar10;
              do {
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                cVar2 = *pcVar11;
                pcVar11 = pcVar11 + 1;
              } while (cVar2 != '\0');
              strncpy(param_1 + *(int *)(&g_salvage_availability_name_offset_table + iVar1),pcVar10,
                      ~uVar5 - 1);
            }
          }
        }
      }
      iVar8 = iVar9 + 1;
    } while (iVar8 < *(int *)(&g_salvage_availability_count_table + iVar1));
  }
  return param_2;
}


