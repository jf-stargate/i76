/*
 * Program: i76.exe
 * Function: hud_bitmap_quad_render_context_helper_0045c330
 * Entry: 0045c330
 * Signature: undefined __cdecl hud_bitmap_quad_render_context_helper_0045c330(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: hud bitmap quad render context helper
   based on prior focused closure context. */

void __cdecl hud_bitmap_quad_render_context_helper_0045c330(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(int *)(param_1 + 0x70) = param_1;
    iVar1 = *(int *)(param_1 + 100);
    DAT_0054ac70 = iVar1;
    for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x60)) {
      *(undefined4 *)(iVar1 + 0x6c) = 5;
      *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) | 0x40;
    }
  }
  return;
}


