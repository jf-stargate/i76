/*
 * Program: I76EDIT.EXE
 * Function: __fltin
 * Entry: 00427ac0
 * Signature: undefined * __cdecl __fltin(char * param_1)
 */


/* Library Function - Single Match
    __fltin
   
   Library: Visual Studio 1998 Release */

undefined * __cdecl __fltin(char *param_1)

{
  undefined *puVar1;
  uint uVar2;
  INTRNCVT_STATUS IVar3;
  uint uVar4;
  _CRT_DOUBLE local_18;
  char *local_10;
  _LDBL12 local_c;
  
  uVar4 = 0;
  uVar2 = ___strgtold12(&local_c,&local_10,param_1,0,0,0,0);
  if ((uVar2 & 4) == 0) {
    IVar3 = __ld12tod(&local_c,&local_18);
    if (((uVar2 & 2) != 0) || (IVar3 == INTRNCVT_OVERFLOW)) {
      uVar4 = 0x80;
    }
    if (((uVar2 & 1) != 0) || (IVar3 == INTRNCVT_UNDERFLOW)) {
      uVar4 = uVar4 | 0x100;
    }
  }
  else {
    local_18.x._0_4_ = 0;
    local_18.x._4_4_ = 0;
    uVar4 = 0x200;
  }
  *(uint *)PTR_DAT_00438a60 = uVar4;
  *(int *)(PTR_DAT_00438a60 + 4) = (int)local_10 - (int)param_1;
  puVar1 = PTR_DAT_00438a60;
  *(undefined4 *)(PTR_DAT_00438a60 + 0x14) = local_18.x._4_4_;
  *(undefined4 *)(puVar1 + 0x10) = local_18.x._0_4_;
  return PTR_DAT_00438a60;
}


