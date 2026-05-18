/*
 * Program: i76.exe
 * Function: apply_longitudinal_drag_force_to_velocity
 * Entry: 0043c850
 * Signature: undefined __cdecl apply_longitudinal_drag_force_to_velocity(int param_1, float param_2, undefined4 param_3, float * param_4)
 */


/* [cgpt i76.exe vehicle drivetrain/contact renames v33; confidence=medium-high] Applies a
   longitudinal drag/braking force along the vehicle forward vector into a velocity accumulator. */

void __cdecl
apply_longitudinal_drag_force_to_velocity
          (int param_1,float param_2,undefined4 param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  
  fVar1 = *(float *)(param_1 + 0x1c);
  iVar3 = *(int *)(param_1 + 0x70);
  fVar2 = *(float *)(param_1 + 0x20);
  fVar4 = -((*(float *)(iVar3 + 0xc4) * fVar2 +
            *(float *)(iVar3 + 0xc0) * fVar1 + *(float *)(param_1 + 0x18) * *(float *)(iVar3 + 0xbc)
            ) * *(float *)(iVar3 + 0xb0) * param_2);
  *param_4 = *param_4 + *(float *)(param_1 + 0x18) * fVar4;
  param_4[1] = param_4[1] + fVar1 * fVar4;
  param_4[2] = param_4[2] + fVar2 * fVar4;
  return;
}


