/*
 * Program: i76.exe
 * Function: vehicle_specials_indicator_update_helper_00467400
 * Entry: 00467400
 * Signature: undefined __cdecl vehicle_specials_indicator_update_helper_00467400(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle specials indicator update
   helper based on adjacent named subsystem context. */

void __cdecl vehicle_specials_indicator_update_helper_00467400(int param_1)

{
  int iVar1;
  float10 fVar2;
  
  iVar1 = *(int *)(param_1 + 0x70);
  if ((*(byte *)(iVar1 + 0x454) & 9) == 0) {
    fVar2 = start_vehicle_engine_damage_state_sound(param_1);
    *(float *)(iVar1 + 0x450) = (float)fVar2;
    *(uint *)(iVar1 + 0x454) = *(uint *)(iVar1 + 0x454) | 0x80000008;
  }
  return;
}


