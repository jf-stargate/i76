/*
 * Program: i76.exe
 * Function: set_world_object_class_and_register_runtime
 * Entry: 00461970
 * Signature: undefined __cdecl set_world_object_class_and_register_runtime(int param_1, int param_2)
 */


/* [cgpt i76.exe geometry/texture rename v8; confidence=high] Stores object class, maps special
   classes through class predicate/table, optionally allocates class runtime data, and registers
   object in runtime class lists. */

void __cdecl set_world_object_class_and_register_runtime(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  *(int *)(param_1 + 0x6c) = param_2;
  iVar1 = is_collapsible_special_world_object_class(param_2);
  if ((iVar1 != 0) && (param_2 != 4)) {
    param_2 = 2;
  }
  iVar1 = 0;
  piVar2 = &g_world_object_class_callback_table;
  do {
    if (*piVar2 == param_2) goto LAB_004619ac;
    piVar2 = piVar2 + 0xd;
    iVar1 = iVar1 + 1;
  } while (piVar2 < s_clasfn_004f7c5c);
  iVar1 = 0;
LAB_004619ac:
  if (0 < iVar1) {
    if ((code *)(&DAT_004f76e4)[iVar1 * 0xd] != (code *)0x0) {
      uVar3 = (*(code *)(&DAT_004f76e4)[iVar1 * 0xd])();
      *(undefined4 *)(param_1 + 0x70) = uVar3;
    }
    increment_refcount_recursive_for_object_tree(param_1,s_clasfn_004f7c5c);
    g_queued_world_object_class_callback_list =
         allocate_linked_list_node_3field
                   (g_queued_world_object_class_callback_list,(undefined4 *)0x0,param_1);
    DAT_0054b208 = allocate_linked_list_node_3field
                             (DAT_0054b208,(undefined4 *)0x0,
                              g_queued_world_object_class_callback_list);
    DAT_0054b20c = DAT_0054b20c + 1;
    DAT_0054b210 = DAT_0054b210 + 1;
  }
  return;
}


