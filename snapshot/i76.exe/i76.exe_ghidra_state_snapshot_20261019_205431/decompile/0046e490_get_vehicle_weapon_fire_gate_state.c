/*
 * Program: i76.exe
 * Function: get_vehicle_weapon_fire_gate_state
 * Entry: 0046e490
 * Signature: undefined4 __cdecl get_vehicle_weapon_fire_gate_state(int param_1, int param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Returns vehicle weapon fire-gate
   state used by fire enable and targeting paths. */

undefined4 __cdecl get_vehicle_weapon_fire_gate_state(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 1) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x400);
  }
  else {
    iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x404);
  }
  if (iVar1 == 0) {
    return 0;
  }
  if ((*(undefined4 **)(iVar1 + 0x70))[1] == 0) {
    return 0;
  }
  return *(undefined4 *)**(undefined4 **)(iVar1 + 0x70);
}


