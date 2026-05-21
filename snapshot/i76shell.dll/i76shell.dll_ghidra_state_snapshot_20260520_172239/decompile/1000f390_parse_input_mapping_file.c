/*
 * Program: i76shell.dll
 * Function: parse_input_mapping_file
 * Entry: 1000f390
 * Signature: undefined4 __cdecl parse_input_mapping_file(char * param_1)
 */


undefined4 __cdecl parse_input_mapping_file(char *param_1)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  code *pcVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  code *pcVar12;
  int *piVar13;
  int *piVar14;
  int *piVar15;
  char *pcVar16;
  char *pcVar17;
  FILE *local_1a8;
  undefined1 local_1a2 [2];
  char local_1a0 [32];
  char local_180 [64];
  char local_140 [64];
  char local_100 [256];
  
  scan_configured_input_devices();
  local_1a8 = fopen(param_1,&DAT_100463f4);
  pcVar12 = isspace_exref;
  if (local_1a8 == (FILE *)0x0) {
    if ((DAT_10056bfc & 0x4000) == 0) {
      pcVar17 = s_keyboard_map_10046408;
    }
    else {
      pcVar17 = s_joystick_map_100463f8;
    }
    CopyFileA(pcVar17,param_1,1);
    local_1a8 = fopen(param_1,&DAT_10046418);
    pcVar12 = isspace_exref;
  }
