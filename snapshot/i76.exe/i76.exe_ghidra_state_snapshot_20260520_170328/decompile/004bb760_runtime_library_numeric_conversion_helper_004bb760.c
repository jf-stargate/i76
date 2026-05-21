/*
 * Program: i76.exe
 * Function: runtime_library_numeric_conversion_helper_004bb760
 * Entry: 004bb760
 * Signature: undefined __cdecl runtime_library_numeric_conversion_helper_004bb760(undefined4 * param_1, undefined4 param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set E v17: Readability pass set E: runtime library numeric conversion
   helper based on adjacent named subsystem context. */

void __cdecl
runtime_library_numeric_conversion_helper_004bb760(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 *puVar3;
  float *pfVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar5;
  int iVar6;
  float *pfVar7;
  float local_8c [16];
  float local_4c [3];
  float local_40 [16];
  
  DAT_005dbac4 = param_2;
  DAT_005dbac0 = param_1[5];
  puVar3 = (undefined4 *)vec3_or_matrix_transform_context_helper_004788b0(local_4c,(int *)*param_1);
  _DAT_005dbb08 = *puVar3;
  _DAT_005dbb0c = puVar3[1];
  _DAT_005dbb10 = puVar3[2];
  iVar1 = *(int *)*param_1;
  iVar6 = *(int *)(iVar1 + 100);
  if (*(int *)(iVar1 + 0x6c) == 9) {
    do {
      pfVar4 = compose_matrix_or_transform_a
                         (local_40,(float *)(iVar6 + 0x18),(float *)(iVar1 + 0x18));
      pfVar7 = local_8c;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar7 = *pfVar4;
        pfVar4 = pfVar4 + 1;
        pfVar7 = pfVar7 + 1;
      }
      if ((*(byte *)(iVar6 + 0x10) & 1) == 0) {
        bVar2 = ensure_world_object_geometry_variant_binding(iVar6,DAT_005dbac0);
        if (((CONCAT31(extraout_var_00,bVar2) != 1) || (*(int *)(iVar6 + 0x5c) == 0)) ||
           (*(int *)(*(int *)(iVar6 + 0x5c) + 4) < 3)) goto LAB_004bb899;
        bVar2 = true;
      }
      else {
LAB_004bb899:
        bVar2 = false;
      }
      if (bVar2) {
        runtime_library_string_format_helper_004bb5a0(iVar6,local_8c);
      }
      if (*(int *)(iVar6 + 100) != 0) {
        runtime_library_error_or_exit_helper_004bb990(*(int *)(iVar6 + 100),local_8c);
      }
      iVar6 = *(int *)(iVar6 + 0x60);
      if (iVar6 == 0) {
        return;
      }
    } while( true );
  }
  do {
    pfVar4 = compose_matrix_or_transform_a(local_40,(float *)(iVar6 + 0x18),(float *)(iVar1 + 0x18))
    ;
    pfVar7 = local_8c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar7 = *pfVar4;
      pfVar4 = pfVar4 + 1;
      pfVar7 = pfVar7 + 1;
    }
    if ((*(byte *)(iVar6 + 0x10) & 1) == 0) {
      bVar2 = ensure_world_object_geometry_variant_binding(iVar6,DAT_005dbac0);
      if (((CONCAT31(extraout_var,bVar2) != 1) || (*(int *)(iVar6 + 0x5c) == 0)) ||
         (*(int *)(*(int *)(iVar6 + 0x5c) + 4) < 3)) goto LAB_004bb810;
      bVar2 = true;
    }
    else {
LAB_004bb810:
      bVar2 = false;
    }
    if (bVar2) {
      runtime_library_string_compare_helper_004bb1c0(iVar6,local_8c);
    }
    if (*(int *)(iVar6 + 100) != 0) {
      runtime_library_division_or_math_helper_004bb8e0(*(int *)(iVar6 + 100),local_8c);
    }
    iVar6 = *(int *)(iVar6 + 0x60);
    if (iVar6 == 0) {
      return;
    }
  } while( true );
}


