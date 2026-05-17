/*
 * Program: i76.exe
 * Function: compose_matrix_or_transform_b
 * Entry: 00494f70
 * Signature: undefined __thiscall compose_matrix_or_transform_b(void * this, float * param_1)
 */


/* [cgpt i76.exe vehicle object rename v7; confidence=medium] Builds a rearranged/inverse-style
   affine transform from the object matrix; exact row/column convention still needs math validation.
    */

void __thiscall compose_matrix_or_transform_b(void *this,float *param_1)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  float10 in_ST0;
  float10 in_ST1;
  float10 in_ST2;
  float10 fVar5;
  float10 in_ST3;
  float10 fVar6;
  
  fVar1 = *(float *)((int)this + 0xc);
  fVar2 = *(float *)((int)this + 0x18);
  *param_1 = *(float *)this;
  param_1[1] = fVar1;
  param_1[2] = fVar2;
  fVar1 = *(float *)((int)this + 0x10);
  fVar2 = *(float *)((int)this + 0x1c);
  param_1[3] = *(float *)((int)this + 4);
  param_1[4] = fVar1;
  param_1[5] = fVar2;
  fVar1 = *(float *)((int)this + 0x14);
  fVar2 = *(float *)((int)this + 0x20);
  param_1[6] = *(float *)((int)this + 8);
  param_1[7] = fVar1;
  param_1[8] = fVar2;
  iVar4 = 3;
  pfVar3 = this;
  do {
    fVar6 = in_ST3;
    fVar5 = in_ST2;
    in_ST3 = in_ST1;
    in_ST2 = in_ST0;
    in_ST1 = (float10)pfVar3[2] * (float10)*(double *)((int)this + 0x38);
    in_ST0 = (float10)*pfVar3 * (float10)*(double *)((int)this + 0x28) +
             (float10)pfVar3[1] * (float10)*(double *)((int)this + 0x30);
    pfVar3 = pfVar3 + 3;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(double *)(param_1 + 0xe) = (double)-(in_ST0 + in_ST1);
  *(double *)(param_1 + 10) = (double)-(fVar6 + fVar5);
  *(double *)(param_1 + 0xc) = (double)-(in_ST2 + in_ST3);
  return;
}


