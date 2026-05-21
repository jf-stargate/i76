/*
 * Program: i76shell.dll
 * Function: lock_shell_surface_for_draw
 * Entry: 10039a10
 * Signature: undefined4 __fastcall lock_shell_surface_for_draw(int param_1)
 */


undefined4 __fastcall lock_shell_surface_for_draw(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    iVar1 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar1 != 0) {
      return CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
    uVar2 = *DAT_100533e8;
    *(uint *)(param_1 + 0x30) = uVar2;
    **(uint **)(param_1 + 0x6c) = uVar2;
  }
  return uVar2 & 0xffffff00;
}


