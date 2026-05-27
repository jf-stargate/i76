/*
 * Program: i76.exe
 * Function: handle_xgeo_extended_geometry_null_record
 * Entry: 004b8e20
 * Signature: bool __cdecl handle_xgeo_extended_geometry_null_record(int param_1, undefined4 * param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence null
   [cgpt-i76-v36 medium] XGEO extended geometry/null handler. */

bool __cdecl handle_xgeo_extended_geometry_null_record(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  char *local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = (char *)0x0;
  local_8 = 0;
  local_4 = 0;
  fill_resource_lookup_key_stride100(param_1 + 0xc,(int *)&local_c,3,*(int *)(param_1 + 8));
  if (param_2[1] != 0) {
    iVar2 = _strnicmp(local_c,s_null_004c3280,4);
    if (iVar2 == 0) {
      puVar1 = (undefined4 *)param_2[1];
      *puVar1 = 0x6c6c756e;
      puVar1[1] = 0;
    }
    else {
      puVar1 = (undefined4 *)param_2[1];
      *puVar1 = *(undefined4 *)local_c;
      puVar1[1] = *(undefined4 *)(local_c + 4);
    }
  }
  param_2[2] = *(undefined4 *)local_c;
  param_2[3] = *(undefined4 *)(local_c + 4);
  iVar2 = instantiate_part_record_array_with_geo_cache
                    ((int *)&local_c,(int *)*param_2,3,1,*(int *)(param_1 + 8),(undefined *)0x0);
  param_2[4] = iVar2;
  return iVar2 != 0;
}


