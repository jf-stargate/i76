/*
 * Program: i76.exe
 * Function: update_player_weapon_fire_enable_flags
 * Entry: 004a5870
 * Signature: undefined __cdecl update_player_weapon_fire_enable_flags(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Sets per-weapon fire-enable
   flags based on ammo, controls, damage-suppression state, and active slots. */

void __cdecl update_player_weapon_fire_enable_flags(int *param_1)

{
  int iVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar3 != (int *)0x0) {
    iVar4 = 0;
    if (0 < g_loaded_vehicle_runtime_count) {
      piVar6 = &g_loaded_vehicle_runtime_table;
      do {
        if (*piVar6 == *piVar3) goto LAB_004a58a7;
        iVar4 = iVar4 + 1;
        piVar6 = piVar6 + 0xb2;
      } while (iVar4 < g_loaded_vehicle_runtime_count);
    }
    iVar4 = -1;
LAB_004a58a7:
    if ((iVar4 != -1) && (iVar4 < g_loaded_vehicle_runtime_count)) {
      piVar3 = &g_loaded_vehicle_runtime_table + iVar4 * 0xb2;
      goto LAB_004a58c5;
    }
  }
  piVar3 = (int *)0x0;
LAB_004a58c5:
  if ((piVar3 == param_1) && (piVar3 != (int *)0x0)) {
    iVar4 = is_vehicle_weapon_fire_gate_clear(*param_1,1);
    if ((iVar4 != 0) && (iVar4 = is_vehicle_weapon_fire_gate_clear(*param_1,2), iVar4 != 0)) {
      puVar9 = (undefined4 *)&DAT_004f2364;
      puVar7 = &DAT_005da738;
      piVar3 = param_1 + 0x2a;
      do {
        iVar1 = g_player_weapon_hud_world_object;
        iVar4 = *piVar3;
        if (iVar4 != -1) {
          iVar8 = iVar4 * 0x4c;
          iVar5 = 0;
          piVar6 = param_1;
          do {
            piVar6 = piVar6 + 1;
            if (*piVar6 == (&DAT_005aab24)[iVar4 * 0x13]) {
              if (DAT_005367db != '\0') goto LAB_004a595a;
              break;
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 < 5);
          if (*(char *)*puVar7 == '\0') {
            *(undefined4 *)(&DAT_005aab44 + iVar8) = 0;
          }
          else {
LAB_004a595a:
            fVar2 = _DAT_004beab8;
            if (iVar8 != -0x5aab08) {
              fVar2 = (float)(uint)(&DAT_005aab14)[iVar4 * 0x13] /
                      (float)*(int *)(&DAT_005d893c + (&DAT_005aab38)[iVar4 * 0x13] * 0xd8);
            }
            if (fVar2 <= _DAT_004beab8) {
              *(undefined4 *)(&DAT_005aab44 + iVar8) = 0;
              play_sound_if_object_tree_is_audible(s_WMISS_WAV_004fee24,iVar1,(undefined4 *)0x0);
              iVar1 = (&DAT_005d8930)[(&DAT_005aab38)[iVar4 * 0x13] * 0x36];
              if (iVar1 < 100) {
                *puVar9 = *(undefined4 *)
                           (&DAT_004fec80 +
                           ((&DAT_005d8934)[(&DAT_005aab38)[iVar4 * 0x13] * 0x36] * 7 + iVar1) * 4);
                puVar9[-1] = 1;
              }
              else {
                *puVar9 = *(undefined4 *)
                           (s_3num_tens_1_004feaf0 +
                           ((&DAT_005d8934)[(&DAT_005aab38)[iVar4 * 0x13] * 0x36] * 7 + iVar1) * 4);
                puVar9[-1] = 1;
              }
            }
            else if (((&DAT_005d8934)[(&DAT_005aab38)[iVar4 * 0x13] * 0x36] == 4) &&
                    ((&DAT_005d8930)[(&DAT_005aab38)[iVar4 * 0x13] * 0x36] == 4)) {
              if (_DAT_004beabc <= *(float *)(&DAT_005aab50 + iVar8)) {
                *(undefined4 *)(&DAT_005aab44 + iVar8) = 1;
              }
            }
            else {
              *(undefined4 *)(&DAT_005aab44 + iVar8) = 1;
            }
          }
        }
        puVar7 = puVar7 + 1;
        piVar3 = piVar3 + 0x16;
        puVar9 = puVar9 + 7;
        if (0x5da74b < (int)puVar7) {
          return;
        }
      } while( true );
    }
    iVar4 = is_vehicle_weapon_fire_gate_locked_ready(*param_1,2);
    if (((iVar4 != 0) && (iVar4 = get_vehicle_weapon_fire_gate_state(*param_1,2), iVar4 == 0)) &&
       (param_1[0x98] != -1)) {
      iVar4 = param_1[0x98] * 0x4c;
      if (*(int *)(&DAT_005aab28 + iVar4) < 1) {
        *(undefined4 *)(&DAT_005aab44 + iVar4) = 0;
      }
      else {
        *(int *)(&DAT_005aab44 + iVar4) = (int)DAT_005367db;
      }
    }
    iVar4 = is_vehicle_weapon_fire_gate_locked_ready(*param_1,1);
    if (((iVar4 != 0) && (iVar4 = get_vehicle_weapon_fire_gate_state(*param_1,1), iVar4 == 0)) &&
       (param_1[0xae] != -1)) {
      iVar4 = param_1[0xae] * 0x4c;
      if (0 < *(int *)(&DAT_005aab28 + iVar4)) {
        *(int *)(&DAT_005aab44 + iVar4) = (int)DAT_005367db;
        return;
      }
      *(undefined4 *)(&DAT_005aab44 + iVar4) = 0;
    }
  }
  return;
}


