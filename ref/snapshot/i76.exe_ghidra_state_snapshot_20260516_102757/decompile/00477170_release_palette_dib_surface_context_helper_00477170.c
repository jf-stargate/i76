/*
 * Program: i76.exe
 * Function: release_palette_dib_surface_context_helper_00477170
 * Entry: 00477170
 * Signature: undefined __cdecl release_palette_dib_surface_context_helper_00477170(uint * param_1, int * param_2, int param_3, int param_4, uint param_5)
 */


/* cgpt readability rename set D v16: Readability pass set D: release palette dib surface context
   helper based on adjacent named subsystem context. */

void __cdecl
release_palette_dib_surface_context_helper_00477170
          (uint *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int *local_8;
  
  if (param_2[0xb] != 0) {
    if ((*param_1 & 0x100) == 0) {
      uVar7 = param_5 & 0xff;
      if ((int)param_1[1] < (int)uVar7) {
        uVar7 = 0x2a;
      }
      piVar12 = (int *)param_1[uVar7 + 0x83];
    }
    else {
      sVar1 = *(short *)(DAT_006547e4 + (param_5 & 0xff) * 2);
      if (sVar1 == 0) {
        uVar6 = (ushort)(byte)param_5;
      }
      else {
        uVar6 = sVar1 + ((ushort)param_5 >> 8);
      }
      piVar12 = (int *)param_1[uVar6 + 0x83];
      local_8 = piVar12;
    }
    local_20 = param_3 + param_2[7];
    local_1c = param_4 + param_2[8];
    local_18 = local_20 + -1 + *piVar12;
    local_14 = (param_1[2] - 1) + local_1c;
    iVar8 = clip_rect_to_rect_bounds(&local_20,param_2 + 7);
    if (-1 < iVar8) {
      iVar3 = *piVar12;
      iVar9 = (local_18 - local_20) + 1;
      iVar10 = (local_14 - local_1c) + 1;
      iVar4 = *param_2;
      iVar8 = param_2[5] + (local_1c * iVar4 + local_20) * 2 + iVar9 * 2;
      iVar13 = (int)piVar12 +
               iVar9 + (((local_20 + ((local_1c - param_4) - param_2[8]) * iVar3) - param_3) -
                       param_2[7]) + 4;
      uVar2 = (&DAT_00608460)[(byte)param_1[0x43]];
      iVar11 = -iVar9;
      do {
        do {
          if (*(char *)(iVar13 + iVar11) == '\x01') {
            *(undefined2 *)(iVar8 + iVar11 * 2) = uVar2;
          }
          bVar5 = iVar11 < -1;
          iVar11 = iVar11 + 1;
        } while (bVar5);
        iVar13 = iVar13 + iVar3;
        iVar8 = iVar8 + iVar4 * 2;
        iVar10 = iVar10 + -1;
        iVar11 = -iVar9;
      } while (iVar10 != 0);
    }
  }
  return;
}


