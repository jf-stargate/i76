/*
 * Program: i76.exe
 * Function: parse_labeled_data_record
 * Entry: 00448010
 * Signature: undefined __cdecl parse_labeled_data_record(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: # / dst / label */

void __cdecl parse_labeled_data_record(char *param_1)

{
  char cVar1;
  uint *puVar2;
  int iVar3;
  uint *lpMem;
  uint uVar4;
  uint uVar5;
  size_t sVar6;
  code *pcVar7;
  uint *puVar8;
  int iVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 *puVar12;
  char local_2f4 [4];
  char local_2f0;
  undefined2 local_2ec;
  undefined1 local_2ea;
  uint *local_2e8;
  uint *local_2e4;
  uint *local_2e0;
  uint *local_2dc;
  uint *local_2d8;
  uint *local_2d4;
  uint *local_2d0;
  char local_2cc [16];
  char local_2bc [100];
  undefined4 local_258 [25];
  char local_1f4 [100];
  char local_190 [100];
  char local_12c [100];
  char local_c8 [100];
  char local_64 [100];
  
  local_2f0 = s__004f2714[4];
  local_2ec = DAT_004f1508;
  local_2f4 = (char  [4])s__004f2714._0_4_;
  local_2ea = DAT_004f150a;
  strncpy(local_2cc,param_1,0x10);
  _strlwr(local_2cc);
  if (&stack0x00000000 != (undefined1 *)0x2cc) {
    puVar2 = open_resource_file_into_memory(local_2cc);
    iVar9 = 0;
    if (0 < DAT_00531e1c) {
      pcVar10 = &DAT_00531d18;
      do {
        iVar3 = _stricmp(local_2cc,pcVar10);
        if (iVar3 == 0) {
          return;
        }
        iVar9 = iVar9 + 1;
        pcVar10 = pcVar10 + 0xd;
      } while (iVar9 < DAT_00531e1c);
    }
    uVar4 = 0xffffffff;
    pcVar10 = local_2cc;
    do {
      pcVar11 = pcVar10;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar11 = pcVar10 + 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar11;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar10 = pcVar11 + -uVar4;
    pcVar11 = &DAT_00531d18 + DAT_00531e1c * 0xd;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar11 = *(undefined4 *)pcVar10;
      pcVar10 = pcVar10 + 4;
      pcVar11 = pcVar11 + 4;
    }
    DAT_00531e1c = DAT_00531e1c + 1;
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar11 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      pcVar11 = pcVar11 + 1;
    }
    if (puVar2 != (uint *)0x0) {
      DAT_00531d00 = puVar2;
      puVar2 = (uint *)strpbrk((char *)puVar2,local_2f4);
      pcVar10 = local_2bc;
      for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
        pcVar10[0] = '\0';
        pcVar10[1] = '\0';
        pcVar10[2] = '\0';
        pcVar10[3] = '\0';
        pcVar10 = pcVar10 + 4;
      }
      if ((0 < (int)puVar2 - (int)DAT_00531d00) && (DAT_00531d00 != (uint *)0x0)) {
        strncpy(local_2bc,(char *)DAT_00531d00,(int)puVar2 - (int)DAT_00531d00);
      }
      lpMem = local_2e4;
      DAT_00531d00 = puVar2;
      if (puVar2 == (uint *)0x0) {
LAB_00448181:
        do {
          puVar2 = local_2e8;
          if (local_2bc[0] == '\0') {
            release_resource_file_reference(param_1);
            return;
          }
          iVar9 = _strnicmp(local_2bc,s___004f2710,1);
          pcVar7 = strncpy_exref;
          if (iVar9 == 0) {
            sVar6 = 0xffffffff;
            if (DAT_00531d00 != (uint *)0x0) {
              puVar2 = (uint *)strpbrk((char *)DAT_00531d00,(char *)&local_2ec);
              sVar6 = (int)puVar2 - (int)DAT_00531d00;
              local_2e8 = puVar2;
            }
            pcVar7 = strncpy_exref;
            pcVar10 = local_2bc;
            for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              pcVar10 = pcVar10 + 4;
            }
            if ((0 < (int)sVar6) && (DAT_00531d00 != (uint *)0x0)) {
              strncpy(local_2bc,(char *)DAT_00531d00,sVar6);
            }
            DAT_00531d00 = puVar2;
            if (puVar2 != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840
                                ((char *)puVar2,(char *)&local_2ec);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,(char *)&local_2ec);
              }
            }
          }
          iVar9 = _strnicmp(local_2bc,s_dst_004f270c,4);
          if (iVar9 == 0) {
            iVar9 = -1;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2d4 = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              iVar9 = (int)local_2d4 - (int)DAT_00531d00;
            }
            puVar12 = local_258;
            for (iVar3 = 0x19; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar12 = 0;
              puVar12 = puVar12 + 1;
            }
            if ((0 < iVar9) && (DAT_00531d00 != (uint *)0x0)) {
              (*pcVar7)();
            }
            DAT_00531d00 = local_2d4;
            if (local_2d4 != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840((char *)local_2d4,local_2f4);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,local_2f4);
              }
            }
            if (&stack0x00000000 == (undefined1 *)0x258) {
              lpMem = (uint *)0x0;
            }
            else {
              lpMem = HeapAlloc(DAT_00531d04,8,0x18);
              *lpMem = (uint)DAT_00531d08;
              DAT_00531d08 = (char *)lpMem;
              (*pcVar7)();
              _strlwr((char *)(lpMem + 1));
              lpMem[5] = 0;
              DAT_00531d14 = DAT_00531d14 + 1;
            }
          }
          iVar9 = _strnicmp(local_2bc,(char *)&PTR_DAT_004f2708,4);
          if (iVar9 == 0) {
            iVar9 = -1;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2d8 = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              iVar9 = (int)local_2d8 - (int)DAT_00531d00;
            }
            puVar12 = local_258;
            for (iVar3 = 0x19; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar12 = 0;
              puVar12 = puVar12 + 1;
            }
            if ((0 < iVar9) && (DAT_00531d00 != (uint *)0x0)) {
              (*pcVar7)();
            }
            DAT_00531d00 = local_2d8;
            if (local_2d8 != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840((char *)local_2d8,local_2f4);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,local_2f4);
              }
            }
            if (&stack0x00000000 == (undefined1 *)0x258) {
              lpMem = (uint *)0x0;
            }
            else {
              lpMem = HeapAlloc(DAT_00531d04,8,0x18);
              *lpMem = (uint)DAT_00531d0c;
              DAT_00531d0c = (char *)lpMem;
              (*pcVar7)();
              _strlwr((char *)(lpMem + 1));
              lpMem[5] = 0;
              DAT_00531d10 = DAT_00531d10 + 1;
            }
          }
          iVar9 = _strnicmp(local_2bc,s_label_004f2700,6);
          puVar2 = lpMem;
          if (iVar9 == 0) {
            sVar6 = 0xffffffff;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2d0 = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              sVar6 = (int)local_2d0 - (int)DAT_00531d00;
            }
            puVar8 = local_2d0;
            pcVar10 = local_c8;
            for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              pcVar10 = pcVar10 + 4;
            }
            if ((0 < (int)sVar6) && (DAT_00531d00 != (uint *)0x0)) {
              strncpy(local_c8,(char *)DAT_00531d00,sVar6);
            }
            DAT_00531d00 = puVar8;
            if (puVar8 != (uint *)0x0) {
              do {
                iVar9 = -1;
                uVar4 = 0;
                pcVar10 = local_2f4;
                do {
                  if (iVar9 == 0) break;
                  iVar9 = iVar9 + -1;
                  cVar1 = *pcVar10;
                  pcVar10 = pcVar10 + 1;
                } while (cVar1 != '\0');
                DAT_00531d00 = puVar8;
                if (iVar9 == -2) break;
                while ((char)*puVar8 != local_2f4[uVar4]) {
                  uVar5 = 0xffffffff;
                  uVar4 = uVar4 + 1;
                  pcVar10 = local_2f4;
                  do {
                    if (uVar5 == 0) break;
                    uVar5 = uVar5 - 1;
                    cVar1 = *pcVar10;
                    pcVar10 = pcVar10 + 1;
                  } while (cVar1 != '\0');
                  if (~uVar5 - 1 <= uVar4) goto LAB_0044851a;
                }
                puVar8 = (uint *)((int)puVar8 + 1);
              } while( true );
            }
