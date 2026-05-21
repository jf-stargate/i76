/*
 * Program: i76.exe
 * Function: validate_project_wav_smk_resource_list
 * Entry: 004122d0
 * Signature: undefined __cdecl validate_project_wav_smk_resource_list(char * param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: checks wav via resource_exists and smk via cutscene lookup
   
   I76 rename v43: fsm_validate_wav_smk_resource_list
   Validates project WAV/SMK resource list. */

void __cdecl validate_project_wav_smk_resource_list(char *param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  int iVar4;
  undefined3 extraout_var;
  uint uVar5;
  char *pcVar6;
  byte *pbVar7;
  bool bVar8;
  byte local_8 [4];
  int local_4;
  
  local_4 = param_2;
  local_8[3] = 0;
  if (0 < param_2) {
    param_2 = 0;
    pcVar6 = param_1;
    do {
      uVar5 = 0xffffffff;
      pcVar3 = pcVar6;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      pbVar7 = local_8;
      iVar4 = param_2 + (~uVar5 - 1);
      local_8[0] = param_1[param_2 + (~uVar5 - 4)];
      local_8[2] = param_1[iVar4 + -1];
      local_8[1] = param_1[iVar4 + -2];
      pcVar3 = s_wav_004c331c;
      do {
        bVar2 = *pcVar3;
        bVar8 = bVar2 < *pbVar7;
        if (bVar2 != *pbVar7) {
LAB_00412351:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_00412356;
        }
        if (bVar2 == 0) break;
        bVar2 = pcVar3[1];
        bVar8 = bVar2 < pbVar7[1];
        if (bVar2 != pbVar7[1]) goto LAB_00412351;
        pcVar3 = pcVar3 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar2 != 0);
      iVar4 = 0;
LAB_00412356:
      if (iVar4 == 0) {
        bVar8 = resource_exists_in_cache_or_search_paths(pcVar6);
        if (CONCAT31(extraout_var,bVar8) == 0) {
          pcVar6[0x50] = '\0';
          pcVar6[0x51] = '\0';
          pcVar6[0x52] = '\0';
          pcVar6[0x53] = '\0';
          goto LAB_004123d0;
        }
LAB_004123c1:
        pcVar6[0x50] = '\x01';
        pcVar6[0x51] = '\0';
        pcVar6[0x52] = '\0';
        pcVar6[0x53] = '\0';
      }
      else {
        pbVar7 = local_8;
        pcVar3 = s_smk_004c32ec;
        do {
          bVar2 = *pcVar3;
          bVar8 = bVar2 < *pbVar7;
          if (bVar2 != *pbVar7) {
LAB_0041239f:
            iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
            goto LAB_004123a4;
          }
          if (bVar2 == 0) break;
          bVar2 = pcVar3[1];
          bVar8 = bVar2 < pbVar7[1];
          if (bVar2 != pbVar7[1]) goto LAB_0041239f;
          pcVar3 = pcVar3 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar2 != 0);
        iVar4 = 0;
LAB_004123a4:
        if (iVar4 == 0) {
          iVar4 = find_cutscene_smk_file(pcVar6,0);
          if (iVar4 != 0) goto LAB_004123c1;
          pcVar6[0x50] = '\0';
          pcVar6[0x51] = '\0';
          pcVar6[0x52] = '\0';
          pcVar6[0x53] = '\0';
        }
LAB_004123d0:
        report_error();
      }
      param_2 = param_2 + 0x54;
      pcVar6 = pcVar6 + 0x54;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return;
}


