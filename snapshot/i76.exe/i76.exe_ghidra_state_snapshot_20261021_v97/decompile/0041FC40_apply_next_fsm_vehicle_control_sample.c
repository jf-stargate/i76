/* Decompiled retail i76.exe, Ghidra v97; 0041fc40 apply_next_fsm_vehicle_control_sample */

/* cgpt readability rename v13 set A: Dequeues stored player-control input into vehicle runtime
   steering/throttle/brake fields, or resets drive mode when no sample is available.
   I76 v92 verified: Explicit host driveControl/0x49 at 004141BC calls here; one dequeue and apply
   to vehicle runtime if active */

void __cdecl apply_next_fsm_vehicle_control_sample(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((*(byte *)(iVar1 + 0x454) & 0x20) == 0) {
    iVar2 = get_vehicle_damage_event_state_block(iVar1);
    iVar2 = dequeue_fsm_vehicle_control_sample
                      (iVar2,(undefined4 *)(iVar1 + 0xe4),(undefined4 *)(iVar1 + 0xe0),
                       (undefined4 *)(iVar1 + 0xf0),(undefined4 *)(iVar1 + 0xe8),&local_4,&local_8);
    if (iVar2 == 0) {
      *(undefined4 *)(iVar1 + 0xe4) = 0;
      *(undefined4 *)(iVar1 + 0xe0) = 0;
      *(undefined4 *)(iVar1 + 0xf0) = 0;
      *(undefined4 *)(iVar1 + 0xe8) = 0x3f800000;
      vehicle_specials_state_getter_helper_00467370(param_1,3);
      return;
    }
  }
  mark_active_player_object_control_changed(param_1);
  return;
}


