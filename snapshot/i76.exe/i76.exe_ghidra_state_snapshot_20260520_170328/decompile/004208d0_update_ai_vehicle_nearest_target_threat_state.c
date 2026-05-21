/*
 * Program: i76.exe
 * Function: update_ai_vehicle_nearest_target_threat_state
 * Entry: 004208d0
 * Signature: undefined __cdecl update_ai_vehicle_nearest_target_threat_state(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: AI helper that scans target/vehicle state around the current
   vehicle and updates nearest target or threat behavior state. */

void __cdecl update_ai_vehicle_nearest_target_threat_state(int param_1)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float10 fVar9;
  float fVar10;
  float fVar11;
  float local_10;
  
  bVar5 = true;
  local_10 = 3.4028235e+38;
  piVar1 = *(int **)(*(int *)(param_1 + 0x70) + 0x108);
  fVar3 = (float)*(double *)(*piVar1 + 0x28);
  fVar4 = (float)*(double *)(*piVar1 + 0x38);
  iVar6 = 0;
  iVar2 = *(int *)(piVar1[0x23] + 0x50);
  iVar8 = param_1;
  if (0 < iVar2) {
    pfVar7 = *(float **)(piVar1[0x23] + 0x54);
    do {
      fVar10 = fVar3 - *pfVar7;
      fVar11 = fVar4 - pfVar7[2];
      fVar11 = fVar11 * fVar11 + fVar10 * fVar10;
      if (fVar11 < local_10) {
        param_1 = iVar6;
        local_10 = fVar11;
      }
      iVar6 = iVar6 + 1;
      pfVar7 = pfVar7 + 3;
      iVar8 = param_1;
    } while (iVar6 < iVar2);
  }
  do {
    pfVar7 = *(float **)(piVar1[0x23] + 0x54);
    if (param_1 < iVar2 + -1) {
      fVar11 = pfVar7[param_1 * 3 + 5];
      fVar10 = pfVar7[(param_1 + 1) * 3];
    }
    else {
      fVar11 = pfVar7[2];
      fVar10 = *pfVar7;
    }
    fVar9 = compute_short_2d_segment_alignment_metric
                      (pfVar7[param_1 * 3],pfVar7[param_1 * 3 + 2],fVar10,fVar11,fVar3,fVar4);
    if (fVar9 <= (float10)_DAT_004bcc64) {
LAB_004209ed:
      bVar5 = false;
    }
    else {
      param_1 = param_1 + 1;
      if (iVar2 <= param_1) {
        param_1 = 0;
      }
      if (param_1 == iVar8) goto LAB_004209ed;
    }
    if (!bVar5) {
      piVar1[0x28] = param_1;
      return;
    }
  } while( true );
}


