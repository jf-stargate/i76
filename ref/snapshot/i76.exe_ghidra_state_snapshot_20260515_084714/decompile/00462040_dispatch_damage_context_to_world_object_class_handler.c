/*
 * Program: i76.exe
 * Function: dispatch_damage_context_to_world_object_class_handler
 * Entry: 00462040
 * Signature: undefined4 __cdecl dispatch_damage_context_to_world_object_class_handler(int param_1, undefined4 param_2, undefined4 param_3)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=high] Class-table dispatcher for damage
   context callbacks through the clasfn descriptor table. */

undefined4 __cdecl
dispatch_damage_context_to_world_object_class_handler
          (int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x6c);
  iVar1 = is_collapsible_special_world_object_class(iVar4);
  if ((iVar1 != 0) && (iVar4 != 4)) {
    iVar4 = 2;
  }
  iVar1 = 0;
  piVar2 = &g_world_object_class_callback_table;
  do {
    if (*piVar2 == iVar4) goto LAB_00462078;
    piVar2 = piVar2 + 0xd;
    iVar1 = iVar1 + 1;
  } while (piVar2 < s_clasfn_004f7c5c);
  iVar1 = 0;
LAB_00462078:
  uVar3 = 0;
  if ((code *)(&DAT_004f7708)[iVar1 * 0xd] != (code *)0x0) {
    uVar3 = (*(code *)(&DAT_004f7708)[iVar1 * 0xd])(param_1,param_2,param_3);
  }
  return uVar3;
}


