/*
 * Program: I76EDIT.EXE
 * Function: i76edit_show_edit_terrain_layer_dialog
 * Entry: 004153e0
 * Signature: undefined __cdecl i76edit_show_edit_terrain_layer_dialog(int param_1)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References 'Edit Terrain Layer' and 'Modify the Terrain
   Layer.'; called from main window command dispatcher. */

void __cdecl i76edit_show_edit_terrain_layer_dialog(int param_1)

{
  int *piVar1;
  
  piVar1 = &DAT_00434ae0;
  do {
    if (*piVar1 == *(int *)(param_1 + 4)) {
      *(int **)(param_1 + 0xc) = piVar1 + 1;
      i76edit_set_status_bar_text((char *)((int)piVar1 + 0x22));
    }
    piVar1 = piVar1 + 0x1d;
  } while (piVar1 < &DAT_00435878);
  return;
}


