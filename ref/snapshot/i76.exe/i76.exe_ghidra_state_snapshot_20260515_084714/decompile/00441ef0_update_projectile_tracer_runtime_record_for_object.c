/*
 * Program: i76.exe
 * Function: update_projectile_tracer_runtime_record_for_object
 * Entry: 00441ef0
 * Signature: undefined __cdecl update_projectile_tracer_runtime_record_for_object(int param_1, int param_2)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Finds a projectile tracer/beam record
   for an object and updates its mode-dependent vector/scale parameters. */

void __cdecl update_projectile_tracer_runtime_record_for_object(int param_1,int param_2)

{
  float *pfVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (DAT_0052ba48 != (int *)0x0) {
    piVar6 = (int *)0x0;
    piVar5 = DAT_0052ba48;
    do {
      if (piVar5[1] == param_1) {
        piVar6 = piVar5;
      }
      piVar5 = (int *)*piVar5;
    } while (piVar5 != DAT_0052ba48);
    if (piVar6 != (int *)0x0) {
      piVar6[2] = 1;
      iVar4 = (&DAT_0052ba38)[piVar6[4]];
      piVar6[4] = iVar4;
      if (piVar6[3] == iVar4) {
        piVar6[3] = (&DAT_0052ba38)[piVar6[3]];
      }
      local_4 = *(float *)(&DAT_004f1c00 + param_2 * 4);
      if (piVar6[5] == 2) {
        dVar2 = *(double *)(param_1 + 0x48);
        dVar3 = *(double *)(param_1 + 0x50);
        pfVar1 = (float *)(piVar6 + iVar4 * 9 + 7);
        *pfVar1 = (float)*(double *)(param_1 + 0x40);
        pfVar1[1] = (float)dVar2;
        pfVar1[2] = (float)dVar3;
        return;
      }
      local_24 = local_4 * DAT_004f1b90;
      local_20 = DAT_004f1b94 * local_4;
      local_1c = DAT_004f1b98 * local_4;
      local_18 = local_4 * DAT_004f1b9c;
      local_14 = DAT_004f1ba0 * local_4;
      local_10 = DAT_004f1ba4 * local_4;
      local_c = local_4 * DAT_004f1ba8;
      local_8 = DAT_004f1bac * local_4;
      local_4 = DAT_004f1bb0 * local_4;
      transform_vec3_array_by_matrix
                ((float *)(piVar6 + iVar4 * 9 + 7),&local_24,3,(float *)(param_1 + 0x18));
    }
  }
  return;
}


