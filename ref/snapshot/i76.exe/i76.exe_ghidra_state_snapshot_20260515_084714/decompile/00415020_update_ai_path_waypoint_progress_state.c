/*
 * Program: i76.exe
 * Function: update_ai_path_waypoint_progress_state
 * Entry: 00415020
 * Signature: undefined __cdecl update_ai_path_waypoint_progress_state(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v12 fsm/roadwar/path cluster: Advances AI/path waypoint progress, detects path
   completion, and updates waypoint/segment progress flags. */

void __cdecl update_ai_path_waypoint_progress_state(int *param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  float10 fVar7;
  
  bVar4 = true;
  fVar2 = (float)*(double *)(*param_1 + 0x28);
  fVar3 = (float)*(double *)(*param_1 + 0x38);
  do {
    if (param_1[0x26] != 0) {
      return;
    }
    iVar1 = param_1[0x2a];
    fVar5 = (float)param_1[iVar1 * 5 + 0x2c] - fVar2;
    fVar6 = (float)param_1[(iVar1 + 9) * 5] - fVar3;
    if (iVar1 == param_1[0x2b] + -1) {
      if (fVar6 * fVar6 + fVar5 * fVar5 < _DAT_004bc7c0) {
        param_1[0x26] = 1;
        param_1[0x25] = 1;
      }
LAB_004150c9:
      bVar4 = false;
    }
    else if (iVar1 == 0) {
      if (_DAT_004bc7f8 <= fVar6 * fVar6 + fVar5 * fVar5) goto LAB_004150c9;
      param_1[0x2a] = 1;
    }
    else {
      fVar7 = compute_short_2d_segment_alignment_metric
                        ((float)param_1[iVar1 * 5 + 0x2c],(float)param_1[(iVar1 + 9) * 5],
                         (float)param_1[iVar1 * 5 + 0x31],(float)param_1[(iVar1 + 10) * 5],fVar2,
                         fVar3);
      if (fVar7 <= (float10)_DAT_004bc7fc) goto LAB_004150c9;
      param_1[0x2a] = param_1[0x2a] + 1;
    }
    if (!bVar4) {
      if ((param_1[0x21] != 1) &&
         (iVar1 = param_1[0x28],
         fVar2 = (float)*(double *)(*param_1 + 0x28) -
                 *(float *)(*(int *)(param_1[0x22] + 0x54) + iVar1 * 0xc),
         fVar3 = (float)*(double *)(*param_1 + 0x38) -
                 *(float *)(*(int *)(param_1[0x22] + 0x54) + 8 + iVar1 * 0xc),
         fVar3 * fVar3 + fVar2 * fVar2 < _DAT_004bc800)) {
        param_1[0x25] = 1;
        param_1[0x28] = iVar1 + 1;
        if (param_1[0x29] == iVar1 + 1) {
          param_1[0x27] = 1;
          param_1[0x28] = 0;
        }
      }
      return;
    }
  } while( true );
}


