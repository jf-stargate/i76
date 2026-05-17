/*
 * Program: I76EDIT.EXE
 * Function: i76edit_prepare_object_export_zone_lookup
 * Entry: 0040a680
 * Signature: undefined __cdecl i76edit_prepare_object_export_zone_lookup(int param_1)
 */


/* [cgpt_i76edit_level_renames_v5:medium] Initializes object export support structures, walks all
   object buckets 00439be8..00439d28, registers each object payload, finalizes lookup, and primes
   zone/export state.
   
   [cgpt_i76edit_level_renames_v6:medium] Prepares object export zone lookup state before OBJ
   serialization; traverses the global object bucket/list at 00439be8. */

void __cdecl i76edit_prepare_object_export_zone_lookup(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00439be8;
  thunk_FUN_0040ec40();
  do {
    for (puVar1 = (undefined4 *)*puVar2; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1
        ) {
      thunk_FUN_0040ec80(puVar1[2]);
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_00439d28);
  thunk_FUN_0040ece0();
  thunk_FUN_0040edb0(param_1);
  return;
}


