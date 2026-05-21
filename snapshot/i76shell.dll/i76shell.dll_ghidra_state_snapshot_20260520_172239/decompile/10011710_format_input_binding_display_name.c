/*
 * Program: i76shell.dll
 * Function: format_input_binding_display_name
 * Entry: 10011710
 * Signature: undefined4 __cdecl format_input_binding_display_name(char * param_1)
 */


undefined4 __cdecl format_input_binding_display_name(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  MMRESULT MVar4;
  uint uVar5;
  uint uVar6;
  joyinfoex_tag *pjVar7;
  char *pcVar8;
  char *pcVar9;
  joyinfo_tag local_1d8;
  joyinfoex_tag local_1c8;
  tagJOYCAPSA local_194;
  
  FUN_1000b550((byte *)s_Press_any_key_or_button____10046a04);
  FUN_1001ce70();
LAB_1001173d:
  do {
    do {
      do {
        sVar2 = FUN_1001d960();
        if (sVar2 != 0) {
          iVar3 = *(int *)(&DAT_10045e68 + sVar2 * 4);
          if ((0xff < iVar3) || (iVar3 < 1)) {
            return 0;
          }
          switch(DAT_10056c28) {
          case 0x55:
          case 0x5e:
          case 0x5f:
          case 0x61:
          case 0x62:
          case 99:
          case 100:
          case 0x66:
          case 0x67:
            sprintf(param_1,s_Grey_s_10046a28,*(undefined4 *)(&DAT_1004943c + iVar3 * 2));
            *DAT_10056c2c = 1;
            return 1;
          default:
            uVar5 = 0xffffffff;
            pcVar8 = *(char **)(&DAT_1004943c + iVar3 * 2);
            break;
          case 0x60:
          case 0x65:
            sprintf(param_1,s__Grey_s_10046a20,*(undefined4 *)(&DAT_1004943c + iVar3 * 2));
            *DAT_10056c2c = 1;
            return 1;
          }
          goto code_r0x10011970;
        }
        if ((DAT_10056bfc & 0x2000) != 0) {
          update_debug_mouse_coordinate_overlay(DAT_100cc514);
          iVar3 = FUN_1001fb10(DAT_100cc514);
          if (iVar3 == 1) {
            pcVar8 = s_LeftBtn_10046a30;
          }
          else {
            iVar3 = FUN_1001fb20(DAT_100cc514);
            if (iVar3 == 1) {
              pcVar8 = s_RightBtn_10046a38;
            }
            else {
              iVar3 = FUN_1001fb30(DAT_100cc514);
              if (iVar3 != 1) goto LAB_1001179e;
              pcVar8 = s_MiddleBtn_10046a44;
            }
          }
          uVar5 = 0xffffffff;
          goto code_r0x100119cd;
        }
LAB_1001179e:
      } while ((DAT_10056bfc & 0x4000) == 0);
      joyGetDevCapsA(0,&local_194,0x194);
      if ((3 < local_194.wNumAxes) && (3 < local_194.wMaxButtons)) {
        pjVar7 = &local_1c8;
        for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
          pjVar7->dwSize = 0;
          pjVar7 = (joyinfoex_tag *)&pjVar7->dwFlags;
        }
        local_1c8.dwSize = 0x34;
        local_1c8.dwFlags = 0xc0;
        MVar4 = joyGetPosEx(0,&local_1c8);
        if (MVar4 == 0) {
          if (local_1c8.dwPOV == 0xffff) {
            if (local_1c8.dwButtons != 0) {
              uVar5 = 1;
              iVar3 = 1;
              do {
                if ((local_1c8.dwButtons & uVar5) != 0) {
                  wsprintfA(param_1,s_Button_d_10046a94,iVar3);
                  *DAT_10056c2c = 2;
                  return 1;
                }
                uVar5 = uVar5 << 1;
                iVar3 = iVar3 + 1;
              } while (iVar3 < 0x20);
            }
          }
          else if (local_1c8.dwPOV < 0x2329) {
            if (local_1c8.dwPOV == 9000) {
              wsprintfA(param_1,s_HatRight_10046a78);
              *DAT_10056c2c = 2;
              return 1;
            }
            if (local_1c8.dwPOV == 0) {
              wsprintfA(param_1,s_HatUp_10046a70);
              *DAT_10056c2c = 2;
              return 1;
            }
          }
          else {
            if (local_1c8.dwPOV == 18000) {
              wsprintfA(param_1,s_HatDown_10046a84);
              *DAT_10056c2c = 2;
              return 1;
            }
            if (local_1c8.dwPOV == 27000) {
              wsprintfA(param_1,s_HatLeft_10046a8c);
              goto LAB_10011b25;
            }
          }
        }
        goto LAB_1001173d;
      }
      local_1d8.wXpos = 0;
      local_1d8.wYpos = 0;
      local_1d8.wZpos = 0;
      local_1d8.wButtons = 0;
      MVar4 = joyGetPos(0,&local_1d8);
    } while (MVar4 != 0);
    if (local_1d8.wButtons == 1) {
      pcVar8 = s_Button1_10046a50;
      goto LAB_10011b03;
    }
    if (local_1d8.wButtons == 2) {
      pcVar8 = s_Button2_10046a58;
      goto LAB_10011b03;
    }
    if (local_1d8.wButtons == 4) {
      pcVar8 = s_Button3_10046a60;
      goto LAB_10011b03;
    }
  } while (local_1d8.wButtons != 8);
  pcVar8 = &DAT_10046a68;
LAB_10011b03:
  uVar5 = 0xffffffff;
  do {
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *param_1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    param_1 = param_1 + 1;
  }
LAB_10011b25:
  *DAT_10056c2c = 2;
  return 1;
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
    if (cVar1 == '\0') break;
code_r0x10011970:
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *param_1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    param_1 = param_1 + 1;
  }
  *DAT_10056c2c = 1;
  return 1;
  while( true ) {
    uVar5 = uVar5 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
    if (cVar1 == '\0') break;
code_r0x100119cd:
    pcVar9 = pcVar8;
    if (uVar5 == 0) break;
  }
  uVar5 = ~uVar5;
  pcVar8 = pcVar9 + -uVar5;
  for (uVar6 = uVar5 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
    *(undefined4 *)param_1 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    param_1 = param_1 + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *param_1 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    param_1 = param_1 + 1;
  }
  *DAT_10056c2c = 3;
  return 1;
}


