/*
 * Program: i76.exe
 * Function: reset_vehicle_weapon_target_transform_state
 * Entry: 00460e60
 * Signature: undefined __cdecl reset_vehicle_weapon_target_transform_state(int param_1)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium] Clears vehicle weapon target transform
   state. */

void __cdecl reset_vehicle_weapon_target_transform_state(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (((*(int *)(param_1 + 0x70) != 0) &&
      (iVar1 = *(int *)(*(int *)(param_1 + 0x70) + 0x434), iVar1 != 0)) &&
     (iVar1 = *(int *)(iVar1 + 0x70), iVar1 != 0)) {
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffd;
    puVar3 = &DAT_004faed8;
    puVar4 = (undefined4 *)(iVar1 + 0x10);
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    *(undefined4 *)(iVar1 + 0x50) = 0;
  }
  return;
}


