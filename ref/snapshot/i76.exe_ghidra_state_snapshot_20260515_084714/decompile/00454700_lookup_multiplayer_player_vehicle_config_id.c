/*
 * Program: i76.exe
 * Function: lookup_multiplayer_player_vehicle_config_id
 * Entry: 00454700
 * Signature: undefined4 __cdecl lookup_multiplayer_player_vehicle_config_id(short param_1, undefined4 * param_2)
 */


/* cgpt rename v4: Finds a multiplayer player slot by player id and returns the associated
   vehicle/config id. */

undefined4 __cdecl lookup_multiplayer_player_vehicle_config_id(short param_1,undefined4 *param_2)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = &DAT_00541070;
  do {
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 0x24;
    iVar2 = iVar2 + 1;
  } while ((int)psVar1 < 0x5414f0);
  if (iVar2 == 0x10) {
    iVar2 = -1;
  }
  if (iVar2 == -1) {
    return 0;
  }
  *param_2 = (&DAT_0054108c)[iVar2 * 0x12];
  return 1;
}


