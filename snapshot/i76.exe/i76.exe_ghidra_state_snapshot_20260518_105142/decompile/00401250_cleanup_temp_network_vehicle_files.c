/*
 * Program: i76.exe
 * Function: cleanup_temp_network_vehicle_files
 * Entry: 00401250
 * Signature: undefined __stdcall cleanup_temp_network_vehicle_files(void)
 */


/* i76 second-pass rename
   old_name: FUN_00401250
   suggested_name: cleanup_temp_network_vehicle_files
   basis: References NVCL/*.vcf and _unlink; likely cleanup for generated network vehicle files. */

void cleanup_temp_network_vehicle_files(void)

{
  DAT_00501818 = 0;
  DAT_00501780 = 0;
  team_score_table_context_helper_00452910();
  _unlink(s_NVCL___vcf_004c209c);
  return;
}


