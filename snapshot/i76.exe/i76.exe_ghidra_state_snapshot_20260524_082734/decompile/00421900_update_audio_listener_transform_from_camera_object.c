/*
 * Program: i76.exe
 * Function: update_audio_listener_transform_from_camera_object
 * Entry: 00421900
 * Signature: undefined __cdecl update_audio_listener_transform_from_camera_object(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename v13 set A: Updates audio listener/source transform globals from the
   active camera/object transform and sends them to the audio backend. */

void __cdecl update_audio_listener_transform_from_camera_object(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40 [10];
  double local_18;
  double local_10;
  double local_8;
  
  iVar1 = param_1;
  if (((((DAT_00524564 != 0) && (*(int *)(DAT_00524564 + 8) != 0)) && (param_1 != 0)) &&
      ((*(int *)(param_1 + 0x5c) != 0 && (*(int *)(param_1 + 0x58) != 0)))) &&
     ((*(uint *)(param_1 + 0x14) & 0x100) != 0)) {
    iVar2 = world_object_has_optional_runtime_flag(*(int *)(param_1 + 0x5c));
    if ((iVar2 == 0) || (DAT_004c2724 == 0)) {
      pfVar3 = (float *)compute_transform_relative_to_ancestor(local_40,*(int *)(iVar1 + 0x5c),0);
      pfVar4 = local_40;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *pfVar4 = *pfVar3;
        pfVar3 = pfVar3 + 1;
        pfVar4 = pfVar4 + 1;
      }
      get_world_object_damage_or_target_vectors(*(int *)(iVar1 + 0x5c),&local_4c,&param_1);
      DAT_005fce44 = (float)local_18;
      _DAT_005fce48 = (float)local_10;
      _DAT_005fce4c = (float)local_8;
      _DAT_005fce50 = local_4c;
      _DAT_005fce54 = local_48;
      _DAT_005fce58 = local_44;
    }
    else {
      DAT_005fce44 = DAT_005fcdc4;
      _DAT_005fce48 = DAT_005fcdc8;
      _DAT_005fce4c = DAT_005fcdcc;
      _DAT_005fce50 = DAT_005fcdd0;
      _DAT_005fce54 = DAT_005fcdd4;
      _DAT_005fce58 = DAT_005fcdd8;
    }
    _DAT_005fce74 = 0x42c80000;
    if ((*(uint *)(iVar1 + 0x14) & 0x200) == 0) {
      _DAT_005fce74 = 0x41200000;
    }
    _DAT_005fce78 = 0x43c80000;
    (**(code **)(**(int **)(iVar1 + 0x58) + 0x30))(*(int **)(iVar1 + 0x58),&DAT_005fce40,1);
  }
  return;
}


