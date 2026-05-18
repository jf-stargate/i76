/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_004909b0
 * Entry: 004909b0
 * Signature: undefined __stdcall terrain_map_context_helper_004909b0(void)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_004909b0. Remove
   duplicated terrain wording. */

void terrain_map_context_helper_004909b0(void)

{
  byte *pbVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_005a4588;
  pbVar1 = (byte *)&DAT_005a45c8;
  do {
    if (pbVar1 < (byte *)0x5a4618) {
      load_fullres_texture_list(puVar2,pbVar1);
    }
    else {
      *puVar2 = DAT_005a45a8;
      puVar2[1] = DAT_005a45ac;
    }
    pbVar1 = pbVar1 + 0x10;
    puVar2 = puVar2 + 2;
  } while ((int)pbVar1 < 0x5a4638);
  return;
}


