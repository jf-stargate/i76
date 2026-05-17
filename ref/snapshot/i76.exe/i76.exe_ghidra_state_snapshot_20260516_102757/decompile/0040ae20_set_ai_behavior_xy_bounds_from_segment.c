/*
 * Program: i76.exe
 * Function: set_ai_behavior_xy_bounds_from_segment
 * Entry: 0040ae20
 * Signature: undefined __cdecl set_ai_behavior_xy_bounds_from_segment(int param_1, float param_2, float param_3, float param_4, float param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v10 fsm/ai runtime core cluster: Stores expanded X/Z bounds for an AI/FSM behavior
   segment into state fields +0x9d40..+0x9d54. */

void __cdecl
set_ai_behavior_xy_bounds_from_segment
          (int param_1,float param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  int iVar2;
  float fVar3;
  
                    /* I76 semantic baseline: set_ai_behavior_xy_bounds_from_segment
                       Sets AI behavior XY bounds from a segment/spatial context. */
  iVar2 = *(int *)(*(int *)(param_1 + 0x70) + 0x108);
  fVar1 = param_4;
  if (param_2 < param_4) {
    fVar1 = param_2;
    param_2 = param_4;
  }
  fVar3 = param_2 - _DAT_004bc614;
  *(float *)(iVar2 + 0x9d40) = fVar1 - _DAT_004bc610;
  *(float *)(iVar2 + 0x9d4c) = fVar3;
  fVar1 = param_5;
  if (param_3 < param_5) {
    fVar1 = param_3;
    param_3 = param_5;
  }
  fVar3 = param_3 - _DAT_004bc614;
  *(float *)(iVar2 + 0x9d48) = fVar1 - _DAT_004bc610;
  *(float *)(iVar2 + 0x9d54) = fVar3;
  return;
}


