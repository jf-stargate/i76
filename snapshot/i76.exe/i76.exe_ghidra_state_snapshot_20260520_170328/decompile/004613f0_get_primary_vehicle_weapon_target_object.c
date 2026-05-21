/*
 * Program: i76.exe
 * Function: get_primary_vehicle_weapon_target_object
 * Entry: 004613f0
 * Signature: uint __cdecl get_primary_vehicle_weapon_target_object(int param_1)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=high] Returns primary weapon/radar target object
   from vehicle target state, filtering inactive records. */

uint __cdecl get_primary_vehicle_weapon_target_object(int param_1)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  
  if ((((*(int *)(param_1 + 0x70) != 0) &&
       (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
      (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) &&
     ((puVar2 = *(uint **)(iVar1 + 0x54), puVar2 != (uint *)0x0 && (uVar3 = *puVar2, uVar3 != 0))))
  {
    return uVar3 & ~-(uint)(*(short *)(uVar3 + 8) != 0);
  }
  return 0;
}


