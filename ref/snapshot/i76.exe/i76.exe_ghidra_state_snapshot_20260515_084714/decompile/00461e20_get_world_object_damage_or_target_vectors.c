/*
 * Program: i76.exe
 * Function: get_world_object_damage_or_target_vectors
 * Entry: 00461e20
 * Signature: undefined __cdecl get_world_object_damage_or_target_vectors(int param_1, undefined4 * param_2, undefined4 * param_3)
 */


/* [cgpt i76.exe player weapon targeting rename v26; confidence=medium] Dispatches class-specific
   callback to obtain target/damage vectors for a world object, falling back to zero vectors. */

void __cdecl
get_world_object_damage_or_target_vectors(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x6c);
  iVar1 = is_collapsible_special_world_object_class(iVar3);
  if ((iVar1 != 0) && (iVar3 != 4)) {
    iVar3 = 2;
  }
  iVar1 = 0;
  piVar2 = &g_world_object_class_callback_table;
  do {
    if (*piVar2 == iVar3) goto LAB_00461e5b;
    piVar2 = piVar2 + 0xd;
    iVar1 = iVar1 + 1;
  } while (piVar2 < s_clasfn_004f7c5c);
  iVar1 = 0;
LAB_00461e5b:
  if ((code *)(&DAT_004f76fc)[iVar1 * 0xd] != (code *)0x0) {
    (*(code *)(&DAT_004f76fc)[iVar1 * 0xd])(param_1,param_2,param_3);
    return;
  }
  *param_2 = 0;
  param_2[1] = 0;
  param_2[2] = 0;
  *param_3 = 0;
  return;
}


