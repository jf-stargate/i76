/*
 * Program: i76.exe
 * Function: validate_bridge_is_orthogonal
 * Entry: 0040c480
 * Signature: undefined __cdecl validate_bridge_is_orthogonal(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: bridge not orthoginal */

void __cdecl validate_bridge_is_orthogonal(int *param_1)

{
  double dVar1;
  float fVar2;
  float *pfVar3;
  int iVar4;
  double *pdVar5;
  int iVar6;
  double *pdVar7;
  float *pfVar8;
  float *pfVar9;
  float local_f4;
  float local_f0;
  undefined4 local_ec;
  float local_e8;
  float local_e4;
  undefined4 local_e0;
  float local_dc;
  double local_d8;
  int local_cc;
  float local_c8 [6];
  float local_b0;
  float local_a8;
  float local_88 [16];
  float local_48 [17];
  
  iVar4 = *param_1;
  if (iVar4 == 0) {
    return;
  }
  while( true ) {
    pfVar3 = compose_matrix_or_transform_a(local_48,(float *)(iVar4 + 0x18),(float *)&DAT_004faed8);
    pfVar8 = pfVar3;
    pfVar9 = local_88;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *pfVar9 = *pfVar8;
      pfVar8 = pfVar8 + 1;
      pfVar9 = pfVar9 + 1;
    }
    if (*(int *)(iVar4 + 0x6c) == 0xd) break;
    if ((*(int *)(iVar4 + 100) != 0) &&
       (iVar6 = find_bridge_piece_transform_in_object_tree
                          (*(int *)(iVar4 + 100),local_88,&local_cc,local_c8), iVar6 != 0))
    goto LAB_0040c510;
    iVar4 = *(int *)(iVar4 + 0x60);
    if (iVar4 == 0) {
      return;
    }
  }
  pfVar8 = local_c8;
  for (iVar6 = 0x10; local_cc = iVar4, iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar8 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar8 = pfVar8 + 1;
  }
