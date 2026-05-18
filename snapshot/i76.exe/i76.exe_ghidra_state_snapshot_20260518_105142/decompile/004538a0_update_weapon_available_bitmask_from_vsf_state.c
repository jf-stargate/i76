/*
 * Program: i76.exe
 * Function: update_weapon_available_bitmask_from_vsf_state
 * Entry: 004538a0
 * Signature: undefined __stdcall update_weapon_available_bitmask_from_vsf_state(void)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=medium_high] Collects active weapon
   slots, serializes weapon state, and builds global weapon availability/status bitmask. */

void update_weapon_available_bitmask_from_vsf_state(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int local_78;
  int local_74 [5];
  int local_60;
  int local_5c;
  undefined4 local_58 [19];
  int local_c;
  
  piVar4 = &local_78;
  piVar1 = (int *)get_active_player_or_camera_world_object_entry();
  g_player_weapon_status_bitmask = 0;
  if ((piVar1 != (int *)0x0) &&
     (iVar2 = collect_vehicle_weapon_runtime_slots(*piVar1,&local_78), iVar2 == 1)) {
    iVar2 = 0;
    if (0 < local_78) {
      do {
        piVar4 = piVar4 + 1;
        extract_weapon_runtime_state_to_vsf_record(*piVar4,local_58);
        if (local_c == 0) {
          uVar3 = 0;
        }
        else {
          uVar3 = 1 << ((byte)iVar2 & 0x1f);
        }
        g_player_weapon_status_bitmask = g_player_weapon_status_bitmask | uVar3;
        iVar2 = iVar2 + 1;
      } while (iVar2 < local_78);
    }
    extract_weapon_runtime_state_to_vsf_record(local_60,local_58);
    g_player_weapon_status_bitmask = g_player_weapon_status_bitmask | -(uint)(local_c != 0) & 0x20;
    extract_weapon_runtime_state_to_vsf_record(local_5c,local_58);
    g_player_weapon_status_bitmask = g_player_weapon_status_bitmask | -(uint)(local_c != 0) & 0x40;
  }
  return;
}


