/*
 * Program: i76.exe
 * Function: world_object_geometry_context_helper_004588b0
 * Entry: 004588b0
 * Signature: int __cdecl world_object_geometry_context_helper_004588b0(int param_1, char * param_2)
 */


/* cgpt label refinement v19: was world_object_geometry_world_object_geometry_helper_004588b0.
   Remove duplicated world_object_geometry wording. */

int __cdecl world_object_geometry_context_helper_004588b0(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  ensure_world_object_geometry_variant_binding(param_1,4);
  if ((*(int *)(param_1 + 0x5c) != 0) &&
     (iVar1 = *(int *)(*(int *)(param_1 + 0x5c) + 0x14), iVar1 != 0)) {
    iVar1 = _strnicmp((char *)(iVar1 + 0x20),param_2,0x10);
    if (iVar1 == 0) {
      iVar2 = param_1;
    }
  }
  if (iVar2 == 0) {
    if (*(int *)(param_1 + 100) != 0) {
      iVar2 = world_object_geometry_context_helper_004588b0(*(int *)(param_1 + 100),param_2);
    }
    if ((iVar2 == 0) && (*(int *)(param_1 + 0x60) != 0)) {
      iVar2 = world_object_geometry_context_helper_004588b0(*(int *)(param_1 + 0x60),param_2);
    }
  }
  return iVar2;
}


