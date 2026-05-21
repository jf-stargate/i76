/*
 * Program: i76shell.dll
 * Function: read_user_repair_profile_file
 * Entry: 100347d0
 * Signature: undefined __cdecl read_user_repair_profile_file(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
 */


void __cdecl
read_user_repair_profile_file
          (int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7)

{
  undefined4 uVar1;
  FILE *_File;
  undefined4 *puVar2;
  LPVOID pvVar3;
  int iVar4;
  int local_10;
  int local_8;
  int local_4;
  
  if (DAT_100f5308 != (int *)0x0) {
    destroy_pointer_list_with_optional_item_destructor(DAT_100f5308,(undefined *)0x0);
  }
  DAT_100f5308 = create_pointer_list_with_capacity(0x40);
  _File = fopen(s_user_rpr_1004ce30,s_rb_1004ce2c);
  if (_File != (FILE *)0x0) {
    fread(&local_8,4,1,_File);
    fread(&local_4,4,1,_File);
    local_10 = 0;
    if (0 < local_8) {
      do {
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        if (local_4 <= local_10) {
          iVar4 = param_6;
          switch(*(undefined4 *)((int)pvVar3 + 0x1e)) {
          case 1:
          case 4:
            iVar4 = param_3;
            break;
          case 2:
            iVar4 = param_1;
            break;
          case 3:
            iVar4 = param_2;
            break;
          case 5:
            iVar4 = param_4;
            break;
          case 6:
          case 7:
          case 8:
          case 9:
          case 10:
          case 0xb:
            iVar4 = param_5;
            break;
          case 0xc:
          case 0xd:
            iVar4 = param_7;
            break;
          default:
            goto switchD_10034928_default;
          }
          insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
          iVar4 = param_6;
          goto switchD_10034928_default;
        }
        if (*DAT_100d2164 == 1) {
          uVar1 = *(undefined4 *)((int)pvVar3 + 0x4c);
          puVar2[4] = 2;
          puVar2[3] = uVar1;
        }
        switch(*(undefined4 *)((int)pvVar3 + 0x1e)) {
        case 1:
        case 4:
          iVar4 = param_3;
          break;
        case 2:
          iVar4 = param_1;
          break;
        case 3:
          iVar4 = param_2;
          break;
        case 5:
          iVar4 = param_4;
          break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xb:
          iVar4 = param_5;
          break;
        case 0xc:
        case 0xd:
          iVar4 = param_7;
          break;
        default:
          goto switchD_100348d8_default;
        }
switchD_10034928_default:
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
switchD_100348d8_default:
        local_10 = local_10 + 1;
      } while (local_10 < local_8);
    }
    iVar4 = DAT_100d1dac;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    iVar4 = DAT_100d1dc0;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    iVar4 = DAT_100d1dbc;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    iVar4 = DAT_100d1db8;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    iVar4 = DAT_100d1db4;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    iVar4 = DAT_100d1db0;
    fread(&param_4,4,1,_File);
    param_2 = 0;
    if (0 < param_4) {
      do {
        pvVar3 = HeapAlloc(DAT_10051c50,1,0x54);
        puVar2 = HeapAlloc(DAT_10051c50,1,0x20);
        fread(puVar2,0x20,1,_File);
        fread(pvVar3,0x54,1,_File);
        *puVar2 = pvVar3;
        puVar2[4] = 2;
        insert_pointer_list_item_sorted_or_append(iVar4,(int)puVar2,(undefined *)0x0);
        insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar2,(undefined *)0x0);
        param_2 = param_2 + 1;
      } while (param_2 < param_4);
    }
    fclose(_File);
  }
  return;
}


