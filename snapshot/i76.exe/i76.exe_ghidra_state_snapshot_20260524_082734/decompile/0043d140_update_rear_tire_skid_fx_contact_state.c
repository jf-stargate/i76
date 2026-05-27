/*
 * Program: i76.exe
 * Function: update_rear_tire_skid_fx_contact_state
 * Entry: 0043d140
 * Signature: undefined __cdecl update_rear_tire_skid_fx_contact_state(int param_1, uint param_2, int param_3)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=high] Updates rear tire
   contact/skid state and vehicle contact/skid flag using rear-left and rear-right tire components.
    */

void __cdecl update_rear_tire_skid_fx_contact_state(int param_1,uint param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = get_vehicle_runtime_context(param_1);
  if ((param_3 == 0) || ((param_2 & 0x8020) != 0)) {
    uVar2 = *(uint *)(iVar1 + 0x454) & 0xfffffffd;
  }
  else {
    uVar2 = *(uint *)(iVar1 + 0x454) | 2;
  }
  *(uint *)(iVar1 + 0x454) = uVar2;
  update_tire_contact_skid_fx_state(*(int *)(iVar1 + 0x3bc),param_3);
  update_tire_contact_skid_fx_state(*(int *)(iVar1 + 0x3b8),param_3);
  return;
}


