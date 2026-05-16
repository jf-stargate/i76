/*
 * Program: i76.exe
 * Function: mission_user_vehicle_allowed_by_damage_suppression
 * Entry: 00401320
 * Signature: undefined4 __stdcall mission_user_vehicle_allowed_by_damage_suppression(void)
 */


/* cgpt rename v3: Returns true when a mission/user vehicle check should pass because the local
   override is set or damage side effects are suppressed. */

undefined4 mission_user_vehicle_allowed_by_damage_suppression(void)

{
  int iVar1;
  
  if (DAT_00501818 == 0) {
    iVar1 = is_damage_side_effects_suppressed();
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 1;
}


