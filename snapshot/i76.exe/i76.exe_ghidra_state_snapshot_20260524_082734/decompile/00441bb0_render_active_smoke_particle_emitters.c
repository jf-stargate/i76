/*
 * Program: i76.exe
 * Function: render_active_smoke_particle_emitters
 * Entry: 00441bb0
 * Signature: undefined __cdecl render_active_smoke_particle_emitters(float * param_1)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Renders all active smoke/effect
   particle emitters by building billboard geometry for each active record. */

void __cdecl render_active_smoke_particle_emitters(float *param_1)

{
  int *piVar1;
  
  piVar1 = DAT_0052ba30;
  if (DAT_0052ba34 != 0) {
    for (; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[0x10]) {
      build_smoke_particle_billboard_geometry(param_1,piVar1);
    }
  }
  return;
}


