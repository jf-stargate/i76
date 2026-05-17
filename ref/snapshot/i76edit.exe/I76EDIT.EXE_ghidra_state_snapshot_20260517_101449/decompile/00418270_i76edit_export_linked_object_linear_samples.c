/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_linked_object_linear_samples
 * Entry: 00418270
 * Signature: int __cdecl i76edit_export_linked_object_linear_samples(int param_1, int param_2, int param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v6:medium] Samples linked-object segment geometry and calls
   i76edit_write_scaled_xy_height_sample for each accepted sample. */

int __cdecl
i76edit_export_linked_object_linear_samples(int param_1,int param_2,int param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_c;
  float fStack_8;
  
  iVar6 = 0;
  iVar5 = param_3 * -0x24 + param_2;
  iVar4 = param_3 * 0x24 + param_2;
  fVar1 = *(float *)(iVar5 + 0x34) - *(float *)(iVar4 + 0x10);
  fVar2 = *(float *)(iVar5 + 0x38) - *(float *)(iVar4 + 0x14);
  fStack_20 = *(float *)(iVar4 + 0x10);
  fStack_24 = *(float *)(iVar4 + 0x14);
  fVar3 = param_4 / SQRT(fVar2 * fVar2 + fVar1 * fVar1);
  fVar7 = (float10)FUN_0042357a(fStack_20);
  fStack_c = (float)((float10)fVar1 * fVar7 + (float10)fStack_20);
  fStack_8 = (float)((float10)fVar2 * fVar7 + (float10)fStack_24);
  fStack_1c = (float)(fVar7 + (float10)fVar3);
  if (fVar7 + (float10)fVar3 < (float10)_DAT_004321a8) {
    fStack_24 = fVar2 * fStack_1c + fStack_24;
    fStack_20 = fVar1 * fStack_1c + fStack_20;
    do {
      if (_DAT_0043bd1c <=
          (fStack_20 - fStack_c) * (fStack_20 - fStack_c) +
          (fStack_24 - fStack_8) * (fStack_24 - fStack_8)) {
        iVar4 = i76edit_write_scaled_xy_height_sample(param_1,&fStack_c);
        iVar6 = iVar6 + iVar4;
        fStack_c = fStack_20;
        fStack_8 = fStack_24;
      }
      fStack_24 = fStack_24 + fVar2 * fVar3;
      fStack_20 = fStack_20 + fVar1 * fVar3;
      fStack_1c = fVar3 + fStack_1c;
    } while (fStack_1c < _DAT_004321a8);
  }
  return iVar6;
}


