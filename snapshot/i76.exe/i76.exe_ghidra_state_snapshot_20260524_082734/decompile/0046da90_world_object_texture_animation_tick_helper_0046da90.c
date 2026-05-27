/*
 * Program: i76.exe
 * Function: world_object_texture_animation_tick_helper_0046da90
 * Entry: 0046da90
 * Signature: undefined __cdecl world_object_texture_animation_tick_helper_0046da90(float param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object texture animation tick
   helper based on adjacent named subsystem context. */

void __cdecl world_object_texture_animation_tick_helper_0046da90(float param_1)

{
  int iVar1;
  double *pdVar2;
  float *pfVar3;
  undefined4 *puVar4;
  float local_c [3];
  
  pfVar3 = &param_1;
  iVar1 = *(int *)((int)param_1 + 0x70);
  puVar4 = (undefined4 *)0x0;
  pdVar2 = (double *)compose_world_object_runtime_transform(local_c,(int)param_1);
  probe_effect_target_surface_height_at_position(*pdVar2,*(float *)(pdVar2 + 1),pfVar3,puVar4);
  *(float *)(iVar1 + 0x30) = param_1;
  *(float *)(iVar1 + 0x2c) = param_1;
  *(undefined4 *)(iVar1 + 0x34) = 0;
  return;
}


