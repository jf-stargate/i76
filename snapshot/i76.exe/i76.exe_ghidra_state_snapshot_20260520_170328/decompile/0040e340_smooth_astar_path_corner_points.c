/*
 * Program: i76.exe
 * Function: smooth_astar_path_corner_points
 * Entry: 0040e340
 * Signature: undefined __cdecl smooth_astar_path_corner_points(undefined4 * param_1, undefined4 * param_2, int param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Smooths or adjusts A* path corner points and writes
   the resulting path point sequence. */

void __cdecl
smooth_astar_path_corner_points(undefined4 *param_1,undefined4 *param_2,int param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  float fVar8;
  int *piVar9;
  float10 fVar10;
  int local_3c;
  int local_38;
  undefined4 *local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined4 *local_18;
  int local_14;
  float local_10;
  int local_c;
  
  local_14 = param_3;
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  param_2[2] = param_1[2];
  param_3 = 0;
  local_3c = 1;
  do {
    iVar6 = param_3 + 1;
    local_18 = param_1 + iVar6 * 3;
    local_28 = (float)ftol();
    local_c = ftol();
    fVar8 = (float)(param_3 * 0xc);
    local_10 = fVar8;
    local_24 = (float)ftol();
    iVar2 = ftol();
    if (iVar2 < local_c) {
      if ((int)local_24 < (int)local_28) {
        local_38 = 1;
      }
      else {
        local_38 = (((int)local_24 <= (int)local_28) - 1 & 0xfffffffe) + 6;
      }
    }
    else if (local_c < iVar2) {
      if ((int)local_24 < (int)local_28) {
        local_38 = 2;
      }
      else {
        local_38 = (((int)local_24 <= (int)local_28) - 1 & 0xfffffffe) + 7;
      }
    }
    else {
      local_38 = (((int)local_28 <= (int)local_24) - 1 & 0xfffffffd) + 3;
    }
    if (((float)local_18[2] == _DAT_004bc6b4) && (param_3 + 2 < local_14)) {
      local_24 = (float)(param_3 + 2);
      local_34 = param_1 + (int)local_24 * 3;
      do {
        iVar2 = ftol();
        local_c = ftol();
        iVar3 = ftol();
        iVar4 = ftol();
        if (iVar4 < local_c) {
          if (iVar3 < iVar2) {
            iVar2 = 1;
          }
          else {
            iVar2 = ((iVar3 <= iVar2) - 1 & 0xfffffffe) + 6;
          }
        }
        else if (local_c < iVar4) {
          if (iVar3 < iVar2) {
            iVar2 = 2;
          }
          else {
            iVar2 = ((iVar3 <= iVar2) - 1 & 0xfffffffe) + 7;
          }
        }
        else {
          iVar2 = ((iVar2 <= iVar3) - 1 & 0xfffffffd) + 3;
        }
        if (((float)local_34[-1] == _DAT_004bc6b4) &&
           (iVar2 = fsm_astar_illegal_state_error(&local_38,iVar2), iVar2 != 0)) {
          iVar6 = iVar6 + 1;
          local_34 = local_34 + 3;
          local_24 = (float)((int)local_24 + 1);
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
        if (local_14 <= (int)local_24) {
          bVar1 = false;
        }
        fVar8 = local_10;
      } while (bVar1);
    }
    local_18 = (undefined4 *)(uint)(param_3 < iVar6);
    if (local_18 != (undefined4 *)0x0) {
      piVar9 = param_2 + local_3c * 3;
      piVar7 = param_1 + iVar6 * 3 + 2;
      local_c = -8 - (int)param_1;
      local_1c = fVar8;
      do {
        if (param_3 + 1 == iVar6) {
          *piVar9 = piVar7[-2];
          piVar9[1] = piVar7[-1];
          piVar9[2] = *piVar7;
        }
        else {
          if ((*piVar7 != 0x3f800000) && (*piVar7 != 0x40000000)) {
            local_28 = *(float *)((int)param_1 + (int)local_1c + 4);
            local_24 = *(float *)((int)param_1 + (int)local_1c);
            local_30 = (float)piVar7[-2] - local_24;
            local_34 = (undefined4 *)((float)piVar7[-1] - local_28);
            fVar8 = (float)local_34 * (float)local_34 + local_30 * local_30;
            if ((fVar8 <= _DAT_004bc6a4) || (_DAT_004bc6a8 <= fVar8)) {
              fVar10 = zone_satellite_map_context_helper_00495000
                                 (SUB84((double)fVar8,0),(uint)((ulonglong)(double)fVar8 >> 0x20));
              local_2c = (float)fVar10;
            }
            else {
              local_2c = 1.0;
            }
            local_10 = local_2c - _DAT_004bc6b0;
            local_20 = 0.0;
            local_30 = local_2c * local_30 * _DAT_004bc68c;
            local_34 = (undefined4 *)(local_2c * (float)local_34 * _DAT_004bc68c);
            if (_DAT_004bc6b4 < local_10) {
              do {
                local_28 = local_28 + (float)local_34;
                local_24 = local_24 + local_30;
                uVar5 = terrain_map_context_helper_004926f0((double)local_24,(double)local_28);
                if (uVar5 != 0) {
                  iVar6 = iVar6 + -1;
                  piVar7 = piVar7 + -3;
                  goto LAB_0040e735;
                }
                local_20 = local_2c + local_20;
              } while (local_20 < local_10);
            }
          }
          *piVar9 = piVar7[-2];
          piVar9[1] = piVar7[-1];
          piVar9[2] = *piVar7;
        }
        local_1c = (float)(local_c + (int)piVar7);
        local_18 = (undefined4 *)0x0;
        local_3c = local_3c + 1;
        piVar9 = piVar9 + 3;
        param_3 = iVar6;
LAB_0040e735:
      } while (local_18 != (undefined4 *)0x0);
    }
    if (local_14 + -1 <= param_3) {
      *param_4 = local_3c;
      return;
    }
  } while( true );
}


