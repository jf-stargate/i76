/*
 * Program: i76.exe
 * Function: read_vehicle_scene_state_chunks
 * Entry: 004b0b00
 * Signature: int __cdecl read_vehicle_scene_state_chunks(char * param_1, void * param_2, int param_3)
 */


/* [cgpt i76.exe vehicle/resource rename v4; confidence=high] Reads VCST/WLST/WPST/EXIT chunks from
   a vehicle scene/state file stream. */

int __cdecl read_vehicle_scene_state_chunks(char *param_1,void *param_2,int param_3)

{
  bool bVar1;
  FILE *pFVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int local_4;
  
  local_4 = 0;
  pFVar2 = create_bwd2_chunk_output_file(param_1,2);
  iVar3 = 0;
  if (pFVar2 != (FILE *)0x0) {
    bVar1 = write_bwd2_chunk_record(pFVar2,param_1,0x56435354,param_2,0x4c);
    if (CONCAT31(extraout_var,bVar1) != 0) {
      bVar1 = write_bwd2_chunk_record(pFVar2,param_1,0x574c5354,(void *)((int)param_2 + 0x4c),0x18);
      if (CONCAT31(extraout_var_00,bVar1) != 0) {
        iVar3 = param_3 + -1;
        if (param_3 != 0) {
          pvVar5 = (void *)((int)param_2 + iVar3 * 0xc + 100);
          iVar4 = iVar3;
          do {
            if (*(int *)((int)pvVar5 + 4) != -1) {
              bVar1 = write_bwd2_chunk_record(pFVar2,param_1,0x57505354,pvVar5,0xc);
              iVar3 = iVar4;
              if (CONCAT31(extraout_var_01,bVar1) == 0) break;
            }
            iVar3 = iVar4 + -1;
            pvVar5 = (void *)((int)pvVar5 + -0xc);
            bVar1 = iVar4 != 0;
            iVar4 = iVar3;
          } while (bVar1);
        }
        if (iVar3 < 0) {
          bVar1 = write_bwd2_chunk_record(pFVar2,param_1,0x45584954,(void *)0x0,8);
          if (CONCAT31(extraout_var_02,bVar1) != 0) {
            local_4 = 1;
          }
        }
      }
    }
    close_bwd2_chunk_output_file(pFVar2,param_1,local_4);
    iVar3 = local_4;
  }
  return iVar3;
}


