/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040cbe0
 * Entry: 004013a2
 * Signature: undefined __cdecl thunk_FUN_0040cbe0(undefined4 param_1, undefined2 param_2, undefined4 param_3, undefined4 param_4)
 */


void __cdecl
thunk_FUN_0040cbe0(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  uint uVar11;
  undefined2 uStack0000000a;
  int in_stack_00004058;
  
  FUN_004237d0();
  puVar1 = DAT_01641978;
  for (uVar11 = 0; (puVar1 != (undefined4 *)0x0 && (uVar11 < 0x1000)); uVar11 = uVar11 + 1) {
    *(undefined4 **)(&stack0x00000054 + uVar11 * 4) = puVar1;
    puVar1 = (undefined4 *)*puVar1;
  }
  __write(in_stack_00004058,&stack0x00000000,4);
  puVar1 = DAT_01641978;
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
    puVar2 = (undefined4 *)puVar1[2];
    param_1 = *puVar2;
    param_2 = *(undefined2 *)(puVar2 + 1);
    uStack0000000a = *(undefined2 *)((int)puVar2 + 6);
    param_3 = puVar2[2];
    param_4 = puVar2[3];
    puVar5 = (undefined4 *)&stack0x00000014;
    puVar7 = puVar2 + 4;
    do {
      *puVar5 = *puVar7;
      puVar6 = puVar5 + 3;
      puVar5[1] = puVar7[1];
      puVar5[2] = puVar7[2];
      puVar5 = puVar6;
      puVar7 = puVar7 + 3;
    } while (puVar6 < &stack0x00000044);
    puVar5 = puVar2 + 0x12;
    puVar7 = (undefined4 *)&stack0x0000004c;
    do {
      uVar3 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar7 = uVar3;
      puVar7 = puVar7 + 1;
    } while (puVar7 < &stack0x00000054);
    piVar9 = (int *)&stack0x00000044;
    piVar4 = puVar2 + 0x10;
    do {
      iVar10 = 0;
      piVar8 = (int *)&stack0x00000054;
      do {
        if (*piVar8 == *piVar4) {
          *piVar9 = iVar10;
          break;
        }
        piVar8 = piVar8 + 1;
        iVar10 = iVar10 + 1;
      } while (piVar8 < &stack0x00004054);
      piVar9 = piVar9 + 1;
      piVar4 = piVar4 + 1;
    } while (piVar9 < &stack0x0000004c);
    __write(in_stack_00004058,&param_1,0x50);
    puVar1 = (undefined4 *)*puVar1;
  } while( true );
}


