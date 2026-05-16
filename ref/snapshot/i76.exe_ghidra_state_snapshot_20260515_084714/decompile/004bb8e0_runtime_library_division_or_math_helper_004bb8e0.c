/*
 * Program: i76.exe
 * Function: runtime_library_division_or_math_helper_004bb8e0
 * Entry: 004bb8e0
 * Signature: undefined __cdecl runtime_library_division_or_math_helper_004bb8e0(int param_1, float * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: runtime library division or math
   helper based on adjacent named subsystem context. */

void __cdecl runtime_library_division_or_math_helper_004bb8e0(int param_1,float *param_2)

{
  bool bVar1;
  float *pfVar2;
  undefined3 extraout_var;
  int iVar3;
  float *pfVar4;
  float local_80 [16];
  float local_40 [16];
  
  do {
    pfVar2 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 0x18),param_2);
    pfVar4 = local_80;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar4 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar4 = pfVar4 + 1;
    }
    if ((*(byte *)(param_1 + 0x10) & 1) == 0) {
      bVar1 = ensure_world_object_geometry_variant_binding(param_1,DAT_005dbac0);
      if (((CONCAT31(extraout_var,bVar1) != 1) || (*(int *)(param_1 + 0x5c) == 0)) ||
         (*(int *)(*(int *)(param_1 + 0x5c) + 4) < 3)) goto LAB_004bb946;
      bVar1 = true;
    }
    else {
LAB_004bb946:
      bVar1 = false;
    }
    if (bVar1) {
      runtime_library_string_compare_helper_004bb1c0(param_1,local_80);
    }
    if (*(int *)(param_1 + 100) != 0) {
      runtime_library_division_or_math_helper_004bb8e0(*(int *)(param_1 + 100),local_80);
    }
    param_1 = *(int *)(param_1 + 0x60);
    if (param_1 == 0) {
      return;
    }
  } while( true );
}


