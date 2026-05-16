/*
 * Program: i76.exe
 * Function: bind_optional_vtfc_texture_map_slot
 * Entry: 004b0150
 * Signature: undefined4 __cdecl bind_optional_vtfc_texture_map_slot(uint param_1, byte * param_2, byte * param_3)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Binds optional VTF/VTFC texture map
   slot when the slot value is not NULL. */

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


