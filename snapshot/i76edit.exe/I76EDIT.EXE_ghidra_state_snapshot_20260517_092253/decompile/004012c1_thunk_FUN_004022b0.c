/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_004022b0
 * Entry: 004012c1
 * Signature: int __cdecl thunk_FUN_004022b0(int param_1, int * param_2)
 */


int __cdecl thunk_FUN_004022b0(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  long _Offset;
  int iStack_118;
  undefined4 uStack_114;
  int iStack_110;
  uint uStack_10c;
  int iStack_108;
  long lStack_104;
  char acStack_100 [256];
  
  iStack_118 = 0;
  DAT_00434070 = 0xbf800000;
  DAT_00434074 = 0xbf800000;
  DAT_00434078 = 0xbf800000;
  DAT_00434080 = 0;
  piVar1 = param_2;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      uStack_114 = 0x47455352;
      DAT_00439a20 = 0;
      do {
        if (param_2 == (int *)0x0) {
          return iStack_118;
        }
        _sprintf(acStack_100,s_Exporting_Road__d__00434088,DAT_00439a20);
        thunk_FUN_0041e120(acStack_100);
        iVar3 = thunk_FUN_004024d0((int)param_2);
        iStack_110 = 0x10;
        uStack_10c = (uint)*(ushort *)(*(int *)(iVar3 + 8) + 4);
        iStack_108 = 0;
        lStack_104 = __tell(param_1);
        __write(param_1,&uStack_114,0x10);
        iStack_108 = FUN_00402550(param_1,iVar3);
        iStack_110 = iStack_110 + iStack_108 * 0x18;
        iStack_118 = iStack_118 + iStack_110;
        _Offset = __tell(param_1);
        __lseek(param_1,lStack_104,0);
        __write(param_1,&uStack_114,0x10);
        __lseek(param_1,_Offset,0);
        DAT_00439a20 = DAT_00439a20 + 1;
        iVar3 = param_2[2];
        uVar2 = *(uint *)(iVar3 + 0x50);
        while ((uVar2 & 1) != 0) {
          if (param_2 == (int *)0x0) {
            return iStack_118;
          }
          param_2 = (int *)*param_2;
          if (param_2 != (int *)0x0) {
            iVar3 = param_2[2];
          }
          uVar2 = *(uint *)(iVar3 + 0x50);
        }
      } while( true );
    }
    iVar3 = piVar1[2];
    *(uint *)(iVar3 + 0x50) = *(uint *)(iVar3 + 0x50) & 0xfffffffe;
    if ((*(float *)(iVar3 + 0x10) == *(float *)(iVar3 + 0x34)) &&
       (*(float *)(iVar3 + 0x14) == *(float *)(iVar3 + 0x38))) break;
    piVar1 = (int *)*piVar1;
  }
  thunk_FUN_004157f0(piVar1);
  return -1;
}


