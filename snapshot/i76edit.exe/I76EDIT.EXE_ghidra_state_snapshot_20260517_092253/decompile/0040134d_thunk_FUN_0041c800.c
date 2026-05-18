/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041c800
 * Entry: 0040134d
 * Signature: undefined __cdecl thunk_FUN_0041c800(float * param_1, float param_2, float param_3, float param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7)
 */


void __cdecl
thunk_FUN_0041c800(float *param_1,float param_2,float param_3,float param_4,undefined4 param_5,
                  undefined4 param_6,undefined4 param_7)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  undefined8 uVar4;
  float afStack_90 [6];
  float fStack_78;
  float fStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float afStack_60 [4];
  float fStack_50;
  float fStack_4c;
  float fStack_44;
  undefined4 uStack_40;
  float afStack_30 [12];
  
  pfVar1 = (float *)&DAT_004369a8;
  pfVar3 = afStack_90;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  uVar4 = thunk_FUN_0040f140(param_3);
  afStack_90[0] = (float)((ulonglong)uVar4 >> 0x20);
  fStack_78 = (float)uVar4;
  afStack_90[2] = -fStack_78;
  pfVar1 = (float *)&DAT_004369a8;
  pfVar3 = afStack_60;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  fStack_70 = afStack_90[0];
  uVar4 = thunk_FUN_0040f140(param_2);
  fStack_50 = (float)((ulonglong)uVar4 >> 0x20);
  fStack_4c = (float)uVar4;
  fStack_44 = -fStack_4c;
  uStack_40 = fStack_50;
  pfVar1 = (float *)thunk_FUN_0041dc90(afStack_30,afStack_60,afStack_90);
  pfVar3 = afStack_90;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  pfVar1 = (float *)&DAT_004369a8;
  pfVar3 = afStack_60;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  uVar4 = thunk_FUN_0040f140(param_4);
  afStack_60[0] = (float)((ulonglong)uVar4 >> 0x20);
  afStack_60[1] = (float)uVar4;
  afStack_60[3] = -afStack_60[1];
  fStack_50 = afStack_60[0];
  pfVar1 = (float *)thunk_FUN_0041dc90(afStack_30,afStack_60,afStack_90);
  pfVar3 = afStack_90;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  uStack_6c = param_5;
  uStack_68 = param_6;
  uStack_64 = param_7;
  pfVar1 = afStack_90;
  for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


