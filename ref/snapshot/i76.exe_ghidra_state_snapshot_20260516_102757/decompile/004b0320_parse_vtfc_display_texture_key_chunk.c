/*
 * Program: i76.exe
 * Function: parse_vtfc_display_texture_key_chunk
 * Entry: 004b0320
 * Signature: undefined4 __cdecl parse_vtfc_display_texture_key_chunk(int param_1, char * param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=medium-high] Alternative VTFC callback used
   by display/key descriptor table. */

undefined4 __cdecl parse_vtfc_display_texture_key_chunk(int param_1,char *param_2)

{
  strncpy(param_2,(char *)(param_1 + 0x15),0xf);
  param_2[0xf] = '\0';
  return 1;
}


