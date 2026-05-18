/*
 * Program: I76EDIT.EXE
 * Function: ___sbh_alloc_block_from_page
 * Entry: 00425590
 * Signature: int __cdecl ___sbh_alloc_block_from_page(int * param_1, uint param_2, uint param_3)
 */


/* Library Function - Single Match
    ___sbh_alloc_block_from_page
   
   Library: Visual Studio 1998 Release */

int __cdecl ___sbh_alloc_block_from_page(int *param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  
  pbVar2 = (byte *)*param_1;
  bVar4 = (byte)param_3;
  if (param_3 <= (uint)param_1[1]) {
    *pbVar2 = bVar4;
    if (pbVar2 + param_3 < param_1 + 0x3e) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      param_1[1] = 0;
      *param_1 = (int)(param_1 + 2);
    }
    return (int)pbVar2 * 0x10 + (int)param_1 * -0xf + 0x80;
  }
  pbVar6 = pbVar2;
  if (pbVar2[param_1[1]] != 0) {
    pbVar6 = pbVar2 + param_1[1];
  }
  if (pbVar6 + param_3 < param_1 + 0x3e) {
    do {
      if (*pbVar6 == 0) {
        pbVar3 = pbVar6 + 1;
        uVar5 = 1;
        bVar1 = *pbVar3;
        while (bVar1 == 0) {
          pbVar3 = pbVar3 + 1;
          uVar5 = uVar5 + 1;
          bVar1 = *pbVar3;
        }
        if (param_3 <= uVar5) {
          if (pbVar6 + param_3 < param_1 + 0x3e) {
            *param_1 = (int)(pbVar6 + param_3);
            param_1[1] = uVar5 - param_3;
          }
          else {
            param_1[1] = 0;
            *param_1 = (int)(param_1 + 2);
          }
          *pbVar6 = bVar4;
          return (int)pbVar6 * 0x10 + (int)param_1 * -0xf + 0x80;
        }
        if (pbVar2 == pbVar6) {
          param_1[1] = uVar5;
        }
        else {
          param_2 = param_2 - uVar5;
          if (param_2 < param_3) {
            return 0;
          }
        }
      }
      else {
        pbVar3 = pbVar6 + *pbVar6;
      }
      pbVar6 = pbVar3;
    } while (pbVar3 + param_3 < param_1 + 0x3e);
  }
  pbVar6 = (byte *)(param_1 + 2);
  while( true ) {
    while( true ) {
      if ((pbVar2 <= pbVar6) || ((byte *)((int)param_1 + 0xf7U) < pbVar6 + param_3)) {
        return 0;
      }
      if (*pbVar6 == 0) break;
      pbVar6 = pbVar6 + *pbVar6;
    }
    pbVar3 = pbVar6 + 1;
    uVar5 = 1;
    bVar1 = *pbVar3;
    while (bVar1 == 0) {
      pbVar3 = pbVar3 + 1;
      uVar5 = uVar5 + 1;
      bVar1 = *pbVar3;
    }
    if (param_3 <= uVar5) break;
    param_2 = param_2 - uVar5;
    pbVar6 = pbVar3;
    if (param_2 < param_3) {
      return 0;
    }
  }
  if (pbVar6 + param_3 < param_1 + 0x3e) {
    *param_1 = (int)(pbVar6 + param_3);
    param_1[1] = uVar5 - param_3;
  }
  else {
    param_1[1] = 0;
    *param_1 = (int)(param_1 + 2);
  }
  *pbVar6 = bVar4;
  return (int)pbVar6 * 0x10 + (int)param_1 * -0xf + 0x80;
}


