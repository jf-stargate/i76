/*
 * Program: i76.exe
 * Function: directdraw_error_to_string
 * Entry: 00430cc0
 * Signature: char * __cdecl directdraw_error_to_string(int param_1)
 */


/* i76 first-pass rename
   old_name: FUN_00430cc0
   suggested_name: directdraw_error_to_string
   basis: Maps DirectDraw/D3D HRESULT-style errors to diagnostic strings. */

char * __cdecl directdraw_error_to_string(int param_1)

{
  if (param_1 < -0x7fffbffa) {
    if (param_1 == -0x7fffbffb) {
      return s_Generic_failure__004f0010;
    }
    if (param_1 == -0x7fffbfff) {
      return s_Action_not_supported__004f0024;
    }
  }
  else if (param_1 < -0x7ff8ffa8) {
    if (param_1 == -0x7ff8ffa9) {
      return s_One_or_more_of_the_parameters_pa_004eff84;
    }
    if (param_1 == -0x7ff8fff2) {
      return s_DirectDraw_does_not_have_enough_m_004effcc;
    }
  }
  else if (param_1 < -0x7789fff5) {
    if (param_1 == -0x7789fff6) {
      return s_This_surface_can_not_be_attached_004eff20;
    }
    if (param_1 == -0x7789fffb) {
      return s_This_object_is_already_initializ_004eff5c;
    }
  }
  else if (param_1 < -0x7789ffd7) {
    if (param_1 == -0x7789ffd8) {
      return s_Support_is_currently_not_availab_004efeb8;
    }
    if (param_1 == -0x7789ffec) {
      return s_This_surface_can_not_be_detached_004efee0;
    }
  }
  else if (param_1 < -0x7789ffa5) {
    if (param_1 == -0x7789ffa6) {
      return s_Height_of_rectangle_provided_is_n_004efe2c;
    }
    if (param_1 == -0x7789ffc9) {
      return s_An_exception_was_encountered_whi_004efe70;
    }
  }
  else if (param_1 < -0x7789ff9b) {
    if (param_1 == -0x7789ff9c) {
      return s_One_or_more_of_the_caps_bits_pas_004efd94;
    }
    if (param_1 == -0x7789ffa1) {
      return s_Unable_to_match_primary_surface_c_004efdd8;
    }
  }
  else if (param_1 < -0x7789ff87) {
    if (param_1 == -0x7789ff88) {
      return s_DirectDraw_does_not_support_the_r_004efd2c;
    }
    if (param_1 == -0x7789ff92) {
      return s_DirectDraw_does_not_support_the_p_004efd60;
    }
  }
  else if (param_1 < -0x7789ff6e) {
    if (param_1 == -0x7789ff6f) {
      return s_The_pixel_format_was_invalid_as_s_004efcb8;
    }
    if (param_1 == -0x7789ff7e) {
      return s_DirectDraw_received_a_pointer_th_004efce4;
    }
  }
  else if (param_1 < -0x7789ff5f) {
    if (param_1 == -0x7789ff60) {
      return s_Operation_could_not_be_carried_o_004efc44;
    }
    if (param_1 == -0x7789ff6a) {
      return s_Rectangle_provided_was_invalid__004efc94;
    }
  }
  else if (param_1 < -0x7789ff4b) {
    if (param_1 == -0x7789ff4c) {
      return s_Operation_could_not_be_carried_o_004efbbc;
    }
    if (param_1 == -0x7789ff56) {
      return s_There_is_no_3D_present__004efc28;
    }
  }
  else if (param_1 < -0x7789ff2d) {
    if (param_1 == -0x7789ff2e) {
      return s_Operation_could_not_be_carried_o_004efb3c;
    }
    if (param_1 == -0x7789ff33) {
      return s_No_cliplist_available__004efba4;
    }
  }
  else if (param_1 < -0x7789ff28) {
    if (param_1 == -0x7789ff29) {
      return s_Surface_doesn_t_currently_have_a_004efab4;
    }
    if (param_1 == -0x7789ff2c) {
      return s_Create_function_called_without_D_004efae0;
    }
  }
  else if (param_1 < -0x7789ff1e) {
    if (param_1 == -0x7789ff1f) {
      return s_Operation_requires_the_applicati_004ef9dc;
    }
    if (param_1 == -0x7789ff24) {
      return s_Operation_could_not_be_carried_o_004efa4c;
    }
  }
  else if (param_1 < -0x7789ff0f) {
    if (param_1 == -0x7789ff10) {
      return s_There_is_no_GDI_present__004ef990;
    }
    if (param_1 == -0x7789ff1a) {
      return s_Flipping_visible_surfaces_is_not_004ef9ac;
    }
  }
  else if (param_1 < -0x7789ff00) {
    if (param_1 == -0x7789ff01) {
      return s_Requested_item_was_not_found__004ef918;
    }
    if (param_1 == -0x7789ff06) {
      return s_Operation_could_not_be_carried_o_004ef938;
    }
  }
  else if (param_1 < -0x7789fee7) {
    if (param_1 == -0x7789fee8) {
      return s_Operation_could_not_be_carried_o_004ef848;
    }
    if (param_1 == -0x7789fefc) {
      return s_Operation_could_not_be_carried_o_004ef8b8;
    }
  }
  else if (param_1 < -0x7789fec9) {
    if (param_1 == -0x7789feca) {
      return s_Operation_could_not_be_carried_o_004ef78c;
    }
    if (param_1 == -0x7789fede) {
      return s_Operation_could_not_be_carried_o_004ef7e8;
    }
  }
  else if (param_1 < -0x7789feb5) {
    if (param_1 == -0x7789feb6) {
      return s_Operation_could_not_be_carried_o_004ef5e0;
    }
    if (param_1 == -0x7789fec4) {
      return s_DirectDrawSurface_is_not_in_4_bi_004ef648;
    }
    if (param_1 == -0x7789fec3) {
      return s_DirectDrawSurface_is_not_in_4_bi_004ef6b4;
    }
    if (param_1 == -0x7789fec0) {
      return s_DirectDrawSurface_is_not_in_8_bi_004ef72c;
    }
  }
  else if (param_1 < -0x7789feab) {
    if (param_1 == -0x7789feac) {
      return s_Operation_could_not_be_carried_o_004ef508;
    }
    if (param_1 == -0x7789feb1) {
      return s_Operation_could_not_be_carried_o_004ef568;
    }
  }
  else if (param_1 < -0x7789fe97) {
    if (param_1 == -0x7789fe98) {
      return s_The_hardware_needed_for_the_requ_004ef438;
    }
    if (param_1 == -0x7789fea2) {
      return s_Overlay_surfaces_could_not_be_z_l_004ef488;
    }
  }
  else if (param_1 < -0x7789fe6f) {
    if (param_1 == -0x7789fe70) {
      return s_No_src_color_key_specified_for_t_004ef330;
    }
    switch(param_1) {
    case -0x7789fe84:
      return s_DirectDraw_does_not_have_enough_m_004effcc;
    case -0x7789fe82:
      return s_The_hardware_does_not_support_cl_004ef404;
    case -0x7789fe80:
      return s_Can_only_have_ony_color_key_acti_004ef3c4;
    case -0x7789fe7d:
      return s_Access_to_this_palette_is_being_r_004ef360;
    }
  }
  else if (param_1 < -0x7789fe5b) {
    if (param_1 == -0x7789fe5c) {
      return s_This_surface_is_already_a_depend_004ef28c;
    }
    if (param_1 == -0x7789fe66) {
      return s_This_surface_is_already_attached_004ef2e4;
    }
  }
  else if (param_1 < -0x7789fe47) {
    if (param_1 == -0x7789fe48) {
      return s_Access_to_surface_refused_becaus_004ef1ec;
    }
    if (param_1 == -0x7789fe52) {
      return s_Access_to_this_surface_is_being_r_004ef228;
    }
  }
  else if (param_1 < -0x7789fe33) {
    if (param_1 == -0x7789fe34) {
      return s_The_requested_surface_is_not_att_004ef11c;
    }
    if (param_1 == -0x7789fe3e) {
      return s_Access_to_this_surface_is_being_r_004ef144;
    }
  }
  else if (param_1 < -0x7789fe1f) {
    if (param_1 == -0x7789fe20) {
      return s_Size_requested_by_DirectDraw_is_t_004ef094;
    }
    if (param_1 == -0x7789fe2a) {
      return s_Height_requested_by_DirectDraw_i_004ef0ec;
    }
  }
  else if (param_1 < -0x7789fe01) {
    if (param_1 == -0x7789fe02) {
      return s_FOURCC_format_requested_is_unsup_004ef02c;
    }
    if (param_1 == -0x7789fe16) {
      return s_Width_requested_by_DirectDraw_is_004ef064;
    }
  }
  else if (param_1 < -0x7789fde6) {
    if (param_1 == -0x7789fde7) {
      return s_Vertical_blank_is_in_progress__004eefc4;
    }
    if (param_1 == -0x7789fdf8) {
      return s_Bitmask_in_the_pixel_format_requ_004eefe4;
    }
  }
  else if (param_1 < -0x7789fdcf) {
    if (param_1 == -0x7789fdd0) {
      return s_Rectangle_provided_was_not_horiz_004eef08;
    }
    if (param_1 == -0x7789fde4) {
      return s_Informs_DirectDraw_that_the_prev_004eef50;
    }
  }
  else if (param_1 < -0x7789fd43) {
    if (param_1 == -0x7789fd44) {
      return s_D3DERR_BADMAJORVERSION_004ee64c;
    }
    switch(param_1) {
    case -0x7789fdcf:
      return s_The_GUID_passed_to_DirectDrawCre_004eeb8c;
    case -0x7789fdce:
      return s_A_DirectDraw_object_representing_004eed74;
    case -0x7789fdcd:
      return s_A_hardware_only_DirectDraw_objec_004eea20;
    case -0x7789fdcc:
      return s_This_process_already_has_created_004ee6ec;
    case -0x7789fdcb:
      return s_Software_emulation_not_available_004ee9fc;
    case -0x7789fdca:
      return s_Region_passed_to_Clipper__GetCli_004ee6b4;
    case -0x7789fdc9:
      return s_An_attempt_was_made_to_set_a_cli_004eedd0;
    case -0x7789fdc8:
      return s_No_clipper_object_attached_to_su_004eead4;
    case -0x7789fdc7:
      return s_Clipper_notification_requires_an_004ee994;
    case -0x7789fdc6:
      return s_HWND_used_by_DirectDraw_Cooperat_004eec30;
    case -0x7789fdc5:
      return s_The_CooperativeLevel_HWND_has_al_004eeca0;
    case -0x7789fdc4:
      return s_No_palette_object_attached_to_th_004ee8e0;
    case -0x7789fdc3:
      return s_No_hardware_support_for_16_or_25_004ee8ac;
    case -0x7789fdc2:
      return s_Return_if_a_clipper_object_is_at_004eeeac;
    case -0x7789fdc1:
      return s_No_blitter_hardware_present__004eeb04;
    case -0x7789fdc0:
      return s_No_DirectDraw_ROP_hardware__004eea88;
    case -0x7789fdbf:
      return s_Returned_when_GetOverlayPosition_004ee724;
    case -0x7789fdbe:
      return s_Returned_when_GetOverlayPosition_004ee910;
    case -0x7789fdbd:
      return s_Returned_when_the_position_of_th_004eeb24;
    case -0x7789fdbc:
      return s_Returned_when_an_overlay_member_i_004ee864;
    case -0x7789fdbb:
      return s_An_attempt_was_made_to_set_the_c_004eed1c;
    case -0x7789fdba:
      return s_An_attempt_has_been_made_to_flip_004ee820;
    case -0x7789fdb9:
      return s_Can_t_duplicate_primary___3D_sur_004eee30;
    case -0x7789fdb8:
      return s_Surface_was_not_locked__An_attem_004ee7a0;
    case -0x7789fdb7:
      return s_Windows_can_not_create_any_more_D_004eee84;
    case -0x7789fdb6:
      return s_No_DC_was_ever_created_for_this_s_004eeaa8;
    case -0x7789fdb5:
      return s_This_surface_can_not_be_restored_004ee664;
    case -0x7789fdb4:
      return s_This_surface_can_not_be_restored_004eebe0;
    case -0x7789fdb3:
      return s_The_surface_being_used_is_not_a_p_004ee768;
    }
  }
  else if (param_1 < -0x7789fd39) {
    if (param_1 == -0x7789fd3a) {
      return s_D3DERR_EXECUTE_CREATE_FAILED_004ee614;
    }
    if (param_1 == -0x7789fd43) {
      return s_D3DERR_BADMINORVERSION_004ee634;
    }
  }
  else if (param_1 < -0x7789fd11) {
    if (param_1 == -0x7789fd12) {
      return s_D3DERR_LIGHT_SET_FAILED_004ee368;
    }
    switch(param_1) {
    case -0x7789fd39:
      return s_D3DERR_EXECUTE_DESTROY_FAILED_004ee5c0;
    case -0x7789fd38:
      return s_D3DERR_EXECUTE_LOCK_FAILED_004ee5a4;
    case -0x7789fd37:
      return s_D3DERR_EXECUTE_UNLOCK_FAILED_004ee584;
    case -0x7789fd36:
      return s_D3DERR_EXECUTE_LOCKED_004ee5fc;
    case -0x7789fd35:
      return s_D3DERR_EXECUTE_NOT_LOCKED_004ee5e0;
    case -0x7789fd34:
      return s_D3DERR_EXECUTE_FAILED_004ee56c;
    case -0x7789fd33:
      return s_D3DERR_EXECUTE_CLIPPED_FAILED_004ee54c;
    case -0x7789fd30:
      return s_D3DERR_TEXTURE_NO_SUPPORT_004ee530;
    case -0x7789fd2f:
      return s_D3DERR_TEXTURE_CREATE_FAILED_004ee4dc;
    case -0x7789fd2e:
      return s_D3DERR_TEXTURE_DESTROY_FAILED_004ee4bc;
    case -0x7789fd2d:
      return s_D3DERR_TEXTURE_LOCK_FAILED_004ee4a0;
    case -0x7789fd2c:
      return s_D3DERR_TEXTURE_UNLOCK_FAILED_004ee480;
    case -0x7789fd2b:
      return s_D3DERR_TEXTURE_LOAD_FAILED_004ee464;
    case -0x7789fd29:
      return s_D3DERR_TEXTURELOCKED_004ee4fc;
    case -0x7789fd28:
      return s_D3DERR_TEXTURE_NOT_LOCKED_004ee514;
    case -0x7789fd26:
      return s_D3DERR_MATRIX_CREATE_FAILED_004ee444;
    case -0x7789fd25:
      return s_D3DERR_MATRIX_DESTROY_FAILED_004ee424;
    case -0x7789fd24:
      return s_D3DERR_MATRIX_SETDATA_FAILED_004ee404;
    case -0x7789fd22:
      return s_D3DERR_SETVIEWPORTDATA_FAILED_004ee3e4;
    case -0x7789fd1c:
      return s_D3DERR_MATERIAL_CREATE_FAILED_004ee3c4;
    case -0x7789fd1b:
      return s_D3DERR_MATERIAL_DESTROY_FAILED_004ee3a4;
    case -0x7789fd1a:
      return s_D3DERR_MATERIAL_SETDATA_FAILED_004ee384;
    }
  }
  else if (param_1 < 1) {
    if (param_1 == 0) {
      return s_No_error__004ee234;
    }
    switch(param_1) {
    case -0x7789fcf3:
      return s_D3DRMERR_BADOBJECT_004ee354;
    case -0x7789fcf2:
      return s_D3DRMERR_BADTYPE_004ee340;
    case -0x7789fcf1:
      return s_D3DRMERR_BADALLOC_004ee32c;
    case -0x7789fcf0:
      return s_D3DRMERR_FACEUSED_004ee318;
    case -0x7789fcef:
      return s_D3DRMERR_NOTFOUND_004ee304;
    case -0x7789fcee:
      return s_D3DRMERR_NOTDONEYET_004ee2ec;
    case -0x7789fced:
      return s_The_file_was_not_found__004ee2d0;
    case -0x7789fcec:
      return s_D3DRMERR_BADFILE_004ee2bc;
    case -0x7789fceb:
      return s_D3DRMERR_BADDEVICE_004ee2a8;
    case -0x7789fcea:
      return s_D3DRMERR_BADVALUE_004ee294;
    case -0x7789fce9:
      return s_D3DRMERR_BADMAJORVERSION_004ee278;
    case -0x7789fce8:
      return s_D3DRMERR_BADMINORVERSION_004ee25c;
    case -0x7789fce7:
      return s_D3DRMERR_UNABLETOEXECUTE_004ee240;
    }
  }
  return s_Unrecognized_error_value__004ee218;
}


