/*
 * Program: i76shell.dll
 * Function: compact_or_update_directplay_player_records
 * Entry: 10030338
 * Signature: undefined __stdcall compact_or_update_directplay_player_records(void)
 */


void compact_or_update_directplay_player_records(void)

{
  undefined4 uVar1;
  bool bVar2;
  size_t sVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  size_t _NumOfElements;
  int *piVar7;
  undefined4 *puVar8;
  char *pcVar9;
  undefined4 *puVar10;
  char *pcVar11;
  undefined4 *puVar12;
  bool bVar13;
  int *local_c;
  int local_4;
  
  _NumOfElements = DAT_100f224c;
  bVar2 = false;
  if (0 < DAT_100f224c) {
    piVar7 = &DAT_100f23a8;
    iVar5 = DAT_100f224c;
    do {
      iVar5 = iVar5 + -1;
      *piVar7 = *piVar7 + 1;
      piVar7 = piVar7 + 0x24;
    } while (iVar5 != 0);
  }
  if (0 < DAT_100f4770) {
    local_c = (int *)&DAT_100f35e8;
    local_4 = DAT_100f4770;
    bVar2 = false;
    do {
      sVar3 = 0;
      if (0 < (int)_NumOfElements) {
        piVar7 = &DAT_100f23a0;
        do {
          iVar5 = 2;
          bVar13 = true;
          pcVar9 = (char *)((int)piVar7 + -0x49);
          pcVar11 = (char *)((int)local_c + -0x49);
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar13 = *pcVar9 == *pcVar11;
            pcVar9 = pcVar9 + 1;
            pcVar11 = pcVar11 + 1;
          } while (bVar13);
          if ((bVar13) && (*piVar7 != 0)) {
            uVar1 = *local_c;
            (&DAT_100f23a8)[sVar3 * 0x24] = 0;
            (&DAT_100f23a0)[sVar3 * 0x24] = uVar1;
            break;
          }
          sVar3 = sVar3 + 1;
          piVar7 = piVar7 + 0x24;
        } while ((int)sVar3 < (int)_NumOfElements);
      }
      if (sVar3 == _NumOfElements) {
        _NumOfElements = _NumOfElements + 1;
        puVar4 = local_c + -0x1e;
        puVar8 = &DAT_100f2328 + sVar3 * 0x24;
        for (iVar5 = 0x24; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar8 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar8 = puVar8 + 1;
        }
        bVar2 = true;
      }
      local_c = local_c + 0x24;
      local_4 = local_4 + -1;
      DAT_100f224c = _NumOfElements;
    } while (local_4 != 0);
  }
  iVar5 = 0;
  if (0 < (int)_NumOfElements) {
    puVar4 = &DAT_100f2328;
    puVar8 = &DAT_100f2328 + _NumOfElements * 0x24;
    local_c = &DAT_100f23a8;
    do {
      if (*local_c != 0) {
        puVar8 = puVar8 + -0x24;
        puVar10 = puVar8;
        puVar12 = puVar4;
        for (iVar6 = 0x24; iVar6 != 0; iVar6 = iVar6 + -1) {
          *puVar12 = *puVar10;
          puVar10 = puVar10 + 1;
          puVar12 = puVar12 + 1;
        }
        _NumOfElements = _NumOfElements - 1;
        local_c = local_c + -0x24;
        iVar5 = iVar5 + -1;
        puVar4 = puVar4 + -0x24;
        bVar2 = true;
      }
      iVar5 = iVar5 + 1;
      local_c = local_c + 0x24;
      puVar4 = puVar4 + 0x24;
      DAT_100f224c = _NumOfElements;
    } while (iVar5 < (int)_NumOfElements);
  }
  if (bVar2) {
    qsort(&DAT_100f2328,_NumOfElements,0x90,(_PtFuncCompare *)&LAB_10030688);
    _NumOfElements = DAT_100f224c;
  }
  iVar5 = 0;
  if (0 < (int)_NumOfElements) {
    puVar4 = &DAT_100f2328;
    do {
      FUN_1002cea0((int)puVar4);
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 0x24;
    } while (iVar5 < DAT_100f224c);
  }
  return;
}


