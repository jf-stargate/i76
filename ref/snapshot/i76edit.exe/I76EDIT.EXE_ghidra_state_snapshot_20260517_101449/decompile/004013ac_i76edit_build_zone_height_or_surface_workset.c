/*
 * Program: I76EDIT.EXE
 * Function: i76edit_build_zone_height_or_surface_workset
 * Entry: 004013ac
 * Signature: int * __cdecl i76edit_build_zone_height_or_surface_workset(int param_1, int param_2)
 */


int * __cdecl i76edit_build_zone_height_or_surface_workset(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  ushort *puVar10;
  int iVar11;
  int *piVar12;
  int iStack_36c;
  int iStack_364;
  int iStack_360;
  int iStack_35c;
  int aiStack_358 [214];
  
  iVar7 = 0;
  aiStack_358[0x12] = 0;
  aiStack_358[0x13] = 0;
  aiStack_358[0x14] = 0;
  aiStack_358[0x15] = 0;
  aiStack_358[0x16] = 0;
  aiStack_358[0x17] = 0;
  aiStack_358[0x18] = 0;
  aiStack_358[0x19] = 0;
  aiStack_358[0x1a] = 0;
  aiStack_358[0x1b] = 0;
  aiStack_358[0x1c] = 0;
  aiStack_358[0x1d] = 0;
  aiStack_358[0x1e] = 0;
  aiStack_358[0x1f] = 0;
  aiStack_358[0x20] = 0;
  aiStack_358[0x21] = 0;
  aiStack_358[0x22] = 0;
  aiStack_358[0x23] = 0;
  aiStack_358[0x24] = 0;
  aiStack_358[0x25] = 0;
  aiStack_358[0x26] = 0;
  aiStack_358[0x27] = 0;
  aiStack_358[0x28] = 0;
  aiStack_358[0x29] = 0;
  aiStack_358[0x2a] = 0;
  aiStack_358[0x2b] = 0;
  aiStack_358[0x2c] = 0;
  aiStack_358[0x2d] = 0;
  aiStack_358[0x2e] = 0;
  aiStack_358[0x2f] = 0;
  aiStack_358[0x30] = 0;
  aiStack_358[0x31] = 0;
  aiStack_358[0x32] = 0;
  aiStack_358[0x33] = 0;
  aiStack_358[0x34] = 0;
  aiStack_358[0x35] = 0;
  aiStack_358[0x36] = 0;
  aiStack_358[0x37] = 0;
  aiStack_358[0x38] = 0;
  aiStack_358[0x39] = 0;
  aiStack_358[0x3a] = 0;
  aiStack_358[0x3b] = 0;
  aiStack_358[0x3c] = 0;
  aiStack_358[0x3d] = 0;
  aiStack_358[0x3e] = 0;
  aiStack_358[0x3f] = 0;
  aiStack_358[0x40] = 0;
  aiStack_358[0x41] = 0;
  aiStack_358[0x42] = 0;
  iStack_360 = 0;
  aiStack_358[0x43] = 0xfffffe80;
  aiStack_358[0x44] = 0xffffff00;
  aiStack_358[0x45] = 0xffffff80;
  aiStack_358[0x46] = 0;
  aiStack_358[0x47] = 0x80;
  aiStack_358[0x48] = 0x100;
  aiStack_358[0x49] = 0x180;
  aiStack_358[0x4a] = 0xfffffe80;
  aiStack_358[0x4b] = 0xffffff00;
  aiStack_358[0x4c] = 0xffffff80;
  aiStack_358[0x4d] = 0;
  aiStack_358[0x4e] = 0x80;
  aiStack_358[0x4f] = 0x100;
  aiStack_358[0x50] = 0x180;
  aiStack_358[0x51] = 0xfffffe80;
  aiStack_358[0x52] = 0xffffff00;
  aiStack_358[0x53] = 0xffffff80;
  aiStack_358[0x54] = 0;
  aiStack_358[0x55] = 0x80;
  aiStack_358[0x56] = 0x100;
  aiStack_358[0x57] = 0x180;
  aiStack_358[0x58] = 0xfffffe80;
  aiStack_358[0x59] = 0xffffff00;
  aiStack_358[0x5a] = 0xffffff80;
  aiStack_358[0x5b] = 0;
  aiStack_358[0x5c] = 0x80;
  aiStack_358[0x5d] = 0x100;
  aiStack_358[0x5e] = 0x180;
  aiStack_358[0x5f] = 0xfffffe80;
  aiStack_358[0x60] = 0xffffff00;
  aiStack_358[0x61] = 0xffffff80;
  aiStack_358[0x62] = 0;
  aiStack_358[99] = 0x80;
  aiStack_358[100] = 0x100;
  aiStack_358[0x65] = 0x180;
  aiStack_358[0x66] = 0xfffffe80;
  aiStack_358[0x67] = 0xffffff00;
  aiStack_358[0x68] = 0xffffff80;
  aiStack_358[0x69] = 0;
  aiStack_358[0x6a] = 0x80;
  aiStack_358[0x6b] = 0x100;
  aiStack_358[0x6c] = 0x180;
  aiStack_358[0x6d] = 0xfffffe80;
  aiStack_358[0x6e] = 0xffffff00;
  aiStack_358[0x6f] = 0xffffff80;
  aiStack_358[0x70] = 0;
  aiStack_358[0x71] = 0x80;
  aiStack_358[0x72] = 0x100;
  aiStack_358[0x73] = 0x180;
  aiStack_358[0] = -0x80;
  aiStack_358[1] = 0;
  aiStack_358[2] = 0x80;
  aiStack_358[3] = 0xffffff80;
  aiStack_358[4] = 0;
  aiStack_358[5] = 0x80;
  aiStack_358[6] = 0xffffff80;
  aiStack_358[7] = 0;
  aiStack_358[8] = 0x80;
  aiStack_358[0x74] = 0xfffffe80;
  aiStack_358[0x75] = 0xfffffe80;
  aiStack_358[0x76] = 0xfffffe80;
  aiStack_358[0x77] = 0xfffffe80;
  aiStack_358[0x78] = 0xfffffe80;
  aiStack_358[0x79] = 0xfffffe80;
  aiStack_358[0x7a] = 0xfffffe80;
  aiStack_358[0x7b] = 0xffffff00;
  aiStack_358[0x7c] = 0xffffff00;
  aiStack_358[0x7d] = 0xffffff00;
  aiStack_358[0x7e] = 0xffffff00;
  aiStack_358[0x7f] = 0xffffff00;
  aiStack_358[0x80] = 0xffffff00;
  aiStack_358[0x81] = 0xffffff00;
  aiStack_358[0x82] = 0xffffff80;
  aiStack_358[0x83] = 0xffffff80;
  aiStack_358[0x84] = 0xffffff80;
  aiStack_358[0x85] = 0xffffff80;
  aiStack_358[0x86] = 0xffffff80;
  aiStack_358[0x87] = 0xffffff80;
  aiStack_358[0x88] = 0xffffff80;
  aiStack_358[0x89] = 0;
  aiStack_358[0x8a] = 0;
  aiStack_358[0x8b] = 0;
  aiStack_358[0x8c] = 0;
  aiStack_358[0x8d] = 0;
  aiStack_358[0x8e] = 0;
  aiStack_358[0x8f] = 0;
  aiStack_358[0x90] = 0x80;
  aiStack_358[0x91] = 0x80;
  aiStack_358[0x92] = 0x80;
  aiStack_358[0x93] = 0x80;
  aiStack_358[0x94] = 0x80;
  aiStack_358[0x95] = 0x80;
  aiStack_358[0x96] = 0x80;
  aiStack_358[0x97] = 0x100;
  aiStack_358[0x98] = 0x100;
  aiStack_358[0x99] = 0x100;
  aiStack_358[0x9a] = 0x100;
  aiStack_358[0x9b] = 0x100;
  aiStack_358[0x9c] = 0x100;
  aiStack_358[0x9d] = 0x100;
  aiStack_358[0x9e] = 0x180;
  aiStack_358[0x9f] = 0x180;
  aiStack_358[0xa0] = 0x180;
  aiStack_358[0xa1] = 0x180;
  aiStack_358[0xa2] = 0x180;
  aiStack_358[0xa3] = 0x180;
  aiStack_358[0xa4] = 0x180;
  aiStack_358[9] = 0xffffff80;
  aiStack_358[10] = 0xffffff80;
  aiStack_358[0xb] = 0xffffff80;
  aiStack_358[0xc] = 0;
  aiStack_358[0xd] = 0;
  aiStack_358[0xe] = 0;
  aiStack_358[0xf] = 0x80;
  aiStack_358[0x10] = 0x80;
  aiStack_358[0x11] = 0x80;
  iVar2 = (-(uint)(DAT_004347c0 == 0) & 2) + 1;
  iStack_35c = 0;
  iVar9 = param_2 - iVar2;
  if (iVar9 <= iVar2 + param_2) {
    iVar3 = param_1 - iVar2;
    do {
      if (iVar3 <= param_1 + iVar2) {
        piVar5 = aiStack_358 + iStack_35c + 0xa5;
        iStack_35c = iStack_35c + (iVar2 - iVar3) + 1 + param_1;
        iVar11 = iVar3;
        do {
          if ((((iVar11 < 0) || (iVar9 < 0)) || (0x4f < iVar11)) || (0x4f < iVar9)) {
            *piVar5 = -1;
          }
          else {
            iVar4 = i76edit_get_or_assign_zone_map_cell_id(iVar11,iVar9,0);
            *piVar5 = iVar4;
          }
          piVar5 = piVar5 + 1;
          iVar11 = iVar11 + 1;
        } while (iVar11 <= param_1 + iVar2);
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 <= iVar2 + param_2);
  }
  iStack_364 = (-(uint)(DAT_004347c0 == 0) & 0x28) + 9;
  if (iStack_364 != 0) {
    iVar9 = 0;
    iVar2 = iStack_364;
    do {
      iVar3 = *(int *)((int)aiStack_358 + iVar9 + 0x294);
      if (iVar3 == -1) {
        iVar7 = iVar7 + 9;
        *(undefined4 *)((int)aiStack_358 + iVar9 + 0x48) = 9;
      }
      else {
        iVar11 = 0x32;
        psVar8 = &DAT_0163ce72 + iVar3 * 100;
        do {
          if (*psVar8 != -1) {
            iVar7 = iVar7 + 1;
            *(int *)((int)aiStack_358 + iVar9 + 0x48) =
                 *(int *)((int)aiStack_358 + iVar9 + 0x48) + 1;
          }
          psVar8 = psVar8 + 2;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
      iVar9 = iVar9 + 4;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  uVar6 = iVar7 * 0x14 + 8;
  piVar5 = _malloc(uVar6);
  if (piVar5 == (int *)0x0) {
    return (int *)0x0;
  }
  piVar12 = piVar5;
  for (uVar6 = uVar6 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *piVar12 = 0;
    piVar12 = piVar12 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)piVar12 = 0;
    piVar12 = (int *)((int)piVar12 + 1);
  }
  *piVar5 = iVar7;
  piVar5[1] = (int)(piVar5 + 2);
  if (iStack_364 != 0) {
    iVar2 = 0;
    do {
      iVar9 = 0;
      iVar7 = *(int *)((int)aiStack_358 + iVar2 + 0x294);
      if (iVar7 == -1) {
        iVar3 = 0x12;
        iVar7 = 0x12;
        iStack_36c = 0;
        if (0 < *(int *)((int)aiStack_358 + iVar2 + 0x48)) {
          iVar11 = iStack_360 * 0x14;
          do {
            if (0x7f < iVar3) {
              iVar3 = 0x12;
              iVar7 = iVar7 + 0x2d;
              if (0x7f < iVar7) break;
            }
            if (DAT_004347c0 == 0) {
              *(float *)(piVar5[1] + iVar11) =
                   (float)iVar3 + (float)*(int *)((int)aiStack_358 + iVar2 + 0x10c);
              iVar4 = *(int *)((int)aiStack_358 + iVar2 + 0x1d0);
            }
            else {
              *(float *)(piVar5[1] + iVar11) =
                   (float)iVar3 + (float)*(int *)((int)aiStack_358 + iVar2);
              iVar4 = *(int *)((int)aiStack_358 + iVar2 + 0x24);
            }
            iVar11 = iVar11 + 0x14;
            *(float *)(piVar5[1] + -0x10 + iVar11) = (float)iVar7 + (float)iVar4;
            iVar9 = iVar9 + 1;
            *(undefined4 *)(piVar5[1] + -0xc + iVar11) = 0;
            *(undefined4 *)(piVar5[1] + -8 + iVar11) = 0x3ba3d70a;
            if (*(int *)((int)aiStack_358 + iVar2 + 0x48) <= iVar9) break;
            iVar3 = iVar3 + 0x2d;
            iStack_36c = iStack_36c + 1;
          } while (iStack_36c < *(int *)((int)aiStack_358 + iVar2 + 0x48));
        }
      }
      else {
        iVar3 = 0;
        puVar10 = &DAT_0163ce72 + iVar7 * 100;
        iVar7 = iStack_360 * 0x14;
        do {
          if (*puVar10 != 0xffff) {
            if (DAT_004347c0 == 0) {
              *(float *)(piVar5[1] + iVar7) =
                   (float)*(int *)((int)aiStack_358 + iVar2 + 0x10c) + (float)(byte)puVar10[-1];
              bVar1 = *(byte *)((int)puVar10 + -1);
              iVar11 = *(int *)((int)aiStack_358 + iVar2 + 0x1d0);
            }
            else {
              *(float *)(piVar5[1] + iVar7) =
                   (float)*(int *)((int)aiStack_358 + iVar2) + (float)(byte)puVar10[-1];
              bVar1 = *(byte *)((int)puVar10 + -1);
              iVar11 = *(int *)((int)aiStack_358 + iVar2 + 0x24);
            }
            iVar7 = iVar7 + 0x14;
            *(float *)(piVar5[1] + -0x10 + iVar7) = (float)iVar11 + (float)bVar1;
            *(float *)(piVar5[1] + -0xc + iVar7) = (float)*puVar10;
            iVar9 = iVar9 + 1;
            *(undefined4 *)(piVar5[1] + -8 + iVar7) = 0x3ba3d70a;
            if (*(int *)((int)aiStack_358 + iVar2 + 0x48) <= iVar9) break;
          }
          puVar10 = puVar10 + 2;
          iVar3 = iVar3 + 1;
        } while (iVar3 < 0x32);
      }
      iStack_360 = iStack_360 + *(int *)((int)aiStack_358 + iVar2 + 0x48);
      iVar2 = iVar2 + 4;
      iStack_364 = iStack_364 + -1;
    } while (iStack_364 != 0);
  }
  return piVar5;
}


