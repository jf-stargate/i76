/*
 * Program: i76.exe
 * Function: validate_ai_path_destination_bounds
 * Entry: 00415220
 * Signature: undefined __cdecl validate_ai_path_destination_bounds(int param_1, int * param_2, int param_3, float param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Checks AI path destination/segment bounds and reports the 'dest out of bounds'
   parse error on invalid path geometry. */

void __cdecl validate_ai_path_destination_bounds(int param_1,int *param_2,int param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  float local_24;
  float local_20;
  float local_14;
  float local_10;
  float local_c;
  
  if (*(int *)(param_1 + 0x6c) == 9) {
    param_4 = 24.0;
  }
  iVar5 = param_2[0x2a];
  local_24 = (float)param_2[iVar5 * 5 + 0x2c];
  local_20 = (float)param_2[(iVar5 + 9) * 5];
  if (param_3 != 0) {
    if (iVar5 < 1) {
      fVar1 = (float)param_2[iVar5 * 5 + 0x31] - local_24;
      fVar2 = (float)param_2[(iVar5 + 10) * 5] - local_20;
    }
    else {
      fVar1 = local_24 - (float)param_2[iVar5 * 5 + 0x27];
      fVar2 = local_20 - (float)param_2[(iVar5 + 8) * 5];
    }
    fVar3 = fVar2 * fVar2 + fVar1 * fVar1;
    if ((fVar3 <= _DAT_004bc7ac) || (_DAT_004bc7b0 <= fVar3)) {
      fVar6 = zone_satellite_map_context_helper_00495000
                        (SUB84((double)fVar3,0),(uint)((ulonglong)(double)fVar3 >> 0x20));
    }
    else {
      fVar6 = (float10)_DAT_004bc808;
    }
    local_24 = (float)(fVar6 * (float10)fVar2 * (float10)_DAT_004bc80c + (float10)local_24);
    local_20 = (float)(fVar6 * (float10)fVar1 * (float10)_DAT_004bc7c4 + (float10)local_20);
  }
  fVar6 = (float10)local_24 - (float10)*(double *)(*param_2 + 0x28);
  fVar7 = (float10)local_20 - (float10)*(double *)(*param_2 + 0x38);
  fVar1 = (float)(fVar7 * fVar7 + fVar6 * fVar6);
  if ((param_4 * param_4 < fVar1) || (iVar5 == param_2[0x2b] + -1)) {
    fVar6 = (float10)fpatan(fVar6,fVar7);
    if (((float10)_DAT_004bc810 < fVar6) && (fVar6 < (float10)_DAT_004bc814)) {
      return;
    }
  }
  else {
    iVar5 = iVar5 + 1;
    local_10 = local_24;
    local_c = local_20;
    local_14 = param_4 - SQRT(fVar1);
    if (iVar5 < param_2[0x2b]) {
      pfVar4 = (float *)(param_2 + iVar5 * 5 + 0x2c);
      do {
        local_20 = pfVar4[1];
        local_24 = *pfVar4;
        if (param_3 != 0) {
          fVar3 = *pfVar4 - pfVar4[-5];
          fVar1 = pfVar4[1] - pfVar4[-4];
          fVar2 = fVar1 * fVar1 + fVar3 * fVar3;
          if ((fVar2 <= _DAT_004bc7ac) || (_DAT_004bc7b0 <= fVar2)) {
            fVar6 = zone_satellite_map_context_helper_00495000
                              (SUB84((double)fVar2,0),(uint)((ulonglong)(double)fVar2 >> 0x20));
          }
          else {
            fVar6 = (float10)_DAT_004bc808;
          }
          local_24 = (float)(fVar6 * (float10)fVar1 * (float10)_DAT_004bc80c + (float10)local_24);
          local_20 = (float)(fVar6 * (float10)fVar3 * (float10)_DAT_004bc7c4 + (float10)local_20);
        }
        fVar3 = local_24 - local_10;
        fVar1 = local_20 - local_c;
        fVar2 = SQRT(fVar1 * fVar1 + fVar3 * fVar3);
        if (local_14 < fVar2) {
          local_24 = (fVar3 / fVar2) * local_14 + local_10;
          local_20 = (fVar1 / fVar2) * local_14 + local_c;
          fVar6 = (float10)fpatan((float10)local_24 - (float10)*(double *)(*param_2 + 0x28),
                                  (float10)local_20 - (float10)*(double *)(*param_2 + 0x38));
          if (((float10)_DAT_004bc810 < fVar6) && (fVar6 < (float10)_DAT_004bc814)) {
            return;
          }
          report_chunk_parse_error();
        }
        local_14 = local_14 - fVar2;
        local_10 = local_24;
        local_c = local_20;
        iVar5 = iVar5 + 1;
        pfVar4 = pfVar4 + 5;
      } while (iVar5 < param_2[0x2b]);
    }
    fVar6 = (float10)fpatan((float10)(float)param_2[param_2[0x2a] * 5 + 0x2c] -
                            (float10)*(double *)(param_1 + 0x40),
                            (float10)(float)param_2[(param_2[0x2a] + 9) * 5] -
                            (float10)*(double *)(param_1 + 0x50));
    if (((float10)_DAT_004bc810 < fVar6) && (fVar6 < (float10)_DAT_004bc814)) {
      return;
    }
  }
  report_chunk_parse_error();
  return;
}


