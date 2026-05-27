/*
 * Program: i76.exe
 * Function: draw_classifier_display
 * Entry: 00461a20
 * Signature: undefined __cdecl draw_classifier_display(LPVOID param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: clasfn */

void __cdecl draw_classifier_display(LPVOID param_1)

{
  int iVar1;
  int *piVar2;
  LPVOID pvVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  pvVar3 = release_world_object_tree_reference(param_1,s_clasfn_004f7c5c);
  if (pvVar3 != (LPVOID)0x0) {
    iVar1 = *(int *)((int)pvVar3 + 0x70);
    iVar6 = *(int *)((int)pvVar3 + 0x6c);
    if (iVar1 != 0) {
      iVar4 = is_collapsible_special_world_object_class(iVar6);
      if ((iVar4 != 0) && (iVar6 != 4)) {
        iVar6 = 2;
      }
      iVar4 = 0;
      piVar5 = &g_world_object_class_callback_table;
      do {
        if (*piVar5 == iVar6) goto LAB_00461a77;
        piVar5 = piVar5 + 0xd;
        iVar4 = iVar4 + 1;
      } while (piVar5 < s_clasfn_004f7c5c);
      iVar4 = 0;
LAB_00461a77:
      if ((code *)(&DAT_004f7710)[iVar4 * 0xd] != (code *)0x0) {
        (*(code *)(&DAT_004f7710)[iVar4 * 0xd])(iVar1);
      }
    }
    *(undefined4 *)((int)pvVar3 + 0x6c) = 0;
    *(undefined4 *)((int)pvVar3 + 0x70) = 0;
  }
  piVar5 = g_queued_world_object_class_callback_list;
  if (g_queued_world_object_class_callback_list != (int *)0x0) {
    while ((LPVOID)piVar5[2] != param_1) {
      piVar5 = (int *)*piVar5;
      if (piVar5 == (int *)0x0) {
        return;
      }
    }
    piVar2 = DAT_0054b208;
    if (pvVar3 != (LPVOID)0x0) {
      finalize_released_world_object_after_damage(pvVar3,s_clasfn_004f7c5c);
      piVar2 = DAT_0054b208;
    }
    for (; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
      if ((int *)piVar2[2] == piVar5) {
        unlink_and_free_linked_list_node_3field((int *)&DAT_0054b208,piVar2);
        DAT_0054b20c = DAT_0054b20c + -1;
        break;
      }
    }
    unlink_and_free_linked_list_node_3field
              ((int *)&g_queued_world_object_class_callback_list,piVar5);
    DAT_0054b210 = DAT_0054b210 + -1;
  }
  return;
}


