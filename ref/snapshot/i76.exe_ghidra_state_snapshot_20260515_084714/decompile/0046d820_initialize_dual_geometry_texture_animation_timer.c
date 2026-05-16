/*
 * Program: i76.exe
 * Function: initialize_dual_geometry_texture_animation_timer
 * Entry: 0046d820
 * Signature: undefined __cdecl initialize_dual_geometry_texture_animation_timer(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Initializes a two-variant geometry texture animation timer and registers texture
   animation callbacks. */

void __cdecl initialize_dual_geometry_texture_animation_timer(int param_1)

{
  double dVar1;
  int iVar2;
  float10 fVar3;
  float *pfVar4;
  char *pcVar5;
  float10 fVar6;
  
  iVar2 = *(int *)(param_1 + 0x70);
  dVar1 = *(double *)(param_1 + 0x48);
  *(float *)(iVar2 + 0x28) = (float)dVar1;
  *(float *)(iVar2 + 0x1c) = (float)dVar1;
  *(float *)(iVar2 + 0x38) = (float)dVar1 * _DAT_004be49c;
  *(float *)(iVar2 + 0x3c) = *(float *)(iVar2 + 0x1c) * _DAT_004be4a0;
  pfVar4 = radar_context_helper_0045f3b0(0x18);
  fVar6 = get_multiplayer_or_runtime_seconds();
  fVar3 = (float10)_DAT_004be4a4;
  pfVar4[1] = 0.05;
  pfVar4[2] = 1.68156e-44;
  pfVar4[3] = 0.0;
  pfVar4[4] = 0.0;
  pfVar4[5] = 1.4013e-45;
  *pfVar4 = (float)(fVar6 - fVar3);
  release_or_detach_object_geometry_variant(*(int *)(param_1 + 100),1);
  pcVar5 = (char *)find_object_texture_slot_name(*(int *)(param_1 + 100),0);
  if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
    register_or_replace_texture_animation_timer(param_1,pcVar5,0x46db00,(int)pfVar4);
  }
  release_or_detach_object_geometry_variant(*(int *)(param_1 + 100),0);
  pcVar5 = (char *)find_object_texture_slot_name(*(int *)(param_1 + 100),0);
  if ((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) {
    register_or_replace_texture_animation_timer(param_1,pcVar5,0x46db00,(int)pfVar4);
  }
  *(float **)(iVar2 + 0x84) = pfVar4;
  return;
}


