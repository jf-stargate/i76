/*
 * Program: i76.exe
 * Function: ordnance_projectile_state_context_helper_004aa0f0
 * Entry: 004aa0f0
 * Signature: bool __cdecl ordnance_projectile_state_context_helper_004aa0f0(double param_1, double param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: ordnance projectile state context
   helper based on adjacent named subsystem context. */

bool __cdecl ordnance_projectile_state_context_helper_004aa0f0(double param_1,double param_2)

{
  undefined4 local_8;
  
  local_8 = SUB84((double)(_DAT_006442c4 * (float)param_1 + (float)_DAT_004faf18),0);
  param_1._0_4_ = SUB84((double)(_DAT_006442c4 * (float)param_2 + (float)_DAT_004faf18),0);
  return (bool)('\x01' - (((0x2800 - param_1._0_4_ | 0x2800 - local_8 | param_1._0_4_ | local_8) &
                          0x80000000) != 0));
}


