/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041cb50
 * Entry: 00401375
 * Signature: undefined __thiscall thunk_FUN_0041cb50(void * this, float * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall thunk_FUN_0041cb50(void *this,float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  float *pfVar11;
  float afStack_30 [4];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fVar1 = *(float *)this * *(float *)this * _DAT_004321f8;
  fVar2 = *(float *)((int)this + 4) * *(float *)((int)this + 4) * _DAT_004321f8;
  fVar4 = *(float *)this * *(float *)((int)this + 4) * _DAT_004321f8;
  fVar5 = *(float *)this * *(float *)((int)this + 8) * _DAT_004321f8;
  fVar6 = *(float *)this * *(float *)((int)this + 0xc) * _DAT_004321f8;
  fVar7 = *(float *)((int)this + 4) * *(float *)((int)this + 8) * _DAT_004321f8;
  uStack_c = 0;
  uStack_8 = 0;
  fVar8 = *(float *)((int)this + 4) * *(float *)((int)this + 0xc) * _DAT_004321f8;
  uStack_4 = 0;
  fVar3 = _DAT_004321f4 - *(float *)((int)this + 8) * *(float *)((int)this + 8) * _DAT_004321f8;
  fVar9 = *(float *)((int)this + 8) * *(float *)((int)this + 0xc) * _DAT_004321f8;
  afStack_30[0] = fVar3 - fVar2;
  afStack_30[1] = fVar4 - fVar9;
  afStack_30[3] = fVar4 + fVar9;
  fStack_20 = fVar3 - fVar1;
  afStack_30[2] = fVar8 + fVar5;
  fStack_18 = fVar5 - fVar8;
  fStack_14 = fVar6 + fVar7;
  fStack_10 = (_DAT_004321f4 - fVar2) - fVar1;
  fStack_1c = fVar7 - fVar6;
  pfVar11 = afStack_30;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    *param_1 = *pfVar11;
    pfVar11 = pfVar11 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


