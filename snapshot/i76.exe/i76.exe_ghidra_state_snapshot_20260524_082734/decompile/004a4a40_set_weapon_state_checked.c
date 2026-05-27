/*
 * Program: i76.exe
 * Function: set_weapon_state_checked
 * Entry: 004a4a40
 * Signature: undefined __cdecl set_weapon_state_checked(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence cannot set state on nonexistent weapons */

void __cdecl set_weapon_state_checked(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int local_78 [6];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58 [16];
  undefined4 local_18;
  int local_8;
  
  iVar1 = 0;
  iVar5 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar2 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar2 == param_1) goto LAB_004a4a7c;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a4a7c:
  if (iVar1 != -1) {
    piVar2 = local_78;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar2 = 0;
      piVar2 = piVar2 + 1;
    }
    iVar1 = iVar1 * 0x2c8;
    iVar3 = *(int *)(&DAT_005be528 + iVar1);
    if (0 < iVar3) {
      piVar4 = local_78 + 1;
      piVar2 = (int *)(&DAT_005be580 + iVar1);
      do {
        if (*piVar2 != -1) {
          *piVar4 = *piVar2;
          iVar5 = iVar5 + 1;
          piVar4 = piVar4 + 1;
        }
        piVar2 = piVar2 + 0x16;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    local_60 = *(undefined4 *)(&DAT_005be738 + iVar1);
    local_5c = *(undefined4 *)(&DAT_005be790 + iVar1);
    if (0 < iVar5) {
      piVar2 = local_78;
      local_78[0] = iVar5;
      do {
        piVar2 = piVar2 + 1;
        extract_weapon_runtime_state_to_vsf_record(*piVar2,local_58);
        iVar1 = ftol();
        iVar3 = 0;
        if (0 < g_loaded_vehicle_runtime_count) {
          piVar4 = &g_loaded_vehicle_runtime_table;
          do {
            if (*piVar4 == param_1) goto LAB_004a4b49;
            iVar3 = iVar3 + 1;
            piVar4 = piVar4 + 0xb2;
          } while (iVar3 < g_loaded_vehicle_runtime_count);
        }
        iVar3 = -1;
LAB_004a4b49:
        iVar6 = 0;
        piVar4 = (int *)(&DAT_005be530 + iVar3 * 0x2c8);
        do {
          if (*piVar4 == local_8) goto LAB_004a4b75;
          iVar6 = iVar6 + 1;
          piVar4 = piVar4 + 0x16;
        } while (iVar6 < 7);
        iVar6 = -1;
LAB_004a4b75:
        iVar3 = *(int *)(&DAT_005be580 + iVar6 * 0x58 + iVar3 * 0x2c8);
        if (iVar3 == -1) {
          report_error();
        }
        else {
          (&DAT_005aab14)[iVar3 * 0x13] = local_18;
          if (iVar1 != -1) {
            *(int *)(&DAT_005aab28 + iVar3 * 0x4c) = iVar1;
          }
        }
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return;
}


