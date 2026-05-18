/*
 * Program: i76.exe
 * Function: fsm_or_mission_logic_helper_b
 * Entry: 00456790
 * Signature: undefined __cdecl fsm_or_mission_logic_helper_b(short param_1, uint * param_2)
 */


/* i76 first-pass rename
   old_name: FUN_00456790
   suggested_name: fsm_or_mission_logic_helper_b
   basis: Gameplay/FSM cluster candidate from diagnostics; name intentionally cautious. */

void __cdecl fsm_or_mission_logic_helper_b(short param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  uchar local_18 [24];
  
  puVar3 = param_2;
  if (*param_2 != DAT_00542420) {
    multiplayer_player_count_context_helper_00454620(param_1,local_18);
    report_chunk_parse_error();
  }
  uVar2 = DAT_00542420 + 0x1f >> 5;
  _param_1 = 0;
  if (uVar2 != 0) {
    param_2 = (uint *)0x0;
    puVar5 = &DAT_005423d0;
    uVar4 = DAT_00542420;
    do {
      puVar3 = puVar3 + 1;
      if (*puVar3 != *puVar5) {
        if (_param_1 == uVar2 - 1) {
          uVar2 = uVar4 & 0x1f;
        }
        else {
          uVar2 = 0x20;
        }
        uVar4 = 0;
        if (uVar2 != 0) {
          do {
            if ((1 << ((byte)uVar4 & 0x1f) & (*puVar5 ^ *puVar3)) != 0) {
              iVar1 = (&DAT_005419d0)[uVar4 + (int)param_2];
              if (iVar1 != 0) {
                (&DAT_005419d0)[uVar4 + (int)param_2] = 0;
                create_building_world_object_default(iVar1);
              }
            }
            uVar4 = uVar4 + 1;
          } while (uVar4 < uVar2);
        }
        uVar4 = DAT_00542420;
        *puVar5 = *puVar5 | (1 << ((byte)uVar2 & 0x1f)) - 1U & *puVar3;
      }
      _param_1 = _param_1 + 1;
      param_2 = param_2 + 8;
      uVar2 = uVar4 + 0x1f >> 5;
      puVar5 = puVar5 + 1;
    } while (_param_1 < uVar2);
  }
  return;
}


