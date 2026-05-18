/*
 * Program: i76.exe
 * Function: bitmap_surface_blit_context_helper_004750d0
 * Entry: 004750d0
 * Signature: undefined __cdecl bitmap_surface_blit_context_helper_004750d0(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: bitmap surface blit context helper
   based on adjacent named subsystem context. */

void __cdecl bitmap_surface_blit_context_helper_004750d0(int param_1)

{
  if (*(int *)(param_1 + 0x60) == 1) {
    release_bitmap_surface_context((int *)(param_1 + 0x34));
  }
  if (DAT_0058dacc != (int *)0x0) {
    (**(code **)(*DAT_0058dacc + 8))(DAT_0058dacc);
  }
  if (DAT_0058dad0 != (int *)0x0) {
    (**(code **)(*DAT_0058dad0 + 8))(DAT_0058dad0);
  }
  if (DAT_0058daec != (int *)0x0) {
    if (DAT_0058dadc == 1) {
      (**(code **)(*DAT_0058daec + 0x80))(DAT_0058daec,0);
    }
    (**(code **)(*DAT_0058daec + 8))(DAT_0058daec);
    DAT_0058dadc = 0;
  }
  if (DAT_0058dae0 != (int *)0x0) {
    (**(code **)(*DAT_0058dae0 + 8))(DAT_0058dae0);
  }
  if (DAT_0058dad8 != (int *)0x0) {
    (**(code **)(*DAT_0058dad8 + 8))(DAT_0058dad8);
  }
  DAT_0058dad8 = (int *)0x0;
  DAT_0058dacc = (int *)0x0;
  DAT_0058dad0 = (int *)0x0;
  DAT_0058daec = (int *)0x0;
  DAT_0058dae0 = (int *)0x0;
  return;
}


