/*
 * Program: i76.exe
 * Function: terrain_map_context_helper_00492890
 * Entry: 00492890
 * Signature: undefined __cdecl terrain_map_context_helper_00492890(undefined4 * param_1, double * param_2, double * param_3, double * param_4)
 */


/* cgpt label refinement v19: was terrain_map_runtime_terrain_map_context_helper_00492890. Remove
   duplicated terrain wording. */

void __cdecl
terrain_map_context_helper_00492890
          (undefined4 *param_1,double *param_2,double *param_3,double *param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  undefined8 *puVar6;
  float10 fVar7;
  undefined8 local_18;
  double local_10;
  double local_8;
  
  local_18 = *param_3 - *param_2;
  local_10 = param_3[1] - param_2[1];
  local_8 = param_3[2] - param_2[2];
  dVar4 = (param_4[2] - param_2[2]) * local_10 - (param_4[1] - param_2[1]) * local_8;
  dVar1 = (*param_4 - *param_2) * local_8 - (param_4[2] - param_2[2]) * local_18;
  dVar3 = (param_4[1] - param_2[1]) * local_18 - (*param_4 - *param_2) * local_10;
  dVar2 = dVar3 * dVar3 + dVar1 * dVar1 + dVar4 * dVar4;
  fVar7 = zone_satellite_map_context_helper_00495000
                    (SUB84(dVar2,0),(uint)((ulonglong)dVar2 >> 0x20));
  local_18 = (double)CONCAT44((float)(fVar7 * (float10)dVar1),(float)(fVar7 * (float10)dVar4));
  local_10 = (double)CONCAT44(local_10._4_4_,(float)(fVar7 * (float10)dVar3));
  local_8 = (double)((-(fVar7 * (float10)dVar4) * (float10)*param_2 -
                     fVar7 * (float10)dVar1 * (float10)param_2[1]) -
                    fVar7 * (float10)dVar3 * (float10)param_2[2]);
  puVar6 = &local_18;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_1 = *(undefined4 *)puVar6;
    puVar6 = (undefined8 *)((int)puVar6 + 4);
    param_1 = param_1 + 1;
  }
  return;
}


