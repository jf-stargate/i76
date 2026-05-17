/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00409210
 * Entry: 0040141f
 * Signature: undefined4 __cdecl thunk_FUN_00409210(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


undefined4 __cdecl
thunk_FUN_00409210(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  uVar1 = param_4 - param_2;
  uVar2 = (param_5 - param_1) * uVar1 + (param_1 - param_3) * (param_6 - param_2);
  uVar5 = (int)uVar2 >> 0x1f;
  uVar6 = param_3 - param_1 >> 0x1f;
  iVar3 = (param_3 - param_1 ^ uVar6) - uVar6;
  iVar4 = (uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f);
  if (iVar3 <= iVar4) {
    iVar3 = iVar4;
  }
  if (iVar3 <= (int)((uVar2 ^ uVar5) - uVar5)) {
    return 0;
  }
  if (((param_3 < param_1) && (param_1 < param_5)) || ((param_4 < param_2 && (param_2 < param_6))))
  {
    return 1;
  }
  if (((param_1 <= param_5) || (param_3 <= param_1)) &&
     ((param_2 <= param_6 || (param_4 <= param_2)))) {
    if (((param_1 < param_3) && (param_3 < param_5)) || ((param_2 < param_4 && (param_4 < param_6)))
       ) {
      return 3;
    }
    if (((param_3 <= param_5) || (param_1 <= param_3)) &&
       ((param_4 <= param_6 || (param_2 <= param_4)))) {
      return 2;
    }
    return 3;
  }
  return 1;
}


