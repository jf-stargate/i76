/*
 * Program: i76.exe
 * Function: initialize_display_palette_and_pixel_remap_tables
 * Entry: 0042d6a0
 * Signature: undefined4 __cdecl initialize_display_palette_and_pixel_remap_tables(undefined4 param_1, undefined2 * param_2)
 */


/* cgpt rename v8 display/d3d cluster: Initializes DirectDraw palette entries, game palette mirror
   globals, and RGB pixel-format remap tables for the current display mode. */

undefined4 __cdecl
initialize_display_palette_and_pixel_remap_tables(undefined4 param_1,undefined2 *param_2)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  int *piVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  undefined4 local_46c [27];
  undefined1 local_400 [1020];
  undefined1 uStack_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  
  DAT_00608b80 = (-(uint)(DAT_005fffac != 0) & 0xfffffff2) + 0x29;
  puVar8 = local_46c;
  for (iVar6 = 0x1b; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  puVar7 = local_400 + 1;
  iVar6 = 0x100;
  puVar4 = param_2;
  do {
    puVar7[-1] = *(undefined1 *)puVar4;
    uVar3 = *puVar4;
    *puVar7 = *(undefined1 *)((int)puVar4 + 1);
    puVar7[1] = *(undefined1 *)(puVar4 + 1);
    puVar2 = (undefined2 *)(((int)&DAT_00608680 - (int)param_2) + (int)puVar4);
    puVar7[2] = 4;
    puVar7 = puVar7 + 4;
    *puVar2 = uVar3;
    puVar1 = puVar4 + 1;
    puVar4 = (undefined2 *)((int)puVar4 + 3);
    iVar6 = iVar6 + -1;
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)puVar1;
  } while (iVar6 != 0);
  local_400[0] = 1;
  local_400[1] = 1;
  local_400[2] = 1;
  local_400[3] = 4;
  DAT_0060897d = 0;
  DAT_0060897e = 0;
  DAT_0060897f = 0;
  piVar5 = DAT_006080c8;
  if (DAT_00608408 != 8) {
    build_display_pixel_format_palette_remap_tables((int)param_2,(ushort *)&DAT_00608980,1,0x5fff90)
    ;
    piVar5 = DAT_006080c4;
    local_46c[0] = 0x6c;
    iVar6 = (**(code **)(*DAT_006080c4 + 0x60))(DAT_006080c4);
    if (iVar6 != 0) {
      (**(code **)(*piVar5 + 0x6c))(piVar5);
    }
    (**(code **)(*piVar5 + 0x58))(piVar5,&stack0xfffffb90);
    build_display_pixel_format_palette_remap_tables((int)param_2,&DAT_00608460,0,0x5fff10);
    uStack_4 = 0;
    uStack_3 = 0;
    uStack_2 = 0;
    piVar5 = DAT_006080cc;
    if (DAT_005fff34 != 1) {
      return 1;
    }
  }
  if ((piVar5 != (int *)0x0) &&
     (iVar6 = (**(code **)(*piVar5 + 0x18))(piVar5,0,0,0x100,local_400), iVar6 != 0)) {
    return 0;
  }
  return 1;
}


