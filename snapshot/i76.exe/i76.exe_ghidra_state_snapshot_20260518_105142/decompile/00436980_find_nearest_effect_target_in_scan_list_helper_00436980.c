/*
 * Program: i76.exe
 * Function: find_nearest_effect_target_in_scan_list_helper_00436980
 * Entry: 00436980
 * Signature: undefined __cdecl find_nearest_effect_target_in_scan_list_helper_00436980(int param_1)
 */


/* cgpt readability rename set B v14: Readability pass set B: find nearest effect target in scan
   list helper based on prior focused closure context. */

void __cdecl find_nearest_effect_target_in_scan_list_helper_00436980(int param_1)

{
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x60)) {
    if ((*(uint *)(param_1 + 0x10) & 0xf000) == 0x3000) {
      release_effect_target_collision_payload(param_1);
    }
    if (*(int *)(param_1 + 100) != 0) {
      find_nearest_effect_target_in_scan_list_helper_00436980(*(int *)(param_1 + 100));
    }
  }
  return;
}


