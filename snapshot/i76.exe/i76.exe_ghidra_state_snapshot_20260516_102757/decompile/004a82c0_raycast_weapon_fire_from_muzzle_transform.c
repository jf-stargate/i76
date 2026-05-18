/*
 * Program: i76.exe
 * Function: raycast_weapon_fire_from_muzzle_transform
 * Entry: 004a82c0
 * Signature: int __cdecl raycast_weapon_fire_from_muzzle_transform(int param_1, int param_2)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=medium_high] Computes muzzle world transform and
   dispatches the lower-level weapon raycast/fire helper between shooter and target. */

int __cdecl raycast_weapon_fire_from_muzzle_transform(int param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float local_40 [6];
  float local_28;
  float local_24;
  float local_20;
  double local_18;
  double local_10;
  double local_8;
  
  if (param_1 == 0) {
    return 0;
  }
  pfVar1 = (float *)compute_transform_relative_to_ancestor(local_40,param_1,0);
  pfVar3 = local_40;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = *pfVar1;
    pfVar1 = pfVar1 + 1;
    pfVar3 = pfVar3 + 1;
  }
  iVar2 = find_nearest_effect_target_in_weapon_cone
                    ((float)local_18,(float)local_10,(float)local_8,local_28,local_24,local_20,
                     param_1,param_2);
  return iVar2;
}


