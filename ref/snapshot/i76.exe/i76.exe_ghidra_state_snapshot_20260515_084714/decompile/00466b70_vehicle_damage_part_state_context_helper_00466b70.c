/*
 * Program: i76.exe
 * Function: vehicle_damage_part_state_context_helper_00466b70
 * Entry: 00466b70
 * Signature: undefined4 __cdecl vehicle_damage_part_state_context_helper_00466b70(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: vehicle damage part state context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl vehicle_damage_part_state_context_helper_00466b70(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x3a8 + param_2 * 4);
  if (iVar1 != 0) {
    switch(*(undefined4 *)(iVar1 + 0x6c)) {
    case 0x14:
      return *(undefined4 *)(*(int *)(iVar1 + 0x70) + 4);
    case 0x15:
    case 0x17:
      return *(undefined4 *)(*(int *)(iVar1 + 0x70) + 4);
    case 0x16:
      return *(undefined4 *)(*(int *)(iVar1 + 0x70) + 8);
    case 0x18:
      return *(undefined4 *)(*(int *)(iVar1 + 0x70) + 0xc);
    case 0x1e:
      return *(undefined4 *)(*(int *)(iVar1 + 0x70) + 8);
    case 0x32:
      uVar2 = weapon_fire_request_context_helper_004a4c90(iVar1);
      return uVar2;
    }
  }
  return 0;
}


