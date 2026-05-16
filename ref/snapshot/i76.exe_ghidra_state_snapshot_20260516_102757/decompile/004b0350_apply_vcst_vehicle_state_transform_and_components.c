/*
 * Program: i76.exe
 * Function: apply_vcst_vehicle_state_transform_and_components
 * Entry: 004b0350
 * Signature: undefined4 __cdecl apply_vcst_vehicle_state_transform_and_components(int param_1, int * param_2)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium-high] Alternate VCST callback.
   Validates the source name, applies vehicle state transform/scalars, and updates existing
   engine/brake/suspension component objects. */

undefined4 __cdecl apply_vcst_vehicle_state_transform_and_components(int param_1,int *param_2)

{
  float fVar1;
  int iVar2;
  int local_31c;
  undefined4 *local_30c;
  undefined4 *local_308;
  char local_304 [4];
  char local_300 [256];
  char local_200 [256];
  char local_100 [256];
  
  local_30c = (undefined4 *)0x0;
  local_308 = (undefined4 *)0x0;
  local_31c = 0;
  _splitpath((char *)(param_1 + 8),local_304,local_100,local_300,local_200);
  iVar2 = _strnicmp(local_300,(char *)*param_2,8);
  if (iVar2 != 0) {
    format_8char_resource_basename_with_suffix
              (*(undefined4 *)*param_2,((undefined4 *)*param_2)[1],(char *)0x0);
    report_chunk_parse_error();
  }
  iVar2 = *(int *)(*param_2 + 0x70);
  if (*(int *)(iVar2 + 0x3c4) != 0) {
    local_30c = *(undefined4 **)(*(int *)(iVar2 + 0x3c4) + 0x70);
  }
  if (*(int *)(iVar2 + 0x3c8) != 0) {
    local_308 = *(undefined4 **)(*(int *)(iVar2 + 0x3c8) + 0x70);
  }
  if (*(int *)(iVar2 + 0x3cc) != 0) {
    local_31c = *(int *)(*(int *)(iVar2 + 0x3cc) + 0x70);
  }
  *(undefined4 *)(iVar2 + 0x138) = *(undefined4 *)(param_1 + 0x15);
  *(undefined4 *)(iVar2 + 0x13c) = *(undefined4 *)(param_1 + 0x19);
  *(undefined4 *)(iVar2 + 0x140) = *(undefined4 *)(param_1 + 0x1d);
  *(undefined4 *)(iVar2 + 0x144) = *(undefined4 *)(param_1 + 0x21);
  *(undefined4 *)(iVar2 + 0x158) = *(undefined4 *)(param_1 + 0x15);
  *(undefined4 *)(iVar2 + 0x15c) = *(undefined4 *)(param_1 + 0x19);
  *(undefined4 *)(iVar2 + 0x160) = *(undefined4 *)(param_1 + 0x1d);
  *(undefined4 *)(iVar2 + 0x164) = *(undefined4 *)(param_1 + 0x21);
  *(undefined4 *)(iVar2 + 0x148) = *(undefined4 *)(param_1 + 0x25);
  *(undefined4 *)(iVar2 + 0x14c) = *(undefined4 *)(param_1 + 0x29);
  *(undefined4 *)(iVar2 + 0x150) = *(undefined4 *)(param_1 + 0x2d);
  *(undefined4 *)(iVar2 + 0x154) = *(undefined4 *)(param_1 + 0x31);
  *(undefined4 *)(iVar2 + 0x168) = *(undefined4 *)(param_1 + 0x25);
  *(undefined4 *)(iVar2 + 0x16c) = *(undefined4 *)(param_1 + 0x29);
  *(undefined4 *)(iVar2 + 0x170) = *(undefined4 *)(param_1 + 0x2d);
  *(undefined4 *)(iVar2 + 0x174) = *(undefined4 *)(param_1 + 0x31);
  *local_30c = *(undefined4 *)(param_1 + 0x45);
  *local_308 = *(undefined4 *)(param_1 + 0x4d);
  *(undefined4 *)(local_31c + 4) = *(undefined4 *)(param_1 + 0x49);
  *(float *)(iVar2 + 0xbc) = *(float *)(param_1 + 0x35);
  *(undefined4 *)(iVar2 + 0xc0) = *(undefined4 *)(param_1 + 0x39);
  *(undefined4 *)(iVar2 + 0xc4) = *(undefined4 *)(param_1 + 0x3d);
  fVar1 = *(float *)(param_1 + 0x35);
  *(float *)(iVar2 + 0xac) =
       SQRT(*(float *)(param_1 + 0x3d) * *(float *)(param_1 + 0x3d) +
            *(float *)(param_1 + 0x39) * *(float *)(param_1 + 0x39) + fVar1 * fVar1);
  *(double *)(*param_2 + 0x48) = (double)*(float *)(param_1 + 0x41);
  return 1;
}


