/*
 * Program: i76.exe
 * Function: release_sky_texture_resources
 * Entry: 004051c0
 * Signature: undefined __stdcall release_sky_texture_resources(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Cleanup counterpart for
   sky/background texture resources. */

void release_sky_texture_resources(void)

{
  load_localized_m16_texture_resource(&DAT_00504c38,(char *)&DAT_005dce60);
  _DAT_00507c48 = 0;
  DAT_00507cd4 = 0;
  _DAT_00507cd8 = 0;
  _DAT_00507cdc = 0;
  _DAT_00507c50 = 0;
  _DAT_00507c54 = 0;
  return;
}


