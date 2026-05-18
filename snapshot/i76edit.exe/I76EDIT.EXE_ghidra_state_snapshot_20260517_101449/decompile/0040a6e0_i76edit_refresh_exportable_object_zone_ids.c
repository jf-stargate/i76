/*
 * Program: I76EDIT.EXE
 * Function: i76edit_refresh_exportable_object_zone_ids
 * Entry: 0040a6e0
 * Signature: undefined __stdcall i76edit_refresh_exportable_object_zone_ids(void)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Walks object buckets and updates object zone ids for
   selected runtime-relevant object type ids 2,3,0x50,0x51,0x52,0x53. */

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
  short local_72;
  int *local_5c;
  int local_4c;
  int local_48;
  int local_40 [10];
  int local_18 [3];
  int local_c [3];
  
  local_48 = 0;
  local_4c = 0;
  local_5c = &DAT_00439be8;
  do {
    puVar1 = (undefined4 *)*local_5c;
    if ((puVar1 != (undefined4 *)0x0) && (puVar1[2] != 0)) {
      for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
        iVar2 = puVar1[2];
        iVar5 = *(int *)(iVar2 + 0x1c);
        if (((((iVar5 == 2) || (iVar5 == 3)) || (iVar5 == 0x50)) ||
            ((iVar5 == 0x52 || (iVar5 == 0x53)))) || (iVar5 == 0x51)) {
          puVar4 = i76edit_get_terrain_plane_row_ptr(local_48,0);
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
                               (local_48,*(int *)(iVar2 + 4),*(int *)(iVar2 + 8));
            local_40[8] = (int)uVar14;
            local_40[1] = -iVar5;
            local_40[2] = iVar6;
            local_40[3] = -iVar5;
            local_40[4] = iVar6;
            local_40[0] = 0;
            local_40[5] = 0;
            local_40[6] = 0;
            local_40[7] = 0;
            piVar8 = local_40;
            do {
              piVar12 = piVar8 + 2;
              uVar15 = thunk_FUN_00412cf0(*piVar8,-piVar8[1],-*(int *)(iVar2 + 0x18));
              *(undefined8 *)piVar8 = uVar15;
              *piVar8 = *piVar8 + (int)uVar14;
              piVar8[1] = piVar8[1] + (int)((ulonglong)uVar14 >> 0x20);
              piVar8 = piVar12;
            } while (piVar12 < local_40 + 8);
            piVar8 = local_40;
            iVar5 = local_40[0];
            iVar6 = local_40[1];
            iVar11 = local_40[1];
            iVar13 = local_40[0];
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
            } while (piVar8 < local_40 + 8);
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
                                              (local_c,iVar13 + iVar9,iVar11 + iVar10);
                    local_72 = (&DAT_0043c554)[piVar8[2] * 0x80 + *piVar8 * 0x4002 + piVar8[1]];
                    if (local_72 != -0x8000) break;
                    iVar10 = iVar10 + 1;
                  } while (iVar10 < iVar7);
                }
                if (local_72 != -0x8000) goto LAB_0040a9b5;
                iVar9 = iVar9 + 1;
              } while (iVar9 < iVar5);
            }
            if ((local_72 == -0x8000) && (local_72 = *(short *)(iVar2 + 0xc), local_72 == 0)) {
              local_72 = 1;
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
                                              (local_18,iVar13 + iVar9,iVar11 + iVar7);
                    (&DAT_0043c554)[piVar8[2] * 0x80 + *piVar8 * 0x4002 + piVar8[1]] = local_72;
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
          if ((ushort)(&DAT_0043c554)[*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4) + local_4c]
              != 0xffffffff) {
            *(uint *)(iVar2 + 0xc) =
                 (uint)(ushort)(&DAT_0043c554)
                               [*(int *)(iVar2 + 8) * 0x80 + *(int *)(iVar2 + 4) + local_4c];
          }
        }
      }
    }
    local_4c = local_4c + 0x4002;
    local_5c = local_5c + 1;
    local_48 = local_48 + 1;
    if ((int *)0x439d27 < local_5c) {
      return;
    }
  } while( true );
}


