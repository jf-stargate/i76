/*
 * Program: i76.exe
 * Function: spawn_random_chunk_child_object
 * Entry: 004a1810
 * Signature: undefined4 __cdecl spawn_random_chunk_child_object(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: creates .geo child object from chunk table and attaches to
   world */

undefined4 __cdecl spawn_random_chunk_child_object(int param_1)

{
  byte *_Src;
  LPVOID pvVar1;
  float *pfVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  float *pfVar8;
  int *piVar9;
  int iVar10;
  char local_b1;
  int *local_b0;
  int local_ac;
  int *local_a8;
  int local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  uint local_94;
  int local_90;
  float local_8c [19];
  float local_40 [16];
  
  local_94 = (param_1 * 0x6cd + 0xaabU) % 0x71;
  if (local_94 < 0x71) {
    for (piVar7 = (int *)(&DAT_005a8118)[local_94]; piVar7 != (int *)0x0;
        piVar7 = (int *)piVar7[0x11b]) {
      if (*piVar7 == param_1) goto LAB_004a1860;
    }
  }
  piVar7 = (int *)0x0;
LAB_004a1860:
  if (piVar7 == (int *)0x0) {
    return 0;
  }
  local_a4 = rand();
  local_a4 = local_a4 % (int)(uint)*(ushort *)(piVar7 + 1);
  local_b0 = piVar7 + local_a4 * 0x1c;
  local_a8 = local_b0 + 2;
  pvVar1 = (LPVOID)create_vehicle_child_object_and_copy_ids(0,local_a8);
  pfVar2 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
  pfVar8 = local_8c + 3;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar8 = pfVar8 + 1;
  }
  pfVar2 = compose_matrix_or_transform_a(local_40,(float *)(local_b0 + 4),local_8c + 3);
  pfVar8 = (float *)((int)pvVar1 + 0x18);
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pfVar8 = *pfVar2;
    pfVar2 = pfVar2 + 1;
    pfVar8 = pfVar8 + 1;
  }
  *(int *)((int)pvVar1 + 0x84) = local_b0[0x14];
  *(int *)((int)pvVar1 + 0x88) = local_b0[0x15];
  *(int *)((int)pvVar1 + 0x8c) = local_b0[0x16];
  *(int *)((int)pvVar1 + 0x90) = local_b0[0x17];
  piVar4 = local_b0 + 0x18;
  piVar9 = (int *)((int)pvVar1 + 0x94);
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar9 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar9 = piVar9 + 1;
  }
  *(undefined4 *)((int)pvVar1 + 0x10) = 0;
  set_world_object_class_and_register_runtime((int)pvVar1,0x35);
  if (*(int *)((int)pvVar1 + 0x70) == 0) {
    unlink_and_release_world_object_node_refcounted(pvVar1,s_chnkmgr_004fe71c);
  }
  else {
    iVar10 = 0;
    iVar5 = 0;
    pcVar3 = format_8char_resource_basename_with_suffix(*local_a8,local_a8[1],s__geo_004fe724);
    cache_add_entry((int)pvVar1,pcVar3,iVar5,iVar10);
    iVar5 = piVar7[0x11a];
    local_ac = iVar5;
    if (iVar5 != 0) {
      ensure_world_object_geometry_variant_binding((int)pvVar1,0);
      if (*(int *)((int)pvVar1 + 0x5c) != 0) {
        local_90 = *(int *)(*(int *)((int)pvVar1 + 0x5c) + 0x14);
        _Src = (byte *)(local_90 + 0x20);
        if (*(char *)(local_90 + 0x20) != '\0') {
          iVar10 = -1;
          iVar5 = sscanf((char *)_Src,&DAT_004fe738,&local_b1);
          if (iVar5 == 0) {
            iVar5 = strncmp(s_V1_BO_DY_004fe72c,(char *)_Src,8);
            if (iVar5 == 0) {
              iVar10 = 0xc;
            }
          }
          else {
            pcVar3 = strchr(PTR_s_1234567890AB_004fe708,(int)local_b1);
            iVar10 = (int)pcVar3 - (int)PTR_s_1234567890AB_004fe708;
          }
          iVar5 = local_ac;
          if (-1 < iVar10) {
            bind_texture_resource_to_object_slot
                      ((uint)pvVar1,_Src,(byte *)(iVar10 * 0x10 + local_ac));
            goto LAB_004a1a34;
          }
        }
        if (*(int *)(local_90 + 0x30) != 0) {
          bind_chunk_texture_slot_from_material((uint)pvVar1,*(int *)(local_90 + 0x30),iVar5);
        }
      }
    }
LAB_004a1a34:
    attach_world_object_as_first_child((int)pvVar1,DAT_005aaac4);
    if (DAT_005aaac8 == (LPVOID)0x0) {
      _DAT_005aaacc = *(undefined4 *)((int)pvVar1 + 0x70);
      DAT_005aaac8 = pvVar1;
    }
    local_a0 = 0;
    local_8c[0] = 0.0;
    local_9c = 0x41200000;
    local_98 = 0;
    local_8c[1] = 10.0;
    local_8c[2] = 0.0;
    world_instance_id_lookup_context_helper_004ad2e0((int)pvVar1,local_8c);
  }
  piVar4 = local_b0 + 0x1e;
  piVar9 = local_a8;
  for (uVar6 = (((uint)*(ushort *)(piVar7 + 1) - local_a4) + -1) * 0x70 >> 2; uVar6 != 0;
      uVar6 = uVar6 - 1) {
    *piVar9 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar9 = piVar9 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(char *)piVar9 = (char)*piVar4;
    piVar4 = (int *)((int)piVar4 + 1);
    piVar9 = (int *)((int)piVar9 + 1);
  }
  *(short *)(piVar7 + 1) = (short)piVar7[1] + -1;
  if (((((short)piVar7[1] == 0) && (param_1 != 0)) && (local_94 < 0x71)) &&
     (piVar7 = (int *)(&DAT_005a8118)[local_94], piVar7 != (int *)0x0)) {
    if (*piVar7 == param_1) {
      (&DAT_005a8118)[local_94] = piVar7[0x11b];
      piVar4 = piVar7;
    }
    else {
      piVar4 = (int *)piVar7[0x11b];
      if ((int *)piVar7[0x11b] == (int *)0x0) goto LAB_004a1b43;
      do {
        piVar9 = piVar4;
        if (*piVar9 == param_1) {
          piVar7[0x11b] = piVar9[0x11b];
          piVar4 = piVar9;
          break;
        }
        piVar4 = (int *)piVar9[0x11b];
        piVar7 = piVar9;
      } while (piVar4 != (int *)0x0);
    }
    if (piVar4 != (int *)0x0) {
      HeapFree(DAT_005aaac0,0,piVar4);
    }
  }
LAB_004a1b43:
  dispatch_queued_world_object_class_callbacks();
  return 1;
}


