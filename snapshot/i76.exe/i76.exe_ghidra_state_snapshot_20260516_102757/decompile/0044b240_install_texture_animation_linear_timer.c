/*
 * Program: i76.exe
 * Function: install_texture_animation_linear_timer
 * Entry: 0044b240
 * Signature: undefined __cdecl install_texture_animation_linear_timer(uint param_1, byte * param_2, float param_3, float param_4, float param_5, float param_6)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Installs linear/wrapping
   texture animation timing for a texture-set binding. */

void __cdecl
install_texture_animation_linear_timer
          (uint param_1,byte *param_2,float param_3,float param_4,float param_5,float param_6)

{
  float *pfVar1;
  int iVar2;
  float10 fVar3;
  
  pfVar1 = (float *)xalloc_global_heap(0x1c);
  fVar3 = get_network_or_session_runtime_seconds();
  *pfVar1 = (float)(fVar3 + (float10)param_3);
  pfVar1[1] = param_3;
  pfVar1[2] = param_5;
  pfVar1[3] = 0.0;
  pfVar1[4] = param_4;
  pfVar1[5] = 2.8026e-45;
  pfVar1[6] = param_6;
  iVar2 = register_or_replace_texture_animation_timer(param_1,(char *)param_2,0x44b2d0,(int)pfVar1);
  if (iVar2 != 0) {
    set_texture_binding_frame_and_reload(param_1,param_2,1,(int)pfVar1[4],0);
    set_texture_binding_frame_and_reload(param_1,param_2,0,(int)pfVar1[3],1);
  }
  return;
}


