/*
 * Program: i76.exe
 * Function: bind_odef_vehicle_geometry_context
 * Entry: 004b81c0
 * Signature: undefined __cdecl bind_odef_vehicle_geometry_context(undefined4 * param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle geometry part binding context
   helper based on adjacent named subsystem context.
   
   I76 rename v43: bind_odef_vehicle_geometry_context
   ODEF vehicle/object geometry binding helper called from class paths. */

void __cdecl bind_odef_vehicle_geometry_context(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)xalloc_global_heap(0x3c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1[2] = 4;
    puVar1[1] = 4;
    *puVar1 = 4;
    puVar1[3] = param_1[7];
    puVar1[4] = param_1[6];
    puVar1[5] = param_1[5];
    puVar1[6] = param_1[4];
    puVar1[7] = param_1[0xb];
    puVar1[8] = param_1[10];
    puVar1[9] = param_1[9];
    puVar1[10] = param_1[8];
    puVar1[0xb] = param_1[3];
    puVar1[0xc] = param_1[2];
    puVar1[0xd] = param_1[1];
    puVar1[0xe] = *param_1;
  }
  return;
}


