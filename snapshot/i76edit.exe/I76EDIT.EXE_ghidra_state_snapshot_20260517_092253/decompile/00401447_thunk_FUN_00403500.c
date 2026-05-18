/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00403500
 * Entry: 00401447
 * Signature: undefined __stdcall thunk_FUN_00403500(void)
 */


void thunk_FUN_00403500(void)

{
  undefined4 *puVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  int aiStack_f0 [7];
  int iStack_d4;
  uint uStack_90;
  undefined4 auStack_78 [30];
  
  iVar5 = 0;
  do {
    thunk_FUN_00409d70(iVar5);
    while( true ) {
      puVar1 = thunk_FUN_00409d90();
      if (puVar1 == (undefined4 *)0x0) break;
      piVar2 = (int *)thunk_FUN_00409d20(auStack_78,(int)puVar1);
      piVar6 = aiStack_f0;
      for (iVar4 = 0x1e; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar6 = *piVar2;
        piVar2 = piVar2 + 1;
        piVar6 = piVar6 + 1;
      }
      if ((uStack_90 & 1) == 0) {
        iVar4 = thunk_FUN_0041f5a0(iStack_d4);
        if (iVar4 != 0) {
          uVar7 = thunk_FUN_004121d0(aiStack_f0[0],aiStack_f0[1],aiStack_f0[2]);
          uVar3 = thunk_FUN_0041f2b0((uint)uVar7,(uint)((ulonglong)uVar7 >> 0x20),0);
          thunk_FUN_00409b60((int)puVar1,uVar3);
        }
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x50);
  return;
}


