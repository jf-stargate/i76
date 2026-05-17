/*
 * Program: i76.exe
 * Function: mission_flow_map_context_helper_0049c8d0
 * Entry: 0049c8d0
 * Signature: undefined __cdecl mission_flow_map_context_helper_0049c8d0(float param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v20: was mission_flow_map_camera_mission_flow_or_map_helper_0049c8d0.
   Remove duplicated mission-flow/map wording. */

void __cdecl mission_flow_map_context_helper_0049c8d0(float param_1,int param_2)

{
  short sVar1;
  float10 fVar2;
  
  sVar1 = get_multiplayer_message_source_player_id();
  fVar2 = multiplayer_host_notice_context_helper_00454bc0(sVar1);
  _DAT_005a7e78 = (float)(fVar2 + (float10)param_1);
  _DAT_005a7e7c = (float)((fVar2 + (float10)param_1) - (float10)g_runtime_time_seconds);
  if (param_2 != 0) {
    _DAT_005a7e7c = 0.0;
  }
  DAT_005a7e80 = 1;
  return;
}


