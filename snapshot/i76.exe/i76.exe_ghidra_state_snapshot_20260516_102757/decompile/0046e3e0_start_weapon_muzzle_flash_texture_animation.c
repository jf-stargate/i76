/*
 * Program: i76.exe
 * Function: start_weapon_muzzle_flash_texture_animation
 * Entry: 0046e3e0
 * Signature: undefined __cdecl start_weapon_muzzle_flash_texture_animation(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v2: Starts a weapon/muzzle texture animation by selecting frames on the weapon child
   object. */

void __cdecl start_weapon_muzzle_flash_texture_animation(int param_1,int param_2)

{
  int *piVar1;
  byte *pbVar2;
  uint uVar3;
  float10 fVar4;
  
  if (param_2 == 1) {
    uVar3 = *(uint *)(*(int *)(param_1 + 0x70) + 0x400);
  }
  else {
    uVar3 = *(uint *)(*(int *)(param_1 + 0x70) + 0x404);
  }
  if (((uVar3 != 0) && ((*(undefined4 **)(uVar3 + 0x70))[1] != 0)) &&
     (piVar1 = (int *)**(undefined4 **)(uVar3 + 0x70), piVar1 != (int *)0x0)) {
    pbVar2 = (byte *)find_object_texture_slot_name(uVar3,0);
    if (*piVar1 == 0) {
      *piVar1 = 1;
      piVar1[4] = 1;
      piVar1[3] = 1;
      piVar1[1] = -1;
      piVar1[2] = 2;
      fVar4 = get_network_or_session_runtime_seconds();
      piVar1[5] = (int)(float)(fVar4 - (float10)_DAT_004be4d4);
      set_texture_binding_frame_and_reload(uVar3,pbVar2,1,1,0);
      set_texture_binding_frame_and_reload(uVar3,pbVar2,0,0,1);
    }
  }
  return;
}


