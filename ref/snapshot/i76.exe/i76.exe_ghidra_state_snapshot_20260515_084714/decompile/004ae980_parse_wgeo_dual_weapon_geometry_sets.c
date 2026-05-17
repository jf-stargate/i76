/*
 * Program: i76.exe
 * Function: parse_wgeo_dual_weapon_geometry_sets
 * Entry: 004ae980
 * Signature: bool __cdecl parse_wgeo_dual_weapon_geometry_sets(int param_1, int param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] WGEO callback: expands two parallel
   weapon geometry part sets using generic 0x64-byte part records and .geo cache entries. */

bool __cdecl parse_wgeo_dual_weapon_geometry_sets(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int local_40 [8];
  int local_20 [8];
  
  piVar2 = local_40;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  fill_resource_lookup_key_stride100(param_1 + 0xc,local_40,0x10,*(int *)(param_1 + 8));
  iVar1 = instantiate_part_record_array_with_geo_cache
                    (local_40,*(int **)(param_2 + 0x10),4,2,*(int *)(param_1 + 8),(undefined *)0x0);
  if (iVar1 == 0) {
    return false;
  }
  iVar1 = instantiate_part_record_array_with_geo_cache
                    (local_20,*(int **)(param_2 + 0x14),4,2,*(int *)(param_1 + 8),(undefined *)0x0);
  return iVar1 != 0;
}


