/*
 * Program: i76shell.dll
 * Function: delete_user_repair_profile_file
 * Entry: 10034e50
 * Signature: undefined __stdcall delete_user_repair_profile_file(void)
 */


void delete_user_repair_profile_file(void)

{
  _unlink(s_user_rpr_1004ce3c);
  return;
}


