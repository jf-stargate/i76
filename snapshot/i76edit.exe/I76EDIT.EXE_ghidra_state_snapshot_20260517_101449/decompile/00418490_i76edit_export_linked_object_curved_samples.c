/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_linked_object_curved_samples
 * Entry: 00418490
 * Signature: int __cdecl i76edit_export_linked_object_curved_samples(int param_1, int param_2, int param_3, float param_4, undefined4 param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v6:medium] Alternate curved/smoothed linked-object segment sampler;
   calls trig helpers and i76edit_write_scaled_xy_height_sample. */

int __cdecl
i76edit_export_linked_object_curved_samples
          (int param_1,int param_2,int param_3,float param_4,undefined4 param_5)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float10 fVar7;
  float fStack_30;
  float local_1c;
  float local_18;
  float local_14;
  float fStack_c;
  float fStack_8;
  
  iVar6 = 0;
  local_1c = 0.0;
  pfVar1 = (float *)(param_3 * 0x24 + 0x10 + param_2);
  thunk_FUN_00402e70(pfVar1,(float *)(param_2 + param_3 * 0xc + 0x1c),
                     (float *)(param_2 + param_3 * -0xc + 0x28),
                     (float *)(param_3 * -0x24 + param_2 + 0x34));
  fVar7 = thunk_FUN_00402f40(param_4);
  fVar2 = (float)fVar7;
  local_18 = *pfVar1;
  local_14 = *(float *)(param_3 * 0x24 + param_2 + 0x14);
  thunk_FUN_00403020(fVar2);
  thunk_FUN_00403070(fVar2);
  fVar7 = (float10)FUN_0042357a(param_5);
  fStack_30 = (float)fVar7;
  fVar7 = thunk_FUN_00403020(fStack_30);
  local_18 = (float)fVar7;
  fVar7 = thunk_FUN_00403070(fStack_30);
  local_14 = (float)fVar7;
  fVar2 = fVar2 * _DAT_004321ac;
  fStack_30 = fVar2 + fStack_30;
  if (fStack_30 < _DAT_004321a8) {
    do {
      fVar7 = thunk_FUN_00403020(fStack_30);
      fVar3 = (float)fVar7;
      fVar7 = thunk_FUN_00403070(fStack_30);
      fVar4 = (float)fVar7;
      local_1c = SQRT((fVar4 - local_14) * (fVar4 - local_14) +
                      (fVar3 - local_18) * (fVar3 - local_18)) + local_1c;
      if ((param_4 < local_1c) &&
         (local_1c = 0.0,
         _DAT_0043bd1c <=
         (fVar3 - fStack_c) * (fVar3 - fStack_c) + (fVar4 - fStack_8) * (fVar4 - fStack_8))) {
        iVar5 = i76edit_write_scaled_xy_height_sample(param_1,&local_18);
        iVar6 = iVar6 + iVar5;
        fStack_c = fVar3;
        fStack_8 = fVar4;
      }
      fStack_30 = fVar2 + fStack_30;
      local_18 = fVar3;
      local_14 = fVar4;
    } while (fStack_30 < _DAT_004321a8);
  }
  return iVar6;
}


