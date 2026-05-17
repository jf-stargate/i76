/*
 * Program: i76.exe
 * Function: set_vehicle_damage_texture_frame_group
 * Entry: 004660d0
 * Signature: undefined __cdecl set_vehicle_damage_texture_frame_group(int param_1, uint param_2, undefined4 param_3)
 */


/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=high] Sets texture animation frame
   groups for vehicle body/wheel damage texture regions using the V1 FT/MD map-name table. */

void __cdecl set_vehicle_damage_texture_frame_group(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  
  if (param_2 < 5) {
    uVar1 = *(uint *)(param_1 + 0x408 + (&g_vehicle_damage_texture_slot_offsets)[param_2] * 4);
    uVar2 = uVar1;
    switch(param_3) {
    case 0:
      uVar2 = 0;
      break;
    case 1:
    case 2:
      uVar2 = 1;
      break;
    case 3:
      uVar2 = 2;
      break;
    case 4:
      uVar2 = 3;
    }
    iVar3 = 0;
    if (0 < (int)(&g_vehicle_damage_texture_region_counts)[param_2]) {
      pbVar4 = (byte *)(g_vehicle_damage_texture_name_table + param_2 * 0x82);
      do {
        set_texture_binding_frame_and_reload(uVar1,pbVar4,0,uVar2,1);
        iVar3 = iVar3 + 1;
        pbVar4 = pbVar4 + 0xd;
      } while (iVar3 < (int)(&g_vehicle_damage_texture_region_counts)[param_2]);
    }
  }
  return;
}


