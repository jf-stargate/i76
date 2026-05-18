/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_00401a90
 * Entry: 0040137a
 * Signature: undefined4 __stdcall thunk_FUN_00401a90(undefined4 param_1, undefined4 param_2, char * param_3)
 */


undefined4 thunk_FUN_00401a90(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char cVar1;
  bool bVar2;
  ushort uVar3;
  bool bVar4;
  HDC hdc;
  undefined3 extraout_var;
  undefined4 uVar5;
  ushort *_Str;
  char *pcVar6;
  FILE *_File;
  HWND pHVar7;
  size_t sVar8;
  BOOL BVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  ushort *unaff_EBX;
  int iVar13;
  uint *unaff_ESI;
  ushort *unaff_EDI;
  ushort *puVar14;
  ushort *puVar15;
  char *pcVar16;
  undefined4 *puVar17;
  char *pcVar18;
  UINT UVar19;
  uint *puVar20;
  HWND in_stack_fffffce4;
  ushort *in_stack_fffffce8;
  ushort *in_stack_fffffcec;
  uint *in_stack_fffffcf0;
  uint *in_stack_fffffcf4;
  uint *in_stack_fffffcf8;
  char acStack_300 [256];
  char acStack_200 [256];
  char acStack_100 [256];
  
  bVar2 = true;
  iVar13 = 0;
  puVar20 = (uint *)(uint)DAT_00434068;
  puVar17 = (undefined4 *)&DAT_01642270;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    *puVar17 = 0;
    puVar17 = puVar17 + 1;
  }
  pcVar6 = acStack_200;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  pcVar6 = acStack_300;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  pcVar6 = acStack_100;
  for (iVar10 = 0x40; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar6[0] = '\0';
    pcVar6[1] = '\0';
    pcVar6[2] = '\0';
    pcVar6[3] = '\0';
    pcVar6 = pcVar6 + 4;
  }
  iVar10 = -1;
  pcVar6 = param_3;
  do {
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  if (iVar10 == -2) {
    iVar10 = 0xc;
    hdc = GetDC((HWND)0x0);
    iVar10 = GetDeviceCaps(hdc,iVar10);
    if (iVar10 < 0x10) {
      MessageBoxA((HWND)0x0,s_Your_Display_Properties_setting_d_00433f38,
                  s_Interstate__76_Editor_rel_3_06_v_00434034,0x10);
                    /* WARNING: Subroutine does not return */
      _exit(1);
    }
  }
  bVar4 = thunk_FUN_00402290();
  if (CONCAT31(extraout_var,bVar4) != 0) {
    MessageBoxA((HWND)0x0,s_The_I_76_Editor_is_already_runni_00433f0c,
                s_Interstate__76_Editor_rel_3_06_v_00434034,0x10);
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  DAT_016423a4 = param_1;
  DAT_01642370 = thunk_FUN_00406ff0();
  if (DAT_01642370 == (HWND)0x0) {
    uVar5 = 1;
  }
  else {
    uVar11 = 0xffffffff;
    pcVar6 = param_3;
    do {
      if (uVar11 == 0) break;
      uVar11 = uVar11 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    uVar11 = ~uVar11;
    if (uVar11 == 1) {
      while( true ) {
        do {
          BVar9 = PeekMessageA((LPMSG)&stack0xfffffce4,(HWND)0x0,0,0,1);
        } while (BVar9 == 0);
        if (in_stack_fffffce8 == (ushort *)0x12) break;
        TranslateMessage((MSG *)&stack0xfffffce4);
        DispatchMessageA((MSG *)&stack0xfffffce4);
      }
    }
    else {
      DAT_00433a30 = 1;
      _Str = _malloc(uVar11);
      puVar14 = _Str;
      for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        puVar14[0] = 0;
        puVar14[1] = 0;
        puVar14 = puVar14 + 2;
      }
      for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(char *)puVar14 = '\0';
        puVar14 = (ushort *)((int)puVar14 + 1);
      }
      uVar11 = 0xffffffff;
      do {
        pcVar6 = param_3;
        if (uVar11 == 0) break;
        uVar11 = uVar11 - 1;
        pcVar6 = param_3 + 1;
        cVar1 = *param_3;
        param_3 = pcVar6;
      } while (cVar1 != '\0');
      uVar11 = ~uVar11;
      iVar10 = -1;
      puVar14 = _Str;
      do {
        puVar15 = puVar14;
        if (iVar10 == 0) break;
        iVar10 = iVar10 + -1;
        puVar15 = (ushort *)((int)puVar14 + 1);
        uVar3 = *puVar14;
        puVar14 = puVar15;
      } while ((char)uVar3 != '\0');
      pcVar6 = pcVar6 + -uVar11;
      pcVar18 = (char *)((int)puVar15 + -1);
      for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
        *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        pcVar18 = pcVar18 + 4;
      }
      for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *pcVar18 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        pcVar18 = pcVar18 + 1;
      }
      pcVar6 = _strtok((char *)_Str,&stack0xfffffcdc);
      while (pcVar6 != (char *)0x0) {
        iVar13 = iVar13 + 1;
        iVar10 = __strcmpi(pcVar6,&DAT_00433f08);
        if ((iVar10 == 0) || (iVar10 = __strcmpi(pcVar6,&DAT_00433f04), iVar10 == 0)) {
          _sprintf(acStack_300,s_Usage__I76edit_filename___n___r__00433e94);
          pcVar6 = acStack_300;
          UVar19 = 0x40;
          pcVar18 = s_I76_Edit_00433e88;
          pHVar7 = GetFocus();
          MessageBoxA(pHVar7,pcVar6,pcVar18,UVar19);
          return 1;
        }
        iVar10 = __strcmpi(pcVar6,&DAT_00433e84);
        if (iVar10 == 0) {
          DAT_004347c0 = 0;
        }
        else {
          iVar10 = __strcmpi(pcVar6,&DAT_00433e80);
          if (iVar10 == 0) {
            bVar2 = false;
          }
          else {
            uVar11 = 0xffffffff;
            do {
              pcVar18 = pcVar6;
              if (uVar11 == 0) break;
              uVar11 = uVar11 - 1;
              pcVar18 = pcVar6 + 1;
              cVar1 = *pcVar6;
              pcVar6 = pcVar18;
            } while (cVar1 != '\0');
            uVar11 = ~uVar11;
            iVar10 = -1;
            pcVar6 = acStack_100;
            do {
              pcVar16 = pcVar6;
              if (iVar10 == 0) break;
              iVar10 = iVar10 + -1;
              pcVar16 = pcVar6 + 1;
              cVar1 = *pcVar6;
              pcVar6 = pcVar16;
            } while (cVar1 != '\0');
            pcVar6 = pcVar18 + -uVar11;
            pcVar18 = pcVar16 + -1;
            for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
              *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
              pcVar6 = pcVar6 + 4;
              pcVar18 = pcVar18 + 4;
            }
            for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
              *pcVar18 = *pcVar6;
              pcVar6 = pcVar6 + 1;
              pcVar18 = pcVar18 + 1;
            }
          }
        }
        if (3 < iVar13) {
          _sprintf(acStack_300,s_Usage__I76edit_filename___n___r__00433e94);
          pcVar6 = acStack_300;
          UVar19 = 0x40;
          pcVar18 = s_I76_Edit_00433e88;
          pHVar7 = GetFocus();
          MessageBoxA(pHVar7,pcVar6,pcVar18,UVar19);
          return 1;
        }
        pcVar6 = _strtok((char *)0x0,&stack0xfffffcdc);
      }
      _File = (FILE *)FUN_004232c0(acStack_100,&DAT_00433e7c);
      if (_File == (FILE *)0x0) {
        _sprintf(acStack_300,s_error_opening_file__s_file_may_n_00433e34,acStack_100);
        pcVar6 = acStack_300;
        UVar19 = 0x40;
        pcVar18 = s_I76_Edit_00433e88;
        pHVar7 = GetFocus();
        MessageBoxA(pHVar7,pcVar6,pcVar18,UVar19);
        return 1;
      }
      thunk_FUN_0041e730(0x800f,1);
      thunk_FUN_0041e730(0x8010,2);
      thunk_FUN_0041e730(0x8011,4);
      thunk_FUN_0041e730(0x9c67,8);
      thunk_FUN_0041e730(0x8012,0x10);
      thunk_FUN_0041e730(0x8013,0x20);
      thunk_FUN_0041e730(0x8014,0x40);
      thunk_FUN_0041e730(0x8025,0x80);
      while (sVar8 = _fread(&stack0xfffffcde,1,1,_File), sVar8 != 0) {
        if ((char)((uint)puVar20 >> 0x10) == '\n') {
          pcVar6 = _strtok(&DAT_01642270,&stack0xfffffcdc);
          while (pcVar6 != (char *)0x0) {
            pcVar6 = _strtok((char *)0x0,&stack0xfffffcdc);
          }
          uVar11 = 0xffffffff;
          pcVar6 = &DAT_01642270;
          do {
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar6 + 1;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          if (*(char *)(uVar11 + 0x164226b) != '.') {
            _sprintf(acStack_300,s_Filename_error_in_file___s_00433e10,&DAT_01642270);
            pcVar6 = acStack_300;
            UVar19 = 0x40;
            pcVar18 = s_I76_Edit_00433e88;
            pHVar7 = GetFocus();
            MessageBoxA(pHVar7,pcVar6,pcVar18,UVar19);
            return 1;
          }
          *(undefined4 *)(uVar11 + 0x164226b) = 0;
          *(undefined1 *)((int)&DAT_0164226c + uVar11 + 3) = 0;
          _sprintf(acStack_300,s_Processing__s____00433dfc,&DAT_01642270);
          thunk_FUN_0041e120(acStack_300);
          pcVar6 = acStack_200;
          for (iVar13 = 0x40; iVar13 != 0; iVar13 = iVar13 + -1) {
            pcVar6[0] = '\0';
            pcVar6[1] = '\0';
            pcVar6[2] = '\0';
            pcVar6[3] = '\0';
            pcVar6 = pcVar6 + 4;
          }
          uVar11 = 0xffffffff;
          pcVar6 = &DAT_01642270;
          do {
            pcVar18 = pcVar6;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar18 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar18;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          iVar13 = -1;
          pcVar6 = acStack_200;
          do {
            pcVar16 = pcVar6;
            if (iVar13 == 0) break;
            iVar13 = iVar13 + -1;
            pcVar16 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar16;
          } while (cVar1 != '\0');
          pcVar6 = pcVar18 + -uVar11;
          pcVar18 = pcVar16 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar18 = pcVar18 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar18 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar18 = pcVar18 + 1;
          }
          uVar11 = 0xffffffff;
          pcVar6 = (char *)&DAT_00433df4;
          do {
            pcVar18 = pcVar6;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar18 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar18;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          iVar13 = -1;
          pcVar6 = acStack_200;
          do {
            pcVar16 = pcVar6;
            if (iVar13 == 0) break;
            iVar13 = iVar13 + -1;
            pcVar16 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar16;
          } while (cVar1 != '\0');
          pcVar6 = pcVar18 + -uVar11;
          pcVar18 = pcVar16 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar18 = pcVar18 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar18 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar18 = pcVar18 + 1;
          }
          pcVar6 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
          for (iVar13 = 0x40; iVar13 != 0; iVar13 = iVar13 + -1) {
            pcVar6[0] = '\0';
            pcVar6[1] = '\0';
            pcVar6[2] = '\0';
            pcVar6[3] = '\0';
            pcVar6 = pcVar6 + 4;
          }
          uVar11 = 0xffffffff;
          pcVar6 = s_Interstate__76_Editor_rel_3_06_v_00434034;
          do {
            pcVar18 = pcVar6;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar18 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar18;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          iVar13 = -1;
          pcVar6 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
          do {
            pcVar16 = pcVar6;
            if (iVar13 == 0) break;
            iVar13 = iVar13 + -1;
            pcVar16 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar16;
          } while (cVar1 != '\0');
          pcVar6 = pcVar18 + -uVar11;
          pcVar18 = pcVar16 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar18 = pcVar18 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar18 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar18 = pcVar18 + 1;
          }
          uVar11 = 0xffffffff;
          pcVar6 = acStack_200;
          do {
            pcVar18 = pcVar6;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar18 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar18;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          iVar13 = -1;
          pcVar6 = s_Interstate__76_Editor_rel_3_06_v_004345b0;
          do {
            pcVar16 = pcVar6;
            if (iVar13 == 0) break;
            iVar13 = iVar13 + -1;
            pcVar16 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar16;
          } while (cVar1 != '\0');
          pcVar6 = pcVar18 + -uVar11;
          pcVar18 = pcVar16 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar18 = pcVar18 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar18 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar18 = pcVar18 + 1;
          }
          SendMessageA(DAT_01642370,0xc,0,0x4345b0);
          UpdateWindow(DAT_01642370);
          thunk_FUN_00418870(acStack_200);
          UpdateWindow(DAT_01642370);
          if (bVar2) {
            thunk_FUN_0040e3c0(unaff_EDI,unaff_ESI,unaff_EBX,puVar20,_Str,
                               (ushort *)in_stack_fffffce4,in_stack_fffffce8,in_stack_fffffcec,
                               in_stack_fffffcf0,in_stack_fffffcf4,in_stack_fffffcf8);
            UpdateWindow(DAT_01642370);
          }
          thunk_FUN_0041b150(&DAT_01642270,1);
          if (bVar2) {
            thunk_FUN_0041a7e0(acStack_200);
          }
          puVar17 = (undefined4 *)&DAT_01642270;
          for (iVar13 = 0x40; iVar13 != 0; iVar13 = iVar13 + -1) {
            *puVar17 = 0;
            puVar17 = puVar17 + 1;
          }
        }
        else {
          uVar11 = 0xffffffff;
          pcVar6 = &stack0xfffffcde;
          do {
            pcVar18 = pcVar6;
            if (uVar11 == 0) break;
            uVar11 = uVar11 - 1;
            pcVar18 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar18;
          } while (cVar1 != '\0');
          uVar11 = ~uVar11;
          iVar13 = -1;
          pcVar6 = &DAT_01642270;
          do {
            pcVar16 = pcVar6;
            if (iVar13 == 0) break;
            iVar13 = iVar13 + -1;
            pcVar16 = pcVar6 + 1;
            cVar1 = *pcVar6;
            pcVar6 = pcVar16;
          } while (cVar1 != '\0');
          pcVar6 = pcVar18 + -uVar11;
          pcVar18 = pcVar16 + -1;
          for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
            *(undefined4 *)pcVar18 = *(undefined4 *)pcVar6;
            pcVar6 = pcVar6 + 4;
            pcVar18 = pcVar18 + 4;
          }
          for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pcVar18 = *pcVar6;
            pcVar6 = pcVar6 + 1;
            pcVar18 = pcVar18 + 1;
          }
        }
        puVar20 = (uint *)((uint)puVar20 & 0xffff);
      }
      _fclose(_File);
      _free(_Str);
    }
    uVar5 = 0;
  }
  return uVar5;
}


