/*
 * Program: i76.exe
 * Function: restore_or_acquire_directdraw_surface_if_needed
 * Entry: 0042dd00
 * Signature: undefined __stdcall restore_or_acquire_directdraw_surface_if_needed(void)
 */


/* [cgpt i76.exe main runtime loop rename v22; confidence=MEDIUM] Small repeated frame-phase helper
   that calls the DirectDraw surface vtable method at +0x2c when a pending restore flag is set.
   old_name: FUN_0042dd00 */

void restore_or_acquire_directdraw_surface_if_needed(void)

{
  int iVar1;
  
  if (DAT_005280d8 != 0) {
    iVar1 = (**(code **)(*DAT_006080c0 + 0x2c))(DAT_006080c0,0,0);
    if (iVar1 != -0x7789fde4) {
      DAT_005280d8 = 0;
    }
  }
  return;
}


