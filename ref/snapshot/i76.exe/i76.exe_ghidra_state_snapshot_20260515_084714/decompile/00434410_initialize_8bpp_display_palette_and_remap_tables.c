/*
 * Program: i76.exe
 * Function: initialize_8bpp_display_palette_and_remap_tables
 * Entry: 00434410
 * Signature: undefined4 __stdcall initialize_8bpp_display_palette_and_remap_tables(void)
 */


/* cgpt label refinement v18: was initialize_8bpp_display_palette_remap_tables. Clarify that this
   belongs to palette plus remap table setup. */

undefined4 initialize_8bpp_display_palette_and_remap_tables(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  byte *pbVar5;
  int iVar6;
  undefined1 *puVar7;
  short *psVar8;
  short *psVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined1 uStack0000006c;
  undefined1 uStack0000006d;
  undefined1 uStack0000006e;
  undefined1 uStack0000006f;
  undefined2 *in_stack_00001074;
  
  zfsf_error_context_helper_004ba0a0();
  puVar11 = (undefined4 *)register0x00000010;
  for (iVar6 = 0x1b; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  puVar7 = &stack0x0000006d;
  iVar6 = 0x100;
  puVar4 = in_stack_00001074;
  do {
    puVar7[-1] = *(undefined1 *)puVar4;
    uVar3 = *puVar4;
    *puVar7 = *(undefined1 *)((int)puVar4 + 1);
    puVar7[1] = *(undefined1 *)(puVar4 + 1);
    puVar2 = (undefined2 *)(((int)&DAT_00608680 - (int)in_stack_00001074) + (int)puVar4);
    puVar7[2] = 4;
    puVar7 = puVar7 + 4;
    *puVar2 = uVar3;
    puVar1 = puVar4 + 1;
    puVar4 = (undefined2 *)((int)puVar4 + 3);
    iVar6 = iVar6 + -1;
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)puVar1;
  } while (iVar6 != 0);
  uStack0000006c = 1;
  uStack0000006d = 1;
  uStack0000006e = 1;
  uStack0000006f = 4;
  DAT_0060897d = 0;
  DAT_0060897e = 0;
  DAT_0060897f = 0;
  if (DAT_00608408 != 8) {
    build_8bit_to_pixel_mask_lookup_table(0xf800,(int *)&stack0x0000046c);
    build_8bit_to_pixel_mask_lookup_table(0x7e0,(int *)&stack0x0000086c);
    build_8bit_to_pixel_mask_lookup_table(0x1f,(int *)&stack0x00000c6c);
    pbVar5 = (byte *)(in_stack_00001074 + 1);
    psVar8 = &DAT_00608460;
    do {
      psVar9 = psVar8 + 1;
      *psVar8 = (short)*(undefined4 *)(&stack0x00000c6c + (uint)*pbVar5 * 4) +
                (short)*(undefined4 *)(&stack0x0000086c + (uint)pbVar5[-1] * 4) +
                (short)*(undefined4 *)(&stack0x0000046c + (uint)pbVar5[-2] * 4);
      pbVar5 = pbVar5 + 3;
      psVar8 = psVar9;
    } while ((int)psVar9 < 0x608660);
    DAT_0060865e = 0;
    DAT_00608460 = 0;
    *DAT_0052b91c = 0x100;
    puVar10 = (undefined4 *)&DAT_00608460;
    puVar11 = DAT_0052b91c;
    for (iVar6 = 0x80; puVar11 = puVar11 + 1, iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar11 = *puVar10;
      puVar10 = puVar10 + 1;
    }
    return 1;
  }
  if (DAT_006080c8 != (int *)0x0) {
    iVar6 = (**(code **)(*DAT_006080c8 + 0x18))();
    if (iVar6 != 0) {
      return 0;
    }
  }
  return 1;
}


