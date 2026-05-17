/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_linked_object_obj_records
 * Entry: 0040152d
 * Signature: int __cdecl i76edit_export_runtime_linked_object_obj_records(int param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

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
  int iStack_78;
  int iStack_74;
  long lStack_70;
  undefined *puStack_6c;
  int iStack_68;
  char acStack_64 [92];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  DAT_00436494 = 0;
  iStack_78 = 0;
  iStack_74 = 0;
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
      ppuVar5 = &puStack_6c;
      for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
        *ppuVar5 = (undefined *)0x0;
        ppuVar5 = ppuVar5 + 1;
      }
      pcVar6 = acStack_64;
      for (iVar3 = 0x19; iVar3 != 0; iVar3 = iVar3 + -1) {
        pcVar6[0] = '\0';
        pcVar6[1] = '\0';
        pcVar6[2] = '\0';
        pcVar6[3] = '\0';
        pcVar6 = pcVar6 + 4;
      }
      puStack_6c = &DAT_004a424f;
      iStack_68 = 0x6c;
      if (DAT_0043c540 != (FILE *)0x0) {
        _fprintf(DAT_0043c540,s_File___s_00434768,iVar2 + 0x20);
      }
      uStack_8 = *(undefined4 *)(iVar2 + 0x1c);
      uStack_4 = *(undefined4 *)(iVar2 + 0x60);
      _strncpy(acStack_64,(char *)(iVar2 + 0x20),8);
      _Offset = __tell(param_1);
      __write(param_1,&puStack_6c,0x6c);
      _Offset_00 = __tell(param_1);
      __write(param_1,&iStack_74,4);
      iStack_74 = i76edit_export_linked_object_sampled_segments(param_1,(int)param_2);
      lStack_70 = __tell(param_1);
      __lseek(param_1,_Offset,0);
      iStack_68 = iStack_74 * 0xc + 0x70;
      iVar2 = __write(param_1,&puStack_6c,0x6c);
      __lseek(param_1,_Offset_00,0);
      iVar3 = __write(param_1,&iStack_74,4);
      __lseek(param_1,lStack_70,0);
      DAT_0043bd14 = DAT_0043bd14 + 1;
      iStack_78 = iStack_78 + iVar2 + iVar3 + iStack_74 * 0xc;
      iVar2 = param_2[2] + 0x78;
      uVar1 = *(uint *)(param_2[2] + 200);
      while ((uVar1 & 1) != 0) {
        if (param_2 == (int *)0x0) {
          return iStack_78;
        }
        param_2 = (int *)*param_2;
        if (param_2 != (int *)0x0) {
          iVar2 = param_2[2] + 0x78;
        }
        uVar1 = *(uint *)(iVar2 + 0x50);
      }
    }
  }
  return iStack_78;
}


