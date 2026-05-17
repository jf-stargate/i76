/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_0045bc20
 * Entry: 0045bc20
 * Signature: undefined __cdecl cockpit_gauge_context_helper_0045bc20(int param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_0045bc20. Remove duplicated
   cockpit wording. */

void __cdecl cockpit_gauge_context_helper_0045bc20(int param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  float *pfVar3;
  int local_4c;
  int local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38 [4];
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  ushort local_18 [12];
  
  if ((param_2 != (int *)0x0) && (iVar2 = is_damage_side_effects_suppressed(), iVar2 != 0)) {
    pfVar3 = (float *)get_effect_target_transformed_position_radius(local_38,param_2);
    local_28 = *pfVar3;
    local_24 = pfVar3[1];
    local_20 = pfVar3[2];
    local_1c = pfVar3[3];
    pfVar3 = (float *)raster_scratch_arena_context_helper_00472d30
                                (local_38,param_1,(double)local_28,(double)local_24,(double)local_20
                                );
    local_44 = *pfVar3;
    local_40 = pfVar3[1];
    if ((pfVar3[2] <= *(float *)(param_1 + 0x34) * *(float *)(param_1 + 0x10)) ||
       (DAT_0054a2e8 != 0)) {
      local_3c = _DAT_004bdfd8 / pfVar3[2];
      ftol();
      iVar2 = cockpit_gauge_context_helper_0045baa0(&local_44,param_1,&local_48,&local_4c);
      if (iVar2 == 0) {
        iVar2 = ftol();
        local_4c = local_4c + (-9 - iVar2);
        if ((-1 < local_4c) &&
           (iVar2 = multiplayer_player_count_context_helper_00454620
                              (*(short *)(*(int *)(*param_2 + 0x70) + 0x480),(uchar *)local_18),
           iVar2 != 0)) {
          uVar1 = DAT_00504c0c[2];
          iVar2 = dib_surface_context_update_helper_00476780(DAT_00504c0c,local_18);
          local_48 = local_48 - iVar2 / 2;
          dib_surface_context_setter_helper_004766e0
                    ((int)DAT_00504c0c,
                     (uint)**(byte **)(&DAT_0054a46c +
                                      (*(uint *)(*param_2 + 0x10) >> 0x10 & 7) * 0xd0));
          copy_bitmap_surface_to_dib_context_helper_00477760
                    (DAT_00504c0c,*(int **)(param_1 + 0x3c),local_48,local_4c - uVar1,local_18);
        }
      }
    }
  }
  return;
}


