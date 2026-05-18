/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_runtime_object_obj_records
 * Entry: 0040a400
 * Signature: int __cdecl i76edit_export_runtime_object_obj_records(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt_i76edit_level_renames_v3] Exports object records into runtime BWD2/ODEF chunk.
   
   [cgpt_i76edit_level_renames_v6:high] Runtime ODEF object exporter. Emits OBJ records of size
   0x6c, resolves object zone origin, scales coordinates, and writes object filename/type/position
   fields. */

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
  undefined4 *local_e8;
  int local_e4;
  int local_d4;
  int local_d0;
  undefined *local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  undefined4 local_bc [12];
  undefined4 local_8c;
  undefined4 local_88;
  int local_68;
  int local_64;
  float local_60 [12];
  float local_30 [12];
  
  local_e4 = 0;
  i76edit_prepare_object_export_zone_lookup(param_2);
  local_cc = &DAT_004a424f;
  local_c8 = 0x6c;
  local_e8 = &DAT_00439be8;
  do {
    i76edit_set_status_bar_text(s_Zone__00434774);
    for (puVar1 = (undefined4 *)*local_e8; puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      piVar2 = (int *)puVar1[2];
      if (DAT_0043c540 != (FILE *)0x0) {
        _fprintf(DAT_0043c540,s_File___s_00434768,piVar2 + 8);
      }
      uVar8 = i76edit_find_zone_cell_origin_by_zone_id(*piVar2,piVar2[1],piVar2[2]);
      local_c4 = piVar2[0x16];
      local_c0 = piVar2[0x17];
      iVar3 = i76edit_object_type_has_runtime_position_override(piVar2[7]);
      local_d4 = (int)uVar8;
      local_d0 = (int)((ulonglong)uVar8 >> 0x20);
      if (iVar3 == 0) {
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(local_d0);
        fVar11 = (float)fVar7;
        fVar10 = (float)piVar2[3] * _DAT_004320b0;
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(local_d4);
        fVar9 = (float)piVar2[6] * _DAT_004320b8;
        pfVar5 = local_60;
      }
      else {
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(local_d0);
        fVar10 = (float)piVar2[3] * _DAT_004320b0;
        fVar11 = (float)(fVar7 + (float10)_DAT_004320ac);
        fVar7 = i76edit_convert_int_to_runtime_object_scale_float(local_d4);
        fVar7 = fVar7 + (float10)_DAT_004320ac;
        pfVar5 = local_30;
        fVar9 = (float)piVar2[6] * _DAT_004320b8;
      }
      puVar4 = (undefined4 *)thunk_FUN_0041c800(pfVar5,0.0,fVar9,0.0,(float)fVar7,fVar10,fVar11);
      puVar6 = local_bc;
      for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar6 = puVar6 + 1;
      }
      local_8c = 0;
      local_88 = 0;
      local_68 = piVar2[7];
      local_64 = piVar2[0x18];
      __write(param_1,&local_cc,0x6c);
      local_e4 = local_e4 + local_c8;
    }
    local_e8 = local_e8 + 1;
  } while (local_e8 < &DAT_00439d28);
  return local_e4;
}


