/*
 * Program: i76.exe
 * Function: raster_span_builder_context_helper_00473400
 * Entry: 00473400
 * Signature: undefined __stdcall raster_span_builder_context_helper_00473400(undefined4 param_1, undefined4 param_2, int * param_3, int * param_4)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster span builder context helper
   based on adjacent named subsystem context. */

void raster_span_builder_context_helper_00473400
               (undefined4 param_1,undefined4 param_2,int *param_3,int *param_4)

{
  int *piVar1;
  
  while (param_4 != (int *)0x0) {
    piVar1 = (int *)param_4[1];
    *(int **)(param_4[3] + 0x24) = param_4;
    param_4[1] = param_4[-7];
    param_4[2] = param_4[-6];
    *(int **)(param_4[-7] + 8) = param_4;
    *(int **)(param_4[-6] + 4) = param_4;
    param_4[4] = param_4[-4];
    *param_4 = *param_4 - param_4[6];
    param_4 = piVar1;
  }
  while (param_3 != (int *)0x0) {
    piVar1 = (int *)param_3[1];
    *(int **)(param_3[3] + 0x20) = param_3;
    param_3[1] = param_3[-7];
    param_3[2] = param_3[-6];
    *(int **)(param_3[-7] + 8) = param_3;
    *(int **)(param_3[-6] + 4) = param_3;
    param_3[4] = param_3[-4];
    *param_3 = *param_3 - param_3[6];
    param_3 = piVar1;
  }
  return;
}


