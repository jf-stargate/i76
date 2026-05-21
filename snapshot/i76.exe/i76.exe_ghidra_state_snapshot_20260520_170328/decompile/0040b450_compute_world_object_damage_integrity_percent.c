/*
 * Program: i76.exe
 * Function: compute_world_object_damage_integrity_percent
 * Entry: 0040b450
 * Signature: float10 __cdecl compute_world_object_damage_integrity_percent(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v7 fsm predicate/bridge cluster: Computes a 0..100 integrity/health percentage for
   vehicles, child damage parts, and related damage-bearing world objects. */

float10 __cdecl compute_world_object_damage_integrity_percent(int param_1)

{
  float fVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  float local_44;
  float local_40;
  float local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  float local_24;
  float local_20;
  float local_1c [7];
  
  iVar6 = param_1;
  iVar7 = 0;
  local_44 = 3.4028235e+38;
  local_40 = 3.4028235e+38;
  local_3c = 3.4028235e+38;
  local_24 = 3.4028235e+38;
  local_20 = 0.0;
  switch(*(undefined4 *)(param_1 + 0x6c)) {
  case 1:
    iVar2 = get_vehicle_runtime_context(param_1);
    iVar4 = is_damage_side_effects_suppressed();
    if ((iVar4 != 0) && ((*(byte *)(iVar6 + 0x10) & 0x20) != 0)) {
      return (float10)*(float *)(iVar2 + 0x484);
    }
    extract_engine_or_suspension_state_pair(*(int *)(iVar2 + 0x3c4),&param_1,&local_38);
    local_1c[0] = (float)param_1 / (float)local_38;
    extract_engine_or_suspension_state_pair(*(int *)(iVar2 + 0x3c8),&local_34,&local_30);
    local_1c[1] = (float)local_34 / (float)local_30;
    extract_part_damage_state_pair(*(int *)(iVar2 + 0x3cc),&local_2c,&local_28);
    pfVar5 = local_1c;
    iVar6 = 3;
    local_1c[2] = (float)local_2c / (float)local_28;
    fVar8 = (float10)local_24;
    do {
      if (_DAT_004bc624 <= *pfVar5) {
        if (*pfVar5 < _DAT_004bc61c) {
          *pfVar5 = 0.0;
        }
        if (_DAT_004bc628 < *pfVar5) {
          *pfVar5 = 1.0;
        }
        if ((float10)*pfVar5 < fVar8) {
          fVar8 = (float10)*pfVar5;
        }
      }
      else {
        iVar7 = iVar7 + 1;
      }
      pfVar5 = pfVar5 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    if ((fVar8 < (float10)_DAT_004bc62c) || (0 < iVar7)) {
      switch(iVar7) {
      case 0:
      case 1:
      case 2:
      case 3:
        break;
      default:
        fVar8 = (float10)local_20;
      }
    }
    else {
      piVar3 = (int *)(iVar2 + 0x158);
      iVar6 = 4;
      do {
        if (0 < *piVar3) {
          fVar1 = (float)piVar3[-8] / (float)*piVar3;
          if (fVar1 < _DAT_004bc61c) {
            fVar1 = _DAT_004bc61c;
          }
          if (_DAT_004bc628 < fVar1) {
            fVar1 = _DAT_004bc628;
          }
          if (fVar1 < local_44) {
            local_44 = fVar1;
          }
        }
        if (0 < piVar3[4]) {
          fVar1 = (float)piVar3[-4] / (float)piVar3[4];
          if (fVar1 < _DAT_004bc61c) {
            fVar1 = _DAT_004bc61c;
          }
          if (_DAT_004bc628 < fVar1) {
            fVar1 = _DAT_004bc628;
          }
          if (fVar1 < local_40) {
            local_40 = fVar1;
          }
        }
        piVar3 = piVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      if (local_40 <= local_44) {
        fVar8 = (float10)local_40 * (float10)_DAT_004bc630 - (float10)_DAT_004bc634;
      }
      else {
        fVar8 = (float10)local_44 * (float10)_DAT_004bc630 - (float10)_DAT_004bc634;
      }
    }
    if ((float10)_DAT_004bc620 < fVar8) {
      fVar8 = (float10)_DAT_004bc620;
    }
    if ((float10)_DAT_004bc61c <= fVar8) {
      return fVar8;
    }
    return (float10)_DAT_004bc61c;
  case 2:
  case 3:
  case 0xb:
  case 0xc:
    for (iVar6 = *(int *)(param_1 + 100); iVar6 != 0; iVar6 = *(int *)(iVar6 + 0x60)) {
      iVar7 = is_transform_composed_world_object_class(iVar6);
      if ((((iVar7 != 0) && (0x1000 < (*(uint *)(iVar6 + 0x10) & 0xf000))) &&
          (piVar3 = *(int **)(iVar6 + 0x70), piVar3 != (int *)0x0)) &&
         ((local_20 = (float)piVar3[1], 0 < (int)local_20 &&
          ((float)*piVar3 / (float)(int)local_20 < local_3c)))) {
        local_3c = (float)*piVar3 / (float)(int)local_20;
      }
    }
    return (float10)local_3c * (float10)_DAT_004bc620;
  default:
    goto switchD_0040b495_caseD_4;
  case 8:
    piVar3 = *(int **)(*(int *)(param_1 + 0x70) + 0x508);
    break;
  case 9:
    iVar7 = *(int *)(param_1 + 0x70);
    iVar2 = is_damage_side_effects_suppressed();
    if ((iVar2 != 0) && ((*(byte *)(iVar6 + 0x10) & 0x20) != 0)) {
      return (float10)*(float *)(iVar7 + 0x484);
    }
    piVar3 = *(int **)(iVar7 + 0x508);
  }
  if (0 < piVar3[1]) {
    return (float10)*piVar3 * (float10)(float)piVar3[2] * (float10)_DAT_004bc620;
  }
switchD_0040b495_caseD_4:
  return (float10)_DAT_004bc620;
}


