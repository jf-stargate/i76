/*
 * Program: i76shell.dll
 * Function: rebuild_directplay_session_pointer_list
 * Entry: 100304e8
 * Signature: undefined __stdcall rebuild_directplay_session_pointer_list(void)
 */


void rebuild_directplay_session_pointer_list(void)

{
  bool bVar1;
  size_t sVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  size_t _NumOfElements;
  int *piVar7;
  char *pcVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 *puVar12;
  bool bVar13;
  undefined4 *local_c;
  int local_4;
  
  _NumOfElements = DAT_100f3558;
  bVar1 = false;
  if (0 < DAT_100f3558) {
    piVar7 = &DAT_100f4970;
    iVar4 = DAT_100f3558;
    do {
      iVar4 = iVar4 + -1;
      *piVar7 = *piVar7 + 1;
      piVar7 = piVar7 + 0x17;
    } while (iVar4 != 0);
  }
  if (0 < DAT_100f3568) {
    local_c = &DAT_100f4bf8;
    local_4 = DAT_100f3568;
    bVar1 = false;
    do {
      sVar2 = 0;
      if (0 < (int)_NumOfElements) {
        pcVar6 = &DAT_100f4938;
LAB_10030536:
        iVar4 = 2;
        bVar13 = true;
        pcVar8 = pcVar6;
        pcVar11 = (char *)(local_c + 8);
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar13 = *pcVar8 == *pcVar11;
          pcVar8 = pcVar8 + 1;
          pcVar11 = pcVar11 + 1;
        } while (bVar13);
        if (!bVar13) goto code_r0x1003054a;
        puVar10 = local_c;
        puVar3 = &DAT_100f4918 + sVar2 * 0x17;
        for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar3 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar3 = puVar3 + 1;
        }
        (&DAT_100f4970)[sVar2 * 0x17] = 0;
      }
LAB_1003057a:
      if (sVar2 == _NumOfElements) {
        _NumOfElements = _NumOfElements + 1;
        puVar10 = local_c;
        puVar3 = &DAT_100f4918 + sVar2 * 0x17;
        for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar3 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar3 = puVar3 + 1;
        }
        bVar1 = true;
      }
      local_c = local_c + 0x17;
      local_4 = local_4 + -1;
      DAT_100f3558 = _NumOfElements;
    } while (local_4 != 0);
  }
  iVar4 = 0;
  if (0 < (int)_NumOfElements) {
    puVar3 = &DAT_100f4918;
    piVar7 = &DAT_100f4970;
    puVar10 = &DAT_100f4918 + _NumOfElements * 0x17;
    do {
      if (*piVar7 != 0) {
        puVar10 = puVar10 + -0x17;
        _NumOfElements = _NumOfElements - 1;
        iVar4 = iVar4 + -1;
        puVar9 = puVar10;
        puVar12 = puVar3;
        for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar12 = *puVar9;
          puVar9 = puVar9 + 1;
          puVar12 = puVar12 + 1;
        }
        piVar7 = piVar7 + -0x17;
        puVar3 = puVar3 + -0x17;
        bVar1 = true;
      }
      iVar4 = iVar4 + 1;
      piVar7 = piVar7 + 0x17;
      puVar3 = puVar3 + 0x17;
      DAT_100f3558 = _NumOfElements;
    } while (iVar4 < (int)_NumOfElements);
  }
  if (bVar1) {
    qsort(&DAT_100f4918,_NumOfElements,0x5c,(_PtFuncCompare *)&LAB_100306e8);
    clear_pointer_list(DAT_100f21d4);
    iVar4 = 0;
    if (0 < DAT_100f3558) {
      puVar10 = &DAT_100f4918;
      do {
        insert_pointer_list_item_sorted_or_append((int)DAT_100f21d4,(int)puVar10,(undefined *)0x0);
        iVar4 = iVar4 + 1;
        puVar10 = puVar10 + 0x17;
      } while (iVar4 < DAT_100f3558);
    }
  }
  return;
code_r0x1003054a:
  sVar2 = sVar2 + 1;
  pcVar6 = pcVar6 + 0x5c;
  if ((int)_NumOfElements <= (int)sVar2) goto LAB_1003057a;
  goto LAB_10030536;
}


