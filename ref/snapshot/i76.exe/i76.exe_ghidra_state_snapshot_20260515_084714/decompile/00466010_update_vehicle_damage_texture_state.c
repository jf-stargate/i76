/*
 * Program: i76.exe
 * Function: update_vehicle_damage_texture_state
 * Entry: 00466010
 * Signature: undefined __cdecl update_vehicle_damage_texture_state(int * param_1, uint param_2, uint param_3)
 */


/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=high] Maps vehicle/part damage
   severity to texture-binding frame state for body and wheel damage regions. */

void __cdecl update_vehicle_damage_texture_state(int *param_1,uint param_2,uint param_3)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int *piVar3;
  int iVar4;
  
  iVar1 = (&g_vehicle_damage_texture_slot_offsets)[param_2];
  if (param_2 < 5) {
    iVar4 = param_1[iVar1 + 0x102];
    if (iVar4 == 0) {
      return;
    }
  }
  else {
    if (param_1[iVar1 + 0xea] == 0) {
      return;
    }
    iVar4 = *(int *)(param_1[iVar1 + 0xea] + 100);
  }
  piVar3 = param_1;
  switch(param_3) {
  case 0:
  case 1:
    piVar3 = (int *)0x0;
    break;
  case 2:
    piVar3 = (int *)0x1;
    break;
  case 3:
    piVar3 = (int *)0x2;
    break;
  case 4:
    piVar3 = (int *)0x3;
  }
  if (4 < param_2) {
    if (param_3 < 3) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)0x1;
      play_flat_tire_blowout_sound(param_1[iVar1 + 0xea]);
    }
  }
  if ((iVar4 != 0) &&
     (bVar2 = release_geometry_variant_recursive(iVar4,(int)piVar3),
     CONCAT31(extraout_var,bVar2) == 1)) {
    has_world_object_class_damage_handler(*param_1);
  }
  return;
}


