/*
 * Program: i76.exe
 * Function: instantiate_vdf_vehicle_geometry_part_sets
 * Entry: 004b7800
 * Signature: undefined4 __cdecl instantiate_vdf_vehicle_geometry_part_sets(int * param_1, int * param_2, int param_3, int param_4, int param_5, undefined * param_6)
 */


/* [i76 level/static/material baseline v48]
   name: instantiate_vdf_vehicle_geometry_part_sets
   confidence: medium_high
   module: vehicle_vdf_geo
   Instantiates VDF vehicle geometry part sets. Related to VCF-backed ODEF classes; static SDF path
   is separate.
   note: Name already matches baseline. */

undefined4 __cdecl
instantiate_vdf_vehicle_geometry_part_sets
          (int *param_1,int *param_2,int param_3,int param_4,int param_5,undefined *param_6)

{
  int iVar1;
  float *pfVar2;
  int *piVar3;
  int *piVar4;
  char *pcVar5;
  float *pfVar6;
  int iVar7;
  int *local_1c0;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  int local_1ac;
  char local_1a0 [8];
  undefined1 local_198;
  char local_190 [8];
  undefined1 local_188;
  float local_180 [16];
  int local_140 [80];
  
  if (param_5 == 0) {
    return 0;
  }
  local_140[0] = 0;
  local_1b4 = 0;
  if (param_3 < 1) {
    return 0;
  }
  do {
    local_1b0 = 0;
    if (0 < param_4) {
      do {
        local_1ac = 0;
        if (0 < param_5) {
          local_1b8 = 0;
          local_1c0 = local_140;
          do {
            pcVar5 = (char *)(*param_1 + local_1b8);
            if (local_1b0 == 0 && local_1b4 == 0) {
              piVar4 = (int *)(pcVar5 + 0x38);
              piVar3 = (int *)0x0;
              iVar1 = _strnicmp((char *)piVar4,s_world_00500c08,5);
              if ((iVar1 == 0) || (iVar1 = _strnicmp((char *)piVar4,s_null_004c3280,4), iVar1 == 0))
              {
LAB_004b7924:
                if ((piVar3 == (int *)0x0) && (*(int *)(pcVar5 + 0x5c) != 0x51)) {
                  piVar3 = param_2;
                }
              }
              else {
                piVar3 = find_vehicle_child_object_by_ids(param_2,*piVar4,*(int *)(pcVar5 + 0x3c));
                if (piVar3 == (int *)0x0) {
                  strncpy(local_1a0,(char *)piVar4,8);
                  local_198 = 0;
                  strncpy(local_190,pcVar5,8);
                  local_188 = 0;
                  report_error();
                  goto LAB_004b7924;
                }
              }
              local_1bc = create_child_object_from_part_transform_record
                                    ((int)piVar3,(int)pcVar5,pcVar5,0,1);
              if (local_1bc == 0) {
                return 0;
              }
              if (*(int *)(local_1bc + 0x6c) == 0x51) {
                if (param_2 != (int *)0x0) {
                  piVar4 = param_2;
                  do {
                    pfVar2 = compose_matrix_or_transform_a
                                       (local_180,(float *)(local_1bc + 0x18),(float *)(piVar4 + 6))
                    ;
                    pfVar6 = (float *)(local_1bc + 0x18);
                    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
                      *pfVar6 = *pfVar2;
                      pfVar2 = pfVar2 + 1;
                      pfVar6 = pfVar6 + 1;
                    }
                    piVar4 = (int *)piVar4[0x1a];
                  } while (piVar4 != (int *)0x0);
                }
                compute_world_object_bounds_and_link_global(local_1bc);
              }
              *local_1c0 = local_1bc;
              if (param_6 != (undefined *)0x0) {
                (*(code *)param_6)(local_1bc,param_2);
              }
            }
            else {
              local_1bc = *local_1c0;
            }
            iVar1 = local_1b0;
            iVar7 = local_1b4;
            pcVar5 = format_8char_resource_basename_with_suffix
                               (*(undefined4 *)pcVar5,*(undefined4 *)(pcVar5 + 4),s__geo_004fe724);
            cache_add_entry(local_1bc,pcVar5,iVar1,iVar7);
            local_1ac = local_1ac + 1;
            local_1b8 = local_1b8 + 0x78;
            local_1c0 = local_1c0 + 1;
          } while (local_1ac < param_5);
        }
        local_1b0 = local_1b0 + 1;
        param_1 = param_1 + 1;
      } while (local_1b0 < param_4);
    }
    local_1b4 = local_1b4 + 1;
    if (param_3 <= local_1b4) {
      return local_140[0];
    }
  } while( true );
}


