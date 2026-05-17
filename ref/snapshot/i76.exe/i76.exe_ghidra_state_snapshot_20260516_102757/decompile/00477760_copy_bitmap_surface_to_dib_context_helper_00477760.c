/*
 * Program: i76.exe
 * Function: copy_bitmap_surface_to_dib_context_helper_00477760
 * Entry: 00477760
 * Signature: undefined __cdecl copy_bitmap_surface_to_dib_context_helper_00477760(uint * param_1, int * param_2, int param_3, int param_4, ushort * param_5)
 */


/* cgpt readability rename set D v16: Readability pass set D: copy bitmap surface to dib context
   helper based on adjacent named subsystem context. */

void __cdecl
copy_bitmap_surface_to_dib_context_helper_00477760
          (uint *param_1,int *param_2,int param_3,int param_4,ushort *param_5)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  ushort uVar4;
  int *piVar5;
  ushort *puVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *extraout_EDX;
  ushort *extraout_EDX_00;
  int iVar9;
  undefined8 uVar10;
  int local_c;
  int *local_8;
  
  iVar3 = param_3;
  iVar9 = 0;
  local_c = 0;
  local_8 = (int *)0x0;
  if (param_2 == &DAT_005dcec0) {
    uVar10 = (*DAT_005dd2bc)(&DAT_005dcec0);
    puVar8 = (ushort *)((ulonglong)uVar10 >> 0x20);
    if ((int)uVar10 != 0) {
      bVar2 = (byte)*param_5;
      do {
        if (bVar2 == 0) {
          (*DAT_005dd2c0)(&DAT_005dcec0);
          return;
        }
        if (local_8 == (int *)0x0) {
          puVar8 = (ushort *)(param_3 - iVar3);
          piVar5 = &DAT_004fa020 + iVar9;
          do {
            local_c = iVar9;
            if ((int)puVar8 < *piVar5) break;
            if (*piVar5 == -1) {
              local_8 = (int *)0x1;
            }
            iVar9 = iVar9 + 1;
            piVar5 = piVar5 + 1;
            local_c = iVar9;
          } while (local_8 == (int *)0x0);
        }
        if (bVar2 == 9) {
          if (local_8 == (int *)0x0) {
            param_3 = (&DAT_004fa020)[iVar9] + iVar3;
          }
          else {
            param_3 = param_3 + 0x20;
          }
        }
        else {
          if (iRam005dcec8 == 0) {
            create_palette_dib_surface_context_helper_00476ec0
                      (param_1,&DAT_005dcec0,param_3,param_4,
                       CONCAT22((short)((uint)puVar8 >> 0x10),*param_5));
            puVar8 = extraout_EDX;
          }
          else {
            release_palette_dib_surface_context_helper_00477170
                      (param_1,&DAT_005dcec0,param_3,param_4,
                       CONCAT22((short)((uint)iRam005dcec8 >> 0x10),*param_5));
            puVar8 = extraout_EDX_00;
          }
          uVar4 = *param_5;
          if ((*param_1 & 0x100) == 0) {
            puVar8 = (ushort *)(uVar4 & 0xff);
            puVar6 = puVar8;
            if ((int)param_1[1] < (int)puVar8) {
              puVar6 = (ushort *)0x2a;
            }
            piVar5 = (int *)param_1[(int)((int)puVar6 + 0x83)];
          }
          else {
            sVar1 = *(short *)(DAT_006547e4 + (uVar4 & 0xffff00ff) * 2);
            if (sVar1 == 0) {
              uVar4 = uVar4 & 0xff;
            }
            else {
              uVar4 = sVar1 + (uVar4 >> 8);
            }
            piVar5 = (int *)param_1[uVar4 + 0x83];
            iVar9 = local_c;
          }
          param_3 = param_3 + 2 + *piVar5;
        }
        if (((((DAT_005a7c94 == 0) || (bVar2 = (byte)*param_5, puVar8 = param_5, bVar2 < 0x81)) ||
             (bVar2 == 0x85)) ||
            (((bVar2 == 0x86 || (bVar2 == 0xeb)) ||
             ((bVar2 == 0xec || ((0x90 < (bVar2 & 0xf0) && ((bVar2 & 0xf0) < 0xe0)))))))) ||
           ((0xee < bVar2 && (bVar2 < 0xfa)))) {
          puVar6 = (ushort *)((int)param_5 + 1);
        }
        else {
          puVar6 = param_5 + 1;
        }
        bVar2 = (byte)*puVar6;
        param_5 = puVar6;
      } while( true );
    }
  }
  else {
    bVar2 = (byte)*param_5;
    piVar5 = local_8;
    while (bVar2 != 0) {
      local_8 = piVar5;
      if (piVar5 == (int *)0x0) {
        piVar5 = &DAT_004fa020 + local_c;
        do {
          if (param_3 - iVar3 < *piVar5) break;
          if (*piVar5 == -1) {
            local_8 = (int *)0x1;
          }
          piVar5 = piVar5 + 1;
          local_c = local_c + 1;
        } while (local_8 == (int *)0x0);
      }
      if (bVar2 == 9) {
        if (local_8 == (int *)0x0) {
          param_3 = (&DAT_004fa020)[local_c] + iVar3;
        }
        else {
          param_3 = param_3 + 0x20;
        }
      }
      else {
        create_palette_dib_surface_context_helper_00476ec0
                  (param_1,param_2,param_3,param_4,CONCAT22((short)((uint)piVar5 >> 0x10),*param_5))
        ;
        uVar4 = *param_5;
        if ((*param_1 & 0x100) == 0) {
          uVar7 = uVar4 & 0xff;
          if ((int)param_1[1] < (int)uVar7) {
            uVar7 = 0x2a;
          }
          piVar5 = (int *)param_1[uVar7 + 0x83];
        }
        else {
          sVar1 = *(short *)(DAT_006547e4 + (uVar4 & 0xffff00ff) * 2);
          if (sVar1 == 0) {
            uVar4 = uVar4 & 0xff;
          }
          else {
            uVar4 = sVar1 + (uVar4 >> 8);
          }
          piVar5 = (int *)param_1[uVar4 + 0x83];
        }
        param_3 = param_3 + 2 + *piVar5;
      }
      if ((((((DAT_005a7c94 == 0) || (bVar2 = (byte)*param_5, bVar2 < 0x81)) || (bVar2 == 0x85)) ||
           ((bVar2 == 0x86 || (bVar2 == 0xeb)))) ||
          ((bVar2 == 0xec || ((0x90 < (bVar2 & 0xf0) && ((bVar2 & 0xf0) < 0xe0)))))) ||
         ((0xee < bVar2 && (bVar2 < 0xfa)))) {
        param_5 = (ushort *)((int)param_5 + 1);
      }
      else {
        param_5 = param_5 + 1;
      }
      piVar5 = local_8;
      bVar2 = (byte)*param_5;
    }
  }
  return;
}


