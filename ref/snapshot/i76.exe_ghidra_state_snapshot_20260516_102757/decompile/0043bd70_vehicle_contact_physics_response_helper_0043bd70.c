/*
 * Program: i76.exe
 * Function: vehicle_contact_physics_response_helper_0043bd70
 * Entry: 0043bd70
 * Signature: undefined __cdecl vehicle_contact_physics_response_helper_0043bd70(int param_1, undefined4 * param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: vehicle contact physics response
   helper based on prior focused closure context. */

void __cdecl vehicle_contact_physics_response_helper_0043bd70(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x28) = *param_2;
  *(undefined4 *)(param_1 + 0x2c) = param_2[1];
  *(undefined4 *)(param_1 + 0x30) = param_2[2];
  *(undefined4 *)(param_1 + 0x34) = param_2[3];
  *(undefined4 *)(param_1 + 0x38) = param_2[4];
  *(undefined4 *)(param_1 + 0x3c) = param_2[5];
  return;
}


