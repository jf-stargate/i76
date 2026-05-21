/*
 * Program: i76.exe
 * Function: parse_ggeo_equipment_geometry_chunk
 * Entry: 004af680
 * Signature: undefined4 __cdecl parse_ggeo_equipment_geometry_chunk(int param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium-high] GGEO callback for
   equipment/gadget geometry records. */

undefined4 __cdecl parse_ggeo_equipment_geometry_chunk(int param_1,int *param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  float *pfVar7;
  int *local_b4;
  int local_b0 [6];
  int local_98 [3];
  int local_8c [3];
  float local_80 [16];
  float local_40 [16];
  
  iVar4 = *(int *)(*param_2 + 4);
  piVar5 = local_b0;
  for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  fill_resource_lookup_key_stride100(param_1 + 0xc,local_b0,0xc,*(int *)(param_1 + 8));
  iVar3 = *(int *)(iVar4 + 0xa5c);
  iVar1 = 0;
  iVar4 = iVar4 + 0x378;
  if (0 < iVar3) {
    do {
      if (*(int *)(iVar4 + 0xb0) == param_2[4]) goto LAB_004af6ec;
      iVar1 = iVar1 + 1;
      iVar4 = iVar4 + 0xfc;
    } while (iVar1 < iVar3);
  }
  iVar4 = 0;
LAB_004af6ec:
  if (iVar4 != 0) {
    if (param_2[10] < 100) {
      iVar4 = *(int *)(iVar4 + 0xb8);
    }
    else {
      iVar4 = 3;
    }
    switch(iVar4) {
    case 1:
      local_b4 = local_b0;
      break;
    case 2:
      local_b4 = local_b0 + 3;
      break;
    case 3:
      local_b4 = local_98;
      break;
    case 4:
      break;
    case 5:
      local_b4 = local_8c;
      break;
    default:
      goto switchD_004af713_default;
    }
    if (((iVar4 == 4) ||
        (iVar4 = instantiate_part_record_array_with_geo_cache
                           (local_b4,(int *)param_2[0x51],3,1,*(int *)(param_1 + 8),(undefined *)0x0
                           ), iVar4 != 0)) || (*(int *)(param_1 + 8) == 0)) {
      iVar4 = param_2[0x51];
      for (iVar3 = *(int *)(param_2[0x51] + 100); iVar3 != 0; iVar3 = *(int *)(iVar3 + 100)) {
        iVar4 = iVar3;
      }
      iVar3 = create_vehicle_child_object_and_copy_ids(iVar4,(undefined4 *)0x0);
      param_2[0x53] = iVar3;
      if (iVar3 != 0) {
        set_world_object_class_and_register_runtime(iVar3,0x29);
        piVar5 = param_2 + 0x54;
        piVar6 = (int *)(param_2[0x53] + 0x18);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar6 = *piVar5;
          piVar5 = piVar5 + 1;
          piVar6 = piVar6 + 1;
        }
        pfVar2 = (float *)compute_transform_relative_to_ancestor(local_40,iVar4,param_2[0x51]);
        pfVar7 = local_80;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar7 = *pfVar2;
          pfVar2 = pfVar2 + 1;
          pfVar7 = pfVar7 + 1;
        }
        pfVar2 = (float *)compose_matrix_or_transform_b(local_80,local_40);
        iVar4 = param_2[0x53];
        pfVar7 = local_80;
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *pfVar7 = *pfVar2;
          pfVar2 = pfVar2 + 1;
          pfVar7 = pfVar7 + 1;
        }
        pfVar2 = compose_matrix_or_transform_a(local_40,local_80,(float *)(iVar4 + 0x18));
        pfVar7 = (float *)(param_2[0x53] + 0x18);
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          *pfVar7 = *pfVar2;
          pfVar2 = pfVar2 + 1;
          pfVar7 = pfVar7 + 1;
        }
        return 1;
      }
    }
  }
switchD_004af713_default:
  return 0;
}


