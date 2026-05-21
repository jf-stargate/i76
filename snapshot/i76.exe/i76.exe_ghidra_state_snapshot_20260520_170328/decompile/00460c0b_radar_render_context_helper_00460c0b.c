/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460c0b
 * Entry: 00460c0b
 * Signature: undefined __stdcall radar_render_context_helper_00460c0b(void)
 */


/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460c0b. Shorten
   readability label. */

void radar_render_context_helper_00460c0b(void)

{
  int *unaff_EBX;
  int unaff_EBP;
  
  projection_or_clip_context_helper_0047a1b0(*(int **)(unaff_EBP + -0x1e8),0x54ad48);
  matrix_identity_or_copy_context_helper_00479740(1,0xff);
  DAT_0063b2bf = DAT_005dd328;
  blit_bitmap_surface_context_clipped_with_palette_blend
            (unaff_EBX,&DAT_0054b030,0,(uint *)0x0,(uint *)0x1);
  DAT_0063b2bf = 0xff;
  matrix_identity_or_copy_context_helper_00479740(1,1);
  ExceptionList = *(void **)(unaff_EBP + -0x10);
  return;
}


