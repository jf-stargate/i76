/*
 * Program: i76.exe
 * Function: register_odef_spawn_or_regen_transform
 * Entry: 00450f90
 * Signature: undefined __cdecl register_odef_spawn_or_regen_transform(int param_1, int param_2)
 */


/* [i76 level/static/material baseline v48]
   name: write_spawn_regen_marker_table_entry
   confidence: medium_high
   module: level_object_dispatch
   Special spawn/regen marker table writer. ODEF class 0x01 labels 'spawn' and 'regen' are not
   ordinary label.vcf geometry objects.
   note: Rename skipped because existing name appears user-defined. */

void __cdecl register_odef_spawn_or_regen_transform(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  if (param_2 == 0) {
    if (0x3f < g_odef_spawn_transform_count) {
      return;
    }
    puVar1 = (undefined4 *)(&g_odef_spawn_transform_table + g_odef_spawn_transform_count * 0x40);
    g_odef_spawn_transform_count = g_odef_spawn_transform_count + 1;
  }
  else {
    if (param_2 != 1) {
      return;
    }
    if (0x3f < g_odef_regen_transform_count) {
      return;
    }
    puVar1 = (undefined4 *)(&g_odef_regen_transform_table + g_odef_regen_transform_count * 0x40);
    g_odef_regen_transform_count = g_odef_regen_transform_count + 1;
  }
  *puVar1 = *(undefined4 *)(param_1 + 8);
  puVar1[1] = *(undefined4 *)(param_1 + 0xc);
  puVar1[2] = *(undefined4 *)(param_1 + 0x10);
  puVar1[3] = *(undefined4 *)(param_1 + 0x14);
  puVar1[4] = *(undefined4 *)(param_1 + 0x18);
  puVar1[5] = *(undefined4 *)(param_1 + 0x1c);
  puVar1[6] = *(undefined4 *)(param_1 + 0x20);
  puVar1[7] = *(undefined4 *)(param_1 + 0x24);
  puVar1[8] = *(undefined4 *)(param_1 + 0x28);
  *(double *)(puVar1 + 10) = (double)*(float *)(param_1 + 0x2c);
  *(double *)(puVar1 + 0xc) = (double)*(float *)(param_1 + 0x30);
  *(double *)(puVar1 + 0xe) = (double)*(float *)(param_1 + 0x34);
  return;
}


