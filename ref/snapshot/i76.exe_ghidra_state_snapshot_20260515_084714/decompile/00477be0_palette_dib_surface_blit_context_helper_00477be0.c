/*
 * Program: i76.exe
 * Function: palette_dib_surface_blit_context_helper_00477be0
 * Entry: 00477be0
 * Signature: undefined __stdcall palette_dib_surface_blit_context_helper_00477be0(void)
 */


/* cgpt readability rename set D v16: Readability pass set D: palette dib surface blit context
   helper based on adjacent named subsystem context. */

void palette_dib_surface_blit_context_helper_00477be0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  release_resource_file_reference((&PTR_s_nk_1mon1_map_004fa0b4)[DAT_0058db00 * 5]);
  puVar2 = &DAT_0058db00;
  for (iVar1 = 0x3621; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  DAT_006435e0 = 0;
  return;
}


