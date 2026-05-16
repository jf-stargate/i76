/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460bfe
 * Entry: 00460bfe
 * Signature: undefined __stdcall radar_render_context_helper_00460bfe(void)
 */


/* WARNING: Stack frame is not setup normally: Input value of stackpointer is not used */
/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460bfe. Shorten
   readability label. */

void radar_render_context_helper_00460bfe(void)

{
  int iVar1;
  undefined4 uVar2;
  int unaff_EBP;
  
  iVar1 = *(int *)(unaff_EBP + -0x18);
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  uVar2 = *(undefined4 *)(unaff_EBP + -0x4c);
  *(undefined1 **)(iVar1 + -4) = &DAT_0054ad48;
  *(undefined4 *)(iVar1 + -8) = *(undefined4 *)(unaff_EBP + -0x1e8);
  *(undefined4 *)(iVar1 + -0xc) = 0x460c1c;
  projection_or_clip_context_helper_0047a1b0(*(int **)(iVar1 + -8),*(int *)(iVar1 + -4));
  *(undefined4 *)(iVar1 + -4) = 0xff;
  *(undefined4 *)(iVar1 + -8) = 1;
  *(undefined4 *)(iVar1 + -0xc) = 0x460c2b;
  matrix_identity_or_copy_context_helper_00479740(*(uint *)(iVar1 + -8),*(undefined1 *)(iVar1 + -4))
  ;
  DAT_0063b2bf = DAT_005dd328;
  *(undefined4 *)(iVar1 + -4) = 1;
  *(undefined4 *)(iVar1 + -8) = 0;
  *(undefined4 *)(iVar1 + -0xc) = 0;
  *(undefined4 **)(iVar1 + -0x10) = &DAT_0054b030;
  *(undefined4 *)(iVar1 + -0x14) = uVar2;
  *(undefined4 *)(iVar1 + -0x18) = 0x460c4b;
  blit_bitmap_surface_context_clipped_with_palette_blend
            (*(int **)(iVar1 + -0x14),*(int **)(iVar1 + -0x10),*(int *)(iVar1 + -0xc),
             *(uint **)(iVar1 + -8),*(uint **)(iVar1 + -4));
  DAT_0063b2bf = 0xff;
  *(undefined4 *)(iVar1 + -4) = 1;
  *(undefined4 *)(iVar1 + -8) = 1;
  *(undefined4 *)(iVar1 + -0xc) = 0x460c5e;
  matrix_identity_or_copy_context_helper_00479740(*(uint *)(iVar1 + -8),*(undefined1 *)(iVar1 + -4))
  ;
  ExceptionList = *(void **)(unaff_EBP + -0x10);
  return;
}


