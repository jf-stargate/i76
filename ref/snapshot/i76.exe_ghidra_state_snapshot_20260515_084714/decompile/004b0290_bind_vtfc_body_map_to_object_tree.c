/*
 * Program: i76.exe
 * Function: bind_vtfc_body_map_to_object_tree
 * Entry: 004b0290
 * Signature: undefined4 __cdecl bind_vtfc_body_map_to_object_tree(uint param_1, char * param_2, byte * param_3)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Recursively binds the VTFC
   body-map texture slot to an object tree. */

undefined4 __cdecl bind_vtfc_body_map_to_object_tree(uint param_1,char *param_2,byte *param_3)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 1;
  }
  while( true ) {
    if ((*(uint *)(param_1 + 0x10) & 0x100000) != 0) {
      ordnance_runtime_context_helper_004a11e0(param_1,param_2);
    }
    iVar1 = _strnicmp((char *)param_3,s_null_004c3280,4);
    if (iVar1 == 0) {
      iVar1 = 1;
    }
    else {
      iVar1 = bind_texture_resource_to_object_slot(param_1,(byte *)s_V1_BO_DY_map_004ffe34,param_3);
    }
    if (iVar1 == 0) break;
    if (*(uint *)(param_1 + 100) != 0) {
      bind_vtfc_body_map_to_object_tree(*(uint *)(param_1 + 100),param_2,param_3);
    }
    param_1 = *(uint *)(param_1 + 0x60);
    if (param_1 == 0) {
      return 1;
    }
  }
  return 0;
}


