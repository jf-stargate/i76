/*
 * Program: i76.exe
 * Function: apply_vehicle_collision_radial_damage_response
 * Entry: 004643c0
 * Signature: undefined __cdecl apply_vehicle_collision_radial_damage_response(LPVOID param_1, int param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe vehicle class physics rename v29; confidence=medium-high] Class-id 1 callback that
   builds relative damage vectors between world objects and dispatches radial damage/impulse to the
   target. */

void __cdecl
apply_vehicle_collision_radial_damage_response(LPVOID param_1,int param_2,undefined4 *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_3c [15];
  
  if (((*(byte *)((int)param_1 + 0x10) & 0x20) == 0) &&
     (iVar4 = is_world_object_class_geometry_or_light_range(param_2), iVar4 == 0)) {
    if ((*(int *)(param_2 + 0x6c) != 3) || ((*(uint *)(param_2 + 0x10) & 0x200) == 0)) {
      puVar5 = param_3;
      puVar6 = (undefined4 *)(*(int *)((int)param_1 + 0x70) + 0x38);
      for (iVar4 = 0x1b; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    if (*(int *)(param_2 + 0x6c) != 3) {
      iVar4 = build_world_object_class_damage_transform(local_3c,(int)param_1);
      fVar1 = *(float *)(iVar4 + 0x18);
      fVar2 = *(float *)(iVar4 + 0x1c);
      fVar3 = *(float *)(iVar4 + 0x20);
      iVar4 = build_world_object_class_damage_transform(local_3c,param_2);
      local_48 = *(float *)(iVar4 + 0x18) - fVar1;
      local_44 = *(float *)(iVar4 + 0x1c) - fVar2;
      local_40 = *(float *)(iVar4 + 0x20) - fVar3;
      apply_radial_damage_and_impulse_to_target
                (param_1,param_2,&local_48,(float *)(param_3 + 0x18),(float *)(param_3 + 0x12));
    }
  }
  return;
}


