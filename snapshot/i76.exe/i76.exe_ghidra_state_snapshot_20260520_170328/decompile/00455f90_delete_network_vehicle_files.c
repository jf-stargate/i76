/*
 * Program: i76.exe
 * Function: delete_network_vehicle_files
 * Entry: 00455f90
 * Signature: undefined __stdcall delete_network_vehicle_files(void)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Deletes temporary network
   vehicle VCF files matching NVCL/*.vcf. */

void delete_network_vehicle_files(void)

{
  _unlink(s_NVCL___vcf_004c209c);
  return;
}


