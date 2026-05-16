/*
 * Program: i76.exe
 * Function: play_vehicle_engine_event_sound_unattached
 * Entry: 00424e90
 * Signature: int * __cdecl play_vehicle_engine_event_sound_unattached(int param_1)
 */


/* cgpt rename v3: Plays a vehicle engine event sound without attaching it to the vehicle object. */

int * __cdecl play_vehicle_engine_event_sound_unattached(int param_1)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((iVar1 != 0) && (iVar1 = *(int *)(*(int *)(iVar1 + 0x3c4) + 0x70), iVar1 != 0)) {
    pcVar2 = get_engine_event_sound_name(iVar1);
    if (pcVar2 != (char *)0x0) {
      piVar3 = play_named_sound_attached_to_object_or_player(pcVar2,0,(undefined4 *)0x0);
      return piVar3;
    }
  }
  return (int *)0x0;
}


