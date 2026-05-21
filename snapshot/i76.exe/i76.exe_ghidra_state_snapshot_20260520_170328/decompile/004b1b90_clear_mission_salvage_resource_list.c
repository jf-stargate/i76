/*
 * Program: i76.exe
 * Function: clear_mission_salvage_resource_list
 * Entry: 004b1b90
 * Signature: undefined __stdcall clear_mission_salvage_resource_list(void)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Randomly prunes category lists
   in the mission salvage-resource list unless salvage pruning is disabled by global flags. */

void clear_mission_salvage_resource_list(void)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  int *piVar10;
  undefined4 local_190 [100];
  
  puVar3 = g_mission_salvage_resource_list;
  if (((byte)DAT_00654b98 & 2) == 0) {
    for (; puVar3 != (undefined4 *)0x0; puVar3 = (undefined4 *)*puVar3) {
      iVar9 = 0;
      puVar8 = local_190;
      for (iVar7 = 100; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar8 = 0;
        puVar8 = puVar8 + 1;
      }
      if ((undefined4 *)puVar3[1] != (undefined4 *)0x0) {
        puVar8 = local_190;
        puVar4 = (undefined4 *)puVar3[1];
        do {
          puVar1 = (undefined4 *)*puVar4;
          *puVar8 = puVar4;
          iVar9 = iVar9 + 1;
          puVar8 = puVar8 + 1;
          *puVar4 = 0;
          puVar4 = puVar1;
        } while (puVar1 != (undefined4 *)0x0);
      }
      puVar3[1] = 0;
      if (iVar9 != 0) {
        switch(puVar3[2]) {
        case 0:
          iVar7 = 4;
          break;
        default:
          iVar7 = 2;
          uVar5 = rand();
          if ((uVar5 & 1) == 0) {
            if ((uVar5 & 2) != 0) goto switchD_004b1bfa_caseD_5;
          }
          else {
            iVar7 = 3;
          }
          break;
        case 5:
switchD_004b1bfa_caseD_5:
          iVar7 = 1;
        }
        if (iVar9 < iVar7) {
          iVar7 = iVar9;
        }
        piVar10 = (int *)0x0;
        if (0 < iVar7) {
          do {
            do {
              iVar6 = rand();
              piVar2 = (int *)local_190[iVar6 % iVar9];
            } while (piVar2 == (int *)0x0);
            local_190[iVar6 % iVar9] = 0;
            if (piVar10 == (int *)0x0) {
              puVar3[1] = piVar2;
            }
            else {
              *piVar10 = (int)piVar2;
            }
            iVar7 = iVar7 + -1;
            piVar10 = piVar2;
          } while (iVar7 != 0);
        }
        if (0 < iVar9) {
          puVar8 = local_190;
          do {
            if ((LPVOID)*puVar8 != (LPVOID)0x0) {
              xfree_global_heap((LPVOID)*puVar8);
            }
            puVar8 = puVar8 + 1;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
      }
    }
  }
  return;
}


