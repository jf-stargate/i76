/*
 * Program: i76.exe
 * Function: collect_forward_facing_vehicle_weapon_slots
 * Entry: 00409cf0
 * Signature: undefined __cdecl collect_forward_facing_vehicle_weapon_slots(int param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: Builds a list of vehicle weapon slots that face
   forward or are eligible relative to the active player/camera vehicle. */

void __cdecl collect_forward_facing_vehicle_weapon_slots(int param_1,int *param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  undefined4 local_58 [6];
  float local_40;
  float local_3c;
  float local_38;
  
  iVar8 = 0;
  iVar1 = *param_2;
  fVar2 = *(float *)(iVar1 + 0x18);
  fVar3 = *(float *)(iVar1 + 0x1c);
  fVar4 = *(float *)(iVar1 + 0x20);
  param_2[0x29bd] = 0;
  if (0 < param_2[0x29c6]) {
    piVar6 = param_2 + 0x29c7;
    piVar7 = param_2 + 0x29d5;
    do {
      if (*piVar7 == 3) {
        piVar5 = (int *)get_active_player_or_camera_world_object_entry();
        if ((piVar5 == (int *)0x0) || (*piVar5 != param_1)) {
          set_weapon_runtime_state_field_04(param_1,*piVar6,iVar8);
        }
      }
      else {
        extract_weapon_runtime_state_to_vsf_record(*piVar6,local_58);
        if (_DAT_004bc5f8 < fVar4 * local_38 + fVar3 * local_3c + fVar2 * local_40) {
          param_2[param_2[0x29bd] + 0x29be] = iVar8;
          param_2[0x29bd] = param_2[0x29bd] + 1;
        }
      }
      iVar8 = iVar8 + 1;
      piVar6 = piVar6 + 1;
      piVar7 = piVar7 + 8;
    } while (iVar8 < param_2[0x29c6]);
  }
  return;
}


