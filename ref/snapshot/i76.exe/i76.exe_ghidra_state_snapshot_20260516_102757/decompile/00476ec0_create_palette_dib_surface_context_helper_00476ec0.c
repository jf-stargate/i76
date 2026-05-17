/*
 * Program: i76.exe
 * Function: create_palette_dib_surface_context_helper_00476ec0
 * Entry: 00476ec0
 * Signature: undefined __cdecl create_palette_dib_surface_context_helper_00476ec0(uint * param_1, int * param_2, int param_3, int param_4, uint param_5)
 */


/* cgpt readability rename set D v16: Readability pass set D: create palette dib surface context
   helper based on adjacent named subsystem context. */

void __cdecl
create_palette_dib_surface_context_helper_00476ec0
          (uint *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  short sVar1;
  bool bVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int iVar11;
  undefined4 local_128 [64];
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  if (param_2[0xb] != 0) {
    if ((*param_1 & 0x100) == 0) {
      uVar4 = param_5 & 0xff;
      if ((int)param_1[1] < (int)uVar4) {
        uVar4 = 0x2a;
      }
      piVar10 = (int *)param_1[uVar4 + 0x83];
    }
    else {
      sVar1 = *(short *)(DAT_006547e4 + (param_5 & 0xff) * 2);
      if (sVar1 == 0) {
        uVar3 = (ushort)(byte)param_5;
      }
      else {
        uVar3 = sVar1 + ((ushort)param_5 >> 8);
      }
      piVar10 = (int *)param_1[uVar3 + 0x83];
      local_8 = piVar10;
    }
    local_18 = param_3 + param_2[7];
    local_14 = param_4 + param_2[8];
    local_10 = local_18 + -1 + *piVar10;
    local_c = local_14 + -1 + param_1[2];
    iVar5 = clip_rect_to_rect_bounds(&local_18,param_2 + 7);
    if (-1 < iVar5) {
      local_28 = *piVar10;
      iVar5 = (local_18 - param_3) - param_2[7];
      local_8 = (int *)(((local_14 - param_4) - param_2[8]) * local_28);
      iVar11 = (local_10 - local_18) + 1;
      local_1c = (local_c - local_14) + 1;
      local_24 = *param_2;
      local_20 = local_14 * local_24 + param_2[5] + local_18;
      param_3 = (int)piVar10 + (int)local_8 + iVar5 + 4;
      if ((*param_1 & 0x100) != 0) {
        piVar9 = piVar10 + 1;
        puVar6 = local_128;
        for (iVar7 = 0x40; iVar7 != 0; iVar7 = iVar7 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        iVar7 = *piVar10;
        puVar6 = local_128;
        if (iVar7 < 9) {
          param_3 = 0;
          if (0 < (int)param_1[2]) {
            do {
              if ((char)*piVar9 == '\0') {
                puVar6 = (undefined4 *)((int)puVar6 + *piVar10);
              }
              else {
                iVar8 = 7;
                if (8 - iVar7 < 8) {
                  do {
                    if (((int)(char)*piVar9 & 1 << ((byte)iVar8 & 0x1f)) != 0) {
                      *(undefined1 *)puVar6 = 1;
                    }
                    puVar6 = (undefined4 *)((int)puVar6 + 1);
                    iVar8 = iVar8 + -1;
                  } while (8 - iVar7 <= iVar8);
                }
              }
              piVar9 = (int *)((int)piVar9 + 1);
              param_3 = param_3 + 1;
            } while (param_3 < (int)param_1[2]);
          }
        }
        else {
          param_3 = 0;
          if (0 < (int)param_1[2]) {
            do {
              if ((char)*piVar9 == '\0') {
                puVar6 = puVar6 + 2;
              }
              else {
                iVar8 = 7;
                do {
                  if (((int)(char)*piVar9 & 1 << ((byte)iVar8 & 0x1f)) != 0) {
                    *(undefined1 *)puVar6 = 1;
                  }
                  puVar6 = (undefined4 *)((int)puVar6 + 1);
                  iVar8 = iVar8 + -1;
                } while (-1 < iVar8);
              }
              if (*(char *)((int)piVar9 + 1) == '\0') {
                puVar6 = (undefined4 *)((int)puVar6 + *piVar10 + -8);
              }
              else {
                iVar8 = 7;
                if (0x10 - iVar7 < 8) {
                  do {
                    if (((int)*(char *)((int)piVar9 + 1) & 1 << ((byte)iVar8 & 0x1f)) != 0) {
                      *(undefined1 *)puVar6 = 1;
                    }
                    puVar6 = (undefined4 *)((int)puVar6 + 1);
                    iVar8 = iVar8 + -1;
                  } while (0x10 - iVar7 <= iVar8);
                }
              }
              piVar9 = (int *)((int)piVar9 + 2);
              param_3 = param_3 + 1;
            } while (param_3 < (int)param_1[2]);
          }
        }
        param_3 = (int)local_128 + (int)local_8 + iVar5;
      }
      local_20 = local_20 + iVar11;
      iVar7 = param_3 + iVar11;
      iVar5 = -iVar11;
      do {
        do {
          *(undefined1 *)(local_20 + iVar5) =
               *(undefined1 *)
                ((int)param_1 +
                CONCAT11(*(undefined1 *)(iVar7 + iVar5),*(undefined1 *)(local_20 + iVar5)) + 0xc);
          bVar2 = iVar5 < -1;
          iVar5 = iVar5 + 1;
        } while (bVar2);
        local_20 = local_20 + local_24;
        iVar7 = iVar7 + local_28;
        local_1c = local_1c + -1;
        iVar5 = -iVar11;
      } while (local_1c != 0);
    }
  }
  return;
}


