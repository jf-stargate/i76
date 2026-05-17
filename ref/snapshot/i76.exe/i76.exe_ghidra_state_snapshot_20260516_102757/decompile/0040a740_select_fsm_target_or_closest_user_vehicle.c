/*
 * Program: i76.exe
 * Function: select_fsm_target_or_closest_user_vehicle
 * Entry: 0040a740
 * Signature: int __cdecl select_fsm_target_or_closest_user_vehicle(int param_1)
 */


/* cgpt rename v10 fsm/ai runtime core cluster: Selects a script/FSM target object and falls back to
   the closest user/player vehicle candidate when appropriate. */

int __cdecl select_fsm_target_or_closest_user_vehicle(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  
  iVar7 = param_1;
  iVar8 = is_vehicle_or_actor_runtime_world_object(param_1);
  if (iVar8 == 0) {
    return 0;
  }
  fsm_format_default_label_name(iVar7,&param_1,DAT_0051f620,&DAT_0051f624);
  if (param_1 < DAT_0051f624) {
    iVar8 = *(int *)(param_1 * 0x60 + 0x58 + DAT_0051f620);
  }
  else {
    iVar8 = 0;
  }
  piVar9 = (int *)get_active_player_or_camera_world_object_entry();
  if ((piVar9 != (int *)0x0) && (*piVar9 != iVar7)) {
    return iVar8;
  }
  iVar10 = vehicle_specials_display_context_helper_00462cc0(iVar7);
  if (iVar8 != 0) {
    if (iVar10 == 0) {
      return iVar8;
    }
    fVar6 = (float)*(double *)(iVar8 + 0x40) - (float)*(double *)(iVar7 + 0x40);
    fVar5 = (float)*(double *)(iVar8 + 0x48) - (float)*(double *)(iVar7 + 0x48);
    fVar1 = (float)*(double *)(iVar8 + 0x50) - (float)*(double *)(iVar7 + 0x50);
    fVar2 = (float)*(double *)(iVar10 + 0x40) - (float)*(double *)(iVar7 + 0x40);
    fVar3 = (float)*(double *)(iVar10 + 0x48) - (float)*(double *)(iVar7 + 0x48);
    fVar4 = (float)*(double *)(iVar10 + 0x50) - (float)*(double *)(iVar7 + 0x50);
    if (fVar1 * fVar1 + fVar5 * fVar5 + fVar6 * fVar6 <
        fVar4 * fVar4 + fVar3 * fVar3 + fVar2 * fVar2) {
      return iVar8;
    }
  }
  return iVar10;
}


