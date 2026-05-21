/*
 * Program: i76.exe
 * Function: parse_command_line_options
 * Entry: 0049d1d0
 * Signature: undefined4 __cdecl parse_command_line_options(char * param_1, undefined1 * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_0049d1d0
   suggested_name: parse_command_line_options
   basis: Parses glide/redline/powervr/recordLoads/interval options.
   
   [cgpt_i76exe_render_mode_v13] proposed=parse_command_line_render_backend_options :: Parses
   command-line render backend options including gdi, glide, redline, d3d/dx5draw, powervr, and
   hardware/window mode flags. */

undefined4 __cdecl parse_command_line_options(char *param_1,undefined1 *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  char *_Str1;
  
  *param_2 = 0;
  pcVar2 = strtok(param_1,&DAT_004fe5ec);
  g_resource_cache_prefer_directory_first = 0;
  do {
    if (pcVar2 == (char *)0x0) {
      s_ZPOWERVR_DLL_004fe60c[0] = (char)s_ZPOWERVR_DLL_004fe60c._0_4_;
      s_ZPOWERVR_DLL_004fe60c[1] = SUB41(s_ZPOWERVR_DLL_004fe60c._0_4_,1);
      s_ZPOWERVR_DLL_004fe60c[2] = SUB41(s_ZPOWERVR_DLL_004fe60c._0_4_,2);
      s_ZPOWERVR_DLL_004fe60c[3] = SUB41(s_ZPOWERVR_DLL_004fe60c._0_4_,3);
      s_ZPOWERVR_DLL_004fe60c[4] = (char)s_ZPOWERVR_DLL_004fe60c._4_4_;
      s_ZPOWERVR_DLL_004fe60c[5] = SUB41(s_ZPOWERVR_DLL_004fe60c._4_4_,1);
      s_ZPOWERVR_DLL_004fe60c[6] = SUB41(s_ZPOWERVR_DLL_004fe60c._4_4_,2);
      s_ZPOWERVR_DLL_004fe60c[7] = SUB41(s_ZPOWERVR_DLL_004fe60c._4_4_,3);
      s_ZPOWERVR_DLL_004fe60c[8] = (char)s_ZPOWERVR_DLL_004fe60c._8_4_;
      s_ZPOWERVR_DLL_004fe60c[9] = SUB41(s_ZPOWERVR_DLL_004fe60c._8_4_,1);
      s_ZPOWERVR_DLL_004fe60c[10] = SUB41(s_ZPOWERVR_DLL_004fe60c._8_4_,2);
      s_ZPOWERVR_DLL_004fe60c[0xb] = SUB41(s_ZPOWERVR_DLL_004fe60c._8_4_,3);
      s_ZDX5DRAW_DLL_004fe624[0] = (char)s_ZDX5DRAW_DLL_004fe624._0_4_;
      s_ZDX5DRAW_DLL_004fe624[1] = SUB41(s_ZDX5DRAW_DLL_004fe624._0_4_,1);
      s_ZDX5DRAW_DLL_004fe624[2] = SUB41(s_ZDX5DRAW_DLL_004fe624._0_4_,2);
      s_ZDX5DRAW_DLL_004fe624[3] = SUB41(s_ZDX5DRAW_DLL_004fe624._0_4_,3);
      s_ZDX5DRAW_DLL_004fe624[4] = (char)s_ZDX5DRAW_DLL_004fe624._4_4_;
      s_ZDX5DRAW_DLL_004fe624[5] = SUB41(s_ZDX5DRAW_DLL_004fe624._4_4_,1);
      s_ZDX5DRAW_DLL_004fe624[6] = SUB41(s_ZDX5DRAW_DLL_004fe624._4_4_,2);
      s_ZDX5DRAW_DLL_004fe624[7] = SUB41(s_ZDX5DRAW_DLL_004fe624._4_4_,3);
      s_ZDX5DRAW_DLL_004fe624[8] = (char)s_ZDX5DRAW_DLL_004fe624._8_4_;
      s_ZDX5DRAW_DLL_004fe624[9] = SUB41(s_ZDX5DRAW_DLL_004fe624._8_4_,1);
      s_ZDX5DRAW_DLL_004fe624[10] = SUB41(s_ZDX5DRAW_DLL_004fe624._8_4_,2);
      s_ZDX5DRAW_DLL_004fe624[0xb] = SUB41(s_ZDX5DRAW_DLL_004fe624._8_4_,3);
      s_ZREDLINE_DLL_004fe638[0] = (char)s_ZREDLINE_DLL_004fe638._0_4_;
      s_ZREDLINE_DLL_004fe638[1] = SUB41(s_ZREDLINE_DLL_004fe638._0_4_,1);
      s_ZREDLINE_DLL_004fe638[2] = SUB41(s_ZREDLINE_DLL_004fe638._0_4_,2);
      s_ZREDLINE_DLL_004fe638[3] = SUB41(s_ZREDLINE_DLL_004fe638._0_4_,3);
      s_ZREDLINE_DLL_004fe638[4] = (char)s_ZREDLINE_DLL_004fe638._4_4_;
      s_ZREDLINE_DLL_004fe638[5] = SUB41(s_ZREDLINE_DLL_004fe638._4_4_,1);
      s_ZREDLINE_DLL_004fe638[6] = SUB41(s_ZREDLINE_DLL_004fe638._4_4_,2);
      s_ZREDLINE_DLL_004fe638[7] = SUB41(s_ZREDLINE_DLL_004fe638._4_4_,3);
      s_ZREDLINE_DLL_004fe638[8] = (char)s_ZREDLINE_DLL_004fe638._8_4_;
      s_ZREDLINE_DLL_004fe638[9] = SUB41(s_ZREDLINE_DLL_004fe638._8_4_,1);
      s_ZREDLINE_DLL_004fe638[10] = SUB41(s_ZREDLINE_DLL_004fe638._8_4_,2);
      s_ZREDLINE_DLL_004fe638[0xb] = SUB41(s_ZREDLINE_DLL_004fe638._8_4_,3);
      s_ZGLIDE_DLL_004fe650[0] = (char)s_ZGLIDE_DLL_004fe650._0_4_;
      s_ZGLIDE_DLL_004fe650[1] = SUB41(s_ZGLIDE_DLL_004fe650._0_4_,1);
      s_ZGLIDE_DLL_004fe650[2] = SUB41(s_ZGLIDE_DLL_004fe650._0_4_,2);
      s_ZGLIDE_DLL_004fe650[3] = SUB41(s_ZGLIDE_DLL_004fe650._0_4_,3);
      s_ZGLIDE_DLL_004fe650[4] = (char)s_ZGLIDE_DLL_004fe650._4_4_;
      s_ZGLIDE_DLL_004fe650[5] = SUB41(s_ZGLIDE_DLL_004fe650._4_4_,1);
      s_ZGLIDE_DLL_004fe650[6] = SUB41(s_ZGLIDE_DLL_004fe650._4_4_,2);
      s_ZGLIDE_DLL_004fe650[7] = SUB41(s_ZGLIDE_DLL_004fe650._4_4_,3);
      s_ZGLIDE_DLL_004fe650[8] = (char)s_ZGLIDE_DLL_004fe650._8_2_;
      s_ZGLIDE_DLL_004fe650[9] = SUB21(s_ZGLIDE_DLL_004fe650._8_2_,1);
      g_selected_raster_plugin_dll_name = (char)_g_selected_raster_plugin_dll_name;
      g_selected_raster_plugin_dll_name_1._0_1_ = SUB41(_g_selected_raster_plugin_dll_name,1);
      g_selected_raster_plugin_dll_name_1._1_1_ = SUB41(_g_selected_raster_plugin_dll_name,2);
      g_selected_raster_plugin_dll_name_1._2_1_ = SUB41(_g_selected_raster_plugin_dll_name,3);
      DAT_005dd344 = (char)_DAT_005dd344;
      DAT_005dd344_1._0_1_ = SUB41(_DAT_005dd344,1);
      DAT_005dd344_1._1_1_ = SUB41(_DAT_005dd344,2);
      DAT_005dd344_1._2_1_ = SUB41(_DAT_005dd344,3);
      DAT_005dd348 = (char)_DAT_005dd348;
      DAT_005dd348_1._0_1_ = SUB41(_DAT_005dd348,1);
      DAT_005dd34a = SUB41(_DAT_005dd348,2);
      DAT_005dd348_1._2_1_ = SUB41(_DAT_005dd348,3);
      return 1;
    }
    if ((*pcVar2 == '/') || (*pcVar2 == '-')) {
      _Str1 = pcVar2 + 1;
      iVar3 = _stricmp(_Str1,s_gdi_004fe664);
      if (iVar3 == 0) {
        DAT_004f9f20 = 0;
      }
      else {
        iVar3 = _stricmp(_Str1,s_glide_004fe65c);
        if (iVar3 == 0) {
          g_selected_raster_plugin_dll_name = s_ZGLIDE_DLL_004fe650[0];
          g_selected_raster_plugin_dll_name_1._0_1_ = s_ZGLIDE_DLL_004fe650[1];
          g_selected_raster_plugin_dll_name_1._1_1_ = s_ZGLIDE_DLL_004fe650[2];
          g_selected_raster_plugin_dll_name_1._2_1_ = s_ZGLIDE_DLL_004fe650[3];
          g_cmdline_hardware_window_or_hal_requested = 1;
          g_cmdline_hardware_raster_requested = 1;
          DAT_005dd344 = s_ZGLIDE_DLL_004fe650[4];
          DAT_005dd344_1._0_1_ = s_ZGLIDE_DLL_004fe650[5];
          DAT_005dd344_1._1_1_ = s_ZGLIDE_DLL_004fe650[6];
          DAT_005dd344_1._2_1_ = s_ZGLIDE_DLL_004fe650[7];
          DAT_005dd34a = s_ZGLIDE_DLL_004fe650[10];
          DAT_005dd348 = s_ZGLIDE_DLL_004fe650[8];
          DAT_005dd348_1._0_1_ = s_ZGLIDE_DLL_004fe650[9];
        }
        else {
          iVar3 = _stricmp(_Str1,s_redline_004fe648);
          if (iVar3 == 0) {
            g_selected_raster_plugin_dll_name = s_ZREDLINE_DLL_004fe638[0];
            g_selected_raster_plugin_dll_name_1._0_1_ = s_ZREDLINE_DLL_004fe638[1];
            g_selected_raster_plugin_dll_name_1._1_1_ = s_ZREDLINE_DLL_004fe638[2];
            g_selected_raster_plugin_dll_name_1._2_1_ = s_ZREDLINE_DLL_004fe638[3];
            g_cmdline_hardware_window_or_hal_requested = 1;
            g_cmdline_hardware_raster_requested = 1;
            DAT_005dd344 = s_ZREDLINE_DLL_004fe638[4];
            DAT_005dd344_1._0_1_ = s_ZREDLINE_DLL_004fe638[5];
            DAT_005dd344_1._1_1_ = s_ZREDLINE_DLL_004fe638[6];
            DAT_005dd344_1._2_1_ = s_ZREDLINE_DLL_004fe638[7];
            DAT_005dd348 = s_ZREDLINE_DLL_004fe638[8];
            DAT_005dd348_1._0_1_ = s_ZREDLINE_DLL_004fe638[9];
            DAT_005dd34a = s_ZREDLINE_DLL_004fe638[10];
            DAT_005dd348_1._2_1_ = s_ZREDLINE_DLL_004fe638[0xb];
            DAT_005dd34c = s_ZREDLINE_DLL_004fe638[0xc];
          }
          else {
            iVar3 = _stricmp(_Str1,(char *)&PTR_DAT_004fe634);
            if (iVar3 == 0) {
              g_selected_raster_plugin_dll_name = s_ZDX5DRAW_DLL_004fe624[0];
              g_selected_raster_plugin_dll_name_1._0_1_ = s_ZDX5DRAW_DLL_004fe624[1];
              g_selected_raster_plugin_dll_name_1._1_1_ = s_ZDX5DRAW_DLL_004fe624[2];
              g_selected_raster_plugin_dll_name_1._2_1_ = s_ZDX5DRAW_DLL_004fe624[3];
              g_cmdline_hardware_window_or_hal_requested = 1;
              g_cmdline_hardware_raster_requested = 1;
              DAT_005dd344 = s_ZDX5DRAW_DLL_004fe624[4];
              DAT_005dd344_1._0_1_ = s_ZDX5DRAW_DLL_004fe624[5];
              DAT_005dd344_1._1_1_ = s_ZDX5DRAW_DLL_004fe624[6];
              DAT_005dd344_1._2_1_ = s_ZDX5DRAW_DLL_004fe624[7];
              DAT_005dd348 = s_ZDX5DRAW_DLL_004fe624[8];
              DAT_005dd348_1._0_1_ = s_ZDX5DRAW_DLL_004fe624[9];
              DAT_005dd34a = s_ZDX5DRAW_DLL_004fe624[10];
              DAT_005dd348_1._2_1_ = s_ZDX5DRAW_DLL_004fe624[0xb];
              DAT_005dd34c = s_ZDX5DRAW_DLL_004fe624[0xc];
            }
            else {
              iVar3 = _stricmp(_Str1,s_powervr_004fe61c);
              if (iVar3 == 0) {
                g_selected_raster_plugin_dll_name = s_ZPOWERVR_DLL_004fe60c[0];
                g_selected_raster_plugin_dll_name_1._0_1_ = s_ZPOWERVR_DLL_004fe60c[1];
                g_selected_raster_plugin_dll_name_1._1_1_ = s_ZPOWERVR_DLL_004fe60c[2];
                g_selected_raster_plugin_dll_name_1._2_1_ = s_ZPOWERVR_DLL_004fe60c[3];
                g_cmdline_hardware_window_or_hal_requested = 1;
                g_cmdline_hardware_raster_requested = 1;
                DAT_005dd344 = s_ZPOWERVR_DLL_004fe60c[4];
                DAT_005dd344_1._0_1_ = s_ZPOWERVR_DLL_004fe60c[5];
                DAT_005dd344_1._1_1_ = s_ZPOWERVR_DLL_004fe60c[6];
                DAT_005dd344_1._2_1_ = s_ZPOWERVR_DLL_004fe60c[7];
                DAT_005dd348 = s_ZPOWERVR_DLL_004fe60c[8];
                DAT_005dd348_1._0_1_ = s_ZPOWERVR_DLL_004fe60c[9];
                DAT_005dd34a = s_ZPOWERVR_DLL_004fe60c[10];
                DAT_005dd348_1._2_1_ = s_ZPOWERVR_DLL_004fe60c[0xb];
                DAT_005dd34c = s_ZPOWERVR_DLL_004fe60c[0xc];
              }
              else {
                iVar3 = _stricmp(_Str1,s_hal_004fe608);
                if (iVar3 == 0) {
                  g_cmdline_hardware_window_or_hal_requested = 1;
                }
                else {
                  iVar3 = _stricmp(_Str1,s_recordLoads_004fe5fc);
                  if (iVar3 == 0) {
                    DAT_00504bfc = 1;
                  }
                  else {
                    iVar3 = _strnicmp(_Str1,s_interval_004fe5f0,8);
                    if (iVar3 == 0) {
                      uVar4 = 0xffffffff;
                      DAT_00504c08 = 1;
                      do {
                        if (uVar4 == 0) break;
                        uVar4 = uVar4 - 1;
                        cVar1 = *_Str1;
                        _Str1 = _Str1 + 1;
                      } while (cVar1 != '\0');
                      if (8 < ~uVar4 - 1) {
                        sscanf(pcVar2 + 9,s__d_004f8b80,&DAT_00504c08);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    pcVar2 = strtok((char *)0x0,&DAT_004fe5ec);
  } while( true );
}


