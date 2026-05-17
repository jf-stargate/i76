/*
 * Program: i76.exe
 * Function: update_ai_behavior_target_projection_state
 * Entry: 004170c0
 * Signature: undefined4 __cdecl update_ai_behavior_target_projection_state(int param_1, int param_2)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Updates AI behavior projection state from target object
   position when target is a valid runtime object. */

undefined4 __cdecl update_ai_behavior_target_projection_state(int param_1,int param_2)

{
  int *piVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x6c) != 9) {
    iVar7 = is_vehicle_or_actor_runtime_world_object(param_2);
    if (iVar7 != 0) {
      dVar2 = *(double *)(param_1 + 0x40);
      iVar7 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
      dVar3 = *(double *)(param_1 + 0x48);
      dVar4 = *(double *)(param_1 + 0x50);
      project_point_to_path_segment_context_helper_0048e700
                ((float)dVar2,(float)dVar3,(float)dVar4,(int *)(iVar7 + 0xa96c),
                 (int *)(iVar7 + 0xa950));
      iVar5 = *(int *)(*(int *)(param_2 + 0x70) + 0x108);
      piVar1 = (int *)(iVar5 + 0xa96c);
      project_point_to_path_segment_context_helper_0048e700
                ((float)dVar2,(float)dVar3,(float)dVar4,piVar1,(int *)(iVar5 + 0xa950));
      if (*(int *)(iVar7 + 0xa96c) != 0) {
        piVar6 = *(int **)(iVar7 + 0xa96c);
        piVar1 = (int *)*piVar1;
        if (((piVar6 != (int *)0x0) && (piVar1 != (int *)0x0)) && (*piVar6 == *piVar1)) {
          return 1;
        }
      }
    }
  }
  return 0;
}


