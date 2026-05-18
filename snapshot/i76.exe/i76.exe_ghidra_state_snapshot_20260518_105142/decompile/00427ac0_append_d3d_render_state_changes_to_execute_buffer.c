/*
 * Program: i76.exe
 * Function: append_d3d_render_state_changes_to_execute_buffer
 * Entry: 00427ac0
 * Signature: undefined __cdecl append_d3d_render_state_changes_to_execute_buffer(int param_1, uint param_2)
 */


/* cgpt rename v8 display/d3d cluster: Appends render-state change instructions to the current
   Direct3D execute buffer when shade/texture/fill state globals change. */

void __cdecl append_d3d_render_state_changes_to_execute_buffer(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int local_100 [64];
  
  iVar1 = 0;
  if (param_1 != DAT_005280a8) {
    DAT_005280a8 = param_1;
    local_100[0] = 1;
    local_100[1] = param_1;
    iVar1 = 2;
  }
  uVar3 = param_2 & 1;
  if (uVar3 != DAT_004ede74) {
    local_100[iVar1] = 9;
    local_100[iVar1 + 1] = 1;
    if (uVar3 != 0) {
      local_100[iVar1 + 1] = 2;
    }
    iVar1 = iVar1 + 2;
    DAT_004ede74 = uVar3;
  }
  uVar3 = param_2 & 0x74;
  if (uVar3 != DAT_004ede78) {
    if (DAT_004ede78 == 0x40) {
      local_100[iVar1] = 0x15;
      local_100[iVar1 + 1] = 2;
      iVar1 = iVar1 + 2;
    }
    if (uVar3 == 0) {
      local_100[iVar1] = DAT_00608b80;
      local_100[iVar1 + 1] = 0;
    }
    else {
      iVar2 = iVar1;
      if (DAT_004ede78 == 0) {
        local_100[iVar1] = DAT_00608b80;
        local_100[iVar1 + 1] = 1;
        iVar2 = iVar1 + 2;
      }
      if ((param_2 & 0x20) == 0) {
        if ((param_2 & 0x40) == 0) {
          local_100[iVar2] = 0x13;
          if ((param_2 & 4) == 0) {
            local_100[iVar2 + 1] = 9;
            iVar1 = iVar2 + 2;
            local_100[iVar1] = 0x14;
            local_100[iVar2 + 3] = 2;
          }
          else {
            local_100[iVar2 + 1] = 5;
            iVar1 = iVar2 + 2;
            local_100[iVar1] = 0x14;
            local_100[iVar2 + 3] = 6;
          }
        }
        else {
          local_100[iVar2] = 0x15;
          local_100[iVar2 + 1] = 4;
          local_100[iVar2 + 2] = 0x13;
          local_100[iVar2 + 3] = 5;
          iVar1 = iVar2 + 4;
          local_100[iVar1] = 0x14;
          local_100[iVar2 + 5] = 2;
        }
      }
      else {
        local_100[iVar2] = 0x13;
        local_100[iVar2 + 1] = 9;
        iVar1 = iVar2 + 2;
        local_100[iVar1] = 0x14;
        local_100[iVar2 + 3] = 1;
      }
    }
    iVar1 = iVar1 + 2;
    DAT_004ede78 = uVar3;
  }
  if ((DAT_005fe55c & 2) == 0) {
    param_2 = param_2 & 0xfffffffd;
  }
  uVar3 = param_2 & 2;
  if (uVar3 != DAT_004ede7c) {
    local_100[iVar1] = 0x11;
    if (uVar3 == 0) {
      local_100[iVar1 + 1] = 1;
      local_100[iVar1 + 2] = 0x12;
      local_100[iVar1 + 3] = 1;
    }
    else {
      local_100[iVar1 + 1] = 2;
      local_100[iVar1 + 2] = 0x12;
      local_100[iVar1 + 3] = 2;
    }
    iVar1 = iVar1 + 4;
    DAT_004ede7c = uVar3;
  }
  if ((DAT_005fe564 & 3) == 0) {
    param_2 = 0;
  }
  uVar3 = param_2 & 8;
  if (uVar3 != DAT_005280ac) {
    if (uVar3 == 0) {
      local_100[iVar1] = 3;
      local_100[iVar1 + 1] = 1;
    }
    else {
      local_100[iVar1] = 3;
      local_100[iVar1 + 1] = 3;
    }
    iVar1 = iVar1 + 2;
    DAT_005280ac = uVar3;
  }
  if (iVar1 != 0) {
    **(undefined1 **)(&DAT_00524778 + DAT_00526770 * 0x20) = 8;
    *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
    *(ushort *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = (ushort)iVar1 >> 1;
    iVar2 = DAT_00526770;
    piVar4 = (int *)(&DAT_00524778 + DAT_00526770 * 0x20);
    *piVar4 = *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4;
    if (iVar1 != 0) {
      piVar5 = local_100 + 1;
      uVar3 = iVar1 + 1U >> 1;
      do {
        *(int *)*piVar4 = piVar5[-1];
        iVar1 = *piVar5;
        piVar5 = piVar5 + 2;
        *(int *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4) = iVar1;
        iVar2 = DAT_00526770;
        piVar4 = (int *)(&DAT_00524778 + DAT_00526770 * 0x20);
        uVar3 = uVar3 - 1;
        *piVar4 = *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 8;
      } while (uVar3 != 0);
    }
    if (((uint)*(undefined1 **)(&DAT_00524778 + iVar2 * 0x20) & 7) == 0) {
      **(undefined1 **)(&DAT_00524778 + iVar2 * 0x20) = 3;
      *(undefined1 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 1) = 8;
      *(undefined2 *)(*(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 2) = 0;
      *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) =
           *(int *)(&DAT_00524778 + DAT_00526770 * 0x20) + 4;
    }
  }
  return;
}


