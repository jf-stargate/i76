/*
 * Program: i76.exe
 * Function: world_object_texture_animation_update_helper_0046db00
 * Entry: 0046db00
 * Signature: undefined __cdecl world_object_texture_animation_update_helper_0046db00(int param_1, byte * param_2, float * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: world object texture animation update
   helper based on adjacent named subsystem context. */

void __cdecl
world_object_texture_animation_update_helper_0046db00(int param_1,byte *param_2,float *param_3)

{
  float fVar1;
  float10 fVar2;
  uint uVar3;
  int iVar4;
  
  fVar1 = *(float *)(*(int *)(param_1 + 0x70) + 0x20);
  if (fVar1 < _DAT_004be498) {
    param_3[5] = 0.0;
    fVar1 = -fVar1;
  }
  else {
    param_3[5] = 1.4013e-45;
  }
  if (fVar1 <= _DAT_004be4b0) {
    if (fVar1 <= _DAT_004be4b4) {
      if (fVar1 <= _DAT_004be4b8) {
        set_texture_binding_frame_and_reload(*(uint *)(param_1 + 100),param_2,1,0,1);
        return;
      }
      uVar3 = *(uint *)(param_1 + 100);
      iVar4 = 0;
    }
    else {
      uVar3 = *(uint *)(param_1 + 100);
      iVar4 = 1;
    }
  }
  else {
    uVar3 = *(uint *)(param_1 + 100);
    iVar4 = 2;
  }
  set_texture_binding_frame_and_reload(uVar3,param_2,1,iVar4,0);
  fVar2 = get_multiplayer_or_runtime_seconds();
  if (fVar2 <= (float10)*param_3) {
    return;
  }
  fVar1 = param_3[3];
  *param_3 = param_3[1] + *param_3;
  if (param_3[5] == 0.0) {
    if (fVar1 == 0.0) {
      fVar1 = param_3[2];
    }
    fVar1 = (float)((int)fVar1 + -1);
  }
  else if ((int)fVar1 < (int)param_3[2] + -1) {
    fVar1 = (float)((int)fVar1 + 1);
  }
  else {
    fVar1 = 0.0;
  }
  param_3[3] = fVar1;
  set_texture_binding_frame_and_reload
            (*(uint *)(param_1 + 100),param_2,(int)param_3[4],(int)fVar1,1);
  return;
}


