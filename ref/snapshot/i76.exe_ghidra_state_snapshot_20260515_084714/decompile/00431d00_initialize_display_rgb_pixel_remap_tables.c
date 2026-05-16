/*
 * Program: i76.exe
 * Function: initialize_display_rgb_pixel_remap_tables
 * Entry: 00431d00
 * Signature: undefined4 __stdcall initialize_display_rgb_pixel_remap_tables(void)
 */


/* cgpt readability rename v13 set A: Builds display RGB mask/remap lookup tables for the active
   pixel format. */

undefined4 initialize_display_rgb_pixel_remap_tables(void)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  int *piVar4;
  byte *pbVar5;
  int iVar6;
  undefined1 *puVar7;
  short *psVar8;
  short *psVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  uint in_stack_0000004c;
  uint in_stack_00000050;
  uint in_stack_00000054;
  short sStack00000060;
  int in_stack_00001268;
  undefined2 *in_stack_00001274;
  
  zfsf_error_context_helper_004ba0a0();
  puVar11 = (undefined4 *)register0x00000010;
  for (iVar6 = 0x1b; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  puVar7 = &stack0x0000026d;
  iVar6 = (int)&DAT_00608680 - (int)in_stack_00001274;
  iVar12 = 0x100;
  do {
    puVar7[-1] = *(undefined1 *)in_stack_00001274;
    uVar3 = *in_stack_00001274;
    *puVar7 = *(undefined1 *)((int)in_stack_00001274 + 1);
    puVar7[1] = *(undefined1 *)(in_stack_00001274 + 1);
    puVar2 = (undefined2 *)(iVar6 + (int)in_stack_00001274);
    puVar7[2] = 4;
    puVar7 = puVar7 + 4;
    *puVar2 = uVar3;
    puVar1 = in_stack_00001274 + 1;
    in_stack_00001274 = (undefined2 *)((int)in_stack_00001274 + 3);
    iVar12 = iVar12 + -1;
    *(undefined1 *)(puVar2 + 1) = *(undefined1 *)puVar1;
    piVar4 = DAT_006080c4;
  } while (iVar12 != 0);
  DAT_0060897d = 0;
  DAT_0060897e = 0;
  DAT_0060897f = 0;
  if (DAT_00608408 != 8) {
    iVar6 = (**(code **)(*DAT_006080c4 + 0x60))();
    if (iVar6 != 0) {
      (**(code **)(*piVar4 + 0x6c))();
    }
    (**(code **)(*piVar4 + 0x58))();
    build_8bit_to_pixel_mask_lookup_table(in_stack_0000004c,(int *)&stack0x00000a60);
    build_8bit_to_pixel_mask_lookup_table(in_stack_00000050,(int *)&stack0x00000660);
    build_8bit_to_pixel_mask_lookup_table(in_stack_00000054,(int *)&stack0x00000e60);
    pbVar5 = (byte *)(in_stack_00001268 + 2);
    psVar9 = &DAT_00608460;
    do {
      psVar8 = psVar9 + 1;
      *psVar9 = (short)*(undefined4 *)(&stack0x00000e60 + (uint)*pbVar5 * 4) +
                (short)*(undefined4 *)(&stack0x00000660 + (uint)pbVar5[-1] * 4) +
                (short)*(undefined4 *)(&stack0x00000a60 + (uint)pbVar5[-2] * 4);
      pbVar5 = pbVar5 + 3;
      psVar9 = psVar8;
    } while ((int)psVar8 < 0x608660);
    DAT_0060865e = 0;
    DAT_00608460 = 0;
    build_8bit_to_pixel_mask_lookup_table(0xf800,(int *)&stack0x00000a60);
    build_8bit_to_pixel_mask_lookup_table(0x7e0,(int *)&stack0x00000660);
    build_8bit_to_pixel_mask_lookup_table(0x1f,(int *)&stack0x00000e60);
    iVar6 = 0x100;
    pbVar5 = (byte *)(in_stack_00001268 + 2);
    psVar9 = &stack0x00000060;
    do {
      iVar6 = iVar6 + -1;
      *psVar9 = (short)*(undefined4 *)(&stack0x00000e60 + (uint)*pbVar5 * 4) +
                (short)*(undefined4 *)(&stack0x00000660 + (uint)pbVar5[-1] * 4) +
                (short)*(undefined4 *)(&stack0x00000a60 + (uint)pbVar5[-2] * 4);
      pbVar5 = pbVar5 + 3;
      psVar9 = psVar9 + 1;
    } while (iVar6 != 0);
    sStack00000060 = 0;
    *DAT_0052b91c = 0x100;
    puVar10 = (undefined4 *)&stack0x00000060;
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


