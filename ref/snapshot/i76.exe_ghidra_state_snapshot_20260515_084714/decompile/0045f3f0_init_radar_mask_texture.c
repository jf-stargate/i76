/*
 * Program: i76.exe
 * Function: init_radar_mask_texture
 * Entry: 0045f3f0
 * Signature: undefined __stdcall init_radar_mask_texture(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_0045f3f0
   suggested_name: init_radar_mask_texture
   basis: References zradmask.map and radar mask diagnostic. */

void init_radar_mask_texture(void)

{
  uint *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_34 [13];
  
  _DAT_0054b16c = 0;
  DAT_0054b1f0 = HeapCreate(0,0,0);
  DAT_0054b1f4 = HeapCreate(0,0,0);
  DAT_0054b1f8 = HeapCreate(0,0,0);
  DAT_0054b1ec = 0;
  entity_instance_id_allocate_context_helper_00457270(initialize_radar_context);
  register_world_object_tree_callback(&LAB_0045f720);
  puVar1 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)s_zradmask_map_004f7684);
  if (puVar1 == (uint *)0x0) {
    DAT_0054b200 = 0;
    report_chunk_parse_error();
  }
  else {
    DAT_0054b200 = 1;
    puVar2 = (undefined4 *)
             construct_bitmap_surface_context
                       (local_34,*puVar1,(int)(puVar1[1] << 3) >> 3,(int)(puVar1 + 2),0);
    puVar5 = &DAT_0054b030;
    for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  DAT_0054b1fc = 0;
  iVar4 = 0;
  piVar3 = &DAT_0054b170;
  do {
    iVar4 = iVar4 + 1;
    *piVar3 = iVar4;
    piVar3 = piVar3 + 1;
  } while ((int)piVar3 < 0x54b1e5);
  *(undefined4 *)(&DAT_0054b16c + iVar4 * 4) = 0;
  return;
}


