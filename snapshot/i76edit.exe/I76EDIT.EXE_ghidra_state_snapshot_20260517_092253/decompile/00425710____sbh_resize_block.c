/*
 * Program: I76EDIT.EXE
 * Function: ___sbh_resize_block
 * Entry: 00425710
 * Signature: undefined4 __cdecl ___sbh_resize_block(int param_1, int * param_2, byte * param_3, uint param_4)
 */


/* Library Function - Single Match
    ___sbh_resize_block
   
   Library: Visual Studio 1998 Release */

undefined4 __cdecl ___sbh_resize_block(int param_1,int *param_2,byte *param_3,uint param_4)

{
  char *pcVar1;
  byte bVar2;
  byte bVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  
  uVar4 = 0;
  bVar2 = *param_3;
  uVar7 = (uint)bVar2;
  bVar6 = (byte)param_4;
  if (uVar7 <= param_4) {
    if ((uVar7 < param_4) && (pbVar9 = param_3 + param_4, pbVar9 <= param_2 + 0x3e)) {
      for (pbVar8 = param_3 + uVar7; (pbVar8 < pbVar9 && (*pbVar8 == 0)); pbVar8 = pbVar8 + 1) {
      }
      if (pbVar8 == pbVar9) {
        *param_3 = bVar6;
        if ((param_3 <= (byte *)*param_2) && ((byte *)*param_2 < pbVar9)) {
          if (pbVar9 < param_2 + 0x3e) {
            iVar5 = 0;
            *param_2 = (int)pbVar9;
            bVar3 = *pbVar9;
            while (bVar3 == 0) {
              iVar5 = iVar5 + 1;
              pbVar9 = pbVar9 + 1;
              bVar3 = *pbVar9;
            }
            param_2[1] = iVar5;
          }
          else {
            param_2[1] = 0;
            *param_2 = (int)(param_2 + 2);
          }
        }
        pcVar1 = (char *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1);
        *pcVar1 = *pcVar1 + (bVar2 - bVar6);
        uVar4 = 1;
      }
    }
    return uVar4;
  }
  *param_3 = bVar6;
  pcVar1 = (char *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x10 + param_1);
  *pcVar1 = *pcVar1 + (bVar2 - bVar6);
  *(undefined1 *)(((int)param_2 - *(int *)(param_1 + 0x810) >> 0xc) + 0x410 + param_1) = 0xf1;
  return 1;
}


