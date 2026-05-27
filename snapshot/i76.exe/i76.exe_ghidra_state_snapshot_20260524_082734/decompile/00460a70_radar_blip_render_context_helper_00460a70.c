/*
 * Program: i76.exe
 * Function: radar_blip_render_context_helper_00460a70
 * Entry: 00460a70
 * Signature: undefined __cdecl radar_blip_render_context_helper_00460a70(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set B v14: Readability pass set B: radar blip render context helper based
   on prior focused closure context. */

void __cdecl radar_blip_render_context_helper_00460a70(int param_1)

{
  uint *puVar1;
  int iVar2;
  float *pfVar3;
  int unaff_EBX;
  float unaff_ESI;
  float unaff_EDI;
  float *pfVar4;
  float in_stack_fffffc00;
  float in_stack_fffffc04;
  float *in_stack_fffffc08;
  float *in_stack_fffffc0c;
  undefined4 in_stack_fffffc10;
  undefined4 in_stack_fffffc14;
  undefined4 in_stack_fffffc18;
  undefined4 in_stack_fffffc1c;
  undefined4 in_stack_fffffc20;
  undefined4 in_stack_fffffc24;
  float local_228 [15];
  undefined4 local_1ec;
  uint *local_50;
  undefined1 *local_1c;
  void *local_14;
  undefined *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004be180;
  puStack_10 = &DAT_004ba0d0;
  local_14 = ExceptionList;
  local_1c = &stack0xfffffbf4;
  puVar1 = (uint *)(param_1 + 0x80);
  ExceptionList = &local_14;
  local_50 = puVar1;
  set_bitmap_surface_clip_rect
            ((int *)puVar1,0,0,*puVar1,((*(int *)(param_1 + 0x84) << 3) >> 3) * 5 >> 3);
  bitmap_surface_clip_context_helper_00474f60(puVar1,DAT_0054b168);
  iVar2 = (*(int *)(param_1 + 0x84) << 3) >> 3;
  set_bitmap_surface_clip_rect((int *)puVar1,0,iVar2 * 5 >> 3,*puVar1,iVar2);
  bitmap_surface_clip_context_helper_00474f60(puVar1,DAT_0054b1e8);
  set_bitmap_surface_clip_rect((int *)puVar1,0,0,*puVar1,(*(int *)(param_1 + 0x84) << 3) >> 3);
  pfVar3 = (float *)software_raster_command_context_helper_00472220
                              ((float *)&stack0xfffffc00,(int)puVar1,30.0,0xbf800000,500.0,1.0);
  pfVar4 = local_228;
  for (iVar2 = 0x76; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar4 = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pfVar4 = pfVar4 + 1;
  }
  software_raster_command_context_helper_00472400(local_228,10.0);
  software_raster_queue_context_helper_00472990((int)local_228,(float *)(param_1 + 0x10));
  g_runtime_terrain_render_min_or_near_bound = 0xc1200000;
  _g_runtime_terrain_render_max_or_far_bound = 0x43fa0000;
  local_8 = 0;
  raster_span_builder_context_helper_00473630();
  entity_instance_table_context_helper_00457a90
            ((float)local_228,unaff_EDI,unaff_ESI,unaff_EBX,(int)in_stack_fffffc00,in_stack_fffffc04
             ,in_stack_fffffc08,in_stack_fffffc0c,in_stack_fffffc10,in_stack_fffffc14,
             in_stack_fffffc18,in_stack_fffffc1c,in_stack_fffffc20,in_stack_fffffc24);
  render_projectile_tracer_quads_variant_a((int)local_228);
  render_active_smoke_particle_emitters(local_228);
  merge_world_object_or_geometry_state(local_228,0);
  raster_span_builder_context_helper_00473640(local_1ec);
  local_8 = 0xffffffff;
  radar_render_context_helper_00460c0b();
  return;
}


