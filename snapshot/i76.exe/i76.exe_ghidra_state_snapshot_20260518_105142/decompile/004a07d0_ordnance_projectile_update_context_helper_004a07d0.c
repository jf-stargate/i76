/*
 * Program: i76.exe
 * Function: ordnance_projectile_update_context_helper_004a07d0
 * Entry: 004a07d0
 * Signature: undefined4 __cdecl ordnance_projectile_update_context_helper_004a07d0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: ordnance projectile update context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl ordnance_projectile_update_context_helper_004a07d0(int param_1)

{
  if ((DAT_005a8108 == 0) && (_DAT_004bea34 <= *(float *)(*(int *)(param_1 + 0x70) + 4))) {
    return 0;
  }
  return 1;
}


