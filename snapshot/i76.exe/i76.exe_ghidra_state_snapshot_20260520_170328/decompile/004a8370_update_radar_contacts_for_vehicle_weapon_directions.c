/*
 * Program: i76.exe
 * Function: update_radar_contacts_for_vehicle_weapon_directions
 * Entry: 004a8370
 * Signature: undefined __cdecl update_radar_contacts_for_vehicle_weapon_directions(int param_1)
 */


/* cgpt rename v2: Updates radar contacts/probes for forward/reverse and weapon-direction vectors.
    */

void __cdecl update_radar_contacts_for_vehicle_weapon_directions(int param_1)

{
  uint uVar1;
  LPVOID pvVar2;
  int iVar3;
  
  uVar1 = weapon_mount_context_helper_004a3280(param_1);
  pvVar2 = (LPVOID)find_nearest_primary_effect_target_in_forward_cone
                             ((float)*(double *)(param_1 + 0x40),(float)*(double *)(param_1 + 0x48),
                              (float)*(double *)(param_1 + 0x50),param_1,*(float *)(param_1 + 0x30),
                              *(float *)(param_1 + 0x34),*(float *)(param_1 + 0x38));
  update_radar_display(param_1,pvVar2,1);
  pvVar2 = (LPVOID)0x0;
  if ((uVar1 & 2) != 0) {
    pvVar2 = (LPVOID)find_nearest_primary_effect_target_in_forward_cone
                               ((float)*(double *)(param_1 + 0x40),
                                (float)*(double *)(param_1 + 0x48),
                                (float)*(double *)(param_1 + 0x50),param_1,
                                -*(float *)(param_1 + 0x30),-*(float *)(param_1 + 0x34),
                                -*(float *)(param_1 + 0x38));
  }
  update_radar_display(param_1,pvVar2,2);
  pvVar2 = (LPVOID)0x0;
  if ((uVar1 & 8) != 0) {
    iVar3 = is_vehicle_weapon_fire_gate_clear(param_1,1);
    if ((iVar3 == 0) || ((*(byte *)(param_1 + 0x10) & 0x20) != 0)) {
      pvVar2 = (LPVOID)find_nearest_primary_effect_target_in_forward_cone
                                 ((float)*(double *)(param_1 + 0x40),
                                  (float)*(double *)(param_1 + 0x48),
                                  (float)*(double *)(param_1 + 0x50),param_1,
                                  *(float *)(param_1 + 0x18),*(float *)(param_1 + 0x1c),
                                  *(float *)(param_1 + 0x20));
    }
  }
  update_radar_display(param_1,pvVar2,8);
  pvVar2 = (LPVOID)0x0;
  if ((uVar1 & 0x10) != 0) {
    iVar3 = is_vehicle_weapon_fire_gate_clear(param_1,2);
    if ((iVar3 == 0) || ((*(byte *)(param_1 + 0x10) & 0x20) != 0)) {
      pvVar2 = (LPVOID)find_nearest_primary_effect_target_in_forward_cone
                                 ((float)*(double *)(param_1 + 0x40),
                                  (float)*(double *)(param_1 + 0x48),
                                  (float)*(double *)(param_1 + 0x50),param_1,
                                  -*(float *)(param_1 + 0x18),-*(float *)(param_1 + 0x1c),
                                  -*(float *)(param_1 + 0x20));
    }
  }
  update_radar_display(param_1,pvVar2,0x10);
  return;
}


