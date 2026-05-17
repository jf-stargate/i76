/*
 * Program: i76.exe
 * Function: multiplayer_network_scoreboard_table_helper_00452930
 * Entry: 00452930
 * Signature: int __cdecl multiplayer_network_scoreboard_table_helper_00452930(uint param_1, short * param_2, short * param_3)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely multiplayer_network /
   scoreboard_table_helper based on address neighborhood and prior focused closure context. */

int __cdecl
multiplayer_network_scoreboard_table_helper_00452930(uint param_1,short *param_2,short *param_3)

{
  bool bVar1;
  short *psVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int local_c;
  short local_8 [2];
  short local_4 [2];
  
  psVar2 = param_2;
  iVar5 = 0;
  iVar4 = 0;
  bVar1 = false;
  if (param_2 != (short *)0x0) {
    *param_2 = 0;
  }
  if (param_3 != (short *)0x0) {
    *param_3 = 0;
  }
  do {
    sVar3 = get_multiplayer_player_record_and_copy_name(iVar5,(uchar *)0x0);
    if (sVar3 != 0) {
      lookup_multiplayer_player_vehicle_config_id(sVar3,&param_2);
      if (((uint)param_2 >> 0x10 & 7) == param_1) {
        get_multiplayer_player_spawn_score_fields(sVar3,&local_c,local_8,local_4);
        iVar4 = iVar4 + local_c;
        if (psVar2 != (short *)0x0) {
          *psVar2 = *psVar2 + local_8[0];
        }
        if (param_3 != (short *)0x0) {
          *param_3 = *param_3 + local_4[0];
        }
        bVar1 = true;
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0x10);
  if (bVar1) {
    return iVar4;
  }
  return -1;
}


