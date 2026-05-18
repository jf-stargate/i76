/*
 * Program: I76EDIT.EXE
 * Function: i76edit_release_render_terrain_pipeline
 * Entry: 00401212
 * Signature: undefined __cdecl i76edit_release_render_terrain_pipeline(ushort * param_1, uint * param_2, ushort * param_3, uint * param_4, ushort * param_5, ushort * param_6, ushort * param_7, ushort * param_8, uint * param_9, uint * param_10, uint * param_11)
 */


void __cdecl
i76edit_release_render_terrain_pipeline
          (ushort *param_1,uint *param_2,ushort *param_3,uint *param_4,ushort *param_5,
          ushort *param_6,ushort *param_7,ushort *param_8,uint *param_9,uint *param_10,
          uint *param_11)

{
  int *_Memory;
  uint *unaff_EBX;
  uint *unaff_EBP;
  ushort *unaff_ESI;
  int iVar1;
  uint *unaff_EDI;
  int iVar2;
  uint *puVar3;
  undefined8 in_stack_00000000;
  int in_stack_fffffff8;
  int in_stack_fffffffc;
  
  iVar1 = 0;
  iVar2 = 0;
  i76edit_initialize_terrain_buffers(1);
  do {
    i76edit_convert_zone_id_to_cell_xy(iVar2,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      iVar1 = iVar1 + 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x50);
  iVar2 = 0;
  do {
    i76edit_convert_zone_id_to_cell_xy(iVar2,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      _sprintf(&DAT_00439d70,s_Rendering_Zone__d_of__d__00434944,iVar2 + 1,iVar1);
      i76edit_set_status_bar_text(&DAT_00439d70);
      _Memory = i76edit_build_zone_height_or_surface_workset(in_stack_fffffff8,in_stack_fffffffc);
      i76edit_rasterize_sampler_to_128x128_word_plane(_Memory,0x80,0x80,iVar2);
      _free(_Memory);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x50);
  i76edit_set_status_bar_text(s_Merging_Terrain_map_with_Painted_00434914);
  i76edit_merge_or_normalize_terrain_planes(1);
  i76edit_set_status_bar_text(s_Processing_Grading_lines__004348f4);
  do {
    iVar2 = thunk_FUN_0040fa20(DAT_01641978);
  } while (iVar2 != 0);
  i76edit_set_status_bar_text(s_Grading_Objects__004348e0);
  i76edit_refresh_exportable_object_zone_ids();
  i76edit_set_status_bar_text(s_Rendering_Roads__004348cc);
  do {
    iVar2 = i76edit_export_grade_debug_for_roads(DAT_0043c544);
  } while (iVar2 != 0);
  i76edit_set_status_bar_text(s_Grading_Objects__004348e0);
  puVar3 = (uint *)0x0;
  i76edit_refresh_exportable_object_zone_ids();
  i76edit_set_status_bar_text(s_Smoothing_Roads__004348b8);
  do {
    i76edit_convert_zone_id_to_cell_xy((int)puVar3,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      thunk_FUN_00422870(puVar3);
    }
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((int)puVar3 < 0x50);
  puVar3 = (uint *)0x0;
  i76edit_set_status_bar_text(s_Smoothing_Roads___Pass_2__00434898);
  do {
    i76edit_convert_zone_id_to_cell_xy((int)puVar3,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      thunk_FUN_00422870(puVar3);
    }
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((int)puVar3 < 0x50);
  puVar3 = (uint *)0x0;
  i76edit_set_status_bar_text(s_Smoothing_Roads___Pass_3__00434878);
  do {
    i76edit_convert_zone_id_to_cell_xy((int)puVar3,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      thunk_FUN_00422870(puVar3);
    }
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((int)puVar3 < 0x50);
  puVar3 = (uint *)0x0;
  i76edit_set_status_bar_text(s_Smoothing_Roads___Pass_4__00434858);
  do {
    i76edit_convert_zone_id_to_cell_xy((int)puVar3,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      thunk_FUN_00422870(puVar3);
    }
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((int)puVar3 < 0x50);
  i76edit_set_status_bar_text(s_Merging_all_maps__00434840);
  puVar3 = (uint *)0x0;
  i76edit_merge_or_normalize_terrain_planes(0);
  i76edit_set_status_bar_text(s_Setting_CliffBits_00434828);
  do {
    i76edit_convert_zone_id_to_cell_xy((int)puVar3,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      i76edit_build_zone_128x128_packed_height_surface_alt
                (puVar3,unaff_EBP,unaff_EDI,unaff_ESI,unaff_EBX,in_stack_fffffff8,in_stack_fffffffc,
                 in_stack_00000000,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 param_9,param_10,param_11);
    }
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((int)puVar3 < 0x50);
  iVar2 = 0;
  i76edit_set_status_bar_text(s_Filling_objects_with_current_hei_004347fc);
  i76edit_refresh_object_zone_membership_from_zone_map();
  do {
    i76edit_convert_zone_id_to_cell_xy(iVar2,(int *)&stack0xfffffff8,(int *)&stack0xfffffffc);
    if (in_stack_fffffff8 != -1) {
      _sprintf(&DAT_00439d70,s_Painting_Zone__d_of__d__004347e0,iVar2 + 1,iVar1);
      i76edit_set_status_bar_text(&DAT_00439d70);
      i76edit_export_height_txt_debug_view(iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x50);
  i76edit_set_status_bar_text(s_Ready__00434590);
  return;
}


