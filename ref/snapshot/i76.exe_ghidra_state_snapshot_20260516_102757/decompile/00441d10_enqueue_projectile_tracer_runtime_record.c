/*
 * Program: i76.exe
 * Function: enqueue_projectile_tracer_runtime_record
 * Entry: 00441d10
 * Signature: undefined __cdecl enqueue_projectile_tracer_runtime_record(int param_1, int param_2, undefined4 param_3)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Allocates/enqueues a projectile
   tracer/beam runtime record with mode, source object, and per-mode parameters. */

void __cdecl enqueue_projectile_tracer_runtime_record(int param_1,int param_2,undefined4 param_3)

{
  double dVar1;
  double dVar2;
  undefined4 *puVar3;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (param_2 < 3) {
    DAT_0052ba48[3] = 0;
    DAT_0052ba48[4] = 0;
    DAT_0052ba48[1] = param_1;
    DAT_0052ba48[5] = param_2;
    DAT_0052ba48[2] = 1;
    DAT_0052ba48[6] = param_3;
    puVar3 = DAT_0052ba48;
    local_4 = *(float *)(&DAT_004f1c00 + param_2 * 4);
    if (DAT_0052ba48[5] == 2) {
      dVar1 = *(double *)(param_1 + 0x48);
      dVar2 = *(double *)(param_1 + 0x50);
      DAT_0052ba48[7] = (float)*(double *)(param_1 + 0x40);
      puVar3[8] = (float)dVar1;
      puVar3[9] = (float)dVar2;
      DAT_0052ba48 = (undefined4 *)*DAT_0052ba48;
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
              ((float *)(DAT_0052ba48 + 7),&local_24,3,(float *)(param_1 + 0x18));
    DAT_0052ba48 = (undefined4 *)*DAT_0052ba48;
  }
  return;
}


