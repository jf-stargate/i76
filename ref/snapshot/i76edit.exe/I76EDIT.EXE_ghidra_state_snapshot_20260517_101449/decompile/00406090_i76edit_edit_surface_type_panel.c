/*
 * Program: I76EDIT.EXE
 * Function: i76edit_edit_surface_type_panel
 * Entry: 00406090
 * Signature: undefined4 __stdcall i76edit_edit_surface_type_panel(HWND param_1, int param_2, uint param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v2:medium] References terrain surface labels such as 'Dirt(non-road)'
   and 'Light Vegitation'; uses dialog/control APIs. */

undefined4 i76edit_edit_surface_type_panel(HWND param_1,int param_2,uint param_3)

{
  bool bVar1;
  bool bVar2;
  WPARAM WVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  char *lParam;
  char *pcVar7;
  undefined4 *puVar8;
  int iVar9;
  code *pcVar10;
  undefined4 *puVar11;
  double dVar12;
  char local_100 [256];
  
  pcVar10 = SendDlgItemMessageA_exref;
  bVar1 = false;
  bVar2 = false;
  if (param_2 == 0x110) {
    lParam = s_Dirt_non_road__00434440;
    do {
      WVar3 = SendDlgItemMessageA(param_1,0x406,0x143,0,(LPARAM)lParam);
      SendDlgItemMessageA(param_1,0x406,0x151,WVar3,*(LPARAM *)(lParam + 0x28));
      pcVar7 = lParam + 0x2c;
      WVar3 = SendDlgItemMessageA(param_1,0x409,0x143,0,(LPARAM)lParam);
      SendDlgItemMessageA(param_1,0x409,0x151,WVar3,*(LPARAM *)(lParam + 0x28));
      SendDlgItemMessageA(param_1,0x41a,0xf1,1,0);
      lParam = pcVar7;
    } while (pcVar7 < &DAT_00434548);
    SendDlgItemMessageA(param_1,0x406,0x14e,1,0);
    SendDlgItemMessageA(param_1,0x409,0x14e,1,0);
  }
  else {
    if (param_2 != 0x111) {
      return 0;
    }
    if (param_3 >> 0x10 == 0) {
      switch(param_3 & 0xffff) {
      case 0x40a:
        DAT_00434434 = 2;
        bVar1 = true;
        break;
      case 0x40b:
        DAT_00434434 = 3;
        bVar1 = true;
        break;
      case 0x418:
        DAT_00434434 = 0;
        bVar1 = true;
        break;
      case 0x419:
        bVar1 = true;
        DAT_00434434 = 1;
        break;
      case 0x41a:
        DAT_00434434 = 4;
        bVar1 = true;
        break;
      case 0x41b:
        DAT_00434434 = 5;
        bVar1 = true;
      }
      sVar6 = (short)param_3;
      if (bVar1) {
        SendDlgItemMessageA(param_1,0x418,0xf1,(uint)(sVar6 == 0x418),0);
        SendDlgItemMessageA(param_1,0x419,0xf1,(uint)(sVar6 == 0x419),0);
        SendDlgItemMessageA(param_1,0x40a,0xf1,(uint)(sVar6 == 0x40a),0);
        SendDlgItemMessageA(param_1,0x40b,0xf1,(uint)(sVar6 == 0x40b),0);
        SendDlgItemMessageA(param_1,0x41a,0xf1,(uint)(sVar6 == 0x41a),0);
        SendDlgItemMessageA(param_1,0x41b,0xf1,(uint)(sVar6 == 0x41b),0);
      }
      else if (sVar6 == 0x425) {
        iVar9 = 0;
        do {
          iVar5 = 0;
          do {
            iVar4 = i76edit_get_or_assign_zone_map_cell_id(iVar9,iVar5,0);
            if (iVar4 != -1) {
              _sprintf(local_100,s_Painting_Zone__d_00434598,iVar4 + 1);
              i76edit_set_status_bar_text(local_100);
              i76edit_export_height_txt_debug_view(iVar4);
            }
            iVar5 = iVar5 + 1;
          } while (iVar5 < 0x50);
          iVar9 = iVar9 + 1;
        } while (iVar9 < 0x50);
        i76edit_set_status_bar_text(s_Ready__00434590);
        pcVar10 = SendDlgItemMessageA_exref;
      }
      else if (sVar6 == 0x40d) {
        if (DAT_0043442c == 0) {
          SendDlgItemMessageA(param_1,0x40d,0xf1,0,0);
          DAT_0043442c = 1;
        }
        else {
          SendDlgItemMessageA(param_1,0x40d,0xf1,1,0);
          SendDlgItemMessageA(param_1,0x424,0xf1,0,0);
          DAT_0043442c = 0;
          DAT_00434430 = 1;
        }
      }
      else if (sVar6 == 0x424) {
        if (DAT_00434430 == 0) {
          SendDlgItemMessageA(param_1,0x424,0xf1,0,0);
          DAT_00434430 = 1;
        }
        else {
          SendDlgItemMessageA(param_1,0x424,0xf1,1,0);
          SendDlgItemMessageA(param_1,0x40d,0xf1,0,0);
          DAT_00434430 = 0;
          DAT_0043442c = 1;
        }
      }
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      switch(param_3 & 0xffff) {
      case 0x404:
        (*pcVar10)(param_1,0x404,0xd,0x10,&DAT_01641e70);
        dVar12 = _atof(&DAT_01641e70);
        *(float *)(&DAT_01642052 + DAT_00433a6c * 0x14) = (float)dVar12;
        break;
      case 0x405:
        (*pcVar10)(param_1,0x405,0xd,0x10,&DAT_01641e70);
        dVar12 = _atof(&DAT_01641e70);
        *(float *)(&DAT_0164204e + DAT_00433a6c * 0x14) = (float)dVar12;
        break;
      case 0x406:
        DAT_00433a6c = (*pcVar10)(param_1,0x406,0x147,0,0);
        _DAT_01641e70 = 0;
        DAT_01641e74 = 0;
        DAT_01641e78 = 0;
        DAT_01641e7c = 0;
        _sprintf(&DAT_01641e70,&DAT_00434588,(double)*(float *)(&DAT_0164204a + DAT_00433a6c * 0x14)
                );
        (*pcVar10)(param_1,0x408,0xc,0,&DAT_01641e70);
        _DAT_01641e70 = 0;
        DAT_01641e74 = 0;
        DAT_01641e78 = 0;
        DAT_01641e7c = 0;
        _sprintf(&DAT_01641e70,&DAT_00434588,(double)*(float *)(&DAT_0164204e + DAT_00433a6c * 0x14)
                );
        (*pcVar10)(param_1,0x405,0xc,0,&DAT_01641e70);
        _DAT_01641e70 = 0;
        DAT_01641e74 = 0;
        DAT_01641e78 = 0;
        DAT_01641e7c = 0;
        _sprintf(&DAT_01641e70,&DAT_00434588,(double)*(float *)(&DAT_01642052 + DAT_00433a6c * 0x14)
                );
        (*pcVar10)(param_1,0x404,0xc,0,&DAT_01641e70);
        _DAT_01641e70 = 0;
        DAT_01641e74 = 0;
        DAT_01641e78 = 0;
        DAT_01641e7c = 0;
        _sprintf(&DAT_01641e70,&DAT_00434584,*(undefined4 *)(&DAT_01642056 + DAT_00433a6c * 0x14));
        (*pcVar10)(param_1,0x407,0xc,0,&DAT_01641e70);
        _DAT_01641e70 = 0;
        DAT_01641e74 = 0;
        DAT_01641e78 = 0;
        DAT_01641e7c = 0;
        _sprintf(&DAT_01641e70,&DAT_00434584,*(undefined4 *)(&DAT_0164205a + DAT_00433a6c * 0x14));
        (*pcVar10)(param_1,0x40c,0xc,0,&DAT_01641e70);
        return 1;
      case 0x407:
        (*pcVar10)(param_1,0x407,0xd,0x10,&DAT_01641e70);
        iVar9 = _atoi(&DAT_01641e70);
        *(int *)(&DAT_01642056 + DAT_00433a6c * 0x14) = iVar9;
        break;
      case 0x408:
        (*pcVar10)(param_1,0x408,0xd,0x10,&DAT_01641e70);
        dVar12 = _atof(&DAT_01641e70);
        *(float *)(&DAT_0164204a + DAT_00433a6c * 0x14) = (float)dVar12;
        break;
      case 0x409:
        DAT_00433a70 = (*pcVar10)(param_1,0x409,0x147,0,0);
        i76edit_initialize_terrain_buffers(2);
        break;
      default:
        return 0;
      case 0x40c:
        (*pcVar10)(param_1,0x40c,0xd,0x10,&DAT_01641e70);
        iVar9 = _atoi(&DAT_01641e70);
        *(int *)(&DAT_0164205a + DAT_00433a6c * 0x14) = iVar9;
      }
      puVar8 = &DAT_01642072;
      puVar11 = &DAT_016420c2;
      for (iVar9 = 5; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar11 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar11 = puVar11 + 1;
      }
      puVar8 = &DAT_01642086;
      puVar11 = &DAT_016420d6;
      for (iVar9 = 5; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar11 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar11 = puVar11 + 1;
      }
    }
    else {
      InvalidateRgn(DAT_01641fb4,(HRGN)0x0,0);
    }
  }
  return 1;
}