LAB_0044851a:
            sVar6 = 0xffffffff;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2e0 = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              sVar6 = (int)local_2e0 - (int)DAT_00531d00;
            }
            pcVar10 = local_1f4;
            for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              pcVar10 = pcVar10 + 4;
            }
            if ((0 < (int)sVar6) && (DAT_00531d00 != (uint *)0x0)) {
              strncpy(local_1f4,(char *)DAT_00531d00,sVar6);
            }
            DAT_00531d00 = local_2e0;
            if (local_2e0 != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840((char *)local_2e0,local_2f4);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,local_2f4);
              }
            }
            sVar6 = 0xffffffff;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2dc = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              sVar6 = (int)local_2dc - (int)DAT_00531d00;
            }
            pcVar10 = local_190;
            for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              pcVar10 = pcVar10 + 4;
            }
            if ((0 < (int)sVar6) && (DAT_00531d00 != (uint *)0x0)) {
              strncpy(local_190,(char *)DAT_00531d00,sVar6);
            }
            DAT_00531d00 = local_2dc;
            if (local_2dc != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840((char *)local_2dc,local_2f4);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,local_2f4);
              }
            }
            sVar6 = 0xffffffff;
            if (DAT_00531d00 != (uint *)0x0) {
              local_2e4 = (uint *)strpbrk((char *)DAT_00531d00,local_2f4);
              sVar6 = (int)local_2e4 - (int)DAT_00531d00;
            }
            pcVar10 = local_12c;
            for (iVar9 = 0x19; iVar9 != 0; iVar9 = iVar9 + -1) {
              pcVar10[0] = '\0';
              pcVar10[1] = '\0';
              pcVar10[2] = '\0';
              pcVar10[3] = '\0';
              pcVar10 = pcVar10 + 4;
            }
            if ((0 < (int)sVar6) && (DAT_00531d00 != (uint *)0x0)) {
              strncpy(local_12c,(char *)DAT_00531d00,sVar6);
            }
            DAT_00531d00 = local_2e4;
            if (local_2e4 != (uint *)0x0) {
              iVar9 = definition_record_parser_context_helper_00448840((char *)local_2e4,local_2f4);
              while (iVar9 != 0) {
                DAT_00531d00 = (uint *)((int)DAT_00531d00 + 1);
                iVar9 = definition_record_parser_context_helper_00448840
                                  ((char *)DAT_00531d00,local_2f4);
              }
            }
            definition_record_parser_context_helper_00448890((char *)0x0,local_2f4,local_64);
            if (((((lpMem != (uint *)0x0) && (&stack0x00000000 != (undefined1 *)0xc8)) &&
                 (&stack0x00000000 != (undefined1 *)0x1f4)) &&
                ((&stack0x00000000 != (undefined1 *)0x190 &&
                 (&stack0x00000000 != (undefined1 *)0x12c)))) &&
               (&stack0x00000000 != (undefined1 *)0x64)) {
              uVar4 = lpMem[5];
              lpMem[5] = uVar4 + 1;
              puVar2 = HeapReAlloc(DAT_00531d04,8,lpMem,(uVar4 + 1) * 0x20 + 0x18);
              puVar8 = (uint *)DAT_00531d0c;
              if (((puVar2 != lpMem) && (puVar8 = puVar2, lpMem != (uint *)DAT_00531d0c)) &&
                 (puVar8 = (uint *)DAT_00531d0c, lpMem == (uint *)DAT_00531d08)) {
                DAT_00531d08 = (char *)puVar2;
              }
              DAT_00531d0c = (char *)puVar8;
              uVar4 = puVar2[5];
              strncpy((char *)(puVar2 + uVar4 * 8 + -2),local_c8,0x10);
              _strlwr((char *)(puVar2 + uVar4 * 8 + -2));
              uVar4 = atol(local_1f4);
              puVar2[puVar2[5] * 8 + 2] = uVar4;
              uVar4 = atol(local_190);
              puVar2[puVar2[5] * 8 + 3] = uVar4;
              uVar4 = atol(local_12c);
              puVar2[puVar2[5] * 8 + 4] = uVar4;
              uVar4 = atol(local_64);
              puVar2[puVar2[5] * 8 + 5] = uVar4;
            }
          }
          definition_record_parser_context_helper_00448890((char *)0x0,local_2f4,local_2bc);
          lpMem = puVar2;
        } while( true );
      }
      do {
        iVar9 = -1;
        uVar4 = 0;
        pcVar10 = local_2f4;
        do {
          if (iVar9 == 0) break;
          iVar9 = iVar9 + -1;
          cVar1 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar1 != '\0');
        DAT_00531d00 = puVar2;
        if (iVar9 == -2) goto LAB_00448181;
        while ((char)*puVar2 != local_2f4[uVar4]) {
          uVar5 = 0xffffffff;
          uVar4 = uVar4 + 1;
          pcVar10 = local_2f4;
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar10 + 1;
          } while (cVar1 != '\0');
          if (~uVar5 - 1 <= uVar4) goto LAB_00448181;
        }
        puVar2 = (uint *)((int)puVar2 + 1);
      } while( true );
    }
  }
  return;
}


