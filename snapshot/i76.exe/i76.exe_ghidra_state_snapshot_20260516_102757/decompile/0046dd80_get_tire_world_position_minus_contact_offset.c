/*
 * Program: i76.exe
 * Function: get_tire_world_position_minus_contact_offset
 * Entry: 0046dd80
 * Signature: undefined __cdecl get_tire_world_position_minus_contact_offset(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Tire child helper
   returning world position adjusted by contact offset. */

void __cdecl get_tire_world_position_minus_contact_offset(undefined4 *param_1,int param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  float local_c [3];
  
  iVar2 = *(int *)(param_2 + 0x70);
  puVar5 = (undefined4 *)compose_world_object_runtime_transform(local_c,param_2);
  fVar3 = (float)puVar5[1];
  uVar4 = puVar5[2];
  fVar1 = *(float *)(iVar2 + 0x1c);
  *param_1 = *puVar5;
  param_1[1] = fVar3 - fVar1;
  param_1[2] = uVar4;
  return;
}


