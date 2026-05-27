/*
 * Program: i76.exe
 * Function: parse_input_map
 * Entry: 0044cc90
 * Signature: undefined4 __cdecl parse_input_map(FILE * param_1)
 */


/* i76 second-pass rename
   old_name: FUN_0044cc90
   suggested_name: parse_input_map
   basis: Parses input.map controls, throttle fields, discrete control limits, and line diagnostics.
    */

undefined4 __cdecl parse_input_map(FILE *param_1)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar8;
  undefined **ppuVar9;
  char *pcVar10;
  char *pcVar11;
  char local_166 [2];
  char local_164 [40];
  char local_13c [40];
  char local_114 [20];
  char local_100 [256];
  
LAB_0044cca0:
  do {
    bVar2 = false;
    do {
      pcVar3 = fgets(local_100,0xff,param_1);
      if (pcVar3 == (char *)0x0) {
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
        pcVar11 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar1 = *pcVar11;
      }
    } while (!bVar2);
    iVar5 = sscanf(local_100,s__s___004f4ba4,local_164);
    if (iVar5 != 1) {
      report_error();
      return 0;
    }
    iVar5 = 0;
    ppuVar9 = &PTR_s_input_axis_throttle_004f2860;
    do {
      iVar6 = _stricmp(*ppuVar9,local_164);
      iVar7 = g_input_condition_binding_count;
      if (iVar6 == 0) {
        ppuVar9 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
        goto LAB_0044cd82;
      }
      ppuVar9 = ppuVar9 + 8;
      iVar5 = iVar5 + 1;
    } while (ppuVar9 < &PTR_s_COCKPIT_VIEW_004f3320);
    ppuVar9 = (undefined **)0x0;
LAB_0044cd82:
    if (ppuVar9 == (undefined **)0x0) {
      report_error();
      return 0;
    }
    if (ppuVar9[2] != (undefined *)0x0) {
      if (ppuVar9[2] == (undefined *)0x1) {
        iVar5 = g_input_condition_binding_count * 0x70;
        bVar2 = parse_input_chord_binding
                          (param_1,&DAT_0053ae90 + g_input_condition_binding_count * 0x1c,
                           (int)(&DAT_0053ae98 + g_input_condition_binding_count * 0x1c));
        if (CONCAT31(extraout_var_00,bVar2) != 0) {
          g_input_condition_binding_count = g_input_condition_binding_count + 1;
          if (100 < g_input_condition_binding_count) {
            report_error();
            return 0;
          }
          pcVar3 = *ppuVar9;
          (&DAT_0053ae88)[iVar7 * 0x1c] = ppuVar9[1];
          *(undefined1 *)(&DAT_0053ae8c + iVar7 * 0x1c) = 0;
          iVar7 = strncmp(pcVar3,s_menu__004f4a58,5);
          *(uint *)(&DAT_0053ae94 + iVar5) = (uint)(iVar7 == 0);
          pcVar3 = strstr(local_164,s__plus_004f4a28);
          if ((pcVar3 != (char *)0x0) ||
             (pcVar3 = strstr(local_164,s__minus_004f4a20), pcVar3 != (char *)0x0)) {
            *pcVar3 = '\0';
            iVar5 = 0;
            ppuVar9 = &PTR_s_input_axis_throttle_004f2860;
            do {
              iVar7 = _stricmp(*ppuVar9,local_164);
              if (iVar7 == 0) {
                ppuVar9 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
                goto LAB_0044d097;
              }
              ppuVar9 = ppuVar9 + 8;
              iVar5 = iVar5 + 1;
            } while (ppuVar9 < &PTR_s_COCKPIT_VIEW_004f3320);
            ppuVar9 = (undefined **)0x0;
LAB_0044d097:
            if (ppuVar9 == (undefined **)0x0) {
              uVar4 = 0xffffffff;
              pcVar3 = &DAT_004f4a30;
              do {
                pcVar11 = pcVar3;
                if (uVar4 == 0) break;
                uVar4 = uVar4 - 1;
                pcVar11 = pcVar3 + 1;
                cVar1 = *pcVar3;
                pcVar3 = pcVar11;
              } while (cVar1 != '\0');
              uVar4 = ~uVar4;
              iVar5 = -1;
              pcVar3 = local_164;
              do {
                pcVar10 = pcVar3;
                if (iVar5 == 0) break;
                iVar5 = iVar5 + -1;
                pcVar10 = pcVar3 + 1;
                cVar1 = *pcVar3;
                pcVar3 = pcVar10;
              } while (cVar1 != '\0');
              pcVar3 = pcVar11 + -uVar4;
              pcVar11 = pcVar10 + -1;
              for (uVar8 = uVar4 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                *(undefined4 *)pcVar11 = *(undefined4 *)pcVar3;
                pcVar3 = pcVar3 + 4;
                pcVar11 = pcVar11 + 4;
              }
              for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
                *pcVar11 = *pcVar3;
                pcVar3 = pcVar3 + 1;
                pcVar11 = pcVar11 + 1;
              }
              iVar5 = 0;
              ppuVar9 = &PTR_s_input_axis_throttle_004f2860;
              do {
                iVar7 = _stricmp(*ppuVar9,local_164);
                if (iVar7 == 0) {
                  ppuVar9 = &PTR_s_input_axis_throttle_004f2860 + iVar5 * 8;
                  goto LAB_0044d0fc;
                }
                ppuVar9 = ppuVar9 + 8;
                iVar5 = iVar5 + 1;
              } while (ppuVar9 < &PTR_s_COCKPIT_VIEW_004f3320);
              ppuVar9 = (undefined **)0x0;
LAB_0044d0fc:
              if (ppuVar9 == (undefined **)0x0) goto LAB_0044cca0;
            }
            iVar5 = parse_analog_control_binding(ppuVar9,(char *)0x0,0);
            if (iVar5 < 0) {
              return 0;
            }
          }
        }
      }
      else {
        iVar5 = g_input_condition_binding_count * 0x70;
        bVar2 = parse_input_chord_binding
                          (param_1,&DAT_0053ae90 + g_input_condition_binding_count * 0x1c,
                           (int)(&DAT_0053ae98 + g_input_condition_binding_count * 0x1c));
        if (CONCAT31(extraout_var_01,bVar2) != 0) {
          pcVar3 = *ppuVar9;
          g_input_condition_binding_count = g_input_condition_binding_count + 1;
          (&DAT_0053ae88)[iVar7 * 0x1c] = ppuVar9[1];
          *(undefined1 *)(&DAT_0053ae8c + iVar7 * 0x1c) = 1;
          iVar7 = strncmp(pcVar3,s_menu__004f4a58,5);
          *(uint *)(&DAT_0053ae94 + iVar5) = (uint)(iVar7 == 0);
        }
      }
      goto LAB_0044cca0;
    }
    bVar2 = false;
    do {
      pcVar3 = fgets(local_100,0xff,param_1);
      if (pcVar3 == (char *)0x0) {
        report_error();
        return 0;
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
        pcVar11 = pcVar3 + 1;
        pcVar3 = pcVar3 + 1;
        cVar1 = *pcVar11;
      }
    } while (!bVar2);
    iVar5 = sscanf(local_100,s__1______s__s_004f4ad4,local_166,local_13c,local_114);
    if (iVar5 != 3) {
      report_error();
      return 0;
    }
    iVar5 = 0;
    if (0 < g_input_device_context_count) {
      pcVar3 = (char *)&DAT_0053da68;
      do {
        iVar7 = _stricmp(pcVar3,local_13c);
        if (iVar7 == 0) {
          if ((&DAT_0053da50)[iVar5] == 0) {
            iVar5 = -1;
          }
          goto LAB_0044cea5;
        }
        iVar5 = iVar5 + 1;
        pcVar3 = pcVar3 + 0x28;
      } while (iVar5 < g_input_device_context_count);
    }
    iVar5 = validate_input_device(local_13c);
LAB_0044cea5:
    iVar5 = resolve_analog_input_channel(iVar5,local_114);
    if (iVar5 == -1) {
      do {
        bVar2 = false;
        do {
          pcVar3 = fgets(local_100,0xff,param_1);
          if (pcVar3 == (char *)0x0) goto LAB_0044cca0;
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
            pcVar11 = pcVar3 + 1;
            pcVar3 = pcVar3 + 1;
            cVar1 = *pcVar11;
          }
        } while (!bVar2);
      } while (local_100[0] != '}');
    }
    else {
      iVar5 = parse_analog_control_binding(ppuVar9,local_13c,iVar5);
      if (iVar5 < 0) {
        return 0;
      }
      (&DAT_00536848)[iVar5 * 0x20] = (-(uint)(local_166[0] != '-') & 2) - 1;
      bVar2 = parse_input_chord_binding
                        (param_1,&DAT_00536850 + iVar5 * 0x20,(int)(&DAT_00536854 + iVar5 * 0x20));
      if (CONCAT31(extraout_var,bVar2) == 0) {
        return 0;
      }
    }
  } while( true );
}


