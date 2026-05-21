/*
 * Program: i76shell.dll
 * Function: mpack_database_get_item_alloc_or_alias
 * Entry: 10008320
 * Signature: undefined4 __thiscall mpack_database_get_item_alloc_or_alias(void * this, SIZE_T param_1, undefined4 * param_2, SIZE_T * param_3)
 */


undefined4 __thiscall
mpack_database_get_item_alloc_or_alias
          (void *this,SIZE_T param_1,undefined4 *param_2,SIZE_T *param_3)

{
  undefined1 uVar1;
  long *plVar2;
  int iVar3;
  size_t sVar4;
  undefined1 *puVar5;
  uint uVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  
  if ((*(int *)(*(int *)((int)this + 0x88) + 4) < (int)param_1) || ((int)param_1 < 0)) {
    plVar2 = (long *)0x0;
  }
  else {
    plVar2 = (long *)FUN_10003610(*(int *)((int)this + 0x88),param_1 - 1);
  }
  if (plVar2 == (long *)0x0) {
    return 1;
  }
  iVar3 = fseek(*(FILE **)((int)this + 0x80),*plVar2,0);
  if (iVar3 != 0) {
    return 1;
  }
  sVar4 = fread(&param_1,4,1,*(FILE **)((int)this + 0x80));
  if (sVar4 != 1) {
    return 1;
  }
  puVar5 = HeapAlloc(DAT_10051c50,1,param_1);
  if (puVar5 == (undefined1 *)0x0) {
    fprintf((FILE *)(_iob_exref + 0x40),s_Out_of_memory_in_TMPackDataBaseO_10043b78);
    fflush((FILE *)(_iob_exref + 0x40));
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  *param_2 = puVar5;
  *param_3 = param_1;
  puVar9 = (undefined4 *)&DAT_10052178;
  for (iVar3 = 0x400; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  puVar10 = &DAT_10052178;
  param_2 = (undefined4 *)0x2;
  while (0 < (int)param_1) {
    param_2 = (undefined4 *)((uint)param_2 >> 1);
    if (param_2 == (undefined4 *)0x1) {
      uVar6 = fgetc(*(FILE **)((int)this + 0x80));
      param_2 = (undefined4 *)(uVar6 | 0x100);
    }
    if (((uint)param_2 & 1) == 0) {
      iVar3 = fgetc(*(FILE **)((int)this + 0x80));
      iVar7 = fgetc(*(FILE **)((int)this + 0x80));
      uVar6 = iVar3 + iVar7 * 0x100;
      iVar3 = ((int)uVar6 >> 0xc & 0xfU) + 3;
      puVar8 = &DAT_10052178 + (uVar6 & 0xfff);
      param_1 = param_1 - iVar3;
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        uVar1 = *puVar8;
        *puVar10 = uVar1;
        *puVar5 = uVar1;
        puVar10 = puVar10 + 1;
        puVar8 = puVar8 + 1;
        if (puVar10 == &DAT_10053178) {
          puVar10 = &DAT_10052178;
        }
        if (puVar8 == &DAT_10053178) {
          puVar8 = &DAT_10052178;
        }
        puVar5 = puVar5 + 1;
      }
    }
    else {
      param_1 = param_1 - 1;
      iVar3 = fgetc(*(FILE **)((int)this + 0x80));
      *puVar10 = (char)iVar3;
      *puVar5 = (char)iVar3;
      puVar5 = puVar5 + 1;
      puVar10 = puVar10 + 1;
      if (puVar10 == &DAT_10053178) {
        puVar10 = &DAT_10052178;
      }
    }
  }
  return 0;
}