LAB_0040c510:
  local_f0 = *(float *)(local_cc + 0x94);
  local_ec = *(undefined4 *)(local_cc + 0x98);
  local_e8 = *(float *)(local_cc + 0x9c) - _DAT_004bc68c;
  transform_vec3_array_by_matrix(&local_f0,&local_f0,1,local_c8);
  local_e4 = *(float *)(local_cc + 0xa0);
  local_e0 = *(undefined4 *)(local_cc + 0xa4);
  local_dc = *(float *)(local_cc + 0xa8) - _DAT_004bc690;
  transform_vec3_array_by_matrix(&local_e4,&local_e4,1,local_c8);
  if (_DAT_004bc694 < local_a8) {
    iVar4 = ftol();
    local_dc = (float)(10 - iVar4 % 10) + (float)iVar4;
    iVar4 = ftol();
    local_f4 = 5.0;
    local_e8 = (float)iVar4 - (float)(iVar4 % 10);
    if (local_e4 <= local_f0) {
      local_f4 = -5.0;
    }
    fVar2 = local_f0;
    if (ABS((local_f4 + local_e4) - local_f0) <= (float)_DAT_004bc698) {
      return;
    }
    do {
      dVar1 = (double)fVar2;
      local_d8 = dVar1;
      pdVar5 = (double *)
               append_bridge_validation_span_record(dVar1,(double)local_e8,*param_1,fVar2,local_dc);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      pdVar5 = (double *)
               append_bridge_validation_span_record(dVar1,(double)local_dc,*param_1,fVar2,local_e8);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      fVar2 = fVar2 + local_f4;
    } while ((float)_DAT_004bc698 < ABS((local_f4 + local_e4) - fVar2));
    return;
  }
  if (local_a8 < _DAT_004bc6a0) {
    iVar4 = ftol();
    local_dc = (float)iVar4 - (float)(iVar4 % 10);
    iVar4 = ftol();
    local_f4 = 5.0;
    local_e8 = (float)(10 - iVar4 % 10) + (float)iVar4;
    if (local_e4 <= local_f0) {
      local_f4 = -5.0;
    }
    fVar2 = local_f0;
    if (ABS((local_f4 + local_e4) - local_f0) <= (float)_DAT_004bc698) {
      return;
    }
    do {
      dVar1 = (double)fVar2;
      local_d8 = dVar1;
      pdVar5 = (double *)
               append_bridge_validation_span_record(dVar1,(double)local_e8,*param_1,fVar2,local_dc);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      pdVar5 = (double *)
               append_bridge_validation_span_record(dVar1,(double)local_dc,*param_1,fVar2,local_e8);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      fVar2 = fVar2 + local_f4;
    } while ((float)_DAT_004bc698 < ABS((local_f4 + local_e4) - fVar2));
    return;
  }
  if (_DAT_004bc694 < local_b0) {
    iVar4 = ftol();
    local_e4 = (float)(10 - iVar4 % 10) + (float)iVar4;
    iVar4 = ftol();
    local_f4 = 5.0;
    local_f0 = (float)iVar4 - (float)(iVar4 % 10);
    if (local_dc <= local_e8) {
      local_f4 = -5.0;
    }
    fVar2 = local_e8;
    if (ABS((local_f4 + local_dc) - local_e8) <= (float)_DAT_004bc698) {
      return;
    }
    do {
      dVar1 = (double)fVar2;
      local_d8 = dVar1;
      pdVar5 = (double *)
               append_bridge_validation_span_record((double)local_f0,dVar1,*param_1,local_e4,fVar2);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      pdVar5 = (double *)
               append_bridge_validation_span_record((double)local_e4,dVar1,*param_1,local_f0,fVar2);
      if (DAT_0051f654 != (double *)0x0) {
        if (*pdVar5 <= *DAT_0051f654) {
          pdVar7 = DAT_0051f654 + 4;
        }
        else {
          pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
        }
        insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
        pdVar5 = DAT_0051f654;
      }
      DAT_0051f654 = pdVar5;
      fVar2 = fVar2 + local_f4;
    } while ((float)_DAT_004bc698 < ABS((local_f4 + local_dc) - fVar2));
    return;
  }
  if (_DAT_004bc6a0 <= local_b0) {
    report_error();
    return;
  }
  iVar4 = ftol();
  local_e4 = (float)iVar4 - (float)(iVar4 % 10);
  iVar4 = ftol();
  local_f4 = 5.0;
  local_f0 = (float)(10 - iVar4 % 10) + (float)iVar4;
  if (local_dc <= local_e8) {
    local_f4 = -5.0;
  }
  fVar2 = local_e8;
  if (ABS((local_f4 + local_dc) - local_e8) <= (float)_DAT_004bc698) {
    return;
  }
  do {
    dVar1 = (double)fVar2;
    local_d8 = dVar1;
    pdVar5 = (double *)
             append_bridge_validation_span_record((double)local_f0,dVar1,*param_1,local_e4,fVar2);
    if (DAT_0051f654 != (double *)0x0) {
      if (*pdVar5 <= *DAT_0051f654) {
        pdVar7 = DAT_0051f654 + 4;
      }
      else {
        pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
      }
      insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
      pdVar5 = DAT_0051f654;
    }
    DAT_0051f654 = pdVar5;
    pdVar5 = (double *)
             append_bridge_validation_span_record((double)local_e4,dVar1,*param_1,local_f0,fVar2);
    if (DAT_0051f654 != (double *)0x0) {
      if (*pdVar5 <= *DAT_0051f654) {
        pdVar7 = DAT_0051f654 + 4;
      }
      else {
        pdVar7 = (double *)((int)DAT_0051f654 + 0x1c);
      }
      insert_bridge_validation_span_node_sorted(pdVar5,(undefined4 *)pdVar7);
      pdVar5 = DAT_0051f654;
    }
    DAT_0051f654 = pdVar5;
    fVar2 = fVar2 + local_f4;
  } while ((float)_DAT_004bc698 < ABS((local_f4 + local_dc) - fVar2));
  return;
}


