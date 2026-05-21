/*
 * Program: i76shell.dll
 * Function: validate_joined_multiplayer_session_and_fill_launch_config
 * Entry: 1002fcd8
 * Signature: undefined __stdcall validate_joined_multiplayer_session_and_fill_launch_config(void)
 */


void validate_joined_multiplayer_session_and_fill_launch_config(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;
  char *pcVar6;
  LPCSTR pCVar7;
  HANDLE hObject;
  undefined4 *puVar8;
  LPCSTR lpText;
  DWORD DVar9;
  uint uVar10;
  uint uVar11;
  byte *pbVar12;
  uint *puVar13;
  undefined4 *puVar14;
  char *pcVar15;
  uint *puVar16;
  bool bVar17;
  bool bVar18;
  undefined4 uStackY_38c;
  undefined4 uStackY_358;
  UINT UVar19;
  uint local_328;
  short local_322;
  char local_2f4 [80];
  char local_2a4 [80];
  uint local_254;
  short local_24c;
  undefined2 uStack_24a;
  undefined2 local_248;
  undefined2 uStack_246;
  char local_240 [30];
  char local_222 [18];
  uint local_210;
  undefined4 local_54;
  
  if (DAT_100f4ee8 != 0) {
    do {
      iVar3 = dpReceive();
      if (iVar3 == 0) {
        if (local_322 == 0) {
          if (((short)local_254 == 0x3864) && (local_24c == 3)) {
            puVar8 = (undefined4 *)CONCAT22(local_248,uStack_24a);
            puVar14 = &DAT_100f4778;
            for (iVar5 = 0x66; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar14 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar14 = puVar14 + 1;
            }
            (**(code **)(DAT_10058198 + 100))();
            DAT_100f2324 = 1;
          }
        }
        else if (DAT_100f21cc == 2) {
          if ((local_254 & 0xffff) == 0x444a) {
            iVar5 = CONCAT22(uStack_246,local_248);
            if (iVar5 == 1) {
              UVar19 = 0;
              pCVar7 = (LPCSTR)resolve_localized_shell_string_cached
                                         (DAT_100f5360,s_Timeout_1004c880);
              pcVar6 = s_Your_request_timed_out__Try_agai_1004c888;
            }
            else if (iVar5 == 2) {
              UVar19 = 0;
              pCVar7 = (LPCSTR)resolve_localized_shell_string_cached
                                         (DAT_100f5360,s_You_ve_been_rejected__1004c8cc);
              pcVar6 = s_The_host_has_rejected_you__Go_fi_1004c8e4;
            }
            else {
              if (iVar5 != 4) goto LAB_10030183;
              UVar19 = 0;
              pCVar7 = (LPCSTR)resolve_localized_shell_string_cached
                                         (DAT_100f5360,s_Game_full__1004c8ac);
              pcVar6 = s_The_game_is_full__1004c8b8;
            }
            lpText = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar6);
            MessageBoxA(DAT_100f702c,lpText,pCVar7,UVar19);
LAB_10030183:
            DAT_100f21cc = 0;
            dpClose();
            FUN_1000c2a0();
            DAT_100f4ee4 = 0;
          }
          else if ((local_254 & 0xffff) == 0x4f4a) {
            pbVar12 = (byte *)&local_248;
            pbVar4 = &DAT_1004c724;
            do {
              bVar2 = *pbVar4;
              bVar17 = bVar2 < *pbVar12;
              if (bVar2 != *pbVar12) {
LAB_1002fd9a:
                iVar5 = (1 - (uint)bVar17) - (uint)(bVar17 != 0);
                goto LAB_1002fd9f;
              }
              if (bVar2 == 0) break;
              bVar2 = pbVar4[1];
              bVar17 = bVar2 < pbVar12[1];
              if (bVar2 != pbVar12[1]) goto LAB_1002fd9a;
              pbVar4 = pbVar4 + 2;
              pbVar12 = pbVar12 + 2;
            } while (bVar2 != 0);
            iVar5 = 0;
LAB_1002fd9f:
            bVar17 = iVar5 != 0;
            if (bVar17) {
              pcVar6 = (char *)resolve_localized_shell_string_cached
                                         (DAT_100f5360,s_Your_version__v_s__of_Interstate_1004c734);
              sprintf(local_2f4,pcVar6);
              UVar19 = 0;
              pCVar7 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004c7d4);
              MessageBoxA(DAT_100f702c,local_2f4,pCVar7,UVar19);
            }
            _splitpath(local_222,(char *)0x0,(char *)0x0,(char *)0x0,local_2a4);
            iVar5 = 5;
            bVar18 = true;
            pcVar6 = local_2a4;
            pcVar15 = &DAT_1004c7dc;
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar18 = *pcVar6 == *pcVar15;
              pcVar6 = pcVar6 + 1;
              pcVar15 = pcVar15 + 1;
            } while (bVar18);
            if (bVar18) {
              sprintf(local_2a4,s_addon__s_1004c7e4);
              uStackY_358 = 0x1002fe6f;
              hObject = CreateFileA(local_2a4,0x80000000,0,(LPSECURITY_ATTRIBUTES)0x0,3,0,
                                    (HANDLE)0x0);
              if (hObject == (HANDLE)0xffffffff) {
                pcVar6 = (char *)resolve_localized_shell_string_cached
                                           (DAT_100f5360,s_You_don_t_have_mission__s__Check_1004c7f0
                                           );
                sprintf(local_2f4,pcVar6);
                UVar19 = 0;
                pCVar7 = (LPCSTR)resolve_localized_shell_string_cached
                                           (DAT_100f5360,s_Error_1004c840);
                MessageBoxA(DAT_100f702c,local_2f4,pCVar7,UVar19);
                bVar17 = true;
              }
              else {
                FUN_10022bc0();
                CloseHandle(hObject);
                if (local_328 != local_210) {
                  pcVar6 = (char *)resolve_localized_shell_string_cached
                                             (DAT_100f5360,
                                              s_Your_mission_file__s_does_not_ma_1004c848);
                  sprintf(local_2f4,pcVar6);
                  UVar19 = 0;
                  pCVar7 = (LPCSTR)resolve_localized_shell_string_cached
                                             (DAT_100f5360,s_Error_1004c878);
                  MessageBoxA(DAT_100f702c,local_2f4,pCVar7,UVar19);
                  bVar17 = true;
                }
              }
            }
            else {
              local_328 = 0;
            }
            if (bVar17) goto LAB_10030183;
            if (DAT_100f3548 != (HANDLE)0x0) {
              CloseHandle(DAT_100f3548);
              DAT_100f3548 = (HANDLE)0x0;
            }
            puVar13 = DAT_100f231c;
            for (iVar5 = 0x8c; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar13 = 0;
              puVar13 = puVar13 + 1;
            }
            DAT_100f231c[2] = DAT_100f4ee8;
            DAT_100f231c[1] = DAT_100d217c;
            *(undefined2 *)(DAT_100f231c + 3) = DAT_100f3560;
            *DAT_100f231c = 1;
            *DAT_100f231c = *DAT_100f231c | -(uint)(DAT_100d218c != 0) & 0x20;
            dpGetSessionDesc();
            puVar8 = &local_54;
            puVar14 = &uStackY_38c;
            for (iVar5 = 0x14; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar14 = *puVar8;
              puVar8 = puVar8 + 1;
              puVar14 = puVar14 + 1;
            }
            *(undefined2 *)puVar14 = *(undefined2 *)puVar8;
            *(undefined1 *)((int)puVar14 + 2) = *(undefined1 *)((int)puVar8 + 2);
            puVar8 = find_current_directplay_session_desc();
            if (puVar8 != (undefined4 *)0x0) {
              *DAT_100f231c = *DAT_100f231c | (-(uint)(puVar8[0x22] != 0) & 0xfffffffc) + 4;
              *DAT_100f231c = *DAT_100f231c | -(uint)(puVar8[0x21] != 0) & 8;
              DAT_100f231c[0x24] = puVar8[0x1f];
              DAT_100f231c[0x25] = puVar8[0x23];
            }
            format_launch_config_resource_path_at_0x4e((LPSTR)((int)DAT_100f231c + 0x4e));
            uVar10 = 0xffffffff;
            pcVar6 = local_222;
            do {
              pcVar15 = pcVar6;
              if (uVar10 == 0) break;
              uVar10 = uVar10 - 1;
              pcVar15 = pcVar6 + 1;
              cVar1 = *pcVar6;
              pcVar6 = pcVar15;
            } while (cVar1 != '\0');
            uVar10 = ~uVar10;
            pcVar6 = pcVar15 + -uVar10;
            pcVar15 = (char *)((int)DAT_100f231c + 0x5d);
            for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *(undefined4 *)pcVar15 = *(undefined4 *)pcVar6;
              pcVar6 = pcVar6 + 4;
              pcVar15 = pcVar15 + 4;
            }
            for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
              *pcVar15 = *pcVar6;
              pcVar6 = pcVar6 + 1;
              pcVar15 = pcVar15 + 1;
            }
            DAT_100f231c[0x1b] = local_328;
            uVar10 = 0xffffffff;
            pcVar6 = local_240;
            do {
              pcVar15 = pcVar6;
              if (uVar10 == 0) break;
              uVar10 = uVar10 - 1;
              pcVar15 = pcVar6 + 1;
              cVar1 = *pcVar6;
              pcVar6 = pcVar15;
            } while (cVar1 != '\0');
            uVar10 = ~uVar10;
            puVar13 = (uint *)(pcVar15 + -uVar10);
            puVar16 = DAT_100f231c + 0x1c;
            for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
              *puVar16 = *puVar13;
              puVar13 = puVar13 + 1;
              puVar16 = puVar16 + 1;
            }
            for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
              *(char *)puVar16 = (char)*puVar13;
              puVar13 = (uint *)((int)puVar13 + 1);
              puVar16 = (uint *)((int)puVar16 + 1);
            }
            puVar13 = &DAT_100f4778;
            puVar16 = DAT_100f231c + 0x26;
            for (iVar5 = 0x66; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar16 = *puVar13;
              puVar13 = puVar13 + 1;
              puVar16 = puVar16 + 1;
            }
            DAT_100f21cc = 3;
            FUN_1000c2a0();
            DAT_100f4ee4 = 0;
          }
        }
      }
      if (iVar3 == 0x10) {
        show_modal_ok_dialog(&LAB_100302f8);
      }
    } while (iVar3 == 0);
    if (DAT_100f21cc == 2) {
      iVar3 = FUN_1000c250();
      if (iVar3 != 0) {
        DAT_100f21cc = 0;
        dpClose();
        FUN_1000c2a0();
        DAT_100f4ee4 = 0;
        return;
      }
      DVar9 = GetTickCount();
      if (500 < DVar9 - DAT_100f21d8) {
        DAT_100f21d8 = DVar9;
        iVar3 = dpSend();
        if ((iVar3 != 0) && (iVar3 != 3)) {
          assert();
        }
        DAT_100f21d8 = GetTickCount();
      }
    }
  }
  return;
}


