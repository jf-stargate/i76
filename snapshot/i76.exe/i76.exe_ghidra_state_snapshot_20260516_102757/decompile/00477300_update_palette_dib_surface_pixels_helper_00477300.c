/*
 * Program: i76.exe
 * Function: update_palette_dib_surface_pixels_helper_00477300
 * Entry: 00477300
 * Signature: undefined __cdecl update_palette_dib_surface_pixels_helper_00477300(uint * param_1, int * param_2, undefined4 param_3, undefined4 param_4, ushort * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: update palette dib surface pixels
   helper based on adjacent named subsystem context. */

void __cdecl
update_palette_dib_surface_pixels_helper_00477300
          (uint *param_1,int *param_2,int param_3,undefined4 param_4,ushort *param_5)

{
  short sVar1;
  float fVar2;
  bool bVar3;
  byte bVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  ushort *puVar11;
  undefined8 uVar12;
  int local_c;
  
  local_c = 0;
  bVar3 = false;
  if (param_2 == &DAT_005dcec0) {
    iVar6 = (*DAT_005dd2bc)(&DAT_005dcec0);
    if (iVar6 != 0) {
      fVar2 = (float)((DAT_005dcee4 - DAT_005dcedc) + 1) * _DAT_004be5fc;
      iVar6 = ftol();
      iVar7 = ftol();
      bVar4 = (byte)*param_5;
      param_3 = iVar6;
      do {
        if (bVar4 == 0) {
          (*DAT_005dd2c0)(&DAT_005dcec0);
          return;
        }
        if (!bVar3) {
          piVar10 = &DAT_004fa020 + local_c;
          do {
            if ((float)(param_3 - iVar6) < (float)*piVar10 * fVar2) break;
            if (*piVar10 == -1) {
              bVar3 = true;
            }
            local_c = local_c + 1;
            piVar10 = piVar10 + 1;
          } while (!bVar3);
        }
        if (bVar4 == 9) {
          if (bVar3) {
            iVar8 = ftol();
            param_3 = param_3 + iVar8;
          }
          else {
            param_3 = ftol();
          }
        }
        else {
          uVar9 = CONCAT22((short)((uint)iRam005dcec8 >> 0x10),*param_5);
          if (iRam005dcec8 == 0) {
            create_palette_dib_surface_context_helper_00476ec0
                      (param_1,&DAT_005dcec0,param_3,iVar7,uVar9);
          }
          else {
            release_palette_dib_surface_context_helper_00477170
                      (param_1,&DAT_005dcec0,param_3,iVar7,uVar9);
          }
          uVar5 = *param_5;
          if ((*param_1 & 0x100) == 0) {
            uVar9 = uVar5 & 0xff;
            if ((int)param_1[1] < (int)uVar9) {
              uVar9 = 0x2a;
            }
            piVar10 = (int *)param_1[uVar9 + 0x83];
          }
          else {
            sVar1 = *(short *)(DAT_006547e4 + (uVar5 & 0xffff00ff) * 2);
            if (sVar1 == 0) {
              uVar5 = uVar5 & 0xff;
            }
            else {
              uVar5 = sVar1 + (uVar5 >> 8);
            }
            piVar10 = (int *)param_1[uVar5 + 0x83];
          }
          param_3 = param_3 + 2 + *piVar10;
        }
        if (((((DAT_005a7c94 == 0) || (bVar4 = (byte)*param_5, bVar4 < 0x81)) || (bVar4 == 0x85)) ||
            (((bVar4 == 0x86 || (bVar4 == 0xeb)) ||
             ((bVar4 == 0xec || ((0x90 < (bVar4 & 0xf0) && ((bVar4 & 0xf0) < 0xe0)))))))) ||
           ((0xee < bVar4 && (bVar4 < 0xfa)))) {
          param_5 = (ushort *)((int)param_5 + 1);
        }
        else {
          param_5 = param_5 + 1;
        }
        bVar4 = (byte)*param_5;
      } while( true );
    }
  }
  else {
    fVar2 = (float)((DAT_005dcee4 - DAT_005dcedc) + 1) * _DAT_004be5fc;
    iVar6 = ftol();
    iVar7 = ftol();
    bVar4 = (byte)*param_5;
    puVar11 = param_5;
    param_3 = iVar6;
    while (bVar4 != 0) {
      if (!bVar3) {
        piVar10 = &DAT_004fa020 + local_c;
        do {
          puVar11 = (ushort *)*piVar10;
          if ((float)(param_3 - iVar6) < (float)(int)puVar11 * fVar2) break;
          if (puVar11 == (ushort *)0xffffffff) {
            bVar3 = true;
          }
          local_c = local_c + 1;
          piVar10 = piVar10 + 1;
        } while (!bVar3);
      }
      if (bVar4 == 9) {
        if (bVar3) {
          uVar12 = ftol();
          uVar12 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),param_3 + (int)uVar12);
        }
        else {
          uVar12 = ftol();
        }
      }
      else {
        create_palette_dib_surface_context_helper_00476ec0
                  (param_1,param_2,param_3,iVar7,CONCAT22((short)((uint)puVar11 >> 0x10),*param_5));
        uVar5 = *param_5;
        if ((*param_1 & 0x100) == 0) {
          uVar9 = uVar5 & 0xff;
          if ((int)param_1[1] < (int)uVar9) {
            uVar9 = 0x2a;
          }
          piVar10 = (int *)param_1[uVar9 + 0x83];
        }
        else {
          sVar1 = *(short *)(DAT_006547e4 + (uVar5 & 0xffff00ff) * 2);
          if (sVar1 == 0) {
            uVar5 = uVar5 & 0xff;
          }
          else {
            uVar5 = sVar1 + (uVar5 >> 8);
          }
          piVar10 = (int *)param_1[uVar5 + 0x83];
        }
        iVar8 = param_3 + *piVar10 + 2;
        uVar12 = CONCAT44(iVar8,iVar8);
      }
      puVar11 = (ushort *)((ulonglong)uVar12 >> 0x20);
      param_3 = (int)uVar12;
      if ((((((DAT_005a7c94 == 0) || (bVar4 = (byte)*param_5, bVar4 < 0x81)) || (bVar4 == 0x85)) ||
           ((bVar4 == 0x86 || (bVar4 == 0xeb)))) ||
          ((bVar4 == 0xec || ((0x90 < (bVar4 & 0xf0) && ((bVar4 & 0xf0) < 0xe0)))))) ||
         ((0xee < bVar4 && (bVar4 < 0xfa)))) {
        param_5 = (ushort *)((int)param_5 + 1);
      }
      else {
        param_5 = param_5 + 1;
      }
      bVar4 = (byte)*param_5;
    }
  }
  return;
}


