/*
 * Program: i76.exe
 * Function: is_vehicle_weapon_fire_gate_locked_ready
 * Entry: 0046e540
 * Signature: undefined4 __cdecl is_vehicle_weapon_fire_gate_locked_ready(int param_1, int param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Small vehicle weapon fire-gate
   predicate for locked/ready state. */

undefined4 __cdecl is_vehicle_weapon_fire_gate_locked_ready(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (param_2 == 1) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x400);
  }
  else {
    iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x404);
  }
  if ((((iVar2 != 0) && ((*(int **)(iVar2 + 0x70))[1] != 0)) &&
      (piVar1 = (int *)**(int **)(iVar2 + 0x70), *piVar1 != 1)) &&
     (((piVar1[3] == 0 && (piVar1[1] == 5)) && (piVar1[2] == 5)))) {
    return 1;
  }
  return 0;
}


