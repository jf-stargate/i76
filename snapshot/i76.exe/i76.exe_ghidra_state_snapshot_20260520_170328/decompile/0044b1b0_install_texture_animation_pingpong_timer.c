/*
 * Program: i76.exe
 * Function: install_texture_animation_pingpong_timer
 * Entry: 0044b1b0
 * Signature: undefined __cdecl install_texture_animation_pingpong_timer(uint param_1, byte * param_2, float param_3, float param_4, float param_5, int param_6)
 */


/* [cgpt i76.exe GEO runtime/render renames v30; confidence=medium-high] Installs ping-pong texture
   animation timing for a texture-set binding. */

void __cdecl
install_texture_animation_pingpong_timer
          (uint param_1,byte *param_2,float param_3,float param_4,float param_5,int param_6)

{
  float *pfVar1;
  float10 fVar2;
  
  pfVar1 = (float *)xalloc_global_heap(0x1c);
  fVar2 = get_network_or_session_runtime_seconds();
  pfVar1[1] = param_3;
  *pfVar1 = (float)(fVar2 + (float10)param_3);
  pfVar1[2] = param_5;
  pfVar1[3] = 0.0;
  pfVar1[4] = param_4;
  pfVar1[5] = (float)(uint)(param_6 == 0);
  pfVar1[6] = 0.0;
  register_or_replace_texture_animation_timer(param_1,(char *)param_2,0x44b2d0,(int)pfVar1);
  set_texture_binding_frame_and_reload(param_1,param_2,1,(int)pfVar1[4],0);
  set_texture_binding_frame_and_reload(param_1,param_2,0,(int)pfVar1[3],1);
  return;
}


