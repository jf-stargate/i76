/*
 * Program: i76.exe
 * Function: initialize_vehicle_runtime_context_and_cockpit_state
 * Entry: 00463120
 * Signature: undefined __cdecl initialize_vehicle_runtime_context_and_cockpit_state(float param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle class physics rename v29; confidence=high] Class-id 1 initialization
   callback. Initializes vehicle runtime arrays, component/object references, cockpit textures,
   camera projection, and weapon HUD state. */

void __cdecl initialize_vehicle_runtime_context_and_cockpit_state(float param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  byte bVar8;
  int iVar9;
  int *local_5c;
  undefined4 local_58 [12];
  double local_28;
  undefined4 local_10;
  int local_c;
  
  iVar5 = *(int *)((int)param_1 + 0x70);
  initialize_fixedstep_accumulator_interval((float *)(iVar5 + 0x444),0.05);
  effect_target_selection_context_helper_00438a90(param_1);
  if (*(int *)((int)param_1 + 0x6c) == 1) {
    piVar4 = (int *)(iVar5 + 0x3a8);
    iVar9 = 0x18;
    *(uint *)(iVar5 + 0x454) = *(uint *)(iVar5 + 0x454) | 0x80000;
    do {
      if (*piVar4 != 0) {
        increment_refcount_recursive_for_object_tree(*piVar4,s_vhcl_004f8124);
      }
      piVar4 = piVar4 + 1;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 9U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (iVar9 + *piVar4) * 4) = 0;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 3U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 1;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x30U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 4;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x24U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 5;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  if (*(int *)(iVar5 + 0x3b4) != 0) {
    bVar8 = 0;
    iVar9 = 0;
    piVar4 = (int *)(iVar5 + 0x1a0);
    do {
      if ((1 << (bVar8 & 0x1f) & 0x10U) != 0) {
        *(undefined4 *)(iVar5 + 0x1bc + (iVar9 + *piVar4) * 4) = 2;
        *piVar4 = *piVar4 + 1;
      }
      iVar9 = iVar9 + 0x11;
      bVar8 = bVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar9 < 0x77);
    bVar8 = 0;
    iVar9 = 0;
    piVar4 = (int *)(iVar5 + 0x1a0);
    do {
      if ((1 << (bVar8 & 0x1f) & 4U) != 0) {
        *(undefined4 *)(iVar5 + 0x1bc + (iVar9 + *piVar4) * 4) = 3;
        *piVar4 = *piVar4 + 1;
      }
      iVar9 = iVar9 + 0x11;
      bVar8 = bVar8 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar9 < 0x77);
  }
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x40U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (iVar9 + *piVar4) * 4) = 6;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0xbU) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 7;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x3fU) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 8;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x3fU) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 9;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  local_5c = (int *)(iVar5 + 0x3d0);
  iVar9 = 10;
  do {
    if (*local_5c != 0) {
      uVar6 = 0;
      iVar1 = weapon_mount_context_helper_004a3380(*local_5c,local_58);
      if (iVar1 != 3) {
        if (local_c == 3) {
          uVar6 = 0x7f;
        }
        else if (local_c == 1) {
          if (_DAT_004be1b8 <= local_28) {
            if (local_28 <= _DAT_004be1b8) {
              uVar6 = 0x7f;
            }
            else {
              uVar6 = 0x79;
            }
          }
          else {
            uVar6 = 0x67;
          }
        }
        else {
          switch(local_10) {
          case 1:
            uVar6 = 1;
            if (_DAT_004be1b8 <= local_28) {
              if (_DAT_004be1b8 < local_28) {
                uVar6 = 9;
              }
            }
            else {
              uVar6 = 3;
            }
            break;
          case 2:
            uVar6 = 0x20;
            if (local_c != 4) {
              if (_DAT_004be1b8 <= local_28) {
                if (_DAT_004be1b8 < local_28) {
                  uVar6 = 0x30;
                }
              }
              else {
                uVar6 = 0x24;
              }
            }
            break;
          case 3:
            uVar6 = 0x10;
            break;
          case 4:
            uVar6 = 4;
          }
        }
        bVar8 = 0;
        iVar1 = 0;
        piVar4 = (int *)(iVar5 + 0x1a0);
        do {
          if ((uVar6 & 1 << (bVar8 & 0x1f)) != 0) {
            *(int *)(iVar5 + 0x1bc + (iVar1 + *piVar4) * 4) = iVar9;
            *piVar4 = *piVar4 + 1;
          }
          iVar1 = iVar1 + 0x11;
          bVar8 = bVar8 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar1 < 0x77);
      }
    }
    iVar9 = iVar9 + 1;
    local_5c = local_5c + 1;
  } while (iVar9 < 0x10);
  local_5c = (int *)(iVar5 + 0x3ec);
  iVar9 = 0x11;
  do {
    if (*local_5c != 0) {
      iVar1 = rand();
      piVar4 = (int *)(iVar5 + 0x1a0);
      bVar8 = 0;
      iVar3 = 0;
      do {
        if ((1 << ((byte)(iVar1 % 7) & 0x1f) & 1 << (bVar8 & 0x1f)) != 0) {
          *(int *)(iVar5 + 0x1bc + (iVar3 + *piVar4) * 4) = iVar9;
          *piVar4 = *piVar4 + 1;
        }
        iVar3 = iVar3 + 0x11;
        bVar8 = bVar8 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < 0x77);
    }
    iVar9 = iVar9 + 1;
    local_5c = local_5c + 1;
  } while (iVar9 < 0x13);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x7fU) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 0xffffffff;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x40U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 0xffffffff;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  bVar8 = 0;
  iVar9 = 0;
  piVar4 = (int *)(iVar5 + 0x1a0);
  do {
    if ((1 << (bVar8 & 0x1f) & 0x40U) != 0) {
      *(undefined4 *)(iVar5 + 0x1bc + (*piVar4 + iVar9) * 4) = 0xffffffff;
      *piVar4 = *piVar4 + 1;
    }
    iVar9 = iVar9 + 0x11;
    bVar8 = bVar8 + 1;
    piVar4 = piVar4 + 1;
  } while (iVar9 < 0x77);
  iVar9 = world_object_has_optional_runtime_flag((int)param_1);
  if (iVar9 != 0) {
    iVar9 = is_damage_side_effects_suppressed();
    if (iVar9 == 0) {
      puVar7 = (undefined4 *)(iVar5 + 0x138);
      iVar9 = 4;
      do {
        uVar2 = ftol();
        puVar7[8] = uVar2;
        uVar2 = ftol();
        *puVar7 = uVar2;
        uVar2 = ftol();
        puVar7[0xc] = uVar2;
        uVar2 = ftol();
        puVar7[4] = uVar2;
        puVar7 = puVar7 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      puVar7 = (undefined4 *)(iVar5 + 0x18c);
      iVar9 = 5;
      do {
        uVar2 = ftol();
        puVar7[-5] = uVar2;
        uVar2 = ftol();
        *puVar7 = uVar2;
        puVar7 = puVar7 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      piVar4 = (int *)(iVar5 + 0x3a8);
      iVar5 = 0x18;
      do {
        iVar9 = *piVar4;
        if (iVar9 != 0) {
          switch(*(undefined4 *)(iVar9 + 0x6c)) {
          case 0x14:
          case 0x15:
          case 0x17:
            puVar7 = *(undefined4 **)(iVar9 + 0x70);
            uVar2 = ftol();
            *puVar7 = uVar2;
            iVar9 = *(int *)(iVar9 + 0x70);
            uVar2 = ftol();
            *(undefined4 *)(iVar9 + 4) = uVar2;
            break;
          case 0x16:
          case 0x1e:
            iVar1 = *(int *)(iVar9 + 0x70);
            uVar2 = ftol();
            *(undefined4 *)(iVar1 + 4) = uVar2;
            iVar9 = *(int *)(iVar9 + 0x70);
            uVar2 = ftol();
            *(undefined4 *)(iVar9 + 8) = uVar2;
            break;
          case 0x18:
            iVar1 = *(int *)(iVar9 + 0x70);
            uVar2 = ftol();
            *(undefined4 *)(iVar1 + 8) = uVar2;
            iVar9 = *(int *)(iVar9 + 0x70);
            uVar2 = ftol();
            *(undefined4 *)(iVar9 + 0xc) = uVar2;
          }
        }
        piVar4 = piVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    preload_cockpit_gauge_textures((int)param_1);
    initialize_runtime_camera_projection_matrix(1);
    initialize_or_refresh_player_weapon_hud_overlay((int *)0x1);
    load_specials_backing_texture((int)param_1);
    get_user_entity_or_report_missing();
  }
  return;
}


