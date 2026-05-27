/*
 * Program: i76.exe
 * Function: instantiate_part_record_array_with_geo_cache
 * Entry: 004b75a0
 * Signature: undefined4 __cdecl instantiate_part_record_array_with_geo_cache(int * param_1, int * param_2, int param_3, int param_4, int param_5, undefined * param_6)
 */


/* [cgpt i76.exe vehicle asset renames v19; confidence=high] Generic part-array instantiator for
   0x64-byte part records; resolves world/null/named parents, creates children, and registers
   basename.geo variants. */

undefined4 __cdecl
instantiate_part_record_array_with_geo_cache
          (int *param_1,int *param_2,int param_3,int param_4,int param_5,undefined *param_6)

{
  int *_Str1;
  int iVar1;
  char *pcVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int *local_174;
  int local_170;
  int local_16c;
  int local_168;
  char local_160 [8];
  undefined1 local_158;
  char local_150 [8];
  undefined1 local_148;
  int local_140 [80];
  
  if (param_5 == 0) {
    return 0;
  }
  local_140[0] = 0;
  local_16c = 0;
  if (param_3 < 1) {
    return 0;
  }
  do {
    iVar3 = 0;
    if (0 < param_4) {
      do {
        local_168 = 0;
        if (0 < param_5) {
          local_170 = 0;
          local_174 = local_140;
          do {
            pcVar5 = (char *)(*param_1 + local_170);
            if (iVar3 == 0 && local_16c == 0) {
              _Str1 = (int *)(pcVar5 + 0x38);
              piVar4 = (int *)0x0;
              iVar1 = _strnicmp((char *)_Str1,s_world_00500c08,5);
              if ((iVar1 == 0) || (iVar1 = _strnicmp((char *)_Str1,s_null_004c3280,4), iVar1 == 0))
              {
LAB_004b76c0:
                if (piVar4 == (int *)0x0) {
                  piVar4 = param_2;
                }
              }
              else {
                piVar4 = find_vehicle_child_object_by_ids(param_2,*_Str1,*(int *)(pcVar5 + 0x3c));
                if (piVar4 == (int *)0x0) {
                  strncpy(local_150,(char *)_Str1,8);
                  local_148 = 0;
                  strncpy(local_160,pcVar5,8);
                  local_158 = 0;
                  report_error();
                  goto LAB_004b76c0;
                }
              }
              iVar1 = create_child_object_from_part_transform_record
                                ((int)piVar4,(int)pcVar5,pcVar5,0,1);
              if (iVar1 == 0) {
                return 0;
              }
              *local_174 = iVar1;
              if (param_6 != (undefined *)0x0) {
                (*(code *)param_6)(iVar1,param_2);
              }
            }
            else {
              iVar1 = *local_174;
            }
            iVar6 = iVar3;
            iVar7 = local_16c;
            pcVar2 = format_8char_resource_basename_with_suffix
                               (*(undefined4 *)pcVar5,*(undefined4 *)(pcVar5 + 4),s__geo_004fe724);
            cache_add_entry(iVar1,pcVar2,iVar6,iVar7);
            if (((local_16c == 2) && (param_2 != (int *)0x0)) && (param_2[0x1b] == 0x32)) {
              iVar7 = 3;
              iVar6 = iVar3;
              pcVar5 = format_8char_resource_basename_with_suffix
                                 (*(undefined4 *)pcVar5,*(undefined4 *)(pcVar5 + 4),s__geo_004fe724)
              ;
              cache_add_entry(iVar1,pcVar5,iVar6,iVar7);
            }
            local_168 = local_168 + 1;
            local_170 = local_170 + 100;
            local_174 = local_174 + 1;
          } while (local_168 < param_5);
        }
        iVar3 = iVar3 + 1;
        param_1 = param_1 + 1;
      } while (iVar3 < param_4);
    }
    local_16c = local_16c + 1;
    if (param_3 <= local_16c) {
      return local_140[0];
    }
  } while( true );
}


