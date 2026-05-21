/*
 * Program: i76shell.dll
 * Function: shell_shared_ui_helper
 * Entry: 10039960
 * Signature: undefined __fastcall shell_shared_ui_helper(int param_1)
 */


/* i76shell first-pass rename
   old_name: FUN_10039960
   suggested_name: shell_shared_ui_helper
   basis: Helper shared by ShellMain/ShellWindowProc neighborhoods. */

void __fastcall shell_shared_ui_helper(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar2 != 0) goto LAB_100399df;
    uVar1 = *DAT_100533e8;
    *(undefined4 *)(param_1 + 0x30) = uVar1;
    **(undefined4 **)(param_1 + 0x6c) = uVar1;
  }
  FUN_1003c785((int *)(param_1 + 0x6c),0);
  FUN_1003c785((int *)(param_1 + 0xa8),0);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
LAB_100399df:
  (**(code **)(DAT_100533dc + 0x18))();
  return;
}


