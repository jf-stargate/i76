/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_linked_object_obj_records
 * Entry: 00417ef0
 * Signature: int __cdecl i76edit_export_runtime_linked_object_obj_records(int param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v5:medium] Serializes runtime linked-object records, patches record
   count/size via lseek/write, and advances through linked-object list until completion.
   
   [cgpt_i76edit_level_renames_v6:high] Runtime linked-object exporter. Emits OBJ records of size
   0x6c for linked/spline-like objects and follows helper 004181c0 to emit sampled
   geometry/positions. */

int __cdecl i76edit_export_runtime_linked_object_obj_records(int param_1,int *param_2)

{
  uint uVar1;
  long _Offset;
  long _Offset_00;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined **ppuVar5;
  char *pcVar6;
  double dVar7;
  int local_78;
  int local_74;
  long local_70;
  undefined *local_6c;
  int local_68;
  char local_64 [92];
  undefined4 local_8;
  undefined4 local_4;
  
  DAT_00436494 = 0;
  local_78 = 0;
  local_74 = 0;
  piVar4 = param_2;
  if (param_2 != (int *)0x0) {
    do {
      iVar2 = piVar4[2];
      *(uint *)(iVar2 + 200) = *(uint *)(iVar2 + 200) & 0xfffffffe;
      if ((*(float *)(iVar2 + 0x88) == *(float *)(iVar2 + 0xac)) &&
         (*(float *)(iVar2 + 0x8c) == *(float *)(iVar2 + 0xb0))) {
        thunk_FUN_0040f3f0(piVar4);
        return -1;
      }
      piVar4 = (int *)*piVar4;
    } while (piVar4 != (int *)0x0);
    while (param_2 != (int *)0x0) {
      iVar2 = param_2[2];
      dVar7 = _atof((char *)(iVar2 + 0x6d));
      _DAT_0043bd1c = (float)dVar7 * _DAT_0043219c * (float)dVar7 * _DAT_0043219c;
      ppuVar5 = &local_6c;
      for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
        *ppuVar5 = (undefined *)0x0;
        ppuVar5 = ppuVar5 + 1;
      }
      pcVar6 = local_64;
      for (iVar3 = 0x19; iVar3 != 0; iVar3 = iVar3 + -1) {
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        pcVar6 = pcVar6 + 4;
      }
      local_6c = &DAT_004a424f;
      local_68 = 0x6c;
      if (DAT_0043c540 != (FILE *)0x0) {
        _fprintf(DAT_0043c540,s_File___s_00434768,iVar2 + 0x20);
      }
      local_8 = *(undefined4 *)(iVar2 + 0x1c);
      local_4 = *(undefined4 *)(iVar2 + 0x60);
      _strncpy(local_64,(char *)(iVar2 + 0x20),8);
      _Offset = __tell(param_1);
      __write(param_1,&local_6c,0x6c);
      _Offset_00 = __tell(param_1);
      __write(param_1,&local_74,4);
      local_74 = i76edit_export_linked_object_sampled_segments(param_1,(int)param_2);
      local_70 = __tell(param_1);
      __lseek(param_1,_Offset,0);
      local_68 = local_74 * 0xc + 0x70;
      iVar2 = __write(param_1,&local_6c,0x6c);
      __lseek(param_1,_Offset_00,0);
      iVar3 = __write(param_1,&local_74,4);
      __lseek(param_1,local_70,0);
      DAT_0043bd14 = DAT_0043bd14 + 1;
      local_78 = local_78 + iVar2 + iVar3 + local_74 * 0xc;
      iVar2 = param_2[2] + 0x78;
      uVar1 = *(uint *)(param_2[2] + 200);
      while ((uVar1 & 1) != 0) {
        if (param_2 == (int *)0x0) {
          return local_78;
        }
        param_2 = (int *)*param_2;
        if (param_2 != (int *)0x0) {
          iVar2 = param_2[2] + 0x78;
        }
        uVar1 = *(uint *)(iVar2 + 0x50);
      }
    }
  }
  return local_78;
}


