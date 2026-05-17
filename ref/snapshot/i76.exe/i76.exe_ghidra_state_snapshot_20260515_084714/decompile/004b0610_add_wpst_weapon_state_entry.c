/*
 * Program: i76.exe
 * Function: add_wpst_weapon_state_entry
 * Entry: 004b0610
 * Signature: undefined4 __cdecl add_wpst_weapon_state_entry(int param_1, int * param_2)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium-high] Alternate WPST callback.
   Adds/applies a weapon state entry through the runtime weapon-state helper. */

undefined4 __cdecl add_wpst_weapon_state_entry(int param_1,int *param_2)

{
  apply_weapon_state_entry
            (*param_2,*(int *)(param_1 + 8),*(int *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0xc))
  ;
  return 1;
}


