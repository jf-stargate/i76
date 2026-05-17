/*
 * Program: i76.exe
 * Function: vehicle_specials_display_cleanup_helper_00467810
 * Entry: 00467810
 * Signature: undefined4 * __stdcall vehicle_specials_display_cleanup_helper_00467810(void)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials display cleanup
   helper based on adjacent named subsystem context. */

undefined4 * vehicle_specials_display_cleanup_helper_00467810(void)

{
  int iVar1;
  int iVar2;
  
  if (DAT_0054b9cc != 0) {
    if (DAT_004f863c == 0) {
      iVar2 = 0x25;
      iVar1 = 0x6a;
    }
    else {
      iVar2 = 0x4e;
      iVar1 = 0xb6;
    }
    set_bitmap_surface_clip_rect(&DAT_0054b9b8,0,0,iVar1,iVar2);
    return &DAT_0054b9b8;
  }
  return (undefined4 *)0x0;
}


