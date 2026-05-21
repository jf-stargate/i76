/*
 * Program: i76shell.dll
 * Function: build_vehicle_part_category_lists
 * Entry: 10034f70
 * Signature: undefined __stdcall build_vehicle_part_category_lists(void)
 */


void build_vehicle_part_category_lists(void)

{
  undefined4 *puVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  int *piVar7;
  int local_4;
  
  if (DAT_100f5308 == (int *)0x0) {
    DAT_100f5308 = create_pointer_list_with_capacity(0x100);
  }
  if (DAT_100d1dac == (int *)0x0) {
    DAT_100d1dac = create_pointer_list_default_16();
  }
  if (DAT_100d1dc0 == (int *)0x0) {
    DAT_100d1dc0 = create_pointer_list_default_16();
  }
  if (DAT_100d1dbc == (int *)0x0) {
    DAT_100d1dbc = create_pointer_list_default_16();
  }
  if (DAT_100d1db8 == (int *)0x0) {
    DAT_100d1db8 = create_pointer_list_with_capacity(100);
  }
  if (DAT_100d1db4 == (int *)0x0) {
    DAT_100d1db4 = create_pointer_list_with_capacity(0x40);
  }
  if (DAT_100d1db0 == (int *)0x0) {
    DAT_100d1db0 = create_pointer_list_with_capacity(0x20);
  }
  local_4 = 0;
  if (0 < DAT_10047710) {
    pcVar3 = &DAT_100c6288;
    do {
      iVar2 = 6;
      bVar6 = true;
      pcVar4 = pcVar3;
      pcVar5 = s_EMPTY_1004ce48;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar6 = *pcVar4 == *pcVar5;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
      } while (bVar6);
      if (!bVar6) {
        switch(*(undefined4 *)(pcVar3 + 0x1e)) {
        case 1:
        case 4:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1dbc;
          break;
        case 2:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1dac;
          break;
        case 3:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1dc0;
          break;
        case 5:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1db8;
          break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 0xb:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1db4;
          break;
        case 0xc:
        case 0xd:
          puVar1 = HeapAlloc(DAT_10051c50,1,0x20);
          puVar1[4] = 1;
          *puVar1 = pcVar3;
          puVar1[1] = 0;
          puVar1[2] = 0;
          puVar1[3] = *(undefined4 *)(pcVar3 + 0x4c);
          insert_pointer_list_item_sorted_or_append((int)DAT_100f5308,(int)puVar1,(undefined *)0x0);
          piVar7 = DAT_100d1db0;
          break;
        default:
          goto switchD_10035054_default;
        }
        insert_pointer_list_item_sorted_or_append((int)piVar7,(int)puVar1,(undefined *)0x0);
      }
switchD_10035054_default:
      local_4 = local_4 + 1;
      pcVar3 = pcVar3 + 0x54;
    } while (local_4 < DAT_10047710);
  }
  return;
}


