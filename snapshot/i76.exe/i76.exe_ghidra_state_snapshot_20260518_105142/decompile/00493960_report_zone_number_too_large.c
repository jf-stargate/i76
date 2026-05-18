/*
 * Program: i76.exe
 * Function: report_zone_number_too_large
 * Entry: 00493960
 * Signature: undefined4 __cdecl report_zone_number_too_large(int param_1, int * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence Zone Map
   
   [cgpt_i76exe_runtime_level_loader_v1] proposed=i76_runtime_parse_zmap_chunk :: ZMAP handler.
   Reads active zone count from chunk payload byte 0, copies 80x80 zone map from payload+1, and
   validates zone ids. */

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
  puVar4 = &g_runtime_zmap_80x80_u8;
  g_runtime_active_zone_count = iVar2;
  for (iVar1 = 0x640; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar1 = 0;
  do {
    if (iVar2 <= *(char *)((int)&g_runtime_zmap_80x80_u8 + iVar1)) {
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


