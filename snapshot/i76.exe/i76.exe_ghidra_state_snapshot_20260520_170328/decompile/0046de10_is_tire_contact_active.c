/*
 * Program: i76.exe
 * Function: is_tire_contact_active
 * Entry: 0046de10
 * Signature: undefined4 __cdecl is_tire_contact_active(int param_1)
 */


/* [cgpt i76.exe vehicle suspension/contact renames v32; confidence=high] Returns tire child
   contact-active state. */

undefined4 __cdecl is_tire_contact_active(int param_1)

{
                    /* I76 semantic baseline: is_tire_contact_active
                       Returns whether tire contact is active. */
  return *(undefined4 *)(*(int *)(param_1 + 0x70) + 0x44);
}


