/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_mission_file
 * Entry: 004010cd
 * Signature: undefined __cdecl i76edit_export_runtime_mission_file(char * param_1, int param_2)
 */


void __cdecl i76edit_export_runtime_mission_file(char *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  long lVar4;
  long lVar5;
  void *_Buf;
  long _Offset;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint *_MaxCharCount;
  uint *unaff_EBX;
  int unaff_EBP;
  uint *unaff_ESI;
  undefined4 *puVar11;
  ushort *unaff_EDI;
  undefined4 **ppuVar12;
  undefined4 **ppuVar13;
  char *pcVar14;
  char *pcVar15;
  undefined4 *puVar16;
  int iVar17;
  undefined4 auStack_424 [7];
  char acStack_408 [260];
  undefined4 *apuStack_304 [65];
  char acStack_200 [256];
  undefined4 auStack_100 [64];
  
  puVar3 = auStack_100;
  for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  pcVar2 = acStack_200;
  for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  puVar3 = auStack_424;
  for (iVar6 = 7; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  if (DAT_00433a30 == 0) {
    iVar6 = __open(param_1,0x8301,0x80);
  }
  else {
    pcVar2 = acStack_408;
    for (iVar6 = 0x41; iVar6 != 0; iVar6 = iVar6 + -1) {
      pcVar2[0] = '\0';
      pcVar2[1] = '\0';
      pcVar2[2] = '\0';
      pcVar2[3] = '\0';
      pcVar2 = pcVar2 + 4;
    }
    uVar7 = 0xffffffff;
    pcVar2 = param_1;
    do {
      pcVar14 = pcVar2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar14;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar6 = -1;
    pcVar2 = acStack_408;
    do {
      pcVar15 = pcVar2;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar15 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar15;
    } while (cVar1 != '\0');
    pcVar2 = pcVar14 + -uVar7;
    pcVar14 = pcVar15 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar14 = pcVar14 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar2 = (char *)&DAT_004368d0;
    do {
      pcVar14 = pcVar2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar14;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar6 = -1;
    pcVar2 = acStack_408;
    do {
      pcVar15 = pcVar2;
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      pcVar15 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar15;
    } while (cVar1 != '\0');
    pcVar2 = pcVar14 + -uVar7;
    pcVar14 = pcVar15 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar14 = pcVar14 + 1;
    }
    iVar6 = __open(acStack_408,0x8301,0x80);
    uVar7 = 0xffffffff;
    pcVar2 = (char *)&DAT_004368c8;
    do {
      pcVar14 = pcVar2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar14;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar9 = -1;
    ppuVar12 = apuStack_304;
    do {
      ppuVar13 = ppuVar12;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      ppuVar13 = (undefined4 **)((int)ppuVar12 + 1);
      cVar1 = *(char *)ppuVar12;
      ppuVar12 = ppuVar13;
    } while (cVar1 != '\0');
    pcVar2 = pcVar14 + -uVar7;
    pcVar14 = (char *)((int)ppuVar13 + -1);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar14 = pcVar14 + 1;
    }
  }
  ppuVar12 = apuStack_304;
  for (iVar9 = 0x41; iVar9 != 0; iVar9 = iVar9 + -1) {
    *ppuVar12 = (undefined4 *)0x0;
    ppuVar12 = ppuVar12 + 1;
  }
  pcVar2 = acStack_408;
  for (iVar9 = 0x41; iVar9 != 0; iVar9 = iVar9 + -1) {
    pcVar2[0] = '\0';
    pcVar2[1] = '\0';
    pcVar2[2] = '\0';
    pcVar2[3] = '\0';
    pcVar2 = pcVar2 + 4;
  }
  uVar7 = 0xffffffff;
  pcVar2 = param_1;
  do {
    pcVar14 = pcVar2;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar14;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  iVar9 = -1;
  pcVar2 = acStack_408;
  do {
    pcVar15 = pcVar2;
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    pcVar15 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar15;
  } while (cVar1 != '\0');
  pcVar2 = pcVar14 + -uVar7;
  pcVar14 = pcVar15 + -1;
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar14 = pcVar14 + 1;
  }
  uVar7 = 0xffffffff;
  pcVar2 = param_1;
  do {
    pcVar14 = pcVar2;
    if (uVar7 == 0) break;
    uVar7 = uVar7 - 1;
    pcVar14 = pcVar2 + 1;
    cVar1 = *pcVar2;
    pcVar2 = pcVar14;
  } while (cVar1 != '\0');
  uVar7 = ~uVar7;
  iVar9 = -1;
  ppuVar12 = apuStack_304;
  do {
    ppuVar13 = ppuVar12;
    if (iVar9 == 0) break;
    iVar9 = iVar9 + -1;
    ppuVar13 = (undefined4 **)((int)ppuVar12 + 1);
    cVar1 = *(char *)ppuVar12;
    ppuVar12 = ppuVar13;
  } while (cVar1 != '\0');
  pcVar2 = pcVar14 + -uVar7;
  pcVar14 = (char *)((int)ppuVar13 + -1);
  for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
    pcVar2 = pcVar2 + 4;
    pcVar14 = pcVar14 + 4;
  }
  for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
    *pcVar14 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar14 = pcVar14 + 1;
  }
  if (DAT_00433a30 == 0) {
    pcVar2 = _strchr(acStack_408,0x2e);
    if (pcVar2 == (char *)0x0) {
      uVar7 = 0xffffffff;
      pcVar2 = (char *)&DAT_004368c0;
      do {
        pcVar14 = pcVar2;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar14 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar14;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      iVar9 = -1;
      pcVar2 = acStack_408;
      do {
        pcVar15 = pcVar2;
        if (iVar9 == 0) break;
        iVar9 = iVar9 + -1;
        pcVar15 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar15;
      } while (cVar1 != '\0');
      pcVar2 = pcVar14 + -uVar7;
      pcVar14 = pcVar15 + -1;
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar14 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    else {
      _sprintf(pcVar2,(char *)&DAT_004368c0);
    }
    pcVar2 = _strchr((char *)apuStack_304,0x2e);
    if (pcVar2 == (char *)0x0) {
      uVar7 = 0xffffffff;
      pcVar2 = (char *)&DAT_004368b8;
      do {
        pcVar14 = pcVar2;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar14 = pcVar2 + 1;
        cVar1 = *pcVar2;
        pcVar2 = pcVar14;
      } while (cVar1 != '\0');
      uVar7 = ~uVar7;
      iVar9 = -1;
      ppuVar12 = apuStack_304;
      do {
        ppuVar13 = ppuVar12;
        if (iVar9 == 0) break;
        iVar9 = iVar9 + -1;
        ppuVar13 = (undefined4 **)((int)ppuVar12 + 1);
        cVar1 = *(char *)ppuVar12;
        ppuVar12 = ppuVar13;
      } while (cVar1 != '\0');
      pcVar2 = pcVar14 + -uVar7;
      pcVar14 = (char *)((int)ppuVar13 + -1);
      for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar14 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        pcVar14 = pcVar14 + 1;
      }
    }
    else {
      _sprintf(pcVar2,(char *)&DAT_004368b8);
    }
  }
  else {
    uVar7 = 0xffffffff;
    pcVar2 = (char *)&DAT_004368c0;
    do {
      pcVar14 = pcVar2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar14;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar9 = -1;
    pcVar2 = acStack_408;
    do {
      pcVar15 = pcVar2;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      pcVar15 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar15;
    } while (cVar1 != '\0');
    pcVar2 = pcVar14 + -uVar7;
    pcVar14 = pcVar15 + -1;
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar14 = pcVar14 + 1;
    }
    uVar7 = 0xffffffff;
    pcVar2 = (char *)&DAT_004368b8;
    do {
      pcVar14 = pcVar2;
      if (uVar7 == 0) break;
      uVar7 = uVar7 - 1;
      pcVar14 = pcVar2 + 1;
      cVar1 = *pcVar2;
      pcVar2 = pcVar14;
    } while (cVar1 != '\0');
    uVar7 = ~uVar7;
    iVar9 = -1;
    ppuVar12 = apuStack_304;
    do {
      ppuVar13 = ppuVar12;
      if (iVar9 == 0) break;
      iVar9 = iVar9 + -1;
      ppuVar13 = (undefined4 **)((int)ppuVar12 + 1);
      cVar1 = *(char *)ppuVar12;
      ppuVar12 = ppuVar13;
    } while (cVar1 != '\0');
    pcVar2 = pcVar14 + -uVar7;
    pcVar14 = (char *)((int)ppuVar13 + -1);
    for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined4 *)pcVar14 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar14 = pcVar14 + 4;
    }
    for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
      *pcVar14 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      pcVar14 = pcVar14 + 1;
    }
  }
  uVar7 = __open(acStack_408,0x8301,0x80);
  DAT_0043c540 = (FILE *)FUN_004232c0((char *)apuStack_304,&DAT_004368b4);
  if ((DAT_0043c540 == (FILE *)0x0) && (DAT_00433a30 == 0)) {
    _sprintf(acStack_200,s_Could_not_open__s_for_writing____0043686c,apuStack_304);
    MessageBoxA(DAT_01642370,acStack_200,s_WARNING__File_IO_Error_Sharing_V_00436824,0);
  }
  if (param_2 == 1) {
    i76edit_set_status_bar_text(s_Exporting____00436814);
    puVar3 = _malloc(8);
    *puVar3 = 0x32445742;
    puVar3[1] = 8;
    __write(iVar6,puVar3,8);
    i76edit_write_bwd2_revision_chunk(iVar6,&DAT_00564552,2);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454457;
    puVar3[1] = 8;
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    iVar9 = i76edit_write_bwd2_revision_chunk(iVar6,0x56455257,8);
    puVar3 = _realloc(puVar3,0x146);
    *puVar3 = 0x444c5257;
    puVar3[1] = 0x146;
    iVar9 = iVar9 + 0x146;
    if (DAT_01641fc0 < 1) {
      DAT_01641fc0 = 0;
    }
    if (DAT_01642046 < 0) {
      DAT_01641fc0 = 0;
    }
    puVar11 = &DAT_01641fc0;
    puVar16 = puVar3 + 2;
    for (iVar10 = 0x4f; iVar10 != 0; iVar10 = iVar10 + -1) {
      *puVar16 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar16 = puVar16 + 1;
    }
    *(undefined2 *)puVar16 = *(undefined2 *)puVar11;
    __write(iVar6,puVar3,0x146);
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    _MaxCharCount = (uint *)(iVar9 + iVar10);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454457;
    puVar3[1] = _MaxCharCount + 2;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454454;
    _Buf = (void *)i76edit_export_runtime_tdef_zmap_and_zone_payloads
                             ((undefined4 *)&stack0xfffffbd0,param_1,unaff_EBP,unaff_EDI,unaff_ESI,
                              unaff_EBX,_MaxCharCount,uVar7);
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    __write(iVar6,_Buf,(uint)_MaxCharCount);
    _free(_Buf);
    iVar9 = i76edit_write_bwd2_exit_chunk(iVar6);
    iVar9 = (int)_MaxCharCount + iVar9;
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    puVar3[1] = iVar9 + iVar10 + 8;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454452;
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    iVar9 = i76edit_write_bwd2_revision_chunk(iVar6,0x56455252,1);
    iVar10 = i76edit_export_runtime_all_road_chunks(iVar6);
    iVar9 = iVar9 + iVar10;
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    puVar3[1] = iVar9 + iVar10 + 8;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x4645444f;
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    i76edit_set_status_bar_text(s_Exporting_Objects__004367fc);
    iVar9 = i76edit_write_bwd2_revision_chunk(iVar6,0x5645524f,3);
    iVar10 = i76edit_export_runtime_object_obj_records(iVar6,uVar7);
    iVar9 = iVar9 + iVar10;
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    puVar3[1] = iVar9 + iVar10 + 8;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    i76edit_set_status_bar_text(s_Exporting_Linked_Objects__004367dc);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x4645444c;
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    iVar9 = i76edit_write_bwd2_revision_chunk(iVar6,0x5645524c,1);
    iVar10 = i76edit_export_runtime_all_linked_object_chunks(iVar6);
    iVar9 = iVar9 + iVar10;
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    iVar9 = iVar9 + iVar10;
    if (DAT_0043c540 != (FILE *)0x0) {
      _fclose(DAT_0043c540);
    }
    puVar3[1] = iVar9 + 8;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    i76edit_set_status_bar_text(s_paths_004367d4);
    i76edit_export_runtime_all_path_chunks(uVar7);
    __close(uVar7);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454441;
    puVar3[1] = 8;
    lVar4 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    iVar9 = i76edit_write_bwd2_revision_chunk(iVar6,0x56455241,1);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = &DAT_004d5346;
    puVar3[1] = 8;
    lVar5 = __tell(iVar6);
    __write(iVar6,puVar3,8);
    i76edit_set_status_bar_text(s_Compiling_FSM__004367c0);
    iVar17 = 0x1c;
    __write(iVar6,auStack_424,0x1c);
    puVar3[1] = iVar17 + 8;
    _Offset = __tell(iVar6);
    __lseek(iVar6,lVar5,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,_Offset,0);
    iVar10 = i76edit_write_bwd2_exit_chunk(iVar6);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x46454441;
    puVar3[1] = iVar9 + iVar17 + 8 + iVar10 + 8;
    lVar5 = __tell(iVar6);
    __lseek(iVar6,lVar4,0);
    __write(iVar6,puVar3,8);
    __lseek(iVar6,lVar5,0);
    puVar3 = _realloc(puVar3,8);
    *puVar3 = 0x54495845;
    puVar3[1] = 8;
    __write(iVar6,puVar3,8);
    i76edit_set_status_bar_text(s_Ready__00434590);
    apuStack_304[0] = puVar3;
  }
  _free(apuStack_304[0]);
  __close(iVar6);
  return;
}


