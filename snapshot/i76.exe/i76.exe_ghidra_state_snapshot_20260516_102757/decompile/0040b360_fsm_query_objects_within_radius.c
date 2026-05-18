/*
 * Program: i76.exe
 * Function: fsm_query_objects_within_radius
 * Entry: 0040b360
 * Signature: undefined4 __cdecl fsm_query_objects_within_radius(int param_1, int param_2, int * param_3)
 */


/* cgpt rename v7 fsm predicate/bridge cluster: FSM predicate: compares cached aim positions for two
   world objects and returns true if squared distance is below radius^2. */

undefined4 __cdecl fsm_query_objects_within_radius(int param_1,int param_2,int *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  undefined4 local_18 [3];
  undefined4 local_c [3];
  
  pfVar4 = (float *)get_cached_world_object_aim_position(local_18,param_1);
  fVar1 = *pfVar4;
  fVar2 = pfVar4[1];
  fVar3 = pfVar4[2];
  pfVar4 = (float *)get_cached_world_object_aim_position(local_c,param_2);
  if ((fVar3 - pfVar4[2]) * (fVar3 - pfVar4[2]) +
      (fVar2 - pfVar4[1]) * (fVar2 - pfVar4[1]) + (fVar1 - *pfVar4) * (fVar1 - *pfVar4) <
      (float)(*param_3 * *param_3)) {
    return 1;
  }
  return 0;
}


