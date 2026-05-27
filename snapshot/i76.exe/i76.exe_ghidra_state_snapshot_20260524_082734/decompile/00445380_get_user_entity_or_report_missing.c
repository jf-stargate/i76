/*
 * Program: i76.exe
 * Function: get_user_entity_or_report_missing
 * Entry: 00445380
 * Signature: undefined __stdcall get_user_entity_or_report_missing(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: No User Entity present */

void get_user_entity_or_report_missing(void)

{
  byte bVar1;
  bool bVar2;
  int *piVar3;
  uint uVar4;
  undefined3 extraout_var;
  uint *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  int *piVar13;
  undefined4 *puVar14;
  int local_240 [13];
  int local_20c [13];
  float local_1d8 [118];
  
  DAT_0052bbc8 = 0;
  DAT_004f22f8 = 1;
  puVar6 = &DAT_00608c80;
  for (iVar7 = 0x76; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  piVar3 = (int *)get_active_player_or_camera_world_object_entry();
  if (piVar3 == (int *)0x0) {
    report_error();
    return;
  }
  uVar4 = entity_instance_table_context_helper_00457570(piVar3,0x1d);
  if (uVar4 != 0) {
    if (*(int *)(*piVar3 + 0x70) != 0) {
      *(uint *)(*(int *)(*piVar3 + 0x70) + 0x42c) = uVar4;
      world_object_geometry_context_helper_00458860(uVar4,1);
    }
    bVar2 = ensure_world_object_geometry_variant_binding(uVar4,4);
    if (((CONCAT31(extraout_var,bVar2) == 1) && (*(int *)(uVar4 + 0x5c) != 0)) &&
       (iVar7 = *(int *)(*(int *)(uVar4 + 0x5c) + 0x14), iVar7 != 0)) {
      do {
        if (*(char *)(iVar7 + 0x20) != '\0') break;
        iVar7 = *(int *)(iVar7 + 0x30);
      } while (iVar7 != 0);
      if (iVar7 != 0) {
        pbVar10 = (byte *)(iVar7 + 0x20);
        puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache(pbVar10);
        if (puVar5 != (uint *)0x0) {
          uVar8 = 0xffffffff;
          pbVar11 = pbVar10;
          do {
            pbVar12 = pbVar11;
            if (uVar8 == 0) break;
            uVar8 = uVar8 - 1;
            pbVar12 = pbVar11 + 1;
            bVar1 = *pbVar11;
            pbVar11 = pbVar12;
          } while (bVar1 != 0);
          uVar8 = ~uVar8;
          pbVar11 = pbVar12 + -uVar8;
          pbVar12 = (byte *)&DAT_0052bba0;
          DAT_0052bbc0 = uVar4;
          for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
            *(undefined4 *)pbVar12 = *(undefined4 *)pbVar11;
            pbVar11 = pbVar11 + 4;
            pbVar12 = pbVar12 + 4;
          }
          for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
            *pbVar12 = *pbVar11;
            pbVar11 = pbVar11 + 1;
            pbVar12 = pbVar12 + 1;
          }
          uVar8 = *puVar5;
          uVar9 = (int)(puVar5[1] << 3) >> 3;
          piVar3 = (int *)construct_bitmap_surface_context
                                    (local_20c,uVar8,uVar9,(int)(puVar5 + 2),0);
          piVar13 = local_240;
          for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
            *piVar13 = *piVar3;
            piVar3 = piVar3 + 1;
            piVar13 = piVar13 + 1;
          }
          puVar6 = (undefined4 *)construct_bitmap_surface_context(local_20c,uVar8,uVar9,0,0);
          puVar14 = &DAT_00608c40;
          for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar14 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar14 = puVar14 + 1;
          }
          blit_bitmap_surface_context_clipped_with_palette_blend
                    (&DAT_00608c40,local_240,0,(uint *)0x0,(uint *)0x0);
          release_bitmap_surface_context(local_240);
          release_vqm_texture_cache_reference_by_name((char *)pbVar10);
          puVar6 = (undefined4 *)
                   materialize_texture_binding_surface_context(local_20c,uVar4,pbVar10);
          puVar14 = &DAT_00608c00;
          for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar14 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar14 = puVar14 + 1;
          }
          DAT_0052bbc4 = bind_or_load_texture_set_for_object(uVar4,pbVar10,0);
          puVar6 = (undefined4 *)
                   software_raster_command_context_helper_00472220
                             (local_1d8,0x608c00,0.5235988,0x3f800000,100.0,1.0);
          puVar14 = &DAT_00608c80;
          for (iVar7 = 0x76; iVar7 != 0; iVar7 = iVar7 + -1) {
            *puVar14 = *puVar6;
            puVar6 = puVar6 + 1;
            puVar14 = puVar14 + 1;
          }
          _DAT_00608c88 = -_DAT_00608c88;
          _DAT_00608c8c = -_DAT_00608c8c;
          piVar3 = (int *)get_active_player_or_camera_world_object_entry();
          if (((DAT_00654b8c._1_1_ == '\0') || (DAT_005280d4 != 0)) || (DAT_0054ac68 != 0)) {
            DAT_004f22f8 = 0;
          }
          else {
            DAT_004f22f8 = 1;
          }
          if (((piVar3 != (int *)0x0) && (*piVar3 != 0)) &&
             (iVar7 = *(int *)(*piVar3 + 0x70), iVar7 != 0)) {
            if (DAT_004f22f8 == 0) {
              get_world_object_class_id(*(int *)(iVar7 + 0x42c),1);
              return;
            }
            world_object_geometry_context_helper_00458860(*(int *)(iVar7 + 0x42c),1);
          }
        }
      }
    }
  }
  return;
}


