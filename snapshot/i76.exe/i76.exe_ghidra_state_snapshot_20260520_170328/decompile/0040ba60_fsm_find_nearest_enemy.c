/*
 * Program: i76.exe
 * Function: fsm_find_nearest_enemy
 * Entry: 0040ba60
 * Signature: undefined __cdecl fsm_find_nearest_enemy(int param_1, int * param_2, int param_3, int * param_4)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_0040ba60
   suggested_name: fsm_find_nearest_enemy
   basis: FSM diagnostic string indicates nearestEnemy failure path. */

void __cdecl fsm_find_nearest_enemy(int param_1,int *param_2,int param_3,int *param_4)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  float10 fVar10;
  float10 fVar11;
  int local_3c;
  float local_38;
  int local_34;
  char local_30 [44];
  
  local_38 = 3.4028235e+38;
  local_3c = 0;
  piVar3 = (int *)get_current_effect_target_scan_object();
  while (piVar3 != (int *)0x0) {
    iVar2 = *piVar3;
    iVar4 = is_transform_composed_world_object_class(iVar2);
    iVar5 = local_34;
    if (((iVar4 != 0) && (iVar5 = iVar2, (*(uint *)(iVar2 + 0x10) & 0x200) == 0)) &&
       (fVar10 = (float10)*(double *)(iVar2 + 0x40) - (float10)*(double *)(param_1 + 0x40),
       fVar11 = (float10)*(double *)(iVar2 + 0x50) - (float10)*(double *)(param_1 + 0x50),
       fVar10 = fVar11 * fVar11 + fVar10 * (float10)(float)fVar10, iVar5 = local_34,
       fVar10 < (float10)local_38)) {
      local_38 = (float)fVar10;
      local_3c = iVar2;
    }
    piVar3 = (int *)effect_target_scan_query_context_helper_00436790();
    local_34 = iVar5;
  }
  if (local_38 == _DAT_004bc618) {
    local_3c = local_34;
  }
  if (local_3c == 0) {
    report_error();
  }
  iVar5 = 0;
  iVar2 = *param_4;
  if (0 < iVar2) {
    piVar3 = (int *)(param_3 + 0x58);
    do {
      if (*piVar3 == local_3c) {
        *param_2 = iVar5;
        return;
      }
      iVar5 = iVar5 + 1;
      piVar3 = piVar3 + 0x18;
    } while (iVar5 < iVar2);
  }
  sprintf(local_30,s_NoLabel_d_004c2a94,iVar2);
  uVar6 = 0xffffffff;
  pcVar8 = local_30;
  do {
    pcVar9 = pcVar8;
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    pcVar9 = pcVar8 + 1;
    cVar1 = *pcVar8;
    pcVar8 = pcVar9;
  } while (cVar1 != '\0');
  uVar6 = ~uVar6;
  pcVar8 = pcVar9 + -uVar6;
  pcVar9 = (char *)(*param_4 * 0x60 + param_3);
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
    pcVar8 = pcVar8 + 4;
    pcVar9 = pcVar9 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar9 = *pcVar8;
    pcVar8 = pcVar8 + 1;
    pcVar9 = pcVar9 + 1;
  }
  *(int *)(*param_4 * 0x60 + 0x58 + param_3) = local_3c;
  increment_refcount_recursive_for_object_tree(local_3c,&DAT_004c2a10);
  *param_2 = *param_4;
  *param_4 = *param_4 + 1;
  return;
}


