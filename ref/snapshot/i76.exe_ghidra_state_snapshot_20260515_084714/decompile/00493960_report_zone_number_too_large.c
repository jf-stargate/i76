/*
 * Program: i76.exe
 * Function: report_zone_number_too_large
 * Entry: 00493960
 * Signature: undefined4 __cdecl report_zone_number_too_large(int param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence Zone Map */

undefined4 __cdecl report_zone_number_too_large(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_2 != (int *)0x0) {
    *param_2 = 0;
  }
  iVar2 = (int)*(char *)(param_1 + 8);
  puVar3 = (undefined4 *)(param_1 + 9);
  puVar4 = &DAT_005a4768;
  DAT_005a4620 = iVar2;
  for (iVar1 = 0x640; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar1 = 0;
  do {
    if (iVar2 <= *(char *)((int)&DAT_005a4768 + iVar1)) {
      report_chunk_parse_error();
      return 0;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1900);
  if (param_2 != (int *)0x0) {
    *param_2 = iVar2;
  }
  return 1;
}


