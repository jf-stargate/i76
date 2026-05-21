/*
 * Program: i76.exe
 * Function: register_d3d_device_driver_descriptor
 * Entry: 0042fdd0
 * Signature: undefined4 __stdcall register_d3d_device_driver_descriptor(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Copies and normalizes a D3D driver/device descriptor into the
   global enumerated-driver table. */

undefined4 register_d3d_device_driver_descriptor(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  
  puVar4 = &DAT_005fe5c8 + DAT_005fe5c0 * 0x20;
  for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  puVar4 = param_1;
  puVar6 = &DAT_005fe5c8 + DAT_005fe5c0 * 0x20;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  if ((param_1[0x13] & 0x20) == 0) {
    if ((param_1[0x13] & 8) != 0) {
      return 1;
    }
    if (param_1[0x15] != 0x10) {
      return 1;
    }
    iVar2 = 0;
    *(undefined4 *)(&DAT_005fe634 + DAT_005fe5c0 * 0x80) = 0;
    *(undefined4 *)(&DAT_005fe644 + DAT_005fe5c0 * 0x80) = 0;
    for (uVar1 = param_1[0x16]; (uVar1 & 1) == 0; uVar1 = uVar1 >> 1) {
    }
    iVar5 = 0;
    for (; (uVar1 & 1) != 0; uVar1 = uVar1 >> 1) {
      iVar5 = iVar5 + 1;
    }
    for (uVar1 = param_1[0x17]; (uVar1 & 1) == 0; uVar1 = uVar1 >> 1) {
    }
    iVar3 = 0;
    for (; (uVar1 & 1) != 0; uVar1 = uVar1 >> 1) {
      iVar3 = iVar3 + 1;
    }
    for (uVar1 = param_1[0x18]; (uVar1 & 1) == 0; uVar1 = uVar1 >> 1) {
    }
    do {
      uVar1 = uVar1 >> 1;
      iVar2 = iVar2 + 1;
    } while ((uVar1 & 1) != 0);
    *(int *)(&DAT_005fe638 + DAT_005fe5c0 * 0x80) = iVar5;
    *(int *)(&DAT_005fe640 + DAT_005fe5c0 * 0x80) = iVar3;
    *(int *)(&DAT_005fe63c + DAT_005fe5c0 * 0x80) = iVar2;
  }
  else {
    *(undefined4 *)(&DAT_005fe634 + DAT_005fe5c0 * 0x80) = 1;
    *(undefined4 *)(&DAT_005fe644 + DAT_005fe5c0 * 0x80) = 8;
  }
  DAT_005fe5c0 = DAT_005fe5c0 + 1;
  return 1;
}


