/*
 * Program: i76.exe
 * Function: apply_generic_vehicle_radial_damage_response
 * Entry: 0046f890
 * Signature: undefined __cdecl apply_generic_vehicle_radial_damage_response(LPVOID param_1, int param_2, int param_3)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium-high] Shared class callback
   that builds a class damage transform and dispatches radial damage/impulse using vectors from the
   damage context. */

void __cdecl apply_generic_vehicle_radial_damage_response(LPVOID param_1,int param_2,int param_3)

{
  int iVar1;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c [15];
  
  iVar1 = build_world_object_class_damage_transform(local_3c,param_2);
  local_48 = *(float *)(iVar1 + 0x18);
  local_44 = *(undefined4 *)(iVar1 + 0x1c);
  local_40 = *(undefined4 *)(iVar1 + 0x20);
  apply_radial_damage_and_impulse_to_target
            (param_1,param_2,&local_48,(float *)(param_3 + 0x60),(float *)(param_3 + 0x48));
  return;
}


