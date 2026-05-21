/*
 * Program: i76shell.dll
 * Function: transform_image_point_fixed
 * Entry: 1003e352
 * Signature: undefined __cdecl transform_image_point_fixed(int * param_1, int * param_2, int * param_3, uint param_4, int param_5, int param_6)
 */


void __cdecl
transform_image_point_fixed
          (int *param_1,int *param_2,int *param_3,uint param_4,int param_5,int param_6)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  ushort uVar9;
  uint uVar6;
  ushort uVar10;
  uint uVar7;
  ushort uVar11;
  uint uVar8;
  ushort uVar12;
  int iVar13;
  int local_c;
  int local_8;
  
  FUN_1003e274(param_4,&local_8,&local_c);
  lVar1 = (longlong)((*param_1 - *param_3) * 0x10000) * (longlong)param_5;
  iVar13 = (int)((ulonglong)lVar1 >> 0x20) + (uint)(0xffff7fff < (uint)lVar1);
  lVar1 = (longlong)iVar13 * (longlong)local_8;
  uVar5 = (uint)lVar1;
  uVar9 = (ushort)(uVar5 + 0x8000 >> 0x10);
  lVar2 = (longlong)iVar13 * (longlong)local_c;
  uVar6 = (uint)lVar2;
  uVar10 = (ushort)(uVar6 + 0x8000 >> 0x10);
  lVar3 = (longlong)((param_1[1] - param_3[1]) * 0x10000) * (longlong)param_6;
  iVar13 = (int)((ulonglong)lVar3 >> 0x20) + (uint)(0xffff7fff < (uint)lVar3);
  lVar3 = (longlong)iVar13 * (longlong)local_8;
  uVar7 = (uint)lVar3;
  uVar11 = (ushort)(uVar7 + 0x8000 >> 0x10);
  lVar4 = (longlong)iVar13 * (longlong)local_c;
  uVar8 = (uint)lVar4;
  uVar12 = (ushort)(uVar8 + 0x8000 >> 0x10);
  *param_2 = (((uint)uVar9 |
              CONCAT22(uVar9,(short)((ulonglong)lVar1 >> 0x20) + (ushort)(0xffff7fff < uVar5)) <<
              0x10) - ((uint)uVar12 |
                      CONCAT22(uVar12,(short)((ulonglong)lVar4 >> 0x20) +
                                      (ushort)(0xffff7fff < uVar8)) << 0x10)) + *param_3;
  param_2[1] = ((uint)uVar11 |
               CONCAT22(uVar11,(short)((ulonglong)lVar3 >> 0x20) + (ushort)(0xffff7fff < uVar7)) <<
               0x10) + ((uint)uVar10 |
                       CONCAT22(uVar10,(short)((ulonglong)lVar2 >> 0x20) +
                                       (ushort)(0xffff7fff < uVar6)) << 0x10) + param_3[1];
  return;
}


