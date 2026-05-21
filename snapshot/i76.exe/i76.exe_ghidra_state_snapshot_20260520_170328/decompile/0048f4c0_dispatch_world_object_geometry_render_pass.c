/*
 * Program: i76.exe
 * Function: dispatch_world_object_geometry_render_pass
 * Entry: 0048f4c0
 * Signature: undefined __cdecl dispatch_world_object_geometry_render_pass(int param_1, float * param_2)
 */


/* [cgpt i76.exe GEO lighting/render renames v33; confidence=high] Dispatches between primary and
   secondary world-object geometry tree render passes based on object/list state. */

void __cdecl dispatch_world_object_geometry_render_pass(int param_1,float *param_2)

{
  if (*(int *)(param_1 + 0x38) != 0) {
    render_world_object_geometry_tree_pass_primary((int *)(param_1 + 0x1c),param_2);
    return;
  }
  render_world_object_geometry_tree_pass_secondary((int *)(param_1 + 0x1c),param_2);
  return;
}


