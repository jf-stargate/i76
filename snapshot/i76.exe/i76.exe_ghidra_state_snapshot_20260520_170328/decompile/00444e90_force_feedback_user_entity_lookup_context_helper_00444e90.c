/*
 * Program: i76.exe
 * Function: force_feedback_user_entity_lookup_context_helper_00444e90
 * Entry: 00444e90
 * Signature: undefined __stdcall force_feedback_user_entity_lookup_context_helper_00444e90(void)
 */


/* cgpt label refinement v18: was player_force_feedback_user_entity_lookup_helper_00444e90. Shorten
   readability label; force-feedback/user entity context is sufficient. */

void force_feedback_user_entity_lookup_context_helper_00444e90(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = DAT_0052bb98;
  if (DAT_0052bb98 != (undefined4 *)0x0) {
    do {
      puVar2 = DAT_0052bb98;
      DAT_0052bb98 = (undefined4 *)*DAT_0052bb98;
      xfree_global_heap(puVar2);
    } while (DAT_0052bb98 != puVar1);
  }
  DAT_0052bb98 = (undefined4 *)0x0;
  return;
}


