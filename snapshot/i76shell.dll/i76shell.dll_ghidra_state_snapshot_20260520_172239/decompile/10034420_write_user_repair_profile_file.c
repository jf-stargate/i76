/*
 * Program: i76shell.dll
 * Function: write_user_repair_profile_file
 * Entry: 10034420
 * Signature: undefined __cdecl write_user_repair_profile_file(int * param_1, int * param_2, int * param_3, int * param_4, int * param_5)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl
write_user_repair_profile_file(int *param_1,int *param_2,int *param_3,int *param_4,int *param_5)

{
  int *_Str;
  int iVar1;
  undefined4 *_Str_00;
  double dVar2;
  double dVar3;
  int iVar4;
  FILE *_File;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_4;
  
  local_4 = param_1[1];
  _Str = param_1 + 1;
  iVar6 = 0;
  iVar7 = 0;
  if (0 < local_4) {
    piVar8 = (int *)param_1[2];
    do {
      iVar1 = *(int *)*piVar8;
      dVar3 = (double)((int *)*piVar8)[3];
      dVar2 = (double)*(int *)(iVar1 + 0x4c) * _DAT_10041ec0;
      if (dVar2 <= dVar3) {
        iVar4 = 2;
        if (dVar2 + dVar2 <= dVar3) {
          iVar4 = 1;
        }
      }
      else {
        iVar4 = 3;
      }
      iVar7 = iVar7 + *(int *)(&DAT_10043558 + *(int *)(iVar1 + 0x1e) * 4) * iVar4;
      if (DAT_10052098 < iVar7) {
        local_4 = iVar6 + -1;
        break;
      }
      iVar6 = iVar6 + 1;
      piVar8 = piVar8 + 1;
    } while (iVar6 < local_4);
  }
  _File = fopen(s_user_rpr_1004ce20,s_wb_1004ce1c);
  if (_File != (FILE *)0x0) {
    fwrite(_Str,4,1,_File);
    fwrite(&local_4,4,1,_File);
    iVar6 = 0;
    if (0 < *_Str) {
      do {
        _Str_00 = *(undefined4 **)(param_1[2] + iVar6 * 4);
        fwrite(_Str_00,0x20,1,_File);
        fwrite((void *)*_Str_00,0x54,1,_File);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *_Str);
    }
    iVar1 = DAT_100d1dac;
    iVar6 = *(int *)(DAT_100d1dac + 4);
    iVar7 = DAT_100d1dac;
    while (iVar6 = iVar6 + -1, DAT_100d1dac = iVar7, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar1 + 8) + iVar6 * 4);
      iVar5 = find_pointer_list_item_index(param_2,iVar4);
      iVar7 = DAT_100d1dac;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar1,iVar4);
        iVar7 = DAT_100d1dac;
      }
    }
    iVar6 = *(int *)(iVar7 + 4);
    iVar1 = DAT_100d1dc0;
    while (iVar6 = iVar6 + -1, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar7 + 8) + iVar6 * 4);
      DAT_100d1dc0 = iVar1;
      iVar5 = find_pointer_list_item_index(param_1,iVar4);
      iVar1 = DAT_100d1dc0;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar7,iVar4);
        iVar1 = DAT_100d1dc0;
      }
    }
    iVar6 = *(int *)(iVar1 + 4);
    iVar7 = iVar1;
    while (iVar6 = iVar6 + -1, DAT_100d1dc0 = iVar7, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar1 + 8) + iVar6 * 4);
      iVar5 = find_pointer_list_item_index(param_2,iVar4);
      iVar7 = DAT_100d1dc0;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar1,iVar4);
        iVar7 = DAT_100d1dc0;
      }
    }
    iVar6 = *(int *)(iVar7 + 4);
    iVar1 = DAT_100d1dbc;
    while (iVar6 = iVar6 + -1, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar7 + 8) + iVar6 * 4);
      DAT_100d1dbc = iVar1;
      iVar5 = find_pointer_list_item_index(param_1,iVar4);
      iVar1 = DAT_100d1dbc;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar7,iVar4);
        iVar1 = DAT_100d1dbc;
      }
    }
    iVar6 = *(int *)(iVar1 + 4);
    iVar7 = iVar1;
    while (iVar6 = iVar6 + -1, DAT_100d1dbc = iVar7, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar1 + 8) + iVar6 * 4);
      iVar5 = find_pointer_list_item_index(param_2,iVar4);
      iVar7 = DAT_100d1dbc;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar1,iVar4);
        iVar7 = DAT_100d1dbc;
      }
    }
    iVar6 = *(int *)(iVar7 + 4);
    iVar1 = DAT_100d1db8;
    while (iVar6 = iVar6 + -1, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar7 + 8) + iVar6 * 4);
      DAT_100d1db8 = iVar1;
      iVar5 = find_pointer_list_item_index(param_1,iVar4);
      iVar1 = DAT_100d1db8;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar7,iVar4);
        iVar1 = DAT_100d1db8;
      }
    }
    iVar6 = *(int *)(iVar1 + 4);
    iVar7 = iVar1;
    while (iVar6 = iVar6 + -1, DAT_100d1db8 = iVar7, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar1 + 8) + iVar6 * 4);
      iVar5 = find_pointer_list_item_index(param_2,iVar4);
      iVar7 = DAT_100d1db8;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar1,iVar4);
        iVar7 = DAT_100d1db8;
      }
    }
    iVar6 = *(int *)(iVar7 + 4);
    iVar1 = DAT_100d1db4;
    while (iVar6 = iVar6 + -1, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar7 + 8) + iVar6 * 4);
      DAT_100d1db4 = iVar1;
      iVar5 = find_pointer_list_item_index(param_1,iVar4);
      iVar1 = DAT_100d1db4;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar7,iVar4);
        iVar1 = DAT_100d1db4;
      }
    }
    iVar6 = *(int *)(iVar1 + 4);
    iVar7 = iVar1;
    while (iVar6 = iVar6 + -1, DAT_100d1db4 = iVar7, -1 < iVar6) {
      iVar4 = *(int *)(*(int *)(iVar1 + 8) + iVar6 * 4);
      iVar5 = find_pointer_list_item_index(param_3,iVar4);
      iVar7 = DAT_100d1db4;
      if (iVar5 != -1) {
        remove_pointer_list_item(iVar1,iVar4);
        iVar7 = DAT_100d1db4;
      }
    }
    iVar6 = *(int *)(iVar7 + 4);
    while (iVar6 = iVar6 + -1, -1 < iVar6) {
      iVar1 = *(int *)(*(int *)(iVar7 + 8) + iVar6 * 4);
      iVar4 = find_pointer_list_item_index(param_1,iVar1);
      if (iVar4 != -1) {
        remove_pointer_list_item(iVar7,iVar1);
      }
    }
    remove_pointer_list_items_present_in_other_list(DAT_100d1db4,param_4);
    remove_pointer_list_items_present_in_other_list(DAT_100d1db4,param_1);
    remove_pointer_list_items_present_in_other_list(DAT_100d1db0,param_5);
    remove_pointer_list_items_present_in_other_list(DAT_100d1db0,param_1);
    write_vehicle_part_pointer_list_records(DAT_100d1dac,_File);
    write_vehicle_part_pointer_list_records(DAT_100d1dc0,_File);
    write_vehicle_part_pointer_list_records(DAT_100d1dbc,_File);
    write_vehicle_part_pointer_list_records(DAT_100d1db8,_File);
    write_vehicle_part_pointer_list_records(DAT_100d1db4,_File);
    write_vehicle_part_pointer_list_records(DAT_100d1db0,_File);
    fclose(_File);
  }
  return;
}


