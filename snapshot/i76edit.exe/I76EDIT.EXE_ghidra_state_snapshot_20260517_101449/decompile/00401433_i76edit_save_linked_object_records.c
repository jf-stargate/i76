/*
 * Program: I76EDIT.EXE
 * Function: i76edit_save_linked_object_records
 * Entry: 00401433
 * Signature: undefined __cdecl i76edit_save_linked_object_records(undefined4 param_1, undefined2 param_2, undefined4 param_3, undefined4 param_4)
 */


void __cdecl
i76edit_save_linked_object_records
          (undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  uint uVar10;
  undefined2 uStack0000000a;
  int in_stack_00004058;
  
  FUN_004237d0();
  puVar1 = DAT_0163ce60;
  for (uVar10 = 0; (puVar1 != (undefined4 *)0x0 && (uVar10 < 0x1000)); uVar10 = uVar10 + 1) {
    *(undefined4 **)(&stack0x00000054 + uVar10 * 4) = puVar1;
    puVar1 = (undefined4 *)*puVar1;
  }
  __write(in_stack_00004058,&stack0x00000000,4);
  puVar1 = DAT_0163ce60;
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
    iVar9 = puVar1[2];
    param_1 = *(undefined4 *)(iVar9 + 0x78);
    param_2 = *(undefined2 *)(iVar9 + 0x7c);
    uStack0000000a = *(undefined2 *)(iVar9 + 0x7e);
    param_3 = *(undefined4 *)(iVar9 + 0x80);
    param_4 = *(undefined4 *)(iVar9 + 0x84);
    puVar4 = (undefined4 *)&stack0x00000014;
    puVar6 = (undefined4 *)(iVar9 + 0x88);
    do {
      *puVar4 = *puVar6;
      puVar5 = puVar4 + 3;
      puVar4[1] = puVar6[1];
      puVar4[2] = puVar6[2];
      puVar4 = puVar5;
      puVar6 = puVar6 + 3;
    } while (puVar5 < &stack0x00000044);
    puVar4 = (undefined4 *)(iVar9 + 0xc0);
    puVar6 = (undefined4 *)&stack0x0000004c;
    do {
      uVar2 = *puVar4;
      puVar4 = puVar4 + 1;
      *puVar6 = uVar2;
      puVar6 = puVar6 + 1;
    } while (puVar6 < &stack0x00000054);
    piVar8 = (int *)&stack0x00000044;
    piVar3 = (int *)(iVar9 + 0xb8);
    do {
      iVar9 = 0;
      piVar7 = (int *)&stack0x00000054;
      do {
        if (*piVar7 == *piVar3) {
          *piVar8 = iVar9;
          break;
        }
        piVar7 = piVar7 + 1;
        iVar9 = iVar9 + 1;
      } while (piVar7 < &stack0x00004054);
      piVar8 = piVar8 + 1;
      piVar3 = piVar3 + 1;
    } while (piVar8 < &stack0x0000004c);
    __write(in_stack_00004058,&param_1,0x50);
    __write(in_stack_00004058,(void *)puVar1[2],0x78);
    puVar1 = (undefined4 *)*puVar1;
  } while( true );
}


