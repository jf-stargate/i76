/*
 * Program: i76shell.dll
 * Function: populate_input_binding_device_action_list
 * Entry: 10010530
 * Signature: undefined __cdecl populate_input_binding_device_action_list(int param_1)
 */


void __cdecl populate_input_binding_device_action_list(int param_1)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  piVar7 = (int *)0x0;
  FUN_10018640();
  iVar3 = FUN_100184b0(1);
  clear_pointer_list(DAT_10056c38);
  piVar6 = DAT_10056c38;
  while (iVar3 = iVar3 + -1, -1 < iVar3) {
    iVar4 = FUN_10018610(iVar3);
    piVar6 = DAT_10056c38;
    if (iVar4 != 0) {
      pcVar1 = (char *)(iVar4 + 4);
      iVar5 = _strnicmp(pcVar1,s_k_100468c0,1);
      if (iVar5 == 0) {
        insert_pointer_list_item_sorted_or_append
                  ((int)DAT_10056c38,(int)PTR_s____keyboard____100462b8,(undefined *)0x0);
        piVar6 = DAT_10056c38;
        if (piVar7 != (int *)0x0) {
          *piVar7 = DAT_10056c38[1] + -2;
        }
        DAT_10056c20 = piVar6[1] + -1;
        if (DAT_10056c20 < 0) {
          DAT_10056c20 = 0;
        }
        piVar7 = &DAT_10056c0c;
      }
      else {
        iVar5 = _strnicmp(pcVar1,s_j_100468c4,1);
        if (iVar5 == 0) {
          insert_pointer_list_item_sorted_or_append
                    ((int)DAT_10056c38,(int)PTR_s____Joystick____100462bc,(undefined *)0x0);
          piVar6 = DAT_10056c38;
          if (piVar7 != (int *)0x0) {
            *piVar7 = DAT_10056c38[1] + -2;
          }
          DAT_10056c08 = piVar6[1] + -1;
          if (DAT_10056c08 < 0) {
            DAT_10056c08 = 0;
          }
          piVar7 = &DAT_10056c1c;
        }
        else {
          iVar5 = _strnicmp(pcVar1,s_m_100468c8,1);
          piVar6 = DAT_10056c38;
          if (iVar5 == 0) {
            insert_pointer_list_item_sorted_or_append
                      ((int)DAT_10056c38,(int)PTR_s____Mouse____100462c0,(undefined *)0x0);
            piVar6 = DAT_10056c38;
            if (piVar7 != (int *)0x0) {
              *piVar7 = DAT_10056c38[1] + -2;
            }
            DAT_10056c10 = piVar6[1] + -1;
            if (DAT_10056c10 < 0) {
              DAT_10056c10 = 0;
            }
            piVar7 = &DAT_10056c18;
          }
        }
      }
      if (((*(int *)(iVar4 + 0x70) != 0) && (0 < *(int *)(iVar4 + 0x60))) &&
         (iVar5 = 0, 0 < *(int *)(iVar4 + 0x60))) {
        do {
          pcVar1 = *(char **)(*(int *)(iVar4 + 0x70) + iVar5 * 4);
          cVar2 = *pcVar1;
          if ((cVar2 != '\0') && (cVar2 != '*')) {
            insert_pointer_list_item_sorted_or_append((int)piVar6,(int)pcVar1,(undefined *)0x0);
            piVar6 = DAT_10056c38;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < *(int *)(iVar4 + 0x60));
      }
      if (((param_1 != 0) && (*(int *)(iVar4 + 0x68) != 0)) &&
         ((0 < *(int *)(iVar4 + 0x5c) && (iVar5 = 0, 0 < *(int *)(iVar4 + 0x5c))))) {
        do {
          insert_pointer_list_item_sorted_or_append
                    ((int)piVar6,*(int *)(*(int *)(iVar4 + 0x68) + iVar5 * 4),(undefined *)0x0);
          iVar5 = iVar5 + 1;
          piVar6 = DAT_10056c38;
        } while (iVar5 < *(int *)(iVar4 + 0x5c));
      }
    }
  }
  if (piVar7 != (int *)0x0) {
    *piVar7 = piVar6[1] + -2;
  }
  return;
}


