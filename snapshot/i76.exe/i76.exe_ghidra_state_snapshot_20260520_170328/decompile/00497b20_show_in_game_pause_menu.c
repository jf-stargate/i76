/*
 * Program: i76.exe
 * Function: show_in_game_pause_menu
 * Entry: 00497b20
 * Signature: undefined __stdcall show_in_game_pause_menu(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: strings Load Bookmark/Abort Mission/Options/Exit */

void show_in_game_pause_menu(void)

{
  bool bVar1;
  
  _DAT_004fbe0c =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Load_Bookmark_004fdd98);
  _DAT_004fbe48 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fbe84 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Play_Options_004fdd78);
  _DAT_004fbec0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Graphic_Detail_004fdd68);
  _DAT_004fbefc =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Audio_Control_004fdd58);
  _DAT_004fbf38 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_004fdd50);
  _DAT_004fbf74 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fbfb0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Play_Options_004fdd78);
  _DAT_004fbfec =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Graphic_Detail_004fdd68);
  _DAT_004fc028 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Audio_Control_004fdd58);
  _DAT_004fc064 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_004fdd50);
  _DAT_004fc224 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Replay_004fdd48);
  _DAT_004fc260 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Reconfigure_004fdd3c)
  ;
  _DAT_004fc29c =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fc2d8 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_Game_004fdd30);
  _DAT_004fc314 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fc354 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Replay_004fdd48);
  _DAT_004fc390 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fc3cc = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_Game_004fdd30);
  _DAT_004fc408 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fc4dc =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Arcade_Phys__004fdd18);
  _DAT_004fc518 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_No_Salv__Manag__004fdd08);
  _DAT_004fc554 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Unlim__Ammo_004fdcfc)
  ;
  _DAT_004fc590 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Unlim__Armor_004fdcec);
  _DAT_004fc5cc =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Unlim__Chas__Rein__004fdcd8);
  _DAT_004fc608 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Unlim__Wiper_Fluid_004fdcc4);
  _DAT_004fc644 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Difficulty_Level_004fdcb0);
  _DAT_004fc680 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Done_004fdca8);
  _DAT_004fc6bc = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fc7b4 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Screen_Resolution_004fdc94);
  _DAT_004fc7f0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Monitor_Brightness_004fdc80);
  _DAT_004fc82c =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Visibility_Range_004fdc6c);
  _DAT_004fc868 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Clouds_004fdc64);
  _DAT_004fc8a4 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Horizon_Textures_004fdc50);
  _DAT_004fc8e0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Terrain_Textures_004fdc3c);
  _DAT_004fc91c =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Terrain_Resolution_004fdc28);
  _DAT_004fc958 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Terrain_Detail_004fdc18);
  _DAT_004fc994 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Object_Detail_004fdc08);
  _DAT_004fc9d0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Shadow_Detail_004fdbf8);
  _DAT_004fca0c =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Ext__Instrum__Disp__004fdbe4);
  _DAT_004fca48 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Rear_Mirror_004fdbd8)
  ;
  _DAT_004fca84 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Reset_004fdbd0);
  _DAT_004fcac0 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Done_004fdca8);
  _DAT_004fcafc = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fcbd4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Music_Level_004fdbc4)
  ;
  _DAT_004fcc10 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_SFX_Level_004fdbb8);
  _DAT_004fcc4c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Voice_Level_004fdbac)
  ;
  _DAT_004fcc88 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Number_Of_Channels_004fdb98);
  _DAT_004fccc4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Done_004fdca8);
  _DAT_004fcd00 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fcdd4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Yes_004fdb94);
  _DAT_004fce10 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                     s_Are_you_gonna_leave_me__Sweethea_004fdb70);
  _DAT_004fce4c = 0;
  _DAT_004fce88 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_No_004fdb6c);
  _DAT_004fcf64 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                     s_You_have_chosen_an_option_that_w_004fdb0c);
  _DAT_004fcfa0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_I_m_a_cheater_004fdafc);
  _DAT_004fcfdc =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_I_m_a_swinger_004fdaec);
  _DAT_004fd12c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Replay_004fdd48);
  _DAT_004fd168 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Reconfigure_004fdd3c)
  ;
  _DAT_004fd1a4 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fd1e0 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_Game_004fdd30);
  _DAT_004fd294 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Replay_004fdd48);
  _DAT_004fd2d0 =
       StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Abort_Mission_004fdd88);
  _DAT_004fd30c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Exit_Game_004fdd30);
  _DAT_004fd45c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_OK_004fdae8);
  _DAT_004fd514 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_OK_004fdae8);
  _DAT_004fd550 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Cancel_004fdd28);
  _DAT_004fd660 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Yes_004fdb94);
  _DAT_004fd69c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_No_004fdb6c);
  _DAT_00655120 = s_Meet_Taurus_004fdadc;
  _DAT_00655124 = s_Counter_Strike_004fdacc;
  _DAT_00655128 = s_The_Two_Samurai_004fdabc;
  _DAT_0065512c = s_The_Desert_War_004fdaac;
  _DAT_00655130 = s_Roswell_004fdaa4;
  _DAT_00655134 = s_Fire_In_Barstow_004fda94;
  _DAT_00655138 = s_The_Blood_On_The_Highway_004fda78;
  _DAT_0065513c = s_Raising_Arizona_004fda68;
  _DAT_00655140 = s_Wild_At_Heart_004fda58;
  _DAT_00655144 = s_The_Terminator_004fda48;
  _DAT_00655148 = s_How_The_West_Was_Won_004fda30;
  _DAT_0065514c = s_Revolution__9_004fda20;
  _DAT_00655150 = s_The_Ugly_Underneath_004fda0c;
  _DAT_00655154 = s_Close_To_The_Edge_004fd9f8;
  _DAT_00655158 = s_Take_It_To_The_Limit_004fd9e0;
  _DAT_0065515c = s_Homeward_Bound_004fd9d0;
  _DAT_00655160 = s_The_Truth_Is_Out_There_004fd9b8;
  _DAT_005a60d0 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Wimp_004fd9b0);
  _DAT_005a60d4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Champ_004fd9a8);
  _DAT_005a60d8 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Badass_004fd9a0);
  _DAT_004fc790 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Error_004fd998);
  _DAT_005a60e0 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Near_004fd990);
  _DAT_005a60e4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Med__004fd988);
  _DAT_005a60e8 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Far_004fd984);
  _DAT_005a60f0 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a60f4 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_On_004fd980);
  _DAT_005a60f8 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a60fc = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_On_004fd980);
  _DAT_005a6100 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a6104 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_On_004fd980);
  _DAT_005a6108 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a610c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  _DAT_005a6110 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a6114 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_On_004fd980);
  _DAT_005a6118 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a611c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Med__004fd988);
  _DAT_005a6120 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  _DAT_005a6128 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a612c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  _DAT_005a6130 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a6134 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a6138 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  _DAT_005a6140 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a6144 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  _DAT_005a6148 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,&PTR_DAT_004fd8cc);
  _DAT_005a614c = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Low_004fd97c);
  _DAT_005a6150 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_High_004fd974);
  if (PTR_DAT_004fe194 == (undefined *)0x0) {
    bVar1 = false;
  }
  else {
    bVar1 = *(int *)PTR_DAT_004fe194 == 2;
  }
  if (bVar1) {
    _DAT_004fb310 = 0x9e;
    _DAT_004fb318 = 0x32;
    _DAT_004fb970 = 0x37;
    _DAT_004fb978 = 0x1b;
    _DAT_004fb330 = 0xdf;
    _DAT_004fb338 = 0x42;
    _DAT_004fb990 = 0x52;
    _DAT_004fb998 = 0x2c;
    _DAT_004fb350 = 0x43;
    _DAT_004fb358 = 0x51;
    _DAT_004fb9b0 = 2;
    _DAT_004fb9b8 = 0x32;
    return;
  }
  if (PTR_DAT_004fe194 == (undefined *)0x0) {
    bVar1 = false;
  }
  else {
    bVar1 = *(int *)PTR_DAT_004fe194 == 3;
  }
  if (bVar1) {
    _DAT_004fbb30 = 0x5f;
    _DAT_004fb4d8 = 0x46;
    _DAT_004fbb38 = 0x1c;
    _DAT_004fb330 = 0xdf;
    _DAT_004fb338 = 0x46;
    _DAT_004fb990 = 0x5c;
    _DAT_004fb998 = 0x21;
  }
  return;
}


