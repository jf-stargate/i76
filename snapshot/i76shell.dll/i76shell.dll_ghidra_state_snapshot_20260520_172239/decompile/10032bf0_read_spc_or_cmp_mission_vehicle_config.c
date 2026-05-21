/*
 * Program: i76shell.dll
 * Function: read_spc_or_cmp_mission_vehicle_config
 * Entry: 10032bf0
 * Signature: undefined4 __cdecl read_spc_or_cmp_mission_vehicle_config(char * param_1)
 */


undefined4 __cdecl read_spc_or_cmp_mission_vehicle_config(char *param_1)

{
  bool bVar1;
  int iVar2;
  FILE *_File;
  int *piVar3;
  LPVOID pvVar4;
  code *pcVar5;
  int unaff_ESI;
  int *piVar6;
  code *pcVar7;
  int local_8;
  int local_4;
  
  local_4 = 0;
  iVar2 = _stricmp(param_1,s_trip4_spc_1004cce4);
  if (iVar2 == 0) {
    local_4 = 1;
  }
  FUN_10001340();
  _File = fopen(param_1,s_rb_1004ccf0);
  pcVar5 = fread_exref;
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fread(&DAT_100581a0 + *(int *)(DAT_100c5ad8 + 0x38) * 0x231,0x8c4,1,_File);
  fread(&local_8,4,1,_File);
  param_1 = (char *)0x0;
  pcVar7 = HeapAlloc_exref;
  if (0 < local_8) {
    do {
      pcVar7 = HeapAlloc_exref;
      piVar3 = HeapAlloc(DAT_10051c50,1,0x20);
      fread(piVar3,0x20,1,_File);
      pvVar4 = HeapAlloc(DAT_10051c50,1,0x54);
      *piVar3 = (int)pvVar4;
      fread(pvVar4,0x54,1,_File);
      if (local_4 == 0) {
        if (DAT_100cc500 == (int *)0x0) {
          DAT_100cc500 = piVar3;
          piVar3[1] = (int)piVar3;
          piVar3[2] = (int)piVar3;
        }
        else {
          piVar3[1] = (int)DAT_100cc500;
          *(int **)(DAT_100cc500[2] + 4) = piVar3;
          piVar3[2] = DAT_100cc500[2];
          DAT_100cc500[2] = (int)piVar3;
        }
      }
      else if (piVar3[4] == 4) {
        if ((LPVOID)*piVar3 != (LPVOID)0x0) {
          HeapFree(DAT_10051c50,1,(LPVOID)*piVar3);
          *piVar3 = 0;
        }
        if (piVar3 != (int *)0x0) {
          HeapFree(DAT_10051c50,1,piVar3);
        }
      }
      else if (piVar3[4] == 3) {
        iVar2 = *(int *)(*piVar3 + 0x4c);
        piVar3[4] = 2;
        piVar3[3] = iVar2;
        if (DAT_100cc500 == (int *)0x0) {
          DAT_100cc500 = piVar3;
          piVar3[1] = (int)piVar3;
          piVar3[2] = (int)piVar3;
        }
        else {
          piVar3[1] = (int)DAT_100cc500;
          *(int **)(DAT_100cc500[2] + 4) = piVar3;
          piVar3[2] = DAT_100cc500[2];
          DAT_100cc500[2] = (int)piVar3;
        }
      }
      else if (DAT_100cc500 == (int *)0x0) {
        DAT_100cc500 = piVar3;
        piVar3[1] = (int)piVar3;
        piVar3[2] = (int)piVar3;
      }
      else {
        piVar3[1] = (int)DAT_100cc500;
        *(int **)(DAT_100cc500[2] + 4) = piVar3;
        piVar3[2] = DAT_100cc500[2];
        DAT_100cc500[2] = (int)piVar3;
      }
      param_1 = param_1 + 1;
    } while ((int)param_1 < local_8);
  }
  if (local_4 != 0) {
    fclose(_File);
    return 1;
  }
  fread(&local_8,4,1,_File);
  if (DAT_100520a0 == (int *)0x0) {
    DAT_100520a0 = create_pointer_list_with_capacity(0x40);
  }
  clear_pointer_list(DAT_100520a0);
  piVar3 = (int *)(*pcVar7)(DAT_10051c50,1,0x20);
  pvVar4 = HeapAlloc(DAT_10051c50,1,0x54);
  local_8 = 0;
  *piVar3 = (int)pvVar4;
  if (0 < unaff_ESI) {
    do {
      (*pcVar5)(piVar3,0x20,1,_File);
      *piVar3 = (int)pvVar4;
      (*pcVar5)(pvVar4,0x54,1,_File);
      bVar1 = false;
      piVar6 = DAT_100cc500;
      while (((piVar6 != (int *)0x0 && (piVar6 != DAT_100cc500)) || (!bVar1))) {
        bVar1 = true;
        if (((piVar3[3] == piVar6[3]) &&
            (iVar2 = find_pointer_list_item_index(DAT_100520a0,(int)piVar6), iVar2 == -1)) &&
           ((piVar6[4] == 3 &&
            (iVar2 = _stricmp((char *)(*piVar3 + 0x3b),(char *)(*piVar6 + 0x3b)), iVar2 == 0))))
        goto LAB_10032f05;
        piVar6 = (int *)piVar6[1];
      }
      piVar6 = (int *)0x0;
LAB_10032f05:
      if (piVar6 != (int *)0x0) {
        insert_pointer_list_item_sorted_or_append((int)DAT_100520a0,(int)piVar6,(undefined *)0x0);
      }
      local_8 = local_8 + 1;
      pcVar5 = fread_exref;
    } while (local_8 < unaff_ESI);
  }
  if ((LPVOID)*piVar3 != (LPVOID)0x0) {
    HeapFree(DAT_10051c50,1,(LPVOID)*piVar3);
    *piVar3 = 0;
  }
  if (piVar3 != (int *)0x0) {
    HeapFree(DAT_10051c50,1,piVar3);
  }
  fclose(_File);
  return 1;
}


