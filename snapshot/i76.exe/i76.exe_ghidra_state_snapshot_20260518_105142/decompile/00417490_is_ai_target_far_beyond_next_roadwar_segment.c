/*
 * Program: i76.exe
 * Function: is_ai_target_far_beyond_next_roadwar_segment
 * Entry: 00417490
 * Signature: undefined4 __cdecl is_ai_target_far_beyond_next_roadwar_segment(uint param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Checks whether a next Roadwar segment exists and the
   target is farther than 160 units. */

undefined4 __cdecl is_ai_target_far_beyond_next_roadwar_segment(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  float10 fVar3;
  int local_4;
  
  uVar1 = param_1;
  iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  local_4 = *(int *)(iVar2 + 0xa96c);
  param_1 = *(uint *)(iVar2 + 0xa950);
  iVar2 = roadwar_get_next_road_index(&local_4,*(int *)(iVar2 + 0xa954),(int *)&param_1);
  if (iVar2 != 0) {
    fVar3 = (float10)world_object_geometry_context_helper_004589f0(uVar1,param_2);
    if ((float10)_DAT_004bc8d8 < fVar3) {
      return 1;
    }
  }
  return 0;
}


