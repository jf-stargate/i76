/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00490830
 * Entry: 00490830
 * Signature: undefined __stdcall terrain_map_context_helper_00490830(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490830. Remove
   duplicated terrain wording. */

void terrain_map_context_helper_00490830(void)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  undefined4 *puVar4;
  
  piVar3 = &DAT_005a4588;
  pcVar2 = (char *)&DAT_005a45c8;
  do {
    load_localized_m16_texture_resource(piVar3,pcVar2);
    pcVar2 = pcVar2 + 0x10;
    piVar3 = piVar3 + 2;
  } while (pcVar2 < &DAT_005a4618);
  puVar4 = &DAT_005a4588;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  return;
}


