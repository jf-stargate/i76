/*
 * Program: i76.exe
 * Function: dispatch_queued_world_object_class_callbacks
 * Entry: 00461b80
 * Signature: undefined __stdcall dispatch_queued_world_object_class_callbacks(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Walks queued world-object class
   callback entries, releases invalid references, invokes class descriptor callbacks, and removes
   completed entries. */

void dispatch_queued_world_object_class_callbacks(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  LPVOID pvVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  piVar3 = DAT_0054b208;
  do {
    if (piVar3 == (int *)0x0) {
      return;
    }
    piVar1 = (int *)piVar3[2];
    piVar2 = (int *)*piVar3;
    pvVar4 = release_world_object_tree_reference((LPVOID)piVar1[2],s_clasfn_004f7c5c);
    if (pvVar4 == (LPVOID)0x0) {
LAB_00461c29:
      unlink_and_free_linked_list_node_3field(&g_queued_world_object_class_callback_list,piVar1);
      DAT_0054b210 = DAT_0054b210 + -1;
    }
    else {
      iVar7 = *(int *)((int)pvVar4 + 0x6c);
      iVar5 = is_collapsible_special_world_object_class(iVar7);
      if ((iVar5 != 0) && (iVar7 != 4)) {
        iVar7 = 2;
      }
      iVar5 = 0;
      piVar6 = &g_world_object_class_callback_table;
      do {
        if (*piVar6 == iVar7) goto LAB_00461beb;
        piVar6 = piVar6 + 0xd;
        iVar5 = iVar5 + 1;
      } while (piVar6 < s_clasfn_004f7c5c);
      iVar5 = 0;
LAB_00461beb:
      if ((code *)(&DAT_004f76e8)[iVar5 * 0xd] != (code *)0x0) {
        (*(code *)(&DAT_004f76e8)[iVar5 * 0xd])(pvVar4);
      }
      if (((&DAT_004f76ec)[iVar5 * 0xd] == 0) && ((&DAT_004f76f0)[iVar5 * 0xd] == 0)) {
        finalize_released_world_object_after_damage((LPVOID)piVar1[2],s_clasfn_004f7c5c);
        goto LAB_00461c29;
      }
    }
    unlink_and_free_linked_list_node_3field((int *)&DAT_0054b208,piVar3);
    DAT_0054b20c = DAT_0054b20c + -1;
    piVar3 = piVar2;
  } while( true );
}


