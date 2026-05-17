/*
 * Program: i76.exe
 * Function: definition_record_parser_context_helper_00449610
 * Entry: 00449610
 * Signature: undefined __stdcall definition_record_parser_context_helper_00449610(void)
 */


/* cgpt label refinement v18: was definition_record_parser_definition_parser_helper_00449610. Remove
   duplicated parser wording. */

void definition_record_parser_context_helper_00449610(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  g_texture_set_cache_heap = HeapCreate(0,0,0);
  g_texture_slot_binding_heap = HeapCreate(0,0,0);
  g_texture_object_binding_list_heap = HeapCreate(0,0,0);
  g_texture_name_array_heap = HeapCreate(0,0,0);
  puVar2 = &g_texture_set_cache_hash;
  for (iVar1 = 0x7ed; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &g_texture_slot_binding_hash;
  for (iVar1 = 0x7ed; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  puVar2 = &g_texture_bindings_by_object_hash;
  for (iVar1 = 0x71; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


