/*
 * Program: i76.exe
 * Function: vehicle_vcf_parser_context_helper_004ade50
 * Entry: 004ade50
 * Signature: undefined4 __cdecl vehicle_vcf_parser_context_helper_004ade50(int param_1, int * param_2)
 */


/* cgpt label refinement v20: was vehicle_vcf_parse_context_helper_004ade50. Normalize parser
   wording. */

undefined4 __cdecl vehicle_vcf_parser_context_helper_004ade50(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_2[1] + 0xa70);
  do {
    if (*piVar2 == 0) break;
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 3);
  if (iVar1 != 3) {
    *(undefined4 *)(param_2[1] + 0xa70 + iVar1 * 4) = 1;
    vehicle_specials_log_tag(*param_2,*(int *)(param_1 + 8),iVar1);
  }
  return 1;
}


