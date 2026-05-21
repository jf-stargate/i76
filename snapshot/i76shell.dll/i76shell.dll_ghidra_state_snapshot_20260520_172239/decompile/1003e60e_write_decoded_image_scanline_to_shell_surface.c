/*
 * Program: i76shell.dll
 * Function: write_decoded_image_scanline_to_shell_surface
 * Entry: 1003e60e
 * Signature: undefined4 * __cdecl write_decoded_image_scanline_to_shell_surface(int * param_1, int param_2, undefined4 * param_3, undefined1 * param_4)
 */


undefined4 * __cdecl
write_decoded_image_scanline_to_shell_surface
          (int *param_1,int param_2,undefined4 *param_3,undefined1 *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  bool bVar12;
  int local_8;
  
  piVar1 = (int *)*param_1;
  iVar2 = piVar1[1];
  if ((iVar2 + 1 == 0 || iVar2 < -1) || (iVar3 = piVar1[2], iVar3 < 0)) {
    return (undefined4 *)0xffffffff;
  }
  local_8 = param_1[1];
  iVar5 = local_8;
  if (local_8 < 1) {
    iVar5 = 0;
  }
  iVar4 = param_1[2];
  iVar6 = iVar4;
  if (iVar4 < 1) {
    iVar6 = 0;
  }
  iVar7 = param_1[3];
  if (iVar2 <= param_1[3]) {
    iVar7 = iVar2;
  }
  iVar8 = param_1[4];
  if (iVar3 <= param_1[4]) {
    iVar8 = iVar3;
  }
  if ((iVar5 <= iVar7) && (iVar6 <= iVar8)) {
    iVar4 = param_2 + iVar4;
    puVar9 = (undefined4 *)(((iVar7 - local_8) + 1) - (int)param_4);
    if ((-1 < (int)puVar9) ||
       (bVar12 = SCARRY4((int)param_4,(int)puVar9), param_4 = param_4 + (int)puVar9,
       param_4 != (undefined1 *)0x0 && bVar12 == (int)param_4 < 0)) {
      puVar9 = (undefined4 *)(local_8 - iVar5);
      if ((int)puVar9 < 0) {
        bVar12 = SCARRY4((int)param_4,(int)puVar9);
        param_4 = param_4 + (int)puVar9;
        if (param_4 == (undefined1 *)0x0 || bVar12 != (int)param_4 < 0) {
          return puVar9;
        }
        param_3 = (undefined4 *)((int)param_3 - (int)puVar9);
        local_8 = local_8 - (int)puVar9;
      }
      puVar9 = (undefined4 *)(iVar8 - iVar4);
      if ((-1 < (int)puVar9) && (puVar9 = (undefined4 *)(iVar4 - iVar6), -1 < (int)puVar9)) {
        puVar9 = (undefined4 *)(iVar4 * (iVar2 + 1) + *piVar1 + local_8);
        puVar11 = puVar9;
        for (uVar10 = (uint)param_4 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined1 *)puVar11 = *(undefined1 *)param_3;
          param_3 = (undefined4 *)((int)param_3 + 1);
          puVar11 = (undefined4 *)((int)puVar11 + 1);
        }
        for (uVar10 = (uint)param_4 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *puVar11 = *param_3;
          param_3 = param_3 + 1;
          puVar11 = puVar11 + 1;
        }
      }
    }
    return puVar9;
  }
  return (undefined4 *)0xfffffffe;
}


