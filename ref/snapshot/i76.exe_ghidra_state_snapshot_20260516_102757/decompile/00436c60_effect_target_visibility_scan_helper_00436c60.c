/*
 * Program: i76.exe
 * Function: effect_target_visibility_scan_helper_00436c60
 * Entry: 00436c60
 * Signature: undefined __cdecl effect_target_visibility_scan_helper_00436c60(undefined4 * param_1, float * param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: effect target visibility scan helper
   based on prior focused closure context. */

void __cdecl effect_target_visibility_scan_helper_00436c60(undefined4 *param_1,float *param_2)

{
  bool bVar1;
  float *pfVar2;
  undefined3 extraout_var;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  float local_80 [16];
  float local_40 [16];
  
  do {
    if (param_1 == (undefined4 *)0x0) {
      return;
    }
    pfVar2 = compose_matrix_or_transform_a(local_40,(float *)(param_1 + 6),param_2);
    pfVar6 = local_80;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pfVar6 = *pfVar2;
      pfVar2 = pfVar2 + 1;
      pfVar6 = pfVar6 + 1;
    }
    uVar5 = param_1[4] & 0xf000;
    if (uVar5 == 0x3000) {
      release_effect_target_collision_payload((int)param_1);
    }
    if (uVar5 == 0) {
      uVar5 = DAT_0052b92c;
    }
    if (((uVar5 == 0x1000) || (param_1[0x1b] == 0x37)) || ((*(byte *)(param_1 + 4) & 1) != 0)) {
      param_1[4] = param_1[4] & 0xffff1fff | 0x1000;
    }
    else {
      bVar1 = ensure_world_object_geometry_variant_binding((int)param_1,0);
      if ((CONCAT31(extraout_var,bVar1) == 0) || (param_1[0x17] == 0)) {
        param_1[4] = param_1[4] & 0xffff1fff | 0x1000;
      }
      else {
        if (uVar5 == 0x3000) {
          if (2 < *(int *)(param_1[0x17] + 4)) {
            puVar3 = allocate_effect_target_collision_payload_from_geometry(param_1,local_80);
            param_1[0x20] = puVar3;
            if (puVar3 != (undefined4 *)0x0) {
              param_1[4] = param_1[4] & 0xffff3fff | 0x3000;
              goto LAB_00436d31;
            }
          }
          param_1[4] = param_1[4] & 0xffff1fff | 0x1000;
        }
LAB_00436d31:
        param_1[4] = (uVar5 ^ param_1[4]) & 0xf000 ^ param_1[4];
      }
    }
    if ((undefined4 *)param_1[0x19] != (undefined4 *)0x0) {
      effect_target_visibility_scan_helper_00436c60((undefined4 *)param_1[0x19],local_80);
    }
    param_1 = (undefined4 *)param_1[0x18];
  } while( true );
}


