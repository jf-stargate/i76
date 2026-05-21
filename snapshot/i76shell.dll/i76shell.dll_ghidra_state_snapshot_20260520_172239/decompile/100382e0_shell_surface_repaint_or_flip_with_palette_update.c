/*
 * Program: i76shell.dll
 * Function: shell_surface_repaint_or_flip_with_palette_update
 * Entry: 100382e0
 * Signature: undefined __fastcall shell_surface_repaint_or_flip_with_palette_update(int param_1)
 */


void __fastcall shell_surface_repaint_or_flip_with_palette_update(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (*(int *)(param_1 + 0x20) == 0) goto LAB_100384b7;
  if (*(int *)(param_1 + 0x3d4) == 0) {
    (**(code **)(DAT_100533d8 + 0x14))(0,0x100,param_1 + 0xbc,*(undefined4 *)(param_1 + 0x24));
  }
  else {
    if (DAT_100f6368 != 0) {
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar2 == 0) {
        uVar1 = *DAT_100533e8;
        *(undefined4 *)(param_1 + 0x30) = uVar1;
        **(undefined4 **)(param_1 + 0x6c) = uVar1;
      }
    }
    uVar3 = *(int *)(param_1 + 0x3bc) * *(int *)(param_1 + 0x3c0);
    puVar5 = *(undefined4 **)(param_1 + 0x30);
    puVar6 = *(undefined4 **)(param_1 + 0x44);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    if (DAT_100f6368 == 0) {
LAB_100383a8:
      FUN_1003c785((int *)(param_1 + 0x6c),0);
      FUN_1003c785((int *)(param_1 + 0xa8),0);
      if (DAT_100f6368 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
    }
    else {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)(param_1 + 0x30) = 0;
      if (DAT_100f6368 == 0) goto LAB_100383a8;
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar2 == 0) {
        uVar1 = *DAT_100533e8;
        *(undefined4 *)(param_1 + 0x30) = uVar1;
        **(undefined4 **)(param_1 + 0x6c) = uVar1;
        goto LAB_100383a8;
      }
    }
    (**(code **)(DAT_100533dc + 0x18))();
    (**(code **)(DAT_100533d8 + 0x14))(0,0x100,param_1 + 0xbc,*(undefined4 *)(param_1 + 0x24));
    if (DAT_100f6368 != 0) {
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar2 == 0) {
        uVar1 = *DAT_100533e8;
        *(undefined4 *)(param_1 + 0x30) = uVar1;
        **(undefined4 **)(param_1 + 0x6c) = uVar1;
      }
    }
    uVar3 = *(int *)(param_1 + 0x3bc) * *(int *)(param_1 + 0x3c0);
    puVar5 = *(undefined4 **)(param_1 + 0x44);
    puVar6 = *(undefined4 **)(param_1 + 0x30);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    uVar3 = *(int *)(param_1 + 0x3bc) * *(int *)(param_1 + 0x3c0);
    puVar5 = *(undefined4 **)(param_1 + 0x44);
    puVar6 = *(undefined4 **)(param_1 + 0x58);
    for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
      puVar5 = (undefined4 *)((int)puVar5 + 1);
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    }
    if (DAT_100f6368 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    *(undefined4 *)(param_1 + 0x3d4) = 0;
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
LAB_100384b7:
  if ((*(int *)(param_1 + 0x98) <= *(int *)(param_1 + 0xa0)) &&
     (*(int *)(param_1 + 0x9c) <= *(int *)(param_1 + 0xa4))) {
    if (DAT_10051c4c == 0) {
      (**(code **)(DAT_100533dc + 0x20))();
    }
    else {
      FUN_100225a0(*(int *)(param_1 + 0x98),*(int *)(param_1 + 0x9c),*(int *)(param_1 + 0xa0));
    }
  }
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x78);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x7c);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x74);
  return;
}


