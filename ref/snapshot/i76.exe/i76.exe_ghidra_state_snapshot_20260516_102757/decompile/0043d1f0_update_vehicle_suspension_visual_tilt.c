/*
 * Program: i76.exe
 * Function: update_vehicle_suspension_visual_tilt
 * Entry: 0043d1f0
 * Signature: undefined __cdecl update_vehicle_suspension_visual_tilt(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v3: Applies suspension response scalar to paired visual suspension/tilt objects. */

void __cdecl update_vehicle_suspension_visual_tilt(int param_1)

{
  int iVar1;
  float10 fVar2;
  float10 fVar3;
  
  iVar1 = *(int *)(param_1 + 0x70);
  fVar3 = get_vehicle_suspension_response_scalar(iVar1);
  fVar2 = (float10)_DAT_004bd184;
  world_object_geometry_context_helper_00458980(*(int *)(iVar1 + 0x3ac),(float)(fVar3 * fVar2));
  world_object_geometry_context_helper_00458980(*(int *)(iVar1 + 0x3a8),(float)(fVar3 * fVar2));
  return;
}


