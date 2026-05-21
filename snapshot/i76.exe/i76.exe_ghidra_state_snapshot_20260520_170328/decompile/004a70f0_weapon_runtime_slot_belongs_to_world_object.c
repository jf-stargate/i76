/*
 * Program: i76.exe
 * Function: weapon_runtime_slot_belongs_to_world_object
 * Entry: 004a70f0
 * Signature: bool __cdecl weapon_runtime_slot_belongs_to_world_object(int param_1, int param_2)
 */


/* [cgpt i76.exe player vehicle runtime rename v24; confidence=high] Checks whether a weapon runtime
   slot belongs to a supplied world object. */

bool __cdecl weapon_runtime_slot_belongs_to_world_object(int param_1,int param_2)

{
  return *(int *)(&DAT_005aab20)[param_1 * 0x13] == param_2;
}


