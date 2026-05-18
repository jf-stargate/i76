/*
 * Program: i76.exe
 * Function: load_gamekey_map
 * Entry: 0044d460
 * Signature: undefined4 __stdcall load_gamekey_map(void)
 */


/* i76 second-pass rename
   old_name: FUN_0044d460
   suggested_name: load_gamekey_map
   basis: Parses gamekey.map and validates gamekey names/sequences. */

undefined4 load_gamekey_map(void)

{
  char cVar1;
  bool bVar2;
  FILE *_File;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  undefined **ppuVar8;
  int iVar9;
  char *pcVar10;
  int local_158;
  char local_150 [40];
  char local_128 [40];
  char local_100 [256];
  
  DAT_0053db4b = 0x22;
  DAT_0053dca1 = 0x34;
  DAT_0053dca9 = 0x29;
  DAT_0053dc9e = 0x2a;
  DAT_0053dc98 = 0x2b;
  DAT_0053dc61 = 0x2c;
  DAT_0053dc62 = 0x2d;
  DAT_0053dc63 = 0x2e;
  DAT_0053dc64 = 0x2f;
  DAT_0053dc65 = 0x30;
  DAT_0053dc66 = 0x31;
  DAT_0053dc67 = 0x32;
  DAT_0053db38 = 0x27;
  DAT_0053dca4 = 0x28;
  DAT_0053db50 = 0x26;
  DAT_00536834 = 0;
  _File = fopen(s_gamekey_map_004f4c88,s_r_004ede60);
  if (_File == (FILE *)0x0) {
    report_chunk_parse_error();
    return 0;
  }
LAB_0044d513:
  do {
    bVar2 = false;
    do {
      pcVar3 = fgets(local_100,0xff,_File);
      if (pcVar3 == (char *)0x0) {
        fclose(_File);
        return 1;
      }
      DAT_00536834 = DAT_00536834 + 1;
      pcVar3 = local_100;
      cVar1 = local_100[0];
      while (cVar1 != '\0') {
        cVar1 = *pcVar3;
        if ((cVar1 == '\n') || (cVar1 == '#')) {
          *pcVar3 = '\0';
          break;
        }
        if (*(int *)__mb_cur_max_exref < 2) {
          uVar4 = *(byte *)(*(int *)_pctype_exref + cVar1 * 2) & 8;
        }
        else {
          uVar4 = _isctype((int)cVar1,8);
        }
        if (uVar4 == 0) {
          bVar2 = true;
        }
        pcVar10 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar1 = *pcVar10;
      }
    } while (!bVar2);
    iVar5 = sscanf(local_100,s__s__s_004f4c80,local_150,local_128);
    if (iVar5 != 2) {
      report_chunk_parse_error();
      goto LAB_0044d513;
    }
    pcVar3 = strtok(local_128,s___004f4c7c);
    if (pcVar3 == (char *)0x0) {
      report_chunk_parse_error();
    }
    else {
      local_158 = 0;
      do {
        iVar5 = 0;
        iVar9 = 0;
        ppuVar8 = &PTR_PTR_004f35a0;
        do {
          iVar6 = _stricmp(*ppuVar8,pcVar3);
          if (iVar6 == 0) {
            iVar5 = (int)(short)(&DAT_004f35a4)[iVar9 * 4];
            break;
          }
          ppuVar8 = ppuVar8 + 2;
          iVar9 = iVar9 + 1;
        } while (ppuVar8 < s_Plus_004f3838);
        if (iVar5 == 0) {
          uVar4 = 0xffffffff;
          pcVar10 = pcVar3;
          do {
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            cVar1 = *pcVar10;
            pcVar10 = pcVar10 + 1;
          } while (cVar1 != '\0');
          if (~uVar4 - 1 < 2) {
            iVar5 = tolower((int)*pcVar3);
            local_158 = local_158 + iVar5;
          }
          else {
            report_chunk_parse_error();
          }
        }
        else {
          local_158 = local_158 + iVar5;
        }
        pcVar3 = strtok((char *)0x0,s___004f4c7c);
      } while (pcVar3 != (char *)0x0);
      uVar4 = 0;
      ppuVar8 = &PTR_s_COCKPIT_VIEW_004f3320;
      do {
        iVar5 = _stricmp(*ppuVar8,local_150);
        if (iVar5 == 0) break;
        ppuVar8 = ppuVar8 + 2;
        uVar4 = uVar4 + 1;
      } while (ppuVar8 < &PTR_PTR_004f35a0);
      if (uVar4 < 0x50) {
        sVar7 = (short)local_158;
        if (((&DAT_0053db30)[sVar7] == '\0') ||
           ((&DAT_0053db30)[sVar7] == (&DAT_004f3324)[uVar4 * 8])) {
          if (sVar7 < 0x1001) {
            (&DAT_0053db30)[sVar7] = (&DAT_004f3324)[uVar4 * 8];
          }
        }
        else {
          report_chunk_parse_error();
        }
      }
      else {
        report_chunk_parse_error();
      }
    }
  } while( true );
}


