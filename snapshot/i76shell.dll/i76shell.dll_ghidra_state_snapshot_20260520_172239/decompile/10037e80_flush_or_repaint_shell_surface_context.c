/*
 * Program: i76shell.dll
 * Function: flush_or_repaint_shell_surface_context
 * Entry: 10037e80
 * Signature: undefined __fastcall flush_or_repaint_shell_surface_context(int param_1)
 */


/* i76shell first-pass rename
   old_name: FUN_10037e80
   suggested_name: shell_ui_object_method_high_fan_in
   basis: High-fan-in shell/UI object method; name intentionally cautious. */

void __fastcall flush_or_repaint_shell_surface_context(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  
  if (*(int *)(param_1 + 0x98) < *(int *)(param_1 + 0x70)) {
    *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x70);
  }
  if (*(int *)(param_1 + 0x9c) < *(int *)(param_1 + 0x74)) {
    *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x74);
  }
  if (*(int *)(param_1 + 0x78) < *(int *)(param_1 + 0xa0)) {
    *(int *)(param_1 + 0xa0) = *(int *)(param_1 + 0x78);
  }
  if (*(int *)(param_1 + 0x7c) < *(int *)(param_1 + 0xa4)) {
    *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0x7c);
  }
  if (*(int *)(param_1 + 0x20) == 0) {
    if (*(int *)(param_1 + 0x98) <= *(int *)(param_1 + 0xa0)) {
      if (*(int *)(param_1 + 0x9c) <= *(int *)(param_1 + 0xa4)) {
        if (DAT_10051c40 == 0) {
          (**(code **)(DAT_100533dc + 0x1c))();
        }
        else {
          FUN_100224d0(*(int *)(param_1 + 0x98),*(int *)(param_1 + 0x9c),*(int *)(param_1 + 0xa0),
                       *(int *)(param_1 + 0xa4));
        }
      }
    }
    goto LAB_100382b6;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    if (DAT_100f5770 != 0) {
      puVar5 = &DAT_100f5368;
      for (iVar2 = 0xc0; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      (**(code **)(DAT_100533d8 + 0x14))(0,0x100,&DAT_100f5368,1);
      (**(code **)(DAT_100533dc + 0x18))();
      (**(code **)(DAT_100533d8 + 0x14))(0,0x100,param_1 + 0xbc,*(undefined4 *)(param_1 + 0x24));
      (**(code **)(DAT_100533dc + 0x18))();
      DAT_100f5770 = 0;
      *(undefined4 *)(param_1 + 0x20) = 0;
      goto LAB_100382b6;
    }
    if (DAT_100f6368 == 0) {
LAB_10037f91:
      FUN_1003c785((int *)(param_1 + 0x6c),0);
      FUN_1003c785((int *)(param_1 + 0xa8),0);
      if (DAT_100f6368 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
    }
    else {
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
      iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar2 == 0) {
        uVar1 = *DAT_100533e8;
        *(undefined4 *)(param_1 + 0x30) = uVar1;
        **(undefined4 **)(param_1 + 0x6c) = uVar1;
        goto LAB_10037f91;
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
    uVar3 = *(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc);
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
    uVar3 = *(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc);
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
    (**(code **)(DAT_100533dc + 0x18))();
    *(undefined4 *)(param_1 + 0x20) = 0;
    goto LAB_100382b6;
  }
  if (*(int *)(param_1 + 0x3d4) == 0) {
    (**(code **)(DAT_100533d8 + 0x14))(0,0x100,param_1 + 0xbc,0);
    (**(code **)(DAT_100533dc + 0x1c))
              (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x74),
               *(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x20) = 0;
    goto LAB_100382b6;
  }
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
  uVar3 = *(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc);
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
LAB_10038140:
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
    if (DAT_100f6368 == 0) goto LAB_10038140;
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar2 == 0) {
      uVar1 = *DAT_100533e8;
      *(undefined4 *)(param_1 + 0x30) = uVar1;
      **(undefined4 **)(param_1 + 0x6c) = uVar1;
      goto LAB_10038140;
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
  uVar3 = *(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc);
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
  uVar3 = *(int *)(param_1 + 0x3c0) * *(int *)(param_1 + 0x3bc);
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
  (**(code **)(DAT_100533dc + 0x18))();
  *(undefined4 *)(param_1 + 0x3d4) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
LAB_100382b6:
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x78);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x7c);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x74);
  return;
}


