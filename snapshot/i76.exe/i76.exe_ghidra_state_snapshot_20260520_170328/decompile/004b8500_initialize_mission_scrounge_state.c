/*
 * Program: i76.exe
 * Function: initialize_mission_scrounge_state
 * Entry: 004b8500
 * Signature: undefined4 __cdecl initialize_mission_scrounge_state(char * param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence No scrounge in this mission */

undefined4 __cdecl initialize_mission_scrounge_state(char *param_1)

{
  int iVar1;
  bool bVar2;
  byte *pbVar3;
  undefined3 extraout_var;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  char local_2e0 [4];
  char local_2dc [16];
  undefined4 local_2cc [20];
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  int local_254 [21];
  char local_200 [256];
  char local_100 [256];
  
  if (*param_1 == '\0') {
    report_error();
    return 0;
  }
  piVar6 = local_254;
  for (iVar5 = 0x15; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  puVar7 = local_2cc;
  for (iVar5 = 0x1e; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  local_270 = 5;
  local_27c = 0x42480000;
  local_278 = 0x42480000;
  local_274 = 0x42480000;
  _splitpath(param_1,local_2e0,local_100,local_2dc,local_200);
  strncpy((char *)local_2cc,local_2dc,8);
  local_254[0] = create_child_object_from_part_transform_record
                           (0,(int)local_2cc,(char *)local_2cc,0,1);
  if (local_254[0] != 0) {
    compute_world_object_bounds_and_link_global(local_254[0]);
    pbVar3 = (byte *)format_8char_resource_basename_with_suffix
                               (local_2cc[0],local_2cc[1],&DAT_00500640);
    bVar2 = parse_bwd2_resource_with_descriptor_table
                      (pbVar3,&g_sdf_child_descriptor_table,6,(byte *)local_254);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      iVar5 = *(int *)(local_254[0] + 0x6c);
      if (((((iVar5 == 2) || (iVar5 == 3)) || (iVar5 == 0xc)) || (iVar5 == 0xb)) &&
         (*(int *)(local_254[0] + 0x70) != 0)) {
        for (iVar5 = *(int *)(local_254[0] + 100); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x60)) {
          iVar4 = is_transform_composed_world_object_class(iVar5);
          if (iVar4 != 0) {
            iVar4 = *(int *)(iVar5 + 0x70);
            iVar1 = (*(uint *)(iVar5 + 0x10) >> 10 & 3) * 0xd;
            world_reader_null_handler(&DAT_00500b78 + iVar1,(char *)(iVar4 + 0x10),0);
            *(undefined4 *)(iVar4 + 0x18) = *(undefined4 *)(s_null_00500bb0 + iVar1);
            *(undefined4 *)(iVar4 + 0x1c) = *(undefined4 *)(s_null_00500bb0 + iVar1 + 4);
            *(undefined4 *)(iVar4 + 0x20) = *(undefined4 *)(&DAT_00500bb8 + iVar1);
            *(undefined *)(iVar4 + 0x24) = (&DAT_00500bbc)[iVar1];
          }
          for (iVar4 = *(int *)(iVar5 + 100); iVar4 != 0; iVar4 = *(int *)(iVar4 + 0x60)) {
            mission_scrounge_record_handler(iVar4);
          }
        }
      }
      return 1;
    }
  }
  return 0;
}


