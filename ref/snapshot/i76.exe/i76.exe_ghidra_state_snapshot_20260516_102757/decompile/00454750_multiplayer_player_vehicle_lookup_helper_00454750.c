/*
 * Program: i76.exe
 * Function: multiplayer_player_vehicle_lookup_helper_00454750
 * Entry: 00454750
 * Signature: undefined4 __cdecl multiplayer_player_vehicle_lookup_helper_00454750(short param_1, undefined4 param_2, undefined4 param_3, int param_4)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer player vehicle lookup
   helper based on prior focused closure context. */

undefined4 __cdecl
multiplayer_player_vehicle_lookup_helper_00454750
          (short param_1,undefined4 param_2,undefined4 param_3,int param_4)

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
  *(undefined4 *)(iVar2 * 0x48 + 0x541090) = param_2;
  *(undefined4 *)(iVar2 * 0x48 + 0x541094) = param_3;
  (&DAT_00541098)[iVar2 * 0x12] = param_4;
  if (param_4 != 0) {
    *(short *)(*(int *)(param_4 + 0x70) + 0x480) = param_1;
  }
  return 1;
}