LAB_1000f3f5:
  do {
    bVar3 = false;
    do {
      pcVar17 = fgets(local_100,0xff,local_1a8);
      if (pcVar17 == (char *)0x0) {
        fclose(local_1a8);
        return 1;
      }
      DAT_10056c14 = DAT_10056c14 + 1;
      pcVar17 = local_100;
      cVar2 = local_100[0];
      while (cVar2 != '\0') {
        cVar2 = *pcVar17;
        if ((cVar2 == '\n') || (cVar2 == '#')) {
          *pcVar17 = '\0';
          break;
        }
        iVar8 = (*pcVar12)((int)cVar2);
        if (iVar8 == 0) {
          bVar3 = true;
        }
        pcVar16 = pcVar17 + 1;
        pcVar17 = pcVar17 + 1;
        cVar2 = *pcVar16;
      }
    } while (!bVar3);
    iVar8 = sscanf(local_100,&DAT_1004641c,local_140);
    if (iVar8 != 1) {
      FUN_1000f310(s_input_mapping_error__line__d__re_10046424);
      fclose(local_1a8);
      return 0;
    }
    iVar8 = 0;
    pcVar17 = s_throttle_100450b0;
    do {
      iVar9 = _stricmp(pcVar17,local_140);
      if (iVar9 == 0) {
        piVar13 = &DAT_100450a8 + iVar8 * 0x16;
        goto LAB_1000f4b5;
      }
      pcVar17 = pcVar17 + 0x58;
      iVar8 = iVar8 + 1;
    } while ((int)pcVar17 < 0x10045e70);
    piVar13 = (int *)0x0;
LAB_1000f4b5:
    if (piVar13 != (int *)0x0) {
      bVar3 = false;
      do {
        pcVar17 = fgets(local_100,0xff,local_1a8);
        if (pcVar17 == (char *)0x0) {
          FUN_1000f310(s_input_mapping_error__line__d__un_10046450);
          fclose(local_1a8);
          return 0;
        }
        DAT_10056c14 = DAT_10056c14 + 1;
        pcVar17 = local_100;
        cVar2 = local_100[0];
        while (cVar2 != '\0') {
          cVar2 = *pcVar17;
          if ((cVar2 == '\n') || (cVar2 == '#')) {
            *pcVar17 = '\0';
            break;
          }
          iVar8 = isspace((int)cVar2);
          if (iVar8 == 0) {
            bVar3 = true;
          }
          pcVar16 = pcVar17 + 1;
          pcVar17 = pcVar17 + 1;
          cVar2 = *pcVar16;
        }
      } while (!bVar3);
      iVar8 = sscanf(local_100,s__1______s__s_10046480,local_1a2,local_180,local_1a0);
      if (iVar8 != 3) {
        FUN_1000f310(s_input_map_error__line__d__read_e_10046490);
        fclose(local_1a8);
        return 0;
      }
      iVar8 = _strnicmp(local_180,s_m_10046aa4,1);
      if (iVar8 == 0) {
        iVar8 = 3;
      }
      else {
        iVar8 = _strnicmp(local_180,s_j_10046aa0,1);
        iVar8 = 2 - (uint)(iVar8 != 0);
      }
      uVar10 = DAT_10056bfc;
      *piVar13 = iVar8;
      if ((((iVar8 == 1) && ((uVar10 & 0x8000) == 0)) || ((iVar8 == 2 && ((uVar10 & 0x4000) == 0))))
         || ((iVar8 == 3 && ((uVar10 & 0x2000) == 0)))) {
        FUN_1000f310(s_The_device_you_chosen_is_not_con_100464c0);
      }
      iVar8 = _stricmp(local_140,s_throttle_10046510);
      if (iVar8 == 0) {
        uVar10 = 0xffffffff;
        pcVar17 = local_1a0;
        do {
          pcVar16 = pcVar17;
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          pcVar16 = pcVar17 + 1;
          cVar2 = *pcVar17;
          pcVar17 = pcVar16;
        } while (cVar2 != '\0');
        uVar10 = ~uVar10;
        piVar14 = (int *)(pcVar16 + -uVar10);
        piVar15 = piVar13 + 10;
        for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *piVar15 = *piVar14;
          piVar14 = piVar14 + 1;
          piVar15 = piVar15 + 1;
        }
        for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(char *)piVar15 = (char)*piVar14;
          piVar14 = (int *)((int)piVar14 + 1);
          piVar15 = (int *)((int)piVar15 + 1);
        }
        if (*piVar13 == 2) {
          DAT_10045100 = 0;
          DAT_10045158 = 0;
          wsprintfA((LPSTR)&DAT_10045128,s__s_1004651c,local_180);
          pcVar17 = s__s_10046520;
LAB_1000f67e:
          wsprintfA((LPSTR)&DAT_10045180,pcVar17,local_180);
        }
        else if (*DAT_10056c2c == 3) {
          DAT_10045100 = 0;
          DAT_10045158 = 0;
          wsprintfA((LPSTR)&DAT_10045128,s__s_10046524,local_180);
          pcVar17 = s__s_10046528;
          goto LAB_1000f67e;
        }
        iVar8 = _strnicmp(local_1a0,s_left_1004652c,4);
        cVar2 = DAT_10046538;
        if (iVar8 == 0) {
          iVar8 = -1;
          pcVar17 = (char *)&DAT_10045128;
          do {
            pcVar16 = pcVar17;
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            pcVar16 = pcVar17 + 1;
            cVar1 = *pcVar17;
            pcVar17 = pcVar16;
          } while (cVar1 != '\0');
          *(undefined4 *)(pcVar16 + -1) = DAT_10046534;
          iVar8 = -1;
          pcVar16[3] = cVar2;
          uVar5 = s_Right_1004653c._4_2_;
          pcVar17 = (char *)&DAT_10045180;
          do {
            pcVar16 = pcVar17;
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            pcVar16 = pcVar17 + 1;
            cVar2 = *pcVar17;
            pcVar17 = pcVar16;
          } while (cVar2 != '\0');
          *(undefined4 *)(pcVar16 + -1) = s_Right_1004653c._0_4_;
          *(undefined2 *)(pcVar16 + 3) = uVar5;
        }
        else {
          iVar8 = _strnicmp(local_1a0,&DAT_10046544,4);
          uVar6 = DAT_10046550;
          cVar2 = DAT_1004654e;
          if (iVar8 == 0) {
            iVar8 = -1;
            pcVar17 = (char *)&DAT_10045128;
            do {
              pcVar16 = pcVar17;
              if (iVar8 == 0) break;
              iVar8 = iVar8 + -1;
              pcVar16 = pcVar17 + 1;
              cVar1 = *pcVar17;
              pcVar17 = pcVar16;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar16 + -1) = DAT_1004654c;
            pcVar16[1] = cVar2;
            cVar2 = DAT_10046554;
            iVar8 = -1;
            pcVar17 = (char *)&DAT_10045180;
            do {
              pcVar16 = pcVar17;
              if (iVar8 == 0) break;
              iVar8 = iVar8 + -1;
              pcVar16 = pcVar17 + 1;
              cVar1 = *pcVar17;
              pcVar17 = pcVar16;
            } while (cVar1 != '\0');
            *(undefined4 *)(pcVar16 + -1) = uVar6;
            pcVar16[3] = cVar2;
          }
          else {
            iVar8 = _strnicmp(local_1a0,s_thro_10046558,4);
            cVar2 = s_Throttle_10046560[8];
            uVar6 = s_Throttle_10046560._4_4_;
            if (iVar8 == 0) {
              iVar8 = -1;
              pcVar17 = (char *)&DAT_10045128;
              do {
                pcVar16 = pcVar17;
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                pcVar16 = pcVar17 + 1;
                cVar1 = *pcVar17;
                pcVar17 = pcVar16;
              } while (cVar1 != '\0');
              *(undefined4 *)(pcVar16 + -1) = s_Throttle_10046560._0_4_;
              uVar7 = s_Throttle_1004656c._0_4_;
              *(undefined4 *)(pcVar16 + 3) = uVar6;
              pcVar16[7] = cVar2;
              cVar2 = s_Throttle_1004656c[8];
              uVar6 = s_Throttle_1004656c._4_4_;
              iVar8 = -1;
              pcVar17 = (char *)&DAT_10045180;
              do {
                pcVar16 = pcVar17;
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                pcVar16 = pcVar17 + 1;
                cVar1 = *pcVar17;
                pcVar17 = pcVar16;
              } while (cVar1 != '\0');
              *(undefined4 *)(pcVar16 + -1) = uVar7;
              *(undefined4 *)(pcVar16 + 3) = uVar6;
              pcVar16[7] = cVar2;
            }
            else {
              iVar8 = _strnicmp(local_1a0,s_rudd_10046578,4);
              cVar2 = s_Rudder_10046580[6];
              uVar5 = s_Rudder_10046580._4_2_;
              if (iVar8 == 0) {
                iVar8 = -1;
                pcVar17 = (char *)&DAT_10045128;
                do {
                  pcVar16 = pcVar17;
                  if (iVar8 == 0) break;
                  iVar8 = iVar8 + -1;
                  pcVar16 = pcVar17 + 1;
                  cVar1 = *pcVar17;
                  pcVar17 = pcVar16;
                } while (cVar1 != '\0');
                *(undefined4 *)(pcVar16 + -1) = s_Rudder_10046580._0_4_;
                *(undefined2 *)(pcVar16 + 3) = uVar5;
                iVar8 = -1;
                pcVar16[5] = cVar2;
                cVar2 = s_Rudder_10046588[6];
                uVar5 = s_Rudder_10046588._4_2_;
                pcVar17 = (char *)&DAT_10045180;
                do {
                  pcVar16 = pcVar17;
                  if (iVar8 == 0) break;
                  iVar8 = iVar8 + -1;
                  pcVar16 = pcVar17 + 1;
                  cVar1 = *pcVar17;
                  pcVar17 = pcVar16;
                } while (cVar1 != '\0');
                *(undefined4 *)(pcVar16 + -1) = s_Rudder_10046588._0_4_;
                *(undefined2 *)(pcVar16 + 3) = uVar5;
                pcVar16[5] = cVar2;
              }
            }
          }
        }
      }
      else {
        iVar8 = _stricmp(local_140,s_steer_10046590);
        if (iVar8 != 0) {
          uVar10 = 0xffffffff;
          pcVar17 = local_1a0;
          do {
            pcVar16 = pcVar17;
            if (uVar10 == 0) break;
            uVar10 = uVar10 - 1;
            pcVar16 = pcVar17 + 1;
            cVar2 = *pcVar17;
            pcVar17 = pcVar16;
          } while (cVar2 != '\0');
          uVar10 = ~uVar10;
          piVar14 = (int *)(pcVar16 + -uVar10);
          piVar13 = piVar13 + 10;
          for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
            *piVar13 = *piVar14;
            piVar14 = piVar14 + 1;
            piVar13 = piVar13 + 1;
          }
          for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
            *(char *)piVar13 = (char)*piVar14;
            piVar14 = (int *)((int)piVar14 + 1);
            piVar13 = (int *)((int)piVar13 + 1);
          }
          goto LAB_1000fa4f;
        }
        uVar10 = 0xffffffff;
        pcVar17 = local_1a0;
        do {
          pcVar16 = pcVar17;
          if (uVar10 == 0) break;
          uVar10 = uVar10 - 1;
          pcVar16 = pcVar17 + 1;
          cVar2 = *pcVar17;
          pcVar17 = pcVar16;
        } while (cVar2 != '\0');
        uVar10 = ~uVar10;
        piVar14 = (int *)(pcVar16 + -uVar10);
        piVar15 = piVar13 + 10;
        for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
          *piVar15 = *piVar14;
          piVar14 = piVar14 + 1;
          piVar15 = piVar15 + 1;
        }
        for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(char *)piVar15 = (char)*piVar14;
          piVar14 = (int *)((int)piVar14 + 1);
          piVar15 = (int *)((int)piVar15 + 1);
        }
        if (*piVar13 == 2) {
          DAT_10045208 = 0;
          DAT_10045260 = 0;
          wsprintfA((LPSTR)&DAT_10045230,s__s_10046598,local_180);
          pcVar17 = s__s_1004659c;
LAB_1000f8b2:
          wsprintfA((LPSTR)&DAT_10045288,pcVar17,local_180);
        }
        else if (*DAT_10056c2c == 3) {
          DAT_10045208 = 0;
          DAT_10045260 = 0;
          wsprintfA((LPSTR)&DAT_10045230,s__s_100465a0,local_180);
          pcVar17 = s__s_100465a4;
          goto LAB_1000f8b2;
        }
        iVar8 = _strnicmp(local_1a0,s_left_100465a8,4);
        cVar2 = DAT_100465b4;
        if (iVar8 == 0) {
          iVar8 = -1;
          pcVar17 = (char *)&DAT_10045230;
          do {
            pcVar16 = pcVar17;
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            pcVar16 = pcVar17 + 1;
            cVar1 = *pcVar17;
            pcVar17 = pcVar16;
          } while (cVar1 != '\0');
          *(undefined4 *)(pcVar16 + -1) = DAT_100465b0;
          iVar8 = -1;
          pcVar16[3] = cVar2;
          uVar5 = s_Right_100465b8._4_2_;
          pcVar17 = (char *)&DAT_10045288;
          do {
            pcVar16 = pcVar17;
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            pcVar16 = pcVar17 + 1;
            cVar2 = *pcVar17;
            pcVar17 = pcVar16;
          } while (cVar2 != '\0');
          *(undefined4 *)(pcVar16 + -1) = s_Right_100465b8._0_4_;
          *(undefined2 *)(pcVar16 + 3) = uVar5;
        }
        else {
          iVar8 = _strnicmp(local_1a0,s_down_100465c0,4);
          uVar6 = DAT_100465cc;
          cVar2 = DAT_100465ca;
          if (iVar8 == 0) {
            iVar8 = -1;
            pcVar17 = (char *)&DAT_10045230;
            do {
              pcVar16 = pcVar17;
              if (iVar8 == 0) break;
              iVar8 = iVar8 + -1;
              pcVar16 = pcVar17 + 1;
              cVar1 = *pcVar17;
              pcVar17 = pcVar16;
            } while (cVar1 != '\0');
            *(undefined2 *)(pcVar16 + -1) = DAT_100465c8;
            pcVar16[1] = cVar2;
            cVar2 = DAT_100465d0;
            iVar8 = -1;
            pcVar17 = (char *)&DAT_10045288;
            do {
              pcVar16 = pcVar17;
              if (iVar8 == 0) break;
              iVar8 = iVar8 + -1;
              pcVar16 = pcVar17 + 1;
              cVar1 = *pcVar17;
              pcVar17 = pcVar16;
            } while (cVar1 != '\0');
            *(undefined4 *)(pcVar16 + -1) = uVar6;
            pcVar16[3] = cVar2;
          }
          else {
            iVar8 = _strnicmp(local_1a0,s_thro_100465d4,4);
            cVar2 = s_Throttle_100465dc[8];
            uVar6 = s_Throttle_100465dc._4_4_;
            if (iVar8 == 0) {
              iVar8 = -1;
              pcVar17 = (char *)&DAT_10045230;
              do {
                pcVar16 = pcVar17;
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                pcVar16 = pcVar17 + 1;
                cVar1 = *pcVar17;
                pcVar17 = pcVar16;
              } while (cVar1 != '\0');
              *(undefined4 *)(pcVar16 + -1) = s_Throttle_100465dc._0_4_;
              uVar7 = s_Throttle_100465e8._0_4_;
              *(undefined4 *)(pcVar16 + 3) = uVar6;
              pcVar16[7] = cVar2;
              cVar2 = s_Throttle_100465e8[8];
              uVar6 = s_Throttle_100465e8._4_4_;
              iVar8 = -1;
              pcVar17 = (char *)&DAT_10045288;
              do {
                pcVar16 = pcVar17;
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                pcVar16 = pcVar17 + 1;
                cVar1 = *pcVar17;
                pcVar17 = pcVar16;
              } while (cVar1 != '\0');
              *(undefined4 *)(pcVar16 + -1) = uVar7;
              *(undefined4 *)(pcVar16 + 3) = uVar6;
              pcVar16[7] = cVar2;
            }
            else {
              iVar8 = _strnicmp(local_1a0,s_rudd_100465f4,4);
              cVar2 = s_Rudder_100465fc[6];
              uVar5 = s_Rudder_100465fc._4_2_;
              if (iVar8 == 0) {
                iVar8 = -1;
                pcVar17 = (char *)&DAT_10045230;
                do {
                  pcVar16 = pcVar17;
                  if (iVar8 == 0) break;
                  iVar8 = iVar8 + -1;
                  pcVar16 = pcVar17 + 1;
                  cVar1 = *pcVar17;
                  pcVar17 = pcVar16;
                } while (cVar1 != '\0');
                *(undefined4 *)(pcVar16 + -1) = s_Rudder_100465fc._0_4_;
                *(undefined2 *)(pcVar16 + 3) = uVar5;
                iVar8 = -1;
                pcVar16[5] = cVar2;
                cVar2 = s_Rudder_10046604[6];
                uVar5 = s_Rudder_10046604._4_2_;
                pcVar17 = (char *)&DAT_10045288;
                do {
                  pcVar16 = pcVar17;
                  if (iVar8 == 0) break;
                  iVar8 = iVar8 + -1;
                  pcVar16 = pcVar17 + 1;
                  cVar1 = *pcVar17;
                  pcVar17 = pcVar16;
                } while (cVar1 != '\0');
                *(undefined4 *)(pcVar16 + -1) = s_Rudder_10046604._0_4_;
                *(undefined2 *)(pcVar16 + 3) = uVar5;
                pcVar16[5] = cVar2;
              }
            }
          }
        }
      }
    }
LAB_1000fa4f:
    do {
      pcVar4 = isspace_exref;
      bVar3 = false;
      do {
        pcVar17 = fgets(local_100,0xff,local_1a8);
        pcVar12 = pcVar4;
        if (pcVar17 == (char *)0x0) goto LAB_1000f3f5;
        DAT_10056c14 = DAT_10056c14 + 1;
        pcVar17 = local_100;
        pcVar12 = isspace_exref;
        cVar2 = local_100[0];
        while (isspace_exref = pcVar12, cVar2 != '\0') {
          cVar2 = *pcVar17;
          if ((cVar2 == '\n') || (cVar2 == '#')) {
            *pcVar17 = '\0';
            break;
          }
          iVar8 = isspace((int)cVar2);
          if (iVar8 == 0) {
            bVar3 = true;
          }
          pcVar16 = pcVar17 + 1;
          pcVar17 = pcVar17 + 1;
          pcVar12 = isspace_exref;
          cVar2 = *pcVar16;
        }
      } while (!bVar3);
    } while (local_100[0] != '}');
  } while( true );
}


