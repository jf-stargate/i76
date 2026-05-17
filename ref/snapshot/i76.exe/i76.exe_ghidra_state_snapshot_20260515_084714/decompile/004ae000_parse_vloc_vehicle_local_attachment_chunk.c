/*
 * Program: i76.exe
 * Function: parse_vloc_vehicle_local_attachment_chunk
 * Entry: 004ae000
 * Signature: undefined4 __cdecl parse_vloc_vehicle_local_attachment_chunk(undefined4 * param_1, int * param_2)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] VLOC callback: handles special
   vehicle-local attachments such as needle, headlight mask, and local transform-only child objects.
    */

undefined4 __cdecl parse_vloc_vehicle_local_attachment_chunk(undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  undefined4 local_64 [14];
  undefined4 local_2c;
  undefined4 local_28;
  int local_8;
  undefined4 local_4;
  
  puVar2 = param_1;
  iVar1 = *(int *)(*param_2 + 0x70);
  iVar5 = 0;
  piVar7 = (int *)0x0;
  switch(param_1[2]) {
  case 0x23:
  case 0x24:
    puVar6 = local_64;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    strncpy((char *)local_64,s_needle_004ffcfc,8);
    local_8 = puVar2[2];
    puVar6 = puVar2 + 3;
    puVar8 = local_64 + 2;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    param_1 = local_64;
    local_2c = 0x6c6c756e;
    local_28 = 0;
    local_4 = 0;
    iVar5 = instantiate_part_record_array_with_geo_cache
                      ((int *)&param_1,(int *)*param_2,1,1,1,(undefined *)0x0);
    if (iVar5 == 0) {
      return 0;
    }
    iVar3 = 1;
    do {
      iVar9 = 0;
      iVar10 = iVar3;
      pcVar4 = format_8char_resource_basename_with_suffix(local_64[0],local_64[1],s__geo_004fe724);
      cache_add_entry(iVar5,pcVar4,iVar9,iVar10);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 5);
    if (local_8 == 0x23) {
      piVar7 = (int *)(iVar1 + 0x3f8);
    }
    else {
      piVar7 = (int *)(iVar1 + 0x3fc);
    }
    break;
  case 0x26:
    iVar5 = get_current_headlight_runtime_state();
    if (iVar5 == 1) {
      *(undefined4 *)(iVar1 + 0x440) = 0;
      return 1;
    }
    puVar6 = local_64;
    for (iVar5 = 0x19; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    strncpy((char *)local_64,s_hdlt_msk_004ffcf0,8);
    puVar6 = puVar2 + 3;
    puVar8 = local_64 + 2;
    for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8 = puVar8 + 1;
    }
    local_8 = puVar2[2];
    param_1 = local_64;
    local_2c = 0x6c6c756e;
    local_28 = 0;
    local_4 = 0;
    iVar5 = instantiate_part_record_array_with_geo_cache
                      ((int *)&param_1,(int *)0x0,1,1,1,(undefined *)0x0);
    if (iVar5 == 0) {
      return 0;
    }
    increment_refcount_recursive_for_object_tree(*param_2,s_hlight_004fac9c);
    piVar7 = (int *)(iVar1 + 0x440);
    *piVar7 = iVar5;
    *(int *)(iVar5 + 0x68) = *param_2;
    cache_add_entry(iVar5,s_hdlv_msk_geo_004ffce0,0,4);
    compute_world_object_bounds_and_link_global(iVar5);
    break;
  case 0x28:
    iVar3 = world_object_has_optional_runtime_flag(*param_2);
    if (iVar3 == 0) {
      return 1;
    }
    piVar7 = (int *)(iVar1 + 0x398);
    break;
  case 0x2a:
    *(undefined4 *)(iVar1 + 300) = param_1[0xc];
    *(undefined4 *)(iVar1 + 0x130) = param_1[0xd];
    *(undefined4 *)(iVar1 + 0x134) = param_1[0xe];
    return 1;
  }
  if (iVar5 == 0) {
    iVar5 = create_vehicle_child_object_and_copy_ids(*param_2,(undefined4 *)0x0);
    if (iVar5 == 0) {
      return 0;
    }
    set_world_object_class_and_register_runtime(iVar5,puVar2[2]);
    *(undefined4 *)(iVar5 + 0x18) = puVar2[3];
    *(undefined4 *)(iVar5 + 0x1c) = puVar2[4];
    *(undefined4 *)(iVar5 + 0x20) = puVar2[5];
    *(undefined4 *)(iVar5 + 0x24) = puVar2[6];
    *(undefined4 *)(iVar5 + 0x28) = puVar2[7];
    *(undefined4 *)(iVar5 + 0x2c) = puVar2[8];
    *(undefined4 *)(iVar5 + 0x30) = puVar2[9];
    *(undefined4 *)(iVar5 + 0x34) = puVar2[10];
    *(undefined4 *)(iVar5 + 0x38) = puVar2[0xb];
    *(double *)(iVar5 + 0x40) = (double)(float)puVar2[0xc];
    *(double *)(iVar5 + 0x48) = (double)(float)puVar2[0xd];
    *(double *)(iVar5 + 0x50) = (double)(float)puVar2[0xe];
  }
  if (piVar7 != (int *)0x0) {
    *piVar7 = iVar5;
  }
  return 1;
}


