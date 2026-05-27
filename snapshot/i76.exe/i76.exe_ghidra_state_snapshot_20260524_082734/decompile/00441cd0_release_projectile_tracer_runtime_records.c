/*
 * Program: i76.exe
 * Function: release_projectile_tracer_runtime_records
 * Entry: 00441cd0
 * Signature: undefined __stdcall release_projectile_tracer_runtime_records(void)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Frees all active projectile tracer/beam
   runtime records and clears the tracer list head. */

void release_projectile_tracer_runtime_records(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = DAT_0052ba48;
  if (DAT_0052ba48 != (undefined4 *)0x0) {
    do {
      puVar2 = DAT_0052ba48;
      DAT_0052ba48 = (undefined4 *)*DAT_0052ba48;
      xfree_global_heap(puVar2);
    } while (DAT_0052ba48 != puVar1);
  }
  DAT_0052ba48 = (undefined4 *)0x0;
  return;
}


