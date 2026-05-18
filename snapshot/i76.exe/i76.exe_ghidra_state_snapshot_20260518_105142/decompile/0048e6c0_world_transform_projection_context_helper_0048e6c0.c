/*
 * Program: i76.exe
 * Function: world_transform_projection_context_helper_0048e6c0
 * Entry: 0048e6c0
 * Signature: undefined __stdcall world_transform_projection_context_helper_0048e6c0(void)
 */


/* cgpt label refinement v19: was
   geometry_transform_highlight_world_transform_or_projection_helper_0048e6c0. Shorten readability
   label. */

void world_transform_projection_context_helper_0048e6c0(void)

{
  char *pcVar1;
  int *piVar2;
  
  DAT_0059c490 = 0;
  piVar2 = (int *)&DAT_0059c3a0;
  pcVar1 = &DAT_0059c1c0;
  do {
    load_localized_m16_texture_resource(piVar2,pcVar1);
    pcVar1 = pcVar1 + 0x10;
    piVar2 = piVar2 + 2;
  } while (pcVar1 < &DAT_0059c3a0);
  world_reader_record_table_context_helper_004b8980();
  return;
}


