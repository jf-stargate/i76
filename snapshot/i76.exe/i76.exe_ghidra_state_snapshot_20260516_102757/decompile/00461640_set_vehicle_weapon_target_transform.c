/*
 * Program: i76.exe
 * Function: set_vehicle_weapon_target_transform
 * Entry: 00461640
 * Signature: undefined __cdecl set_vehicle_weapon_target_transform(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Stores target transform/state for
   vehicle weapon targeting. */

void __cdecl set_vehicle_weapon_target_transform(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    puVar3 = (undefined4 *)(iVar1 + 0x10);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *param_2;
      param_2 = param_2 + 1;
      puVar3 = puVar3 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 1;
  }
  return;
}


