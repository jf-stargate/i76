/*
 * Program: i76.exe
 * Function: load_scene_object_or_vehicle_entity_record
 * Entry: 004b7ac0
 * Signature: undefined4 __cdecl load_scene_object_or_vehicle_entity_record(int param_1)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=medium] Scene/world-object loader that
   dispatches vehicle VCF/VDF-backed object creation for vehicle-like object classes and non-vehicle
   SOBJ-style records for other classes.
   
   I76 rename v43: load_odef_object_record
   ODEF/OBJ record handler; dispatches by class byte at payload +0x5c. */

undefined4 __cdecl load_scene_object_or_vehicle_entity_record(int param_1)

{
  int *piVar1;
  int iVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  byte *pbVar6;
  undefined3 extraout_var;
  int iVar7;
  int *piVar8;
  float *pfVar9;
  LPVOID *ppvVar10;
  float *pfVar11;
  int local_98;
  LPVOID local_94 [2];
  int local_8c;
  undefined4 local_88 [12];
  undefined1 local_58 [20];
  int local_44;
  float local_40 [16];
  
  piVar1 = (int *)(param_1 + 8);
  pcVar4 = format_8char_resource_basename_with_suffix
                     (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc),(char *)0x0);
  if (pcVar4 == (char *)0x0) {
    report_error();
    return 1;
  }
  if ((*(int *)(param_1 + 100) == 1) && (iVar5 = _strnicmp(s_spawn_00500c50,pcVar4,8), iVar5 == 0))
  {
    register_odef_spawn_or_regen_transform((int)piVar1,0);
    return 1;
  }
  if ((*(int *)(param_1 + 100) == 1) && (iVar5 = _strnicmp(s_regen_00500c48,pcVar4,8), iVar5 == 0))
  {
    register_odef_spawn_or_regen_transform((int)piVar1,1);
    return 1;
  }
  ppvVar10 = local_94;
  for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
    *ppvVar10 = (LPVOID)0x0;
    ppvVar10 = ppvVar10 + 1;
  }
  switch(*(undefined4 *)(param_1 + 100)) {
  case 1:
  case 8:
  case 9:
    local_94[0] = (LPVOID)create_child_object_from_part_transform_record(0,(int)piVar1,pcVar4,1,0);
    if (local_94[0] == (LPVOID)0x0) {
      return 0;
    }
    local_98 = 0;
    pcVar4 = format_8char_resource_basename_with_suffix
                       (*piVar1,*(undefined4 *)(param_1 + 0xc),&s_dot_vcf);
    iVar5 = load_vehicle_config_for_world_object(piVar1,(byte *)local_94,pcVar4);
    break;
  case 2:
  case 3:
  case 4:
  case 7:
  case 10:
  case 0xb:
  case 0xc:
  case 0x50:
  case 0x52:
  case 0x53:
    local_94[0] = (LPVOID)create_child_object_from_part_transform_record(0,(int)piVar1,pcVar4,1,1);
    if (local_94[0] == (LPVOID)0x0) {
      return 0;
    }
    local_98 = 1;
    pbVar6 = (byte *)format_8char_resource_basename_with_suffix
                               (*piVar1,*(undefined4 *)(param_1 + 0xc),&DAT_00500640);
    bVar3 = parse_bwd2_resource_with_descriptor_table
                      (pbVar6,&g_sdf_child_descriptor_table,6,(byte *)local_94);
    if (CONCAT31(extraout_var,bVar3) != 0) {
      iVar5 = *(int *)((int)local_94[0] + 0x6c);
      if (((((iVar5 == 2) || (iVar5 == 3)) || (iVar5 == 0xc)) || (iVar5 == 0xb)) &&
         (*(int *)((int)local_94[0] + 0x70) != 0)) {
        for (iVar5 = *(int *)((int)local_94[0] + 100); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x60)) {
          iVar7 = is_transform_composed_world_object_class(iVar5);
          if (iVar7 != 0) {
            iVar7 = *(int *)(iVar5 + 0x70);
            iVar2 = (*(uint *)(iVar5 + 0x10) >> 10 & 3) * 0xd;
            world_reader_null_handler(&DAT_00500b78 + iVar2,(char *)(iVar7 + 0x10),0);
            *(undefined4 *)(iVar7 + 0x18) = *(undefined4 *)(s_null_00500bb0 + iVar2);
            *(undefined4 *)(iVar7 + 0x1c) = *(undefined4 *)(s_null_00500bb0 + iVar2 + 4);
            *(undefined4 *)(iVar7 + 0x20) = *(undefined4 *)(&DAT_00500bb8 + iVar2);
            *(undefined *)(iVar7 + 0x24) = (&DAT_00500bbc)[iVar2];
          }
          for (iVar7 = *(int *)(iVar5 + 100); iVar7 != 0; iVar7 = *(int *)(iVar7 + 0x60)) {
            mission_scrounge_record_handler(iVar7);
          }
        }
      }
      iVar5 = 1;
      break;
    }
  default:
    iVar5 = 0;
  }
  if (iVar5 == 0) {
    if (local_98 != 0) {
      draw_classifier_display(local_94[0]);
    }
    unlink_and_release_world_object_node_refcounted(local_94[0],s_wrldr_004ffd3c);
    return 0;
  }
  iVar5 = *(int *)(param_1 + 100);
  if (((iVar5 != 0x50) && (iVar5 != 0x52)) && (iVar5 != 0x53)) {
    if (local_8c == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = bind_odef_vehicle_geometry_context(local_88);
    }
    piVar8 = register_active_world_object_entry
                       ((int)local_94[0],iVar5,(int *)(-(uint)(local_44 != 0) & (uint)local_58));
    if (piVar8 != (int *)0x0) {
      entity_instance_table_context_helper_00457610(*piVar1,*(int *)(param_1 + 0xc),local_94[0]);
      return 1;
    }
    report_error();
    return 0;
  }
  pfVar9 = compose_matrix_or_transform_a
                     (local_40,(float *)(*(int *)((int)local_94[0] + 100) + 0x18),
                      (float *)((int)local_94[0] + 0x18));
  pfVar11 = (float *)(*(int *)((int)local_94[0] + 100) + 0x18);
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar11 = *pfVar9;
    pfVar9 = pfVar9 + 1;
    pfVar11 = pfVar11 + 1;
  }
  compute_world_object_bounds_and_link_global(*(int *)((int)local_94[0] + 100));
  *(undefined4 *)(*(int *)((int)local_94[0] + 100) + 0x68) = 0;
  *(undefined4 *)((int)local_94[0] + 100) = 0;
  unlink_and_release_world_object_node_refcounted(local_94[0],s_wrldr_004ffd3c);
  return 1;
}


