/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00418870
 * Entry: 004011c7
 * Signature: undefined __cdecl thunk_FUN_00418870(char * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl thunk_FUN_00418870(char *param_1)

{
  char cVar1;
  long lVar2;
  int _FileHandle;
  int iVar3;
  long *_DstBuf;
  int iVar4;
  int *_DstBuf_00;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  ushort *puVar8;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  char *pcVar9;
  undefined4 *puVar10;
  byte *pbVar11;
  undefined4 unaff_EDI;
  char *pcVar12;
  char *pcVar13;
  undefined4 *puVar14;
  long *plVar15;
  long *plVar16;
  int iStack_12c;
  byte *pbStack_128;
  undefined *puStack_124;
  int iStack_120;
  int iStack_11c;
  int iStack_118;
  char acStack_114 [16];
  int iStack_104;
  char acStack_100 [256];
  
  iStack_11c = 0;
  iStack_120 = 0;
  iStack_12c = 0;
  thunk_FUN_00411810(0);
  thunk_FUN_00409e50();
  thunk_FUN_0040ce70();
  thunk_FUN_0041e120(s_Clearing_Zones____00436708);
  thunk_FUN_0041e990();
  _sprintf(acStack_100,s_Opening__s____004366f8,param_1);
  thunk_FUN_0041e120(acStack_100);
  _FileHandle = __open(param_1,0x8000);
  if (_FileHandle == 0) {
    _sprintf(acStack_100,s___s__is_not_an_Iterstate__76_Mis_004366c4,param_1);
    MessageBoxA(DAT_01642370,acStack_100,s_File_Error_004366b4,0);
    __close(0);
    return;
  }
  __read(_FileHandle,acStack_100,4);
  iVar3 = _strncmp(acStack_100,&DAT_004366ac,4);
  if (iVar3 != 0) {
    _sprintf(acStack_100,s___s__is_not_an_Iterstate__76_Mis_004366c4,param_1);
    MessageBoxA(DAT_01642370,acStack_100,s_File_Error_004366b4,0);
    __close(_FileHandle);
    return;
  }
  thunk_FUN_0041e120(s_Loading____0043669c);
  __read(_FileHandle,&puStack_124,4);
  do {
    if (puStack_124 == &DAT_00444e45) {
      thunk_FUN_0041e120(s_Ready__00434590);
      __close(_FileHandle);
      return;
    }
    if (puStack_124 < (undefined *)0x44414f53) {
      if (puStack_124 == (undefined *)0x44414f52) {
        thunk_FUN_0041e120(s_Loading_Roads____0043665c);
        thunk_FUN_00415ae0(_FileHandle,unaff_EBP,unaff_EDI,unaff_ESI);
      }
      else {
        if (puStack_124 != &DAT_004a424f) {
LAB_004189f0:
          _sprintf(acStack_100,s_Invalid_chunk_tag___00436610);
          _strncat(acStack_100,(char *)&puStack_124,4);
          uVar5 = 0xffffffff;
          pcVar9 = (char *)&DAT_0043660c;
          break;
        }
        thunk_FUN_0041e120(s_Loading_Objects____00436644);
        thunk_FUN_00409eb0(_FileHandle,iStack_11c);
        if (iStack_11c < 3) {
          thunk_FUN_0040f470();
          thunk_FUN_0040f170();
        }
        else {
          thunk_FUN_0040f4e0(_FileHandle,unaff_EBP,unaff_EDI,unaff_ESI);
        }
      }
    }
    else if (puStack_124 < (undefined *)0x454e4f5b) {
      if (puStack_124 == (undefined *)0x454e4f5a) {
        thunk_FUN_0041e120(s_Loading_Terrain____00436684);
        iVar3 = 0;
        thunk_FUN_004123a0(_FileHandle,iStack_120);
        do {
          thunk_FUN_0040d940(iVar3,&iStack_118,&iStack_104);
          if (iStack_118 != -1) {
            thunk_FUN_004187e0(iVar3,iStack_120);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < 0x50);
        if (3 < iStack_120) {
          thunk_FUN_0040ca50(_FileHandle,unaff_EBP,unaff_EDI,unaff_ESI);
        }
      }
      else {
        if (puStack_124 != (undefined *)0x444c5257) goto LAB_004189f0;
        if (iStack_12c < 8) {
          puVar10 = &DAT_01641fc0;
          for (iVar3 = 0x4f; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar10 = 0;
            puVar10 = puVar10 + 1;
          }
          *(undefined2 *)puVar10 = 0;
          DAT_016420ea = 600;
          if (iStack_12c < 7) {
            if (iStack_12c < 6) {
              if (iStack_12c < 5) {
                if (iStack_12c < 4) {
                  if (iStack_12c < 3) {
                    if (iStack_12c == 0) {
                      _DstBuf = _malloc(0x76);
                      uVar5 = 0x76;
                    }
                    else {
                      _DstBuf = _malloc(0xd6);
                      uVar5 = 0xd6;
                    }
                    __read(_FileHandle,_DstBuf,uVar5);
                    DAT_01641fc0 = *_DstBuf;
                    DAT_01642046 = *(long *)((int)_DstBuf + 0x52);
                    uVar5 = 0xffffffff;
                    plVar15 = _DstBuf + 1;
                    do {
                      plVar16 = plVar15;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      plVar16 = (long *)((int)plVar15 + 1);
                      lVar2 = *plVar15;
                      plVar15 = plVar16;
                    } while ((char)lVar2 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = (char *)&DAT_01641fc4;
                    do {
                      pcVar13 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    pcVar9 = (char *)((int)plVar16 - uVar5);
                    pcVar13 = pcVar13 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    uVar5 = 0xffffffff;
                    pcVar9 = (char *)((int)_DstBuf + 0x11);
                    do {
                      pcVar13 = pcVar9;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = &DAT_01641fd1;
                    do {
                      pcVar12 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar12 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar12;
                    } while (cVar1 != '\0');
                    pcVar9 = pcVar13 + -uVar5;
                    pcVar13 = pcVar12 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    uVar5 = 0xffffffff;
                    pcVar9 = (char *)((int)_DstBuf + 0x1e);
                    do {
                      pcVar13 = pcVar9;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = &DAT_01641fde;
                    do {
                      pcVar12 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar12 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar12;
                    } while (cVar1 != '\0');
                    pcVar9 = pcVar13 + -uVar5;
                    pcVar13 = pcVar12 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    uVar5 = 0xffffffff;
                    pcVar9 = (char *)((int)_DstBuf + 0x2b);
                    do {
                      pcVar13 = pcVar9;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = &DAT_01641feb;
                    do {
                      pcVar12 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar12 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar12;
                    } while (cVar1 != '\0');
                    pcVar9 = pcVar13 + -uVar5;
                    pcVar13 = pcVar12 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    uVar5 = 0xffffffff;
                    plVar15 = _DstBuf + 0xe;
                    do {
                      plVar16 = plVar15;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      plVar16 = (long *)((int)plVar15 + 1);
                      lVar2 = *plVar15;
                      plVar15 = plVar16;
                    } while ((char)lVar2 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = &DAT_01641ff8;
                    do {
                      pcVar13 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    pcVar9 = (char *)((int)plVar16 - uVar5);
                    pcVar13 = pcVar13 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    uVar5 = 0xffffffff;
                    pcVar9 = (char *)((int)_DstBuf + 0x45);
                    do {
                      pcVar13 = pcVar9;
                      if (uVar5 == 0) break;
                      uVar5 = uVar5 - 1;
                      pcVar13 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar13;
                    } while (cVar1 != '\0');
                    uVar5 = ~uVar5;
                    iVar3 = -1;
                    pcVar9 = &DAT_01642005;
                    do {
                      pcVar12 = pcVar9;
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      pcVar12 = pcVar9 + 1;
                      cVar1 = *pcVar9;
                      pcVar9 = pcVar12;
                    } while (cVar1 != '\0');
                    pcVar9 = pcVar13 + -uVar5;
                    pcVar13 = pcVar12 + -1;
                    for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                      pcVar9 = pcVar9 + 4;
                      pcVar13 = pcVar13 + 4;
                    }
                    for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                      *pcVar13 = *pcVar9;
                      pcVar9 = pcVar9 + 1;
                      pcVar13 = pcVar13 + 1;
                    }
                    goto LAB_00419cb0;
                  }
                  _DstBuf = _malloc(0xe3);
                  __read(_FileHandle,_DstBuf,0xe3);
                  DAT_01641fc0 = *_DstBuf;
                  DAT_01642046 = *(long *)((int)_DstBuf + 0x5f);
                  uVar5 = 0xffffffff;
                  plVar15 = _DstBuf + 1;
                  do {
                    plVar16 = plVar15;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    plVar16 = (long *)((int)plVar15 + 1);
                    lVar2 = *plVar15;
                    plVar15 = plVar16;
                  } while ((char)lVar2 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = (char *)&DAT_01641fc4;
                  do {
                    pcVar13 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  pcVar9 = (char *)((int)plVar16 - uVar5);
                  pcVar13 = pcVar13 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x11);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641fd1;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x1e);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641fde;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x2b);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641feb;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  plVar15 = _DstBuf + 0xe;
                  do {
                    plVar16 = plVar15;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    plVar16 = (long *)((int)plVar15 + 1);
                    lVar2 = *plVar15;
                    plVar15 = plVar16;
                  } while ((char)lVar2 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641ff8;
                  do {
                    pcVar13 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  pcVar9 = (char *)((int)plVar16 - uVar5);
                  pcVar13 = pcVar13 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x45);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01642005;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  DAT_0164205e = *(undefined4 *)((int)_DstBuf + 0x73);
                  DAT_01642062 = *(undefined4 *)((int)_DstBuf + 0x77);
                  DAT_01642066 = *(undefined4 *)((int)_DstBuf + 0x7b);
                  DAT_0164206a = *(undefined4 *)((int)_DstBuf + 0x7f);
                  DAT_01642072 = *(undefined4 *)((int)_DstBuf + 0x83);
                  DAT_01642076 = *(undefined4 *)((int)_DstBuf + 0x87);
                  _DAT_0164207a = *(undefined4 *)((int)_DstBuf + 0x8b);
                  _DAT_0164207e = *(undefined4 *)((int)_DstBuf + 0x8f);
                  DAT_01642086 = *(undefined4 *)((int)_DstBuf + 0x93);
                  DAT_0164208a = *(undefined4 *)((int)_DstBuf + 0x97);
                  _DAT_0164208e = *(undefined4 *)((int)_DstBuf + 0x9b);
                  _DAT_01642092 = *(undefined4 *)((int)_DstBuf + 0x9f);
                  _DAT_0164209a = *(undefined4 *)((int)_DstBuf + 0xa3);
                  _DAT_0164209e = *(undefined4 *)((int)_DstBuf + 0xa7);
                  _DAT_016420a2 = *(undefined4 *)((int)_DstBuf + 0xab);
                  _DAT_016420a6 = *(undefined4 *)((int)_DstBuf + 0xaf);
                  _DAT_016420ae = *(undefined4 *)((int)_DstBuf + 0xb3);
                  _DAT_016420b2 = *(undefined4 *)((int)_DstBuf + 0xb7);
                  _DAT_016420b6 = *(undefined4 *)((int)_DstBuf + 0xbb);
                  _DAT_016420ba = *(undefined4 *)((int)_DstBuf + 0xbf);
                }
                else {
                  _DstBuf = _malloc(0x103);
                  __read(_FileHandle,_DstBuf,0x103);
                  DAT_01641fc0 = *_DstBuf;
                  DAT_01642046 = *(long *)((int)_DstBuf + 0x5f);
                  uVar5 = 0xffffffff;
                  plVar15 = _DstBuf + 1;
                  do {
                    plVar16 = plVar15;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    plVar16 = (long *)((int)plVar15 + 1);
                    lVar2 = *plVar15;
                    plVar15 = plVar16;
                  } while ((char)lVar2 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = (char *)&DAT_01641fc4;
                  do {
                    pcVar13 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  pcVar9 = (char *)((int)plVar16 - uVar5);
                  pcVar13 = pcVar13 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x11);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641fd1;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x1e);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641fde;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x2b);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641feb;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  plVar15 = _DstBuf + 0xe;
                  do {
                    plVar16 = plVar15;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    plVar16 = (long *)((int)plVar15 + 1);
                    lVar2 = *plVar15;
                    plVar15 = plVar16;
                  } while ((char)lVar2 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01641ff8;
                  do {
                    pcVar13 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  pcVar9 = (char *)((int)plVar16 - uVar5);
                  pcVar13 = pcVar13 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  uVar5 = 0xffffffff;
                  pcVar9 = (char *)((int)_DstBuf + 0x45);
                  do {
                    pcVar13 = pcVar9;
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    pcVar13 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar13;
                  } while (cVar1 != '\0');
                  uVar5 = ~uVar5;
                  iVar3 = -1;
                  pcVar9 = &DAT_01642005;
                  do {
                    pcVar12 = pcVar9;
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    pcVar12 = pcVar9 + 1;
                    cVar1 = *pcVar9;
                    pcVar9 = pcVar12;
                  } while (cVar1 != '\0');
                  pcVar9 = pcVar13 + -uVar5;
                  pcVar13 = pcVar12 + -1;
                  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                    pcVar9 = pcVar9 + 4;
                    pcVar13 = pcVar13 + 4;
                  }
                  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                    *pcVar13 = *pcVar9;
                    pcVar9 = pcVar9 + 1;
                    pcVar13 = pcVar13 + 1;
                  }
                  DAT_0164205e = *(undefined4 *)((int)_DstBuf + 0x77);
                  DAT_01642062 = *(undefined4 *)((int)_DstBuf + 0x7b);
                  DAT_01642066 = *(undefined4 *)((int)_DstBuf + 0x7f);
                  DAT_0164206a = *(undefined4 *)((int)_DstBuf + 0x83);
                  DAT_0164206e = *(undefined4 *)((int)_DstBuf + 0x87);
                  DAT_01642072 = *(undefined4 *)((int)_DstBuf + 0x8b);
                  DAT_01642076 = *(undefined4 *)((int)_DstBuf + 0x8f);
                  _DAT_0164207a = *(undefined4 *)((int)_DstBuf + 0x93);
                  _DAT_0164207e = *(undefined4 *)((int)_DstBuf + 0x97);
                  _DAT_01642082 = *(undefined4 *)((int)_DstBuf + 0x9b);
                  DAT_01642086 = *(undefined4 *)((int)_DstBuf + 0x9f);
                  DAT_0164208a = *(undefined4 *)((int)_DstBuf + 0xa3);
                  _DAT_0164208e = *(undefined4 *)((int)_DstBuf + 0xa7);
                  _DAT_01642092 = *(undefined4 *)((int)_DstBuf + 0xab);
                  _DAT_01642096 = *(undefined4 *)((int)_DstBuf + 0xaf);
                  _DAT_0164209a = *(undefined4 *)((int)_DstBuf + 0xb3);
                  _DAT_0164209e = *(undefined4 *)((int)_DstBuf + 0xb7);
                  _DAT_016420a2 = *(undefined4 *)((int)_DstBuf + 0xbb);
                  _DAT_016420a6 = *(undefined4 *)((int)_DstBuf + 0xbf);
                  _DAT_016420aa = *(undefined4 *)((int)_DstBuf + 0xc3);
                  _DAT_016420ae = *(undefined4 *)((int)_DstBuf + 199);
                  _DAT_016420b2 = *(undefined4 *)((int)_DstBuf + 0xcb);
                  _DAT_016420b6 = *(undefined4 *)((int)_DstBuf + 0xcf);
                  _DAT_016420ba = *(undefined4 *)((int)_DstBuf + 0xd3);
                  _DAT_016420be = *(undefined4 *)((int)_DstBuf + 0xd7);
                  if (DAT_00436498 == 0) goto LAB_00419ddc;
LAB_00419cb0:
                  DAT_0164205e = 0x3fc00000;
                  DAT_01642062 = 0x3dcccccd;
                  DAT_01642066 = 0;
                  DAT_0164206a = 0;
                  DAT_01642072 = 0x40066666;
                  DAT_01642076 = 0x3c23d70a;
                  _DAT_0164207a = 0;
                  _DAT_0164207e = 0;
                  DAT_01642086 = 0x3ff33333;
                  DAT_0164208a = 0x3cf5c28f;
                  _DAT_0164208e = 0;
                  _DAT_01642092 = 0;
                  _DAT_0164209a = 0x3fc00000;
                  _DAT_0164209e = 0x3da3d70a;
                  _DAT_016420a2 = 0;
                  _DAT_016420a6 = 0;
                  _DAT_016420ae = 0x3fc00000;
                  _DAT_016420b2 = 0x3e4ccccd;
                  _DAT_016420b6 = 0;
                  _DAT_016420ba = 0;
                }
                _DAT_016420aa = 0;
                _DAT_01642096 = 0;
                _DAT_01642082 = 0;
                DAT_0164206e = 3;
                _DAT_016420be = 0xc;
              }
              else {
                _DstBuf = _malloc(0x11d);
                __read(_FileHandle,_DstBuf,0x11d);
                DAT_01641fc0 = *_DstBuf;
                DAT_01642046 = *(long *)((int)_DstBuf + 0x79);
                uVar5 = 0xffffffff;
                plVar15 = _DstBuf + 1;
                do {
                  plVar16 = plVar15;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  plVar16 = (long *)((int)plVar15 + 1);
                  lVar2 = *plVar15;
                  plVar15 = plVar16;
                } while ((char)lVar2 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = (char *)&DAT_01641fc4;
                do {
                  pcVar13 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                pcVar9 = (char *)((int)plVar16 - uVar5);
                pcVar13 = pcVar13 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x11);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01641fd1;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x1e);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01641fde;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x2b);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01641feb;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                plVar15 = _DstBuf + 0xe;
                do {
                  plVar16 = plVar15;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  plVar16 = (long *)((int)plVar15 + 1);
                  lVar2 = *plVar15;
                  plVar15 = plVar16;
                } while ((char)lVar2 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01641ff8;
                do {
                  pcVar13 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                pcVar9 = (char *)((int)plVar16 - uVar5);
                pcVar13 = pcVar13 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x45);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01642005;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x52);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_01642012;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                pcVar9 = (char *)((int)_DstBuf + 0x5f);
                do {
                  pcVar13 = pcVar9;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_0164201f;
                do {
                  pcVar12 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar12 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar12;
                } while (cVar1 != '\0');
                pcVar9 = pcVar13 + -uVar5;
                pcVar13 = pcVar12 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                uVar5 = 0xffffffff;
                plVar15 = _DstBuf + 0x1b;
                do {
                  plVar16 = plVar15;
                  if (uVar5 == 0) break;
                  uVar5 = uVar5 - 1;
                  plVar16 = (long *)((int)plVar15 + 1);
                  lVar2 = *plVar15;
                  plVar15 = plVar16;
                } while ((char)lVar2 != '\0');
                uVar5 = ~uVar5;
                iVar3 = -1;
                pcVar9 = &DAT_0164202c;
                do {
                  pcVar13 = pcVar9;
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  pcVar13 = pcVar9 + 1;
                  cVar1 = *pcVar9;
                  pcVar9 = pcVar13;
                } while (cVar1 != '\0');
                pcVar9 = (char *)((int)plVar16 - uVar5);
                pcVar13 = pcVar13 + -1;
                for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                  *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                  pcVar9 = pcVar9 + 4;
                  pcVar13 = pcVar13 + 4;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *pcVar13 = *pcVar9;
                  pcVar9 = pcVar9 + 1;
                  pcVar13 = pcVar13 + 1;
                }
                DAT_0164205e = *(undefined4 *)((int)_DstBuf + 0x91);
                DAT_01642062 = *(undefined4 *)((int)_DstBuf + 0x95);
                DAT_01642066 = *(undefined4 *)((int)_DstBuf + 0x99);
                DAT_0164206a = *(undefined4 *)((int)_DstBuf + 0x9d);
                DAT_0164206e = *(undefined4 *)((int)_DstBuf + 0xa1);
                DAT_01642072 = *(undefined4 *)((int)_DstBuf + 0xa5);
                DAT_01642076 = *(undefined4 *)((int)_DstBuf + 0xa9);
                _DAT_0164207a = *(undefined4 *)((int)_DstBuf + 0xad);
                _DAT_0164207e = *(undefined4 *)((int)_DstBuf + 0xb1);
                _DAT_01642082 = *(undefined4 *)((int)_DstBuf + 0xb5);
                DAT_01642086 = *(undefined4 *)((int)_DstBuf + 0xb9);
                DAT_0164208a = *(undefined4 *)((int)_DstBuf + 0xbd);
                _DAT_0164208e = *(undefined4 *)((int)_DstBuf + 0xc1);
                _DAT_01642092 = *(undefined4 *)((int)_DstBuf + 0xc5);
                _DAT_01642096 = *(undefined4 *)((int)_DstBuf + 0xc9);
                _DAT_0164209a = *(undefined4 *)((int)_DstBuf + 0xcd);
                _DAT_0164209e = *(undefined4 *)((int)_DstBuf + 0xd1);
                _DAT_016420a2 = *(undefined4 *)((int)_DstBuf + 0xd5);
                _DAT_016420a6 = *(undefined4 *)((int)_DstBuf + 0xd9);
                _DAT_016420aa = *(undefined4 *)((int)_DstBuf + 0xdd);
                _DAT_016420ae = *(undefined4 *)((int)_DstBuf + 0xe1);
                _DAT_016420b2 = *(undefined4 *)((int)_DstBuf + 0xe5);
                _DAT_016420b6 = *(undefined4 *)((int)_DstBuf + 0xe9);
                _DAT_016420ba = *(undefined4 *)((int)_DstBuf + 0xed);
                _DAT_016420be = *(undefined4 *)((int)_DstBuf + 0xf1);
              }
            }
            else {
              _DstBuf = _malloc(0x12a);
              __read(_FileHandle,_DstBuf,0x12a);
              DAT_01641fc0 = *_DstBuf;
              DAT_01642046 = *(long *)((int)_DstBuf + 0x86);
              uVar5 = 0xffffffff;
              plVar15 = _DstBuf + 1;
              do {
                plVar16 = plVar15;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                plVar16 = (long *)((int)plVar15 + 1);
                lVar2 = *plVar15;
                plVar15 = plVar16;
              } while ((char)lVar2 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = (char *)&DAT_01641fc4;
              do {
                pcVar13 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              pcVar9 = (char *)((int)plVar16 - uVar5);
              pcVar13 = pcVar13 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x11);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01641fd1;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x1e);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01641fde;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x2b);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01641feb;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              plVar15 = _DstBuf + 0xe;
              do {
                plVar16 = plVar15;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                plVar16 = (long *)((int)plVar15 + 1);
                lVar2 = *plVar15;
                plVar15 = plVar16;
              } while ((char)lVar2 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01641ff8;
              do {
                pcVar13 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              pcVar9 = (char *)((int)plVar16 - uVar5);
              pcVar13 = pcVar13 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x45);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01642005;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x52);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_01642012;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              pcVar9 = (char *)((int)_DstBuf + 0x5f);
              do {
                pcVar13 = pcVar9;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_0164201f;
              do {
                pcVar12 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar12 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar12;
              } while (cVar1 != '\0');
              pcVar9 = pcVar13 + -uVar5;
              pcVar13 = pcVar12 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              uVar5 = 0xffffffff;
              plVar15 = _DstBuf + 0x1b;
              do {
                plVar16 = plVar15;
                if (uVar5 == 0) break;
                uVar5 = uVar5 - 1;
                plVar16 = (long *)((int)plVar15 + 1);
                lVar2 = *plVar15;
                plVar15 = plVar16;
              } while ((char)lVar2 != '\0');
              uVar5 = ~uVar5;
              iVar3 = -1;
              pcVar9 = &DAT_0164202c;
              do {
                pcVar13 = pcVar9;
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                pcVar13 = pcVar9 + 1;
                cVar1 = *pcVar9;
                pcVar9 = pcVar13;
              } while (cVar1 != '\0');
              pcVar9 = (char *)((int)plVar16 - uVar5);
              pcVar13 = pcVar13 + -1;
              for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                pcVar13 = pcVar13 + 4;
              }
              for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                *pcVar13 = *pcVar9;
                pcVar9 = pcVar9 + 1;
                pcVar13 = pcVar13 + 1;
              }
              DAT_0164205e = *(undefined4 *)((int)_DstBuf + 0x9e);
              DAT_01642062 = *(undefined4 *)((int)_DstBuf + 0xa2);
              DAT_01642066 = *(undefined4 *)((int)_DstBuf + 0xa6);
              DAT_0164206a = *(undefined4 *)((int)_DstBuf + 0xaa);
              DAT_0164206e = *(undefined4 *)((int)_DstBuf + 0xae);
              DAT_01642072 = *(undefined4 *)((int)_DstBuf + 0xb2);
              DAT_01642076 = *(undefined4 *)((int)_DstBuf + 0xb6);
              _DAT_0164207a = *(undefined4 *)((int)_DstBuf + 0xba);
              _DAT_0164207e = *(undefined4 *)((int)_DstBuf + 0xbe);
              _DAT_01642082 = *(undefined4 *)((int)_DstBuf + 0xc2);
              DAT_01642086 = *(undefined4 *)((int)_DstBuf + 0xc6);
              DAT_0164208a = *(undefined4 *)((int)_DstBuf + 0xca);
              _DAT_0164208e = *(undefined4 *)((int)_DstBuf + 0xce);
              _DAT_01642092 = *(undefined4 *)((int)_DstBuf + 0xd2);
              _DAT_01642096 = *(undefined4 *)((int)_DstBuf + 0xd6);
              _DAT_0164209a = *(undefined4 *)((int)_DstBuf + 0xda);
              _DAT_0164209e = *(undefined4 *)((int)_DstBuf + 0xde);
              _DAT_016420a2 = *(undefined4 *)((int)_DstBuf + 0xe2);
              _DAT_016420a6 = *(undefined4 *)((int)_DstBuf + 0xe6);
              _DAT_016420aa = *(undefined4 *)((int)_DstBuf + 0xea);
              _DAT_016420ae = *(undefined4 *)((int)_DstBuf + 0xee);
              _DAT_016420b2 = *(undefined4 *)((int)_DstBuf + 0xf2);
              _DAT_016420b6 = *(undefined4 *)((int)_DstBuf + 0xf6);
              _DAT_016420ba = *(undefined4 *)((int)_DstBuf + 0xfa);
              _DAT_016420be = *(undefined4 *)((int)_DstBuf + 0xfe);
            }
LAB_00419ddc:
            _DAT_0164205a = 0;
            _DAT_01642056 = 0;
            _DAT_01642052 = 0;
            _DAT_0164204e = 0x3cf5c28f;
            _DAT_0164204a = 0x3ff33333;
            puVar10 = &DAT_01642072;
            puVar14 = &DAT_016420c2;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar14 = *puVar10;
              puVar10 = puVar10 + 1;
              puVar14 = puVar14 + 1;
            }
            puVar10 = &DAT_01642086;
            puVar14 = &DAT_016420d6;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar14 = *puVar10;
              puVar10 = puVar10 + 1;
              puVar14 = puVar14 + 1;
            }
          }
          else {
            _DstBuf = _malloc(0x12e);
            __read(_FileHandle,_DstBuf,0x12e);
            DAT_01641fc0 = *_DstBuf;
            DAT_01642046 = *(long *)((int)_DstBuf + 0x86);
            uVar5 = 0xffffffff;
            plVar15 = _DstBuf + 1;
            do {
              plVar16 = plVar15;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              plVar16 = (long *)((int)plVar15 + 1);
              lVar2 = *plVar15;
              plVar15 = plVar16;
            } while ((char)lVar2 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = (char *)&DAT_01641fc4;
            do {
              pcVar13 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            pcVar9 = (char *)((int)plVar16 - uVar5);
            pcVar13 = pcVar13 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x11);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01641fd1;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x1e);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01641fde;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x2b);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01641feb;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            plVar15 = _DstBuf + 0xe;
            do {
              plVar16 = plVar15;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              plVar16 = (long *)((int)plVar15 + 1);
              lVar2 = *plVar15;
              plVar15 = plVar16;
            } while ((char)lVar2 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01641ff8;
            do {
              pcVar13 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            pcVar9 = (char *)((int)plVar16 - uVar5);
            pcVar13 = pcVar13 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x45);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01642005;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x52);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01642012;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x5f);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_0164201f;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            plVar15 = _DstBuf + 0x1b;
            do {
              plVar16 = plVar15;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              plVar16 = (long *)((int)plVar15 + 1);
              lVar2 = *plVar15;
              plVar15 = plVar16;
            } while ((char)lVar2 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_0164202c;
            do {
              pcVar13 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            pcVar9 = (char *)((int)plVar16 - uVar5);
            pcVar13 = pcVar13 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            uVar5 = 0xffffffff;
            pcVar9 = (char *)((int)_DstBuf + 0x79);
            do {
              pcVar13 = pcVar9;
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              pcVar13 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar13;
            } while (cVar1 != '\0');
            uVar5 = ~uVar5;
            iVar3 = -1;
            pcVar9 = &DAT_01642039;
            do {
              pcVar12 = pcVar9;
              if (iVar3 == 0) break;
              iVar3 = iVar3 + -1;
              pcVar12 = pcVar9 + 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar12;
            } while (cVar1 != '\0');
            pcVar9 = pcVar13 + -uVar5;
            pcVar13 = pcVar12 + -1;
            for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
              *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
              pcVar9 = pcVar9 + 4;
              pcVar13 = pcVar13 + 4;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *pcVar13 = *pcVar9;
              pcVar9 = pcVar9 + 1;
              pcVar13 = pcVar13 + 1;
            }
            _DAT_0164204a = 0x3ff33333;
            _DAT_0164204e = 0x3cf5c28f;
            _DAT_01642052 = 0;
            _DAT_01642056 = 0;
            _DAT_0164205a = 0;
            DAT_0164205e = *(undefined4 *)((int)_DstBuf + 0x9e);
            DAT_01642062 = *(undefined4 *)((int)_DstBuf + 0xa2);
            DAT_01642066 = *(undefined4 *)((int)_DstBuf + 0xa6);
            DAT_0164206a = *(undefined4 *)((int)_DstBuf + 0xaa);
            DAT_0164206e = *(undefined4 *)((int)_DstBuf + 0xae);
            DAT_01642072 = *(undefined4 *)((int)_DstBuf + 0xb2);
            DAT_01642076 = *(undefined4 *)((int)_DstBuf + 0xb6);
            _DAT_0164207a = *(undefined4 *)((int)_DstBuf + 0xba);
            _DAT_0164207e = *(undefined4 *)((int)_DstBuf + 0xbe);
            _DAT_01642082 = *(undefined4 *)((int)_DstBuf + 0xc2);
            DAT_01642086 = *(undefined4 *)((int)_DstBuf + 0xc6);
            DAT_0164208a = *(undefined4 *)((int)_DstBuf + 0xca);
            _DAT_0164208e = *(undefined4 *)((int)_DstBuf + 0xce);
            _DAT_01642092 = *(undefined4 *)((int)_DstBuf + 0xd2);
            _DAT_01642096 = *(undefined4 *)((int)_DstBuf + 0xd6);
            _DAT_0164209a = *(undefined4 *)((int)_DstBuf + 0xda);
            _DAT_0164209e = *(undefined4 *)((int)_DstBuf + 0xde);
            _DAT_016420a2 = *(undefined4 *)((int)_DstBuf + 0xe2);
            _DAT_016420a6 = *(undefined4 *)((int)_DstBuf + 0xe6);
            _DAT_016420aa = *(undefined4 *)((int)_DstBuf + 0xea);
            _DAT_016420ae = *(undefined4 *)((int)_DstBuf + 0xee);
            _DAT_016420b2 = *(undefined4 *)((int)_DstBuf + 0xf2);
            _DAT_016420b6 = *(undefined4 *)((int)_DstBuf + 0xf6);
            _DAT_016420ba = *(undefined4 *)((int)_DstBuf + 0xfa);
            _DAT_016420be = *(undefined4 *)((int)_DstBuf + 0xfe);
            puVar10 = &DAT_01642072;
            puVar14 = &DAT_016420c2;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar14 = *puVar10;
              puVar10 = puVar10 + 1;
              puVar14 = puVar14 + 1;
            }
            puVar10 = &DAT_01642086;
            puVar14 = &DAT_016420d6;
            for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar14 = *puVar10;
              puVar10 = puVar10 + 1;
              puVar14 = puVar14 + 1;
            }
            DAT_016420ea = *(long *)((int)_DstBuf + 0x12a);
          }
          _free(_DstBuf);
        }
        else {
          __read(_FileHandle,&DAT_01641fc0,0x13e);
        }
        SendDlgItemMessageA(DAT_0164239c,0x3fd,0xc,0,0x1641fc4);
        SendDlgItemMessageA(DAT_0164239c,0x3fe,0xc,0,0x1641fd1);
        SendDlgItemMessageA(DAT_0164239c,0x3ff,0xc,0,0x1641fde);
        SendDlgItemMessageA(DAT_0164239c,0x400,0xc,0,0x1641feb);
        SendDlgItemMessageA(DAT_0164239c,0x401,0xc,0,0x1641ff8);
        SendDlgItemMessageA(DAT_0164239c,0x402,0xc,0,0x1642005);
        SendDlgItemMessageA(DAT_0164239c,0x406,0xc,0,0x164201f);
        SendDlgItemMessageA(DAT_0164239c,0x407,0xc,0,0x164202c);
        SendDlgItemMessageA(DAT_0164239c,0x405,0xc,0,0x1642012);
        SendDlgItemMessageA(DAT_0164239c,0x408,0xc,0,0x1642039);
        SendDlgItemMessageA(DAT_0164239c,0x40a,0xc,0,0x16420ee);
        __ltoa(DAT_016420ea,acStack_114,10);
        SendDlgItemMessageA(DAT_0164239c,0x409,0xc,0,(LPARAM)acStack_114);
        __ltoa(DAT_01641fc0,acStack_114,10);
        SendDlgItemMessageA(DAT_0164239c,0x403,0xc,0,(LPARAM)acStack_114);
        __ltoa(DAT_01642046,acStack_114,10);
        SendDlgItemMessageA(DAT_0164239c,0x404,0xc,0,(LPARAM)acStack_114);
      }
    }
    else if (puStack_124 < (undefined *)0x56454c46) {
      if (puStack_124 == (undefined *)0x56454c45) {
        thunk_FUN_0041e120(s_Loading_Elevations____00436628);
        pbStack_128 = &DAT_0163ce70;
        do {
          iVar3 = 0;
          __read(_FileHandle,pbStack_128,200);
          pbVar7 = pbStack_128;
          do {
            iVar4 = 0;
            pbVar11 = pbStack_128;
            do {
              if (((*(short *)(pbVar7 + 2) != -1) && (*(short *)(pbVar11 + 2) != -1)) &&
                 (iVar3 != iVar4)) {
                if (((uint)*pbVar7 < *pbVar11 + 2) && ((int)(*pbVar11 - 2) < (int)(uint)*pbVar7)) {
                  if (((uint)pbVar7[1] < pbVar11[1] + 2) &&
                     ((int)(pbVar11[1] - 2) < (int)(uint)pbVar7[1])) {
                    *pbVar7 = 0xff;
                    pbVar7[1] = 0xff;
                    pbVar7[2] = 0xff;
                    pbVar7[3] = 0xff;
                  }
                }
              }
              pbVar11 = pbVar11 + 4;
              iVar4 = iVar4 + 1;
            } while (iVar4 < 0x32);
            pbVar7 = pbVar7 + 4;
            iVar3 = iVar3 + 1;
          } while (iVar3 < 0x32);
          iVar3 = 0x32;
          puVar8 = (ushort *)(pbStack_128 + 2);
          do {
            if ((*puVar8 != 0xffff) && (0xfff < *puVar8)) {
              *puVar8 = 0xfff;
            }
            puVar8 = puVar8 + 2;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          pbStack_128 = pbStack_128 + 200;
        } while (pbStack_128 < &DAT_01640cf0);
      }
      else {
        if (puStack_124 != (undefined *)0x48544150) goto LAB_004189f0;
        thunk_FUN_0041e120(s_Loading_Paths____00436670);
        thunk_FUN_00408d10();
      }
    }
    else {
      if (puStack_124 == (undefined *)0x5645524f) {
        _DstBuf_00 = &iStack_11c;
      }
      else if (puStack_124 == (undefined *)0x56455254) {
        _DstBuf_00 = &iStack_120;
      }
      else {
        if (puStack_124 != (undefined *)0x56455257) goto LAB_004189f0;
        _DstBuf_00 = &iStack_12c;
      }
      __read(_FileHandle,_DstBuf_00,4);
    }
    __read(_FileHandle,&puStack_124,4);
  } while( true );
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar13 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar13;
    if (cVar1 == '\0') break;
    pcVar13 = pcVar9;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  iVar3 = -1;
  pcVar9 = acStack_100;
  do {
    pcVar12 = pcVar9;
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    pcVar12 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar12;
  } while (cVar1 != '\0');
  pcVar9 = pcVar13 + -uVar5;
  pcVar13 = pcVar12 + -1;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    pcVar13 = pcVar13 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar13 = *pcVar9;
    pcVar9 = pcVar9 + 1;
    pcVar13 = pcVar13 + 1;
  }
  MessageBoxA(DAT_01642370,acStack_100,s_File_Error_004366b4,0);
  __close(_FileHandle);
  return;
}


