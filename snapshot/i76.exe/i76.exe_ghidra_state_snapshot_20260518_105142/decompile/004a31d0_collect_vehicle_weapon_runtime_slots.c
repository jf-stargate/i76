/*
 * Program: i76.exe
 * Function: collect_vehicle_weapon_runtime_slots
 * Entry: 004a31d0
 * Signature: undefined4 __cdecl collect_vehicle_weapon_runtime_slots(int param_1, int * param_2)
 */


/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Finds the loaded vehicle runtime
   row and collects active weapon slot indices/count metadata into an eight-dword output block. */

undefined4 __cdecl collect_vehicle_weapon_runtime_slots(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar1 = 0;
  if (0 < g_loaded_vehicle_runtime_count) {
    piVar2 = &g_loaded_vehicle_runtime_table;
    do {
      if (*piVar2 == param_1) goto LAB_004a3201;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0xb2;
    } while (iVar1 < g_loaded_vehicle_runtime_count);
  }
  iVar1 = -1;
LAB_004a3201:
  if (iVar1 != -1) {
    piVar2 = param_2;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *piVar2 = 0;
      piVar2 = piVar2 + 1;
    }
    iVar3 = 0;
    iVar1 = iVar1 * 0x2c8;
    if (0 < *(int *)(&DAT_005be528 + iVar1)) {
      piVar2 = param_2 + 1;
      piVar4 = (int *)(&DAT_005be580 + iVar1);
      do {
        if (*piVar4 != -1) {
          *piVar2 = *piVar4;
          iVar5 = iVar5 + 1;
          piVar2 = piVar2 + 1;
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 0x16;
      } while (iVar3 < *(int *)(&DAT_005be528 + iVar1));
    }
    param_2[6] = *(int *)(&DAT_005be738 + iVar1);
    iVar1 = *(int *)(&DAT_005be790 + iVar1);
    *param_2 = iVar5;
    param_2[7] = iVar1;
    return 1;
  }
  return 2;
}


