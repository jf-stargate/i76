/*
 * Program: i76.exe
 * Function: force_feedback_user_entity_lookup_context_helper_00444e30
 * Entry: 00444e30
 * Signature: undefined __cdecl force_feedback_user_entity_lookup_context_helper_00444e30(int param_1)
 */


/* cgpt label refinement v18: was player_force_feedback_user_entity_lookup_helper_00444e30. Shorten
   readability label; force-feedback/user entity context is sufficient. */

void __cdecl force_feedback_user_entity_lookup_context_helper_00444e30(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  DAT_0052bb98 = (undefined4 *)0x0;
  if (0 < param_1) {
    do {
      puVar2 = (undefined4 *)xalloc_global_heap(0x314);
      if (puVar2 != (undefined4 *)0x0) {
        puVar4 = puVar2;
        for (iVar3 = 0xc5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        *puVar2 = DAT_0052bb98;
        DAT_0052bb98 = puVar2;
      }
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  puVar4 = (undefined4 *)*DAT_0052bb98;
  puVar2 = DAT_0052bb98;
  while (puVar1 = puVar4, puVar1 != (undefined4 *)0x0) {
    puVar2 = puVar1;
    puVar4 = (undefined4 *)*puVar1;
  }
  *puVar2 = DAT_0052bb98;
  return;
}


