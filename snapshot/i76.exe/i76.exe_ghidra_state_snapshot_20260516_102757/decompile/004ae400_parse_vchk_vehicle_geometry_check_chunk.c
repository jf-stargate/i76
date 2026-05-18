/*
 * Program: i76.exe
 * Function: parse_vchk_vehicle_geometry_check_chunk
 * Entry: 004ae400
 * Signature: undefined4 __cdecl parse_vchk_vehicle_geometry_check_chunk(int param_1, undefined4 * param_2)
 */


/* [cgpt i76.exe vehicle asset chunk callback renames v17; confidence=medium] VCHK callback in the
   vehicle descriptor table; likely validates/checks vehicle geometry or damage-state data. */

undefined4 __cdecl parse_vchk_vehicle_geometry_check_chunk(int param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  int local_68 [4];
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  double local_18;
  double local_10;
  double local_8;
  
  piVar1 = find_vehicle_child_object_by_ids
                     ((int *)*param_2,*(int *)(param_1 + 8),*(int *)(param_1 + 0xc));
  if (piVar1 == (int *)0x0) {
    report_chunk_parse_error();
    return 1;
  }
  iVar3 = 0;
  piVar5 = (int *)(param_1 + 0x14);
  piVar1[4] = piVar1[4] | 0x100000;
  if (0 < *(int *)(param_1 + 0x10)) {
    puVar4 = (undefined4 *)(param_1 + 0x24);
    do {
      local_40 = (float)puVar4[-2];
      local_3c = puVar4[-1];
      local_18 = (double)(float)puVar4[7];
      local_38 = *puVar4;
      local_10 = (double)(float)puVar4[8];
      local_34 = puVar4[1];
      local_30 = puVar4[2];
      local_2c = puVar4[3];
      local_28 = puVar4[4];
      local_8 = (double)(float)puVar4[9];
      local_24 = puVar4[5];
      local_20 = puVar4[6];
      local_68[0] = 0;
      local_68[3] = puVar4[0xf];
      local_68[1] = 0;
      local_4c = puVar4[0x10];
      local_68[2] = 0;
      local_48 = puVar4[0x11];
      local_44 = puVar4[0x12];
      local_58 = -(float)puVar4[0x10];
      local_54 = -(float)puVar4[0x11];
      local_50 = -(float)puVar4[0x12];
      iVar2 = cache_vehicle_chunk_geometry_attachment
                        ((int)piVar1,*piVar5,piVar5[1],&local_40,local_68,(int *)&local_58);
      if (iVar2 == 0) {
        report_chunk_parse_error();
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 0x19;
      puVar4 = puVar4 + 0x19;
    } while (iVar3 < *(int *)(param_1 + 0x10));
  }
  return 1;
}


