/*
 * Program: i76.exe
 * Function: world_object_texture_animation_start_helper_0046d900
 * Entry: 0046d900
 * Signature: undefined4 __cdecl world_object_texture_animation_start_helper_0046d900(int param_1, int param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: world object texture animation start
   helper based on adjacent named subsystem context. */

undefined4 __cdecl world_object_texture_animation_start_helper_0046d900(int param_1,int param_2)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  iVar4 = *(int *)(param_1 + 0x70);
  iVar5 = 0;
  piVar6 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar5 & 0x1f)) != 0) {
      if (*(int *)(iVar4 + 4) < *piVar6) {
        *(int *)(param_2 + 8 + iVar5 * 4) = *(int *)(param_2 + 8 + iVar5 * 4) - *(int *)(iVar4 + 4);
        *(undefined4 *)(iVar4 + 4) = 0;
        *(undefined4 *)(iVar4 + 0xc) = 0x3f000000;
        *(undefined4 *)(iVar4 + 0x14) = 0x40000000;
        iVar4 = get_root_ancestor_world_object(param_1);
        update_vehicle_damage_state_speed_scalar_from_tire_load(iVar4);
        return 1;
      }
      *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) - *piVar6;
      *piVar6 = 0;
    }
    iVar5 = iVar5 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar5 < 4);
  fVar3 = (float)*(int *)(iVar4 + 8);
  fVar2 = ((float)*(int *)(iVar4 + 4) / fVar3) * *(float *)(iVar4 + 0x10);
  bVar1 = fVar2 < _DAT_004be4a8;
  *(float *)(iVar4 + 0xc) = fVar2;
  if (bVar1) {
    *(undefined4 *)(iVar4 + 0xc) = 0x3f000000;
  }
  *(float *)(iVar4 + 0x14) =
       (_DAT_004be4ac - *(float *)(iVar4 + 0x18)) *
       ((float)(*(int *)(iVar4 + 8) - *(int *)(iVar4 + 4)) / fVar3) + *(float *)(iVar4 + 0x18);
  iVar4 = get_root_ancestor_world_object(param_1);
  update_vehicle_damage_state_speed_scalar_from_tire_load(iVar4);
  return 0;
}


