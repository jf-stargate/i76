/*
 * Program: I76EDIT.EXE
 * Function: i76edit_refresh_exportable_object_zone_ids
 * Entry: 004011e5
 * Signature: undefined __stdcall i76edit_refresh_exportable_object_zone_ids(void)
 */


void i76edit_refresh_exportable_object_zone_ids(void)

{
  undefined4 *puVar1;
  int iVar2;
  short sVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  short sStack_72;
  int *piStack_5c;
  int iStack_4c;
  int iStack_48;
  int aiStack_40 [10];
  int aiStack_18 [3];
  int aiStack_c [3];
  
  iStack_48 = 0;
  iStack_4c = 0;
  piStack_5c = &DAT_00439be8;
  do {
    puVar1 = (undefined4 *)*piStack_5c;
    if ((puVar1 != (undefined4 *)0x0) && (puVar1[2] != 0)) {
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        iVar2 = puVar1[2];
        iVar5 = *(int *)(iVar2 + 0x1c);
        if (((((iVar5 == 2) || (iVar5 == 3)) || (iVar5 == 0x50)) ||
            ((iVar5 == 0x52 || (iVar5 == 0x53)))) || (iVar5 == 0x51)) {
          puVar4 = i76edit_get_terrain_plane_row_ptr(iStack_48,0);
          *(uint *)(iVar2 + 0xc) =
               (uint)*(ushort *)
                      ((int)puVar4 + (*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4)) * 2);
          iVar5 = _atoi((char *)(iVar2 + 100));
          iVar6 = _atoi((char *)(iVar2 + 0x6d));
          if ((0 < iVar5) && (0 < iVar6)) {
            if (iVar5 % 5 == 0) {
              iVar5 = iVar5 / 5;
            }
            else {
              iVar5 = iVar5 / 5 + 1;
            }
            if (iVar6 % 5 == 0) {
              iVar6 = iVar6 / 5;
            }
            else {
              iVar6 = iVar6 / 5 + 1;
            }
            uVar14 = i76edit_find_zone_cell_origin_by_zone_id
                               (iStack_48,*(int *)(iVar2 + 4),*(int *)(iVar2 + 8));
            aiStack_40[8] = (int)uVar14;
            aiStack_40[1] = -iVar5;
            aiStack_40[2] = iVar6;
            aiStack_40[3] = -iVar5;
            aiStack_40[4] = iVar6;
            aiStack_40[0] = 0;
            aiStack_40[5] = 0;
            aiStack_40[6] = 0;
            aiStack_40[7] = 0;
            piVar8 = aiStack_40;
            do {
              piVar12 = piVar8 + 2;
              uVar15 = thunk_FUN_00412cf0(*piVar8,-piVar8[1],-*(int *)(iVar2 + 0x18));
              *(undefined8 *)piVar8 = uVar15;
              *piVar8 = *piVar8 + (int)uVar14;
              piVar8[1] = piVar8[1] + (int)((ulonglong)uVar14 >> 0x20);
              piVar8 = piVar12;
            } while (piVar12 < aiStack_40 + 8);
            piVar8 = aiStack_40;
            iVar5 = aiStack_40[0];
            iVar6 = aiStack_40[1];
            iVar11 = aiStack_40[1];
            iVar13 = aiStack_40[0];
            do {
              iVar9 = *piVar8;
              if (iVar9 < iVar13) {
                iVar13 = iVar9;
              }
              iVar7 = piVar8[1];
              if (iVar7 < iVar11) {
                iVar11 = iVar7;
              }
              if (iVar5 < iVar9) {
                iVar5 = iVar9;
              }
              if (iVar6 < iVar7) {
                iVar6 = iVar7;
              }
              piVar8 = piVar8 + 2;
            } while (piVar8 < aiStack_40 + 8);
            iVar6 = iVar6 - iVar11;
            iVar5 = (iVar5 - iVar13) + 1;
            if (iVar13 == 0) {
              iVar13 = 1;
            }
            if (iVar11 == 0) {
              iVar11 = 1;
            }
            iVar9 = -1;
            if (-1 < iVar5) {
              iVar7 = iVar6 + 3;
              do {
                iVar10 = 1;
                if (1 < iVar7) {
                  do {
                    i76edit_get_or_create_zone_cell_backing(iVar13 + iVar9,iVar11 + iVar10,1);
                    piVar8 = (int *)i76edit_world_xy_to_zone_local_triplet
                                              (aiStack_c,iVar13 + iVar9,iVar11 + iVar10);
                    sStack_72 = (&DAT_0043c554)[piVar8[2] * 0x80 + *piVar8 * 0x4002 + piVar8[1]];
                    if (sStack_72 != -0x8000) break;
                    iVar10 = iVar10 + 1;
                  } while (iVar10 < iVar7);
                }
                if (sStack_72 != -0x8000) goto LAB_0040a9b5;
                iVar9 = iVar9 + 1;
              } while (iVar9 < iVar5);
            }
            if ((sStack_72 == -0x8000) && (sStack_72 = *(short *)(iVar2 + 0xc), sStack_72 == 0)) {
              sStack_72 = 1;
            }
LAB_0040a9b5:
            switch(*(undefined4 *)(iVar2 + 0x1c)) {
            case 0x50:
            case 0x51:
              sVar3 = 6;
              break;
            case 0x52:
            case 0x53:
              sVar3 = 7;
              break;
            default:
              sVar3 = 0;
            }
            iVar9 = -1;
            if (-1 < iVar5) {
              iVar6 = iVar6 + 3;
              do {
                iVar7 = 1;
                if (1 < iVar6) {
                  do {
                    piVar8 = (int *)i76edit_world_xy_to_zone_local_triplet
                                              (aiStack_18,iVar13 + iVar9,iVar11 + iVar7);
                    (&DAT_0043c554)[piVar8[2] * 0x80 + *piVar8 * 0x4002 + piVar8[1]] = sStack_72;
                    if (sVar3 != 0) {
                      thunk_FUN_0041f4a0(iVar13 + iVar9,iVar11 + iVar7,sVar3,0);
                    }
                    iVar7 = iVar7 + 1;
                  } while (iVar7 < iVar6);
                }
                iVar9 = iVar9 + 1;
              } while (iVar9 < iVar5);
            }
          }
          if ((ushort)(&DAT_0043c554)[*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4) + iStack_4c]
              != 0xffffffff) {
            *(uint *)(iVar2 + 0xc) =
                 (uint)(ushort)(&DAT_0043c554)
                               [*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4) + iStack_4c];
          }
        }
      }
    }
    iStack_4c = iStack_4c + 0x4002;
    piStack_5c = piStack_5c + 1;
    iStack_48 = iStack_48 + 1;
    if ((int *)0x439d27 < piStack_5c) {
      return;
    }
  } while( true );
}


