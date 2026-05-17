/*
 * Program: i76.exe
 * Function: initialize_classifier_display
 * Entry: 00461810
 * Signature: undefined __stdcall initialize_classifier_display(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence: clasfn */

void initialize_classifier_display(void)

{
  int *piVar1;
  int *piVar2;
  LPVOID pvVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  piVar5 = g_queued_world_object_class_callback_list;
  do {
    while( true ) {
      if (piVar5 == (int *)0x0) {
        return;
      }
      piVar1 = (int *)*piVar5;
      pvVar3 = release_world_object_tree_reference((LPVOID)piVar5[2],s_clasfn_004f7c5c);
      piVar2 = DAT_0054b208;
      if (pvVar3 == (LPVOID)0x0) break;
      iVar6 = *(int *)((int)pvVar3 + 0x6c);
      iVar4 = is_collapsible_special_world_object_class(iVar6);
      if ((iVar4 != 0) && (iVar6 != 4)) {
        iVar6 = 2;
      }
      iVar4 = 0;
      piVar5 = &g_world_object_class_callback_table;
      do {
        if (*piVar5 == iVar6) goto LAB_004618b6;
        piVar5 = piVar5 + 0xd;
        iVar4 = iVar4 + 1;
      } while (piVar5 < s_clasfn_004f7c5c);
      iVar4 = 0;
LAB_004618b6:
      piVar5 = piVar1;
      if ((code *)(&DAT_004f770c)[iVar4 * 0xd] != (code *)0x0) {
        (*(code *)(&DAT_004f770c)[iVar4 * 0xd])(pvVar3);
      }
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
    piVar5 = piVar1;
  } while( true );
}


