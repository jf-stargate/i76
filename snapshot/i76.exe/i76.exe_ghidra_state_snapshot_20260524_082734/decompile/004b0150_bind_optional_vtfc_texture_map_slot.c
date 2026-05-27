/*
 * Program: i76.exe
 * Function: bind_optional_vtfc_texture_map_slot
 * Entry: 004b0150
 * Signature: undefined4 __cdecl bind_optional_vtfc_texture_map_slot(uint param_1, byte * param_2, byte * param_3)
 */


/* [i76 level/static/material baseline v48]
   name: bind_optional_vtfc_texture_map_slot
   confidence: high
   module: material_vtfc
   Binds optional VTFC texture map slot. Useful comparison point for static GEO material lookup and
   MAP->M16/VQM fallback.
   note: Name already matches baseline. */

undefined4 __cdecl bind_optional_vtfc_texture_map_slot(uint param_1,byte *param_2,byte *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = _strnicmp((char *)param_3,s_null_004c3280,4);
  if (iVar1 != 0) {
    uVar2 = bind_texture_resource_to_object_slot(param_1,param_2,param_3);
    return uVar2;
  }
  return 1;
}


