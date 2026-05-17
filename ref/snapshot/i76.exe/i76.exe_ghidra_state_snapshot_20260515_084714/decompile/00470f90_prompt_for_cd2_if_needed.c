/*
 * Program: i76.exe
 * Function: prompt_for_cd2_if_needed
 * Entry: 00470f90
 * Signature: int __cdecl prompt_for_cd2_if_needed(int param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=high] ShellMain callback slot +0x44.
   Prompts/checks for CD2 when required by shell/game resource access. */

int __cdecl prompt_for_cd2_if_needed(int param_1)

{
  char cVar1;
  BOOL BVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  char cVar7;
  char *pcVar8;
  bool bVar9;
  undefined4 uVar10;
  int local_a4;
  int local_a0;
  DWORD local_98;
  DWORD local_94;
  DWORD local_90;
  DWORD local_8c;
  DWORD local_88;
  DWORD local_84;
  char local_80;
  undefined3 uStack_7f;
  char local_60;
  undefined3 uStack_5f;
  CHAR local_40 [32];
  CHAR local_20 [32];
  
  local_a0 = 0;
  if ((DAT_00524678 != 0) || (close_mci_cd_audio_device(), DAT_00524678 != 0)) {
    initialize_cd_audio_playback_state();
    if (DAT_00524678 != 0) {
      return -1;
    }
    close_mci_cd_audio_device();
  }
  do {
    bVar9 = false;
    DAT_0058d930 = 0;
    DAT_0058d92c = '\0';
    local_a4 = 0;
    do {
      if (bVar9) break;
      if ((&DAT_00609520)[local_a4] != '\0') {
        DAT_0058d930 = DAT_0058d930 + 1;
        cVar7 = (char)local_a4 + 'A';
        _local_80 = CONCAT31((int3)((uint)PTR_DAT_004f8bac >> 8),cVar7);
        BVar2 = GetVolumeInformationA
                          (&local_80,&DAT_00609540,0x20,&local_84,&local_90,&local_88,local_40,0x20)
        ;
        pcVar6 = (char *)(-(uint)(BVar2 != 0) & 0x609540);
        if (pcVar6 != (char *)0x0) {
          uVar5 = 0xffffffff;
          pcVar4 = s_I76_CD2_004f8bdc;
          do {
            if (uVar5 == 0) break;
            uVar5 = uVar5 - 1;
            cVar1 = *pcVar4;
            pcVar4 = pcVar4 + 1;
          } while (cVar1 != '\0');
          iVar3 = _strnicmp(pcVar6,s_I76_CD2_004f8bdc,~uVar5 - 1);
          if (iVar3 == 0) {
            bVar9 = true;
            DAT_0058d92c = cVar7;
          }
        }
      }
      local_a4 = local_a4 + 1;
    } while (local_a4 < 0x1a);
    if ((bVar9) || (bVar9 = DAT_0058d92c == '\0', !bVar9)) {
      iVar3 = initialize_cd_audio_playback_state();
      bVar9 = iVar3 == 0;
      if (!bVar9) {
        iVar3 = find_cutscene_smk_file(s_int12f01_smk_004f8be4,0);
        bVar9 = iVar3 == 0;
        if (!bVar9) {
          local_a0 = 1;
        }
      }
    }
    if (!bVar9) {
      return 1;
    }
    if (param_1 == 0) {
      return 1;
    }
    pcVar6 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                   s_Interstate__76_CD_2_004f8bb0);
    do {
      if (*pcVar6 == '\0') {
        pcVar4 = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                       s_Interstate__76_CD_2_004f8bb0);
        uVar10 = *(undefined4 *)StrLookup_Global_Object_exref;
      }
      else {
        uVar10 = *(undefined4 *)StrLookup_Global_Object_exref;
        pcVar4 = pcVar6;
      }
      pcVar4 = (char *)StrLookupFind(uVar10,s_Please_insert_CD___s__004f8bc4,pcVar4);
      show_init_graphics_error_dialog(pcVar4);
      bVar9 = false;
      DAT_0058d930 = 0;
      DAT_0058d92c = '\0';
      local_a4 = 0;
      do {
        if (bVar9) break;
        if ((&DAT_00609520)[local_a4] != '\0') {
          DAT_0058d930 = DAT_0058d930 + 1;
          cVar7 = (char)local_a4 + 'A';
          _local_60 = CONCAT31((int3)((uint)PTR_DAT_004f8bac >> 8),cVar7);
          BVar2 = GetVolumeInformationA
                            (&local_60,&DAT_00609540,0x20,&local_94,&local_8c,&local_98,local_20,
                             0x20);
          pcVar4 = (char *)(-(uint)(BVar2 != 0) & 0x609540);
          if (pcVar4 != (char *)0x0) {
            uVar5 = 0xffffffff;
            pcVar8 = s_I76_CD2_004f8bdc;
            do {
              if (uVar5 == 0) break;
              uVar5 = uVar5 - 1;
              cVar1 = *pcVar8;
              pcVar8 = pcVar8 + 1;
            } while (cVar1 != '\0');
            iVar3 = _strnicmp(pcVar4,s_I76_CD2_004f8bdc,~uVar5 - 1);
            if (iVar3 == 0) {
              bVar9 = true;
              DAT_0058d92c = cVar7;
            }
          }
        }
        local_a4 = local_a4 + 1;
      } while (local_a4 < 0x1a);
    } while ((!bVar9) && (DAT_0058d92c == '\0'));
    if (local_a0 != 0) {
      return local_a0;
    }
  } while( true );
}


