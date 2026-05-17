/*
 * Program: i76.exe
 * Function: lock_and_begin_d3d_execute_buffer_batch
 * Entry: 00426f70
 * Signature: undefined4 __cdecl lock_and_begin_d3d_execute_buffer_batch(undefined4 * param_1)
 */


/* cgpt rename v8 display/d3d cluster: Locks or initializes a Direct3D execute buffer and emits the
   initial viewport/execute data records and pending render-state setup. */

undefined4 __cdecl lock_and_begin_d3d_execute_buffer_batch(undefined4 *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  int local_108;
  int local_104;
  undefined4 auStack_100 [64];
  
  if (param_1[5] != 0) {
    if (param_1[5] != 2) {
      local_114 = 0x14;
      local_110 = 1;
      local_10c = 0;
      local_108 = 0x2000;
      local_104 = 0;
      if (DAT_005fe578 != 0) {
        local_108 = DAT_005fe578;
      }
      (**(code **)(*(int *)*param_1 + 0x10))((int *)*param_1,&local_114);
      param_1[1] = local_104;
      iVar4 = DAT_005268a0 * 0x20;
      param_1[5] = 2;
      param_1[3] = iVar4 + local_104;
    }
    param_1[2] = param_1[1];
    param_1[4] = (undefined1 *)param_1[3];
    *(undefined1 *)param_1[3] = 9;
    *(undefined1 *)(param_1[4] + 1) = 0x10;
    *(undefined2 *)(param_1[4] + 2) = 1;
    DAT_0052676c = param_1[4] + 4;
    param_1[4] = DAT_0052676c;
    *(undefined4 *)param_1[4] = 2;
    *(undefined2 *)(param_1[4] + 4) = 0;
    *(undefined2 *)(param_1[4] + 6) = 0;
    *(int *)(param_1[4] + 8) = DAT_005268a0;
    *(undefined4 *)(param_1[4] + 0xc) = 0;
    uVar5 = 0;
    param_1[4] = param_1[4] + 0x10;
    if (DAT_005280a8 != 0) {
      DAT_005280a8 = 0;
      auStack_100[0] = 1;
      auStack_100[1] = 0;
      uVar5 = 2;
    }
    if (DAT_004ede74 != 1) {
      auStack_100[uVar5] = 9;
      auStack_100[uVar5 + 1] = 2;
      DAT_004ede74 = 1;
      uVar5 = uVar5 + 2;
    }
    if (DAT_004ede78 != 0) {
      if (DAT_004ede78 == 0x40) {
        auStack_100[uVar5] = 0x15;
        auStack_100[uVar5 + 1] = 2;
        uVar5 = uVar5 + 2;
      }
      DAT_004ede78 = 0;
      auStack_100[uVar5] = DAT_00608b80;
      auStack_100[uVar5 + 1] = 0;
      uVar5 = uVar5 + 2;
    }
    if (DAT_004ede7c != 0) {
      auStack_100[uVar5] = 0x11;
      auStack_100[uVar5 + 1] = 1;
      auStack_100[uVar5 + 2] = 0x12;
      auStack_100[uVar5 + 3] = 1;
      DAT_004ede7c = 0;
      uVar5 = uVar5 + 4;
    }
    if (DAT_005280ac != 0) {
      auStack_100[uVar5] = 3;
      auStack_100[uVar5 + 1] = 1;
      DAT_005280ac = 0;
      uVar5 = uVar5 + 2;
    }
    if (uVar5 != 0) {
      **(undefined1 **)(&DAT_00524778 + DAT_00526770 * 0x20) = 8;
      *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
      *(short *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = (short)(uVar5 >> 1);
      iVar4 = DAT_00526770;
      piVar2 = (int *)(&DAT_00524778 + DAT_00526770 * 0x20);
      *piVar2 = *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4;
      if (uVar5 != 0) {
        puVar6 = auStack_100 + 1;
        uVar5 = uVar5 + 1 >> 1;
        do {
          *(undefined4 *)*piVar2 = puVar6[-1];
          uVar1 = *puVar6;
          puVar6 = puVar6 + 2;
          *(undefined4 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4) = uVar1;
          iVar4 = DAT_00526770;
          iVar3 = DAT_00526770 * 0x20;
          *(int *)(&DAT_00524778 + iVar3) = *(int *)(&DAT_00524778 + iVar3) + 8;
          piVar2 = (int *)(&DAT_00524778 + iVar3);
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
      if (((uint)*(undefined1 **)(&DAT_00524778 + iVar4 * 0x20) & 7) == 0) {
        **(undefined1 **)(&DAT_00524778 + iVar4 * 0x20) = 3;
        *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
        *(undefined2 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = 0;
        *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) =
             *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4;
      }
    }
    param_1[6] = 0;
    param_1[7] = 0xffffffff;
    return 1;
  }
  return 0;
}


