/*
 * Program: i76.exe
 * Function: build_world_object_class_damage_transform
 * Entry: 00461ed0
 * Signature: undefined __cdecl build_world_object_class_damage_transform(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Class-table dispatcher for damage
   transform callback; falls back to identity transform when absent. */

void __cdecl build_world_object_class_damage_transform(undefined4 *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 local_78 [15];
  undefined1 local_3c [60];
  
  iVar4 = *(int *)(param_2 + 0x6c);
  iVar1 = is_collapsible_special_world_object_class(iVar4);
  if ((iVar1 != 0) && (iVar4 != 4)) {
    iVar4 = 2;
  }
  iVar1 = 0;
  piVar2 = &g_world_object_class_callback_table;
  do {
    if (*piVar2 == iVar4) goto LAB_00461f0e;
    piVar2 = piVar2 + 0xd;
    iVar1 = iVar1 + 1;
  } while (piVar2 < s_clasfn_004f7c5c);
  iVar1 = 0;
LAB_00461f0e:
  if ((code *)(&DAT_004f7700)[iVar1 * 0xd] == (code *)0x0) {
    effect_target_list_scan_context_helper_004382e0(local_78);
  }
  else {
    puVar3 = (undefined4 *)(*(code *)(&DAT_004f7700)[iVar1 * 0xd])(local_3c,param_2);
    puVar5 = local_78;
    for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  puVar3 = local_78;
  for (iVar4 = 0xf; iVar4 != 0; iVar4 = iVar4 + -1) {
    *param_1 = *puVar3;
    puVar3 = puVar3 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


