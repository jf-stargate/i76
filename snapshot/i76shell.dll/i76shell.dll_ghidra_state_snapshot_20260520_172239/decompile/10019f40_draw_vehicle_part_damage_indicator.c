/*
 * Program: i76shell.dll
 * Function: draw_vehicle_part_damage_indicator
 * Entry: 10019f40
 * Signature: undefined __cdecl draw_vehicle_part_damage_indicator(int * param_1, int param_2, int param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl draw_vehicle_part_damage_indicator(int *param_1,int param_2,int param_3)

{
  double dVar1;
  double dVar2;
  
  if (*(int *)(*param_1 + 0x4c) != param_1[3]) {
    dVar2 = (double)param_1[3];
    dVar1 = (double)*(int *)(*param_1 + 0x4c) * _DAT_10041308;
    if (dVar2 < dVar1) {
      draw_mw2_image_subresource_to_shell_surface
                (DAT_100cc518,DAT_100d1dc4,DAT_100d1d88,param_2,param_3,0x8c,0xe);
      return;
    }
    if (dVar2 < dVar1 + dVar1) {
      draw_mw2_image_subresource_to_shell_surface
                (DAT_100cc518,DAT_100d1dc8,DAT_100d1d84,param_2,param_3,0x8c,0xe);
      return;
    }
    draw_mw2_image_subresource_to_shell_surface
              (DAT_100cc518,DAT_100d1dcc,DAT_100d1d8c,param_2,param_3,0x8c,0xe);
  }
  return;
}


