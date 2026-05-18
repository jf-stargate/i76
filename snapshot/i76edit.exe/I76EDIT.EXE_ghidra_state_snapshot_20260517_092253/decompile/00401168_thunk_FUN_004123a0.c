/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004123a0
 * Entry: 00401168
 * Signature: undefined __cdecl thunk_FUN_004123a0(int param_1, int param_2)
 */


void __cdecl thunk_FUN_004123a0(int param_1,int param_2)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  
  __read(param_1,&DAT_00439ef0,0x1900);
  __read(param_1,&DAT_009bc820,0x280140);
  thunk_FUN_0041e120(s_Loading_Surfaces____00434ac0);
  if ((param_2 != 0) && (param_2 < 3)) {
    __read(param_1,&DAT_00ebcaa0,0x280140);
    return;
  }
  if (2 < param_2) {
    __read(param_1,&DAT_00ebcaa0,0x280140);
    thunk_FUN_0041e120(s_Loading_Painted_Terrain____00434aa0);
    __read(param_1,&DAT_0113cbe0,0x280140);
    thunk_FUN_0041e120(s_Loading_Painted_Surface____00434a80);
    __read(param_1,&DAT_00c3c960,0x280140);
    thunk_FUN_0041e120(s_Loading_Workspace____00434a64);
    if (4 < param_2) {
      __read(param_1,&DAT_013bcd20,0x280140);
    }
    psVar1 = &DAT_0113cbe4;
    do {
      iVar2 = 0x80;
      psVar4 = psVar1;
      do {
        iVar3 = 0x80;
        do {
          if (*psVar4 == 0) {
            *psVar4 = -0x8000;
          }
          psVar4 = psVar4 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
      psVar1 = psVar1 + 0x4002;
    } while (psVar1 < &DAT_013bcd24);
  }
  return;
}


