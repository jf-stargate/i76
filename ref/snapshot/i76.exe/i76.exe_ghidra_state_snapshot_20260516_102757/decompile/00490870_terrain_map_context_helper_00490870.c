/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00490870
 * Entry: 00490870
 * Signature: undefined __stdcall terrain_map_context_helper_00490870(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00490870. Remove
   duplicated terrain wording. */

void terrain_map_context_helper_00490870(void)

{
  int iVar1;
  char *pcVar2;
  byte *pbVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  piVar4 = &DAT_005a4588;
  pcVar2 = (char *)&DAT_005a45c8;
  do {
    load_localized_m16_texture_resource(piVar4,pcVar2);
    pcVar2 = pcVar2 + 0x10;
    piVar4 = piVar4 + 2;
  } while (pcVar2 < &DAT_005a4618);
  pbVar3 = (byte *)&DAT_005a45c8;
  puVar5 = &DAT_005a4588;
  for (iVar1 = 0xe; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  puVar5 = &DAT_005a4588;
  do {
    if (pbVar3 < (byte *)0x5a4618) {
      load_fullres_texture_list(puVar5,pbVar3);
    }
    else {
      *puVar5 = DAT_005a45a8;
      puVar5[1] = DAT_005a45ac;
    }
    pbVar3 = pbVar3 + 0x10;
    puVar5 = puVar5 + 2;
  } while ((int)pbVar3 < 0x5a4638);
  return;
}


