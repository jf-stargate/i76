/*
 * Program: i76.exe
 * Function: register_odef_spawn_or_regen_transform
 * Entry: 00450f90
 * Signature: undefined __cdecl register_odef_spawn_or_regen_transform(int param_1, int param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: spawn location lookup context helper
   based on prior focused closure context.
   
   I76 rename v43: register_odef_spawn_or_regen_transform
   Stores spawn/regen transform records into fixed tables. */

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


