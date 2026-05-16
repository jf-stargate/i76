/*
 * Program: i76.exe
 * Function: radar_display_update_context_helper_004615f0
 * Entry: 004615f0
 * Signature: int * __cdecl radar_display_update_context_helper_004615f0(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: radar display update context helper
   based on prior focused closure context. */

int * __cdecl radar_display_update_context_helper_004615f0(int param_1)

{
  int iVar1;
  
  if ((((param_1 != 0) && (*(int *)(param_1 + 0x70) != 0)) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     ((iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0 && (*(int *)(iVar1 + 0x94) != 0)))) {
    set_bitmap_surface_clip_rect((int *)(iVar1 + 0x80),0,0,0xad,0x76);
    return (int *)(iVar1 + 0x80);
  }
  return (int *)0x0;
}


