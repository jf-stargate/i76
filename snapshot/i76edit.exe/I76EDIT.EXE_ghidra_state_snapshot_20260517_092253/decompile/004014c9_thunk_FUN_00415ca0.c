/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00415ca0
 * Entry: 004014c9
 * Signature: undefined __cdecl thunk_FUN_00415ca0(undefined4 param_1, undefined2 param_2, undefined4 param_3, undefined4 param_4)
 */


void __cdecl
thunk_FUN_00415ca0(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  int *piVar10;
  uint uVar11;
  undefined2 uStack0000000a;
  int in_stack_00004058;
  
  FUN_004237d0();
  uVar11 = 0;
  puVar9 = (undefined4 *)&stack0x00000054;
  for (iVar3 = 0x1000; puVar1 = DAT_0043c544, iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  for (; (puVar1 != (undefined4 *)0x0 && (uVar11 < 0x1000)); uVar11 = uVar11 + 1) {
    *(undefined4 **)(&stack0x00000054 + uVar11 * 4) = puVar1;
    puVar1 = (undefined4 *)*puVar1;
  }
  __write(in_stack_00004058,&stack0x00000000,4);
  puVar9 = DAT_0043c544;
  do {
    if (puVar9 == (undefined4 *)0x0) {
      return;
    }
    puVar1 = (undefined4 *)puVar9[2];
    param_1 = *puVar1;
    param_2 = *(undefined2 *)(puVar1 + 1);
    uStack0000000a = *(undefined2 *)((int)puVar1 + 6);
    param_3 = puVar1[2];
    param_4 = puVar1[3];
    puVar5 = (undefined4 *)&stack0x00000014;
    puVar7 = puVar1 + 4;
    do {
      *puVar5 = *puVar7;
      puVar6 = puVar5 + 3;
      puVar5[1] = puVar7[1];
      puVar5[2] = puVar7[2];
      puVar5 = puVar6;
      puVar7 = puVar7 + 3;
    } while (puVar6 < &stack0x00000044);
    puVar5 = puVar1 + 0x12;
    puVar7 = (undefined4 *)&stack0x0000004c;
    do {
      uVar2 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar7 = uVar2;
      puVar7 = puVar7 + 1;
    } while (puVar7 < &stack0x00000054);
    piVar8 = (int *)&stack0x00000044;
    piVar4 = puVar1 + 0x10;
    do {
      iVar3 = 0;
      piVar10 = (int *)&stack0x00000054;
      do {
        if (*piVar10 == *piVar4) {
          *piVar8 = iVar3;
          break;
        }
        piVar10 = piVar10 + 1;
        iVar3 = iVar3 + 1;
      } while (piVar10 < &stack0x00004054);
      piVar8 = piVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (piVar8 < &stack0x0000004c);
    __write(in_stack_00004058,&param_1,0x50);
    puVar9 = (undefined4 *)*puVar9;
  } while( true );
}


