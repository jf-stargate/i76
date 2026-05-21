/*
 * Program: i76.exe
 * Function: recreate_direct3d_render_surfaces_for_mode
 * Entry: 00475b60
 * Signature: undefined4 __cdecl recreate_direct3d_render_surfaces_for_mode(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Releases and recreates D3D render/depth/viewport-style surfaces for a selected
   display mode. */

undefined4 __cdecl recreate_direct3d_render_surfaces_for_mode(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int *piVar5;
  int *piVar6;
  undefined1 *puVar7;
  uint unaff_EBX;
  int **ppiVar8;
  int *piVar9;
  undefined4 *puVar10;
  int *apiStack_52c [3];
  int iStack_50c;
  int iStack_508;
  int iStack_4f4;
  int aiStack_4ac [22];
  undefined1 auStack_454 [984];
  int iStack_7c;
  int *apiStack_74 [9];
  int iStack_50;
  int iStack_3c;
  
  if (param_2 == 0) {
    param_2 = 5;
  }
  if ((&DAT_004f9e08)[param_2 * 7] == 0) {
    return 0;
  }
  uVar1 = (&DAT_004f9e14)[param_2 * 7];
  uVar2 = (&DAT_004f9e18)[param_2 * 7];
  if (*(int *)(param_1 + 0x60) == 1) {
    apiStack_52c[2] = (int *)0x475bba;
    release_bitmap_surface_context((int *)(param_1 + 0x34));
  }
  if (DAT_0058dacc != (int *)0x0) {
    apiStack_52c[2] = (int *)0x475bcc;
    (**(code **)(*DAT_0058dacc + 8))();
  }
  if (DAT_0058dad0 != (int *)0x0) {
    apiStack_52c[2] = (int *)0x475bdb;
    (**(code **)(*DAT_0058dad0 + 8))();
  }
  if (DAT_0058daec != (int *)0x0) {
    if (DAT_0058dadc == 1) {
      apiStack_52c[2] = DAT_0058daec;
      apiStack_52c[1] = (int *)0x475bf7;
      (**(code **)(*DAT_0058daec + 0x80))();
    }
    apiStack_52c[2] = (int *)0x475c02;
    (**(code **)(*DAT_0058daec + 8))();
    DAT_0058dadc = 0;
  }
  if (DAT_0058dae0 != (int *)0x0) {
    apiStack_52c[2] = (int *)0x475c17;
    (**(code **)(*DAT_0058dae0 + 8))();
  }
  DAT_0058dacc = (int *)0x0;
  DAT_0058dad0 = (int *)0x0;
  DAT_0058daec = (int *)0x0;
  DAT_0058dae0 = (int *)0x0;
  apiStack_52c[0] = DAT_0058dad8;
  apiStack_52c[1] = (int *)uVar1;
  apiStack_52c[2] = (int *)uVar2;
  iVar3 = (**(code **)(*DAT_0058dad8 + 0x54))();
  if (iVar3 != 0) {
    return 0;
  }
  puVar10 = (undefined4 *)&stack0xfffffae4;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  iVar3 = (**(code **)(*DAT_0058dad8 + 0x18))(DAT_0058dad8,&stack0xfffffae4,&DAT_0058dae0,0);
  if (iVar3 != 0) {
    return 0;
  }
  ppiVar8 = apiStack_52c;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *ppiVar8 = (int *)0x0;
    ppiVar8 = ppiVar8 + 1;
  }
  apiStack_52c[2] = (int *)(&DAT_004f9e20)[param_2 * 7];
  apiStack_52c[0] = (int *)0x6c;
  apiStack_52c[1] = (int *)0x7;
  iVar3 = (**(code **)(*DAT_0058dad8 + 0x18))(DAT_0058dad8,apiStack_52c,&DAT_0058daec,0);
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = (**(code **)(*DAT_0058dad8 + 0x10))(DAT_0058dad8,0,&DAT_0058dad0,0);
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = (**(code **)(*DAT_0058dad0 + 0x20))(DAT_0058dad0,0,*(undefined4 *)(iStack_3c + 0xbc));
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = (**(code **)(*DAT_0058dae0 + 0x70))(DAT_0058dae0,DAT_0058dad0);
  if (iVar3 != 0) {
    return 0;
  }
  puVar4 = auStack_454 + 1;
  iVar3 = 0x100;
  puVar7 = (undefined1 *)(iStack_50 + 0xe9);
  do {
    puVar4[-1] = puVar7[-1];
    *puVar4 = *puVar7;
    puVar4[1] = puVar7[1];
    puVar4[2] = 4;
    puVar4 = puVar4 + 4;
    iVar3 = iVar3 + -1;
    puVar7 = puVar7 + 3;
  } while (iVar3 != 0);
  iVar3 = (**(code **)(*DAT_0058dad8 + 0x14))(DAT_0058dad8,0x44,auStack_454,&DAT_0058dacc,0);
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = (**(code **)(*DAT_0058dae0 + 0x7c))(DAT_0058dae0,DAT_0058dacc);
  if (iVar3 != 0) {
    return 0;
  }
  iVar3 = (**(code **)(*DAT_0058daec + 0x7c))(DAT_0058daec,DAT_0058dacc);
  piVar6 = apiStack_74[0];
  if (iVar3 != 0) {
    return 0;
  }
  if (DAT_0058dadc != 1) {
    DAT_0058dadc = 1;
    iVar3 = (**(code **)(*DAT_0058daec + 0x60))(DAT_0058daec);
    if (iVar3 != 0) {
      (**(code **)(*DAT_0058daec + 0x6c))(DAT_0058daec);
    }
    puVar10 = (undefined4 *)&stack0xfffffae4;
    for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar10 = 0;
      puVar10 = puVar10 + 1;
    }
    iVar3 = (**(code **)(*DAT_0058daec + 100))(DAT_0058daec,0,&stack0xfffffae4,1,0);
    if (iVar3 != 0) {
      DAT_0058dadc = 0;
      return 0;
    }
    piVar5 = (int *)construct_bitmap_surface_context(aiStack_4ac,iStack_508,unaff_EBX,iStack_4f4,0);
    piVar9 = piVar6;
    for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar9 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar9 = piVar9 + 1;
    }
    set_bitmap_surface_clip_rect(piVar6,0,0,iStack_50c,unaff_EBX);
  }
  if (DAT_0058dadc != 0) {
    DAT_0058dadc = 0;
    (**(code **)(*DAT_0058daec + 0x80))(DAT_0058daec,0);
  }
  piVar6 = (int *)construct_bitmap_surface_context
                            (aiStack_4ac,*apiStack_74[0] >> 3,(apiStack_74[0][1] << 3) >> 3,0,0);
  piVar5 = apiStack_74[0] + 0xd;
  for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar5 = piVar5 + 1;
  }
  if (apiStack_74[0][0x18] == 0) {
    apiStack_74[0][0x39] = 3;
    return 0;
  }
  (*(code *)apiStack_74[0][0x109])(apiStack_74,DAT_005dd32c);
  (*(code *)apiStack_74[0][0x108])(apiStack_74[0]);
  piVar6 = DAT_0058daec;
  _DAT_00643920 = DAT_0058dad8;
  _DAT_00643924 = DAT_0058dae0;
  _DAT_0064392c = DAT_0058dacc;
  _DAT_00643928 = DAT_0058daec;
  puVar10 = &DAT_00643930;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  DAT_00643930 = 0x6c;
  (**(code **)(*piVar6 + 0x58))(piVar6,&DAT_00643930);
  *(undefined4 *)(iStack_7c + 0xdc) = 0;
  return 1;
}


