/*
 * Program: i76.exe
 * Function: fsm_format_default_label_name
 * Entry: 0040a8a0
 * Signature: undefined __cdecl fsm_format_default_label_name(int param_1, int * param_2, int param_3, int * param_4)
 */


/* cgpt whole-binary semantic rename v1: string evidence: NoLabel%d */

void __cdecl fsm_format_default_label_name(int param_1,int *param_2,int param_3,int *param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int *piVar6;
  char *pcVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  float10 fVar11;
  float10 fVar12;
  uint local_4c;
  undefined4 *local_48;
  int local_44;
  float local_3c;
  int local_38;
  char local_30 [44];
  
  uVar4 = *(uint *)(param_1 + 0x10);
  iVar8 = 0;
  local_3c = 3.4028235e+38;
  local_44 = 0;
  local_4c = 0;
  local_48 = &DAT_00507da0;
  piVar6 = &DAT_0051f5d0;
  do {
    iVar2 = is_damage_side_effects_suppressed();
    if ((((iVar2 != 0) || (iVar2 = is_network_or_trip_runtime_mode(), iVar2 != 0)) ||
        (piVar6 != &DAT_0051f5d0)) &&
       ((local_4c != (uVar4 >> 0x10 & 7) && (local_38 = *piVar6, puVar9 = local_48, 0 < local_38))))
    {
      do {
        iVar8 = *(int *)*puVar9;
        iVar2 = is_vehicle_or_actor_runtime_world_object(iVar8);
        if ((iVar2 != 0) &&
           ((iVar2 = get_vehicle_runtime_context(iVar8), (*(byte *)(iVar2 + 0x454) & 0x20) == 0 &&
            (fVar11 = (float10)*(double *)(iVar8 + 0x40) - (float10)*(double *)(param_1 + 0x40),
            fVar12 = (float10)*(double *)(iVar8 + 0x50) - (float10)*(double *)(param_1 + 0x50),
            fVar11 = fVar12 * fVar12 + fVar11 * (float10)(float)fVar11, fVar11 < (float10)local_3c))
           )) {
          local_3c = (float)fVar11;
          local_44 = iVar8;
        }
        local_38 = local_38 + -1;
        iVar8 = local_44;
        puVar9 = puVar9 + 1;
      } while (local_38 != 0);
    }
    piVar6 = piVar6 + 1;
    local_4c = local_4c + 1;
    local_48 = local_48 + 0x40;
  } while ((int)piVar6 < 0x51f5f0);
  if (iVar8 == 0) {
    *(undefined4 *)(*param_4 * 0x60 + 0x58 + param_3) = 0;
    *param_2 = *param_4;
    return;
  }
  iVar3 = 0;
  iVar2 = *param_4;
  if (0 < iVar2) {
    piVar6 = (int *)(param_3 + 0x58);
    do {
      if (*piVar6 == iVar8) {
        *param_2 = iVar3;
        return;
      }
      iVar3 = iVar3 + 1;
      piVar6 = piVar6 + 0x18;
    } while (iVar3 < iVar2);
  }
  sprintf(local_30,s_NoLabel_d_004c2a94,iVar2);
  uVar4 = 0xffffffff;
  pcVar7 = local_30;
  do {
    pcVar10 = pcVar7;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar10 = pcVar7 + 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar10;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar7 = pcVar10 + -uVar4;
  pcVar10 = (char *)(*param_4 * 0x60 + param_3);
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar10 = *(undefined4 *)pcVar7;
    pcVar7 = pcVar7 + 4;
    pcVar10 = pcVar10 + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *pcVar10 = *pcVar7;
    pcVar7 = pcVar7 + 1;
    pcVar10 = pcVar10 + 1;
  }
  *(int *)(*param_4 * 0x60 + 0x58 + param_3) = local_44;
  increment_refcount_recursive_for_object_tree
            (*(int *)(*param_4 * 0x60 + 0x58 + param_3),&DAT_004c2a10);
  *param_2 = *param_4;
  *param_4 = *param_4 + 1;
  return;
}


