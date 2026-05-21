/*
 * Program: i76shell.dll
 * Function: populate_vehicle_parts_by_allowed_mission_inventory
 * Entry: 1002c2f0
 * Signature: undefined __stdcall populate_vehicle_parts_by_allowed_mission_inventory(void)
 */


void populate_vehicle_parts_by_allowed_mission_inventory(void)

{
  int *piVar1;
  int iVar2;
  char *_Str1;
  char *pcVar3;
  char *pcVar4;
  bool bVar5;
  int local_4;
  
  build_special_equipment_name_list(DAT_100d1db0);
  local_4 = 0;
  if (0 < DAT_10047710) {
    _Str1 = &DAT_100c62c3;
    do {
      iVar2 = 6;
      bVar5 = true;
      pcVar3 = _Str1 + -0x3b;
      pcVar4 = s_EMPTY_1004c214;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar5 = *pcVar3 == *pcVar4;
        pcVar3 = pcVar3 + 1;
        pcVar4 = pcVar4 + 1;
      } while (bVar5);
      if (bVar5) goto switchD_1002c347_default;
      switch(*(undefined4 *)(_Str1 + -0x1d)) {
      case 1:
      case 4:
        piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
        *piVar1 = (int)(_Str1 + -0x3b);
        piVar1[1] = 0;
        piVar1[2] = 0;
        piVar1[3] = *(int *)(_Str1 + 0x11);
        insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
        iVar2 = DAT_100d1dbc;
        break;
      case 2:
        piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
        *piVar1 = (int)(_Str1 + -0x3b);
        piVar1[1] = 0;
        piVar1[2] = 0;
        piVar1[3] = *(int *)(_Str1 + 0x11);
        insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
        iVar2 = DAT_100d1dac;
        break;
      case 3:
        piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
        *piVar1 = (int)(_Str1 + -0x3b);
        piVar1[1] = 0;
        piVar1[2] = 0;
        piVar1[3] = *(int *)(_Str1 + 0x11);
        insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
        iVar2 = DAT_100d1dc0;
        break;
      case 5:
        piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
        *piVar1 = (int)(_Str1 + -0x3b);
        piVar1[1] = 0;
        piVar1[2] = 0;
        piVar1[3] = *(int *)(_Str1 + 0x11);
        insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
        iVar2 = DAT_100d1db8;
        break;
      case 6:
      case 7:
      case 9:
      case 10:
      case 0xb:
        iVar2 = _strnicmp(&DAT_100581b4 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,s_natk_1004c238,4);
        if (iVar2 == 0) {
          iVar2 = _strnicmp(_Str1,s_gh45_1004c240,4);
          if ((((iVar2 != 0) && (iVar2 = _strnicmp(_Str1,s_gtktank_1004c248,7), iVar2 != 0)) &&
              (iVar2 = _strnicmp(_Str1,s_gtptank_1004c250,7), iVar2 != 0)) &&
             (iVar2 = _strnicmp(_Str1,s_tthowitz_1004c258,8), iVar2 != 0)) {
            piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
            *piVar1 = (int)(_Str1 + -0x3b);
            piVar1[1] = 0;
            piVar1[2] = 0;
            piVar1[3] = *(int *)(_Str1 + 0x11);
            insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
            iVar2 = DAT_100d1db4;
            break;
          }
        }
        else {
          iVar2 = _strnicmp(_Str1,s_gh45_1004c264,4);
          if ((((((iVar2 != 0) && (iVar2 = _strnicmp(_Str1,s_gtktank_1004c26c,7), iVar2 != 0)) &&
                ((iVar2 = _strnicmp(_Str1,s_gtptank_1004c274,7), iVar2 != 0 &&
                 ((iVar2 = _strnicmp(_Str1,s_tthowitz_1004c27c,8), iVar2 != 0 &&
                  (iVar2 = _strnicmp(_Str1,s_gchades_1004c288,7), iVar2 != 0)))))) &&
               (iVar2 = _strnicmp(_Str1,s_tchades_1004c290,7), iVar2 != 0)) &&
              ((((iVar2 = _strnicmp(_Str1,s_gscherub_1004c298,8), iVar2 != 0 &&
                 (iVar2 = _strnicmp(_Str1,s_tscherub_1004c2a4,8), iVar2 != 0)) &&
                (iVar2 = _strnicmp(_Str1,s_ggchem_1004c2b0,6), iVar2 != 0)) &&
               ((iVar2 = _strnicmp(_Str1,s_gs4get_1004c2b8,6), iVar2 != 0 &&
                (iVar2 = _strnicmp(_Str1,s_gsball_1004c2c0,6), iVar2 != 0)))))) &&
             (((iVar2 = _strnicmp(_Str1,s_tsball_1004c2c8,6), iVar2 != 0 &&
               ((iVar2 = _strnicmp(_Str1,s_tm125mg_1004c2d0,7), iVar2 != 0 &&
                (iVar2 = _strnicmp(_Str1,s_tm125lmg_1004c2d8,8), iVar2 != 0)))) &&
              ((iVar2 = _strnicmp(_Str1,s_gfpyro_1004c2e4,6), iVar2 != 0 &&
               (iVar2 = _strnicmp(_Str1,s_tfpyro_1004c2ec,6), iVar2 != 0)))))) {
            piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
            *piVar1 = (int)(_Str1 + -0x3b);
            piVar1[1] = 0;
            piVar1[2] = 0;
            piVar1[3] = *(int *)(_Str1 + 0x11);
            insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
            iVar2 = DAT_100d1db4;
            break;
          }
        }
        goto switchD_1002c347_default;
      case 8:
        iVar2 = _strnicmp(_Str1,s_gcal_1004c21c,4);
        if (((iVar2 != 0) && (iVar2 = _strnicmp(_Str1,s_gsmo_1004c224,4), iVar2 != 0)) &&
           (iVar2 = _strnicmp(_Str1,s_gceracer_1004c22c,8), iVar2 != 0)) {
          piVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          *piVar1 = (int)(_Str1 + -0x3b);
          piVar1[1] = 0;
          piVar1[2] = 0;
          piVar1[3] = *(int *)(_Str1 + 0x11);
          insert_pointer_list_item_sorted_or_append(DAT_100f21a4,(int)piVar1,(undefined *)0x0);
          iVar2 = DAT_100d1db4;
          break;
        }
      default:
        goto switchD_1002c347_default;
      }
      insert_pointer_list_item_sorted_or_append(iVar2,(int)piVar1,(undefined *)0x0);
switchD_1002c347_default:
      local_4 = local_4 + 1;
      _Str1 = _Str1 + 0x54;
    } while (local_4 < DAT_10047710);
  }
  return;
}


