/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_object_obj_records
 * Entry: 0040113b
 * Signature: int __cdecl i76edit_export_runtime_object_obj_records(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl i76edit_export_runtime_object_obj_records(int param_1,int param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  float *pfVar5;
  undefined4 *puVar6;
  float10 fVar7;
  undefined8 uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined4 *puStack_e8;
  int iStack_e4;
  int iStack_d4;
  int iStack_d0;
  undefined *puStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  undefined4 auStack_bc [12];
  undefined4 uStack_8c;
  undefined4 uStack_88;
  int iStack_68;
  int iStack_64;
  float afStack_60 [12];
  float afStack_30 [12];
  
  iStack_e4 = 0;
  i76edit_prepare_object_export_zone_lookup(param_2);
  puStack_cc = &DAT_004a424f;
  iStack_c8 = 0x6c;
  puStack_e8 = &DAT_00439be8;
  do {
    i76edit_set_status_bar_text(s_Zone__00434774);
    for (puVar1 = (undefined4 *)*puStack_e8; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      piVar2 = (int *)puVar1[2];
      if (DAT_0043c540 != (FILE *)0x0) {
        _fprintf(DAT_0043c540,s_File___s_00434768,piVar2 + 8);
      }
      uVar8 = i76edit_find_zone_cell_origin_by_zone_id(*piVar2,piVar2[1],piVar2[2]);
      iStack_c4 = piVar2[0x16];
      iStack_c0 = piVar2[0x17];
      iVar3 = i76edit_object_type_has_runtime_position_override(piVar2[7]);
      iStack_d4 = (int)uVar8;
      iStack_d0 = (int)((ulonglong)uVar8 >> 0x20);
      if (iVar3 == 0) {
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(iStack_d0);
        fVar11 = (float)fVar7;
        fVar10 = (float)piVar2[3] * _DAT_004320b0;
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(iStack_d4);
        fVar9 = (float)piVar2[6] * _DAT_004320b8;
        pfVar5 = afStack_60;
      }
      else {
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(iStack_d0);
        fVar10 = (float)piVar2[3] * _DAT_004320b0;
        fVar11 = (float)(fVar7 + (float10)_DAT_004320ac);
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(iStack_d4);
        fVar7 = fVar7 + (float10)_DAT_004320ac;
        pfVar5 = afStack_30;
        fVar9 = (float)piVar2[6] * _DAT_004320b8;
      }
      puVar4 = (undefined4 *)thunk_FUN_0041c800(pfVar5,0.0,fVar9,0.0,(float)fVar7,fVar10,fVar11);
      puVar6 = auStack_bc;
      for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      uStack_8c = 0;
      uStack_88 = 0;
      iStack_68 = piVar2[7];
      iStack_64 = piVar2[0x18];
      __write(param_1,&puStack_cc,0x6c);
      iStack_e4 = iStack_e4 + iStack_c8;
    }
    puStack_e8 = puStack_e8 + 1;
  } while (puStack_e8 < &DAT_00439d28);
  return iStack_e4;
}


