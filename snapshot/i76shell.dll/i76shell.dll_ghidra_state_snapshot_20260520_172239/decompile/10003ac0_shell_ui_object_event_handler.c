/*
 * Program: i76shell.dll
 * Function: shell_ui_object_event_handler
 * Entry: 10003ac0
 * Signature: undefined __thiscall shell_ui_object_event_handler(void * this, void * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76shell first-pass rename
   old_name: FUN_10003ac0
   suggested_name: shell_ui_object_event_handler
   basis: Shell UI object/event candidate from ShellWindowProc neighborhood. */

void __thiscall shell_ui_object_event_handler(void *this,void *param_1)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  long extraout_ECX;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  LPVOID pvVar9;
  void *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_1004015c;
  local_c = ExceptionList;
  iVar7 = 0;
  DAT_100d21a8 = redraw_vehicle_config_screen;
  DAT_10051f74 = 0;
  DAT_10051dc4 = 0;
  ExceptionList = &local_c;
  local_10 = this;
  if (0 < DAT_10047710) {
    pcVar6 = &DAT_100c62c3;
    ExceptionList = &local_c;
    do {
      if ((*(int *)(pcVar6 + -0x1d) == 0xe) &&
         (iVar2 = _stricmp(&DAT_100589cd + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4,pcVar6), iVar2 == 0
         )) {
        uVar4 = 0xffffffff;
        pcVar6 = &DAT_100c6288 + iVar7 * 0x54;
        goto code_r0x10003b6b;
      }
      iVar7 = iVar7 + 1;
      pcVar6 = pcVar6 + 0x54;
    } while (iVar7 < DAT_10047710);
  }
  goto LAB_10003b8d;
  while( true ) {
    uVar4 = uVar4 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
    if (cVar1 == '\0') break;
code_r0x10003b6b:
    pcVar8 = pcVar6;
    if (uVar4 == 0) break;
  }
  uVar4 = ~uVar4;
  pcVar6 = pcVar8 + -uVar4;
  pcVar8 = (char *)&DAT_10051cd8;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
LAB_10003b8d:
  FUN_100343a0(*(int *)(DAT_100c5ad8 + 0x38));
  FUN_100196b0();
  preload_shell_ui_image_records(extraout_ECX);
  if (DAT_10051dc0 == 0) {
    pvVar9 = (LPVOID)0x1;
  }
  else {
    pvVar9 = (LPVOID)0x2;
  }
  load_or_apply_shell_surface_record_by_id_candidate(DAT_100cc518,param_1,pvVar9);
  if (DAT_100520b8 == 0) {
    mpack_database_get_item(DAT_100cc53c,0x52,&DAT_10051d04,(long *)&local_10);
    pvVar3 = operator_new(4);
    local_4 = 0;
    if (pvVar3 == (void *)0x0) {
      DAT_10051fbc = 0;
    }
    else {
      DAT_10051fbc = FUN_10036610(pvVar3,DAT_10051d04);
    }
    local_4 = 0xffffffff;
  }
  iVar7 = DAT_100c5ad8;
  if (DAT_10051dc0 == 0) {
    if (DAT_100520b8 == 0) {
      mpack_database_get_item(DAT_100cc53c,0x4f,&DAT_10051d00,(long *)&local_10);
      pvVar3 = operator_new(4);
      local_4 = 1;
      if (pvVar3 == (void *)0x0) {
        DAT_10051fb4 = 0;
      }
      else {
        DAT_10051fb4 = FUN_10036610(pvVar3,DAT_10051d00);
      }
      local_4 = 0xffffffff;
      mpack_database_get_item(DAT_100cc53c,0x50,&DAT_10051cfc,(long *)&local_10);
      pvVar3 = operator_new(4);
      local_4 = 2;
      if (pvVar3 == (void *)0x0) {
        DAT_10051fb0 = 0;
      }
      else {
        DAT_10051fb0 = FUN_10036610(pvVar3,DAT_10051cfc);
      }
      local_4 = 0xffffffff;
      if ((*DAT_100d2180 == 1) && (DAT_100d2174 == 0)) {
        mpack_database_get_item(DAT_100cc53c,0x4e,&DAT_10051cf8,(long *)&local_10);
        pvVar3 = operator_new(4);
        local_4 = 3;
        if (pvVar3 == (void *)0x0) {
          DAT_10051fb8 = (undefined4 *)0x0;
        }
        else {
          DAT_10051fb8 = (undefined4 *)FUN_10036610(pvVar3,DAT_10051cf8);
        }
        local_4 = 0xffffffff;
        FUN_100366d0();
        FUN_10036640(DAT_10051fb8);
      }
    }
    _DAT_1004345c = 10;
    _DAT_10043460 = 0x1c2;
    _DAT_10043464 = 0x268;
    _DAT_10043468 = 0x30;
    _DAT_1004346c = 0x107;
    PTR_DAT_10043470 = &DAT_100433a8;
  }
  else {
    _DAT_1004345c = 0;
    _DAT_10043460 = 0x1ec;
    _DAT_10043464 = 0x276;
    _DAT_10043468 = 0x1c2;
    _DAT_1004346c = 0x1d5;
    PTR_DAT_10043470 = (undefined *)0x0;
    uVar4 = 0xffffffff;
    pcVar6 = &DAT_100581b4 + *(int *)(DAT_100c5ad8 + 0x38) * 0x8c4;
    do {
      pcVar8 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar8 + -uVar4;
    pcVar8 = &DAT_10051f28;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = &DAT_100589cd + *(int *)(iVar7 + 0x38) * 0x8c4;
    do {
      pcVar8 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar8 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar8;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar8 + -uVar4;
    pcVar8 = &DAT_10051e40;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      pcVar8 = pcVar8 + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *pcVar8 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      pcVar8 = pcVar8 + 1;
    }
  }
  initialize_vehicle_config_ui_lists();
  DAT_100d2184 = 0;
  SetCursor(DAT_100d216c);
  FUN_1001eca0(&LAB_10003e70);
  ExceptionList = local_c;
  return;
}


