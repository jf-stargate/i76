/*
 * Program: i76.exe
 * Function: read_vehicle_config_weapon_chunks
 * Entry: 004b0bd0
 * Signature: int __cdecl read_vehicle_config_weapon_chunks(char * param_1, void * param_2, int param_3, int param_4, void * param_5)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Reads VCFC/SPEC/WEPN/EXIT chunks from
   a vehicle config file stream, skipping empty weapon names. */

int __cdecl
read_vehicle_config_weapon_chunks(char *param_1,void *param_2,int param_3,int param_4,void *param_5)

{
  byte bVar1;
  bool bVar2;
  FILE *pFVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  void *pvVar4;
  byte *pbVar5;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  byte *pbVar6;
  int iVar7;
  int local_4;
  
  local_4 = 0;
  pFVar3 = create_bwd2_chunk_output_file(param_1,3);
  iVar7 = 0;
  if (pFVar3 != (FILE *)0x0) {
    bVar2 = write_bwd2_chunk_record(pFVar3,param_1,0x56434643,param_2,0x81);
    if (CONCAT31(extraout_var,bVar2) != 0) {
      iVar7 = 0;
      do {
        bVar2 = write_bwd2_chunk_record(pFVar3,param_1,0x53504543,param_5,4);
        if (CONCAT31(extraout_var_00,bVar2) == 0) break;
        iVar7 = iVar7 + 1;
        param_5 = (void *)((int)param_5 + 4);
      } while (iVar7 < 3);
      iVar7 = param_4 + -1;
      if (param_4 != 0) {
        pvVar4 = (void *)(param_3 + iVar7 * 0x11);
        param_4 = iVar7;
        do {
          pbVar6 = &DAT_00504c28;
          pbVar5 = (byte *)((int)pvVar4 + 4);
          do {
            bVar1 = *pbVar5;
            bVar2 = bVar1 < *pbVar6;
            if (bVar1 != *pbVar6) {
LAB_004b0c82:
              iVar7 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
              goto LAB_004b0c87;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar5[1];
            bVar2 = bVar1 < pbVar6[1];
            if (bVar1 != pbVar6[1]) goto LAB_004b0c82;
            pbVar5 = pbVar5 + 2;
            pbVar6 = pbVar6 + 2;
          } while (bVar1 != 0);
          iVar7 = 0;
LAB_004b0c87:
          if ((iVar7 != 0) &&
             (bVar2 = write_bwd2_chunk_record(pFVar3,param_1,0x5745504e,pvVar4,0x11),
             iVar7 = param_4, CONCAT31(extraout_var_01,bVar2) == 0)) break;
          pvVar4 = (void *)((int)pvVar4 + -0x11);
          iVar7 = param_4 + -1;
          bVar2 = param_4 != 0;
          param_4 = iVar7;
        } while (bVar2);
      }
      if ((iVar7 < 0) &&
         (bVar2 = write_bwd2_chunk_record(pFVar3,param_1,0x45584954,(void *)0x0,8),
         CONCAT31(extraout_var_02,bVar2) != 0)) {
        local_4 = 1;
      }
    }
    close_bwd2_chunk_output_file(pFVar3,param_1,local_4);
    iVar7 = local_4;
  }
  return iVar7;
}


