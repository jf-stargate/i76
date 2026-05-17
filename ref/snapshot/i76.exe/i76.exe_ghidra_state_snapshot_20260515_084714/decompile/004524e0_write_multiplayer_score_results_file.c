/*
 * Program: i76.exe
 * Function: write_multiplayer_score_results_file
 * Entry: 004524e0
 * Signature: undefined __stdcall write_multiplayer_score_results_file(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=MEDIUM_HIGH] Writes NSCR.DAT style
   0x54-byte multiplayer/session score result records. */

void write_multiplayer_score_results_file(void)

{
  short sVar1;
  FILE *_File;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  FILE *pFVar7;
  FILE *local_c8;
  uint local_c4;
  FILE *local_c0;
  int local_bc;
  uint local_b8;
  uint local_b4;
  uint local_b0;
  uint local_ac;
  uint local_a8;
  uchar local_a4 [32];
  uchar local_84 [31];
  undefined1 local_65;
  uint local_64;
  undefined4 local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  undefined4 local_50;
  uchar local_4a [74];
  
  _unlink(s_NSCR_DAT_004f5a9c);
  _File = fopen(s_NSCR_DAT_004f5a9c,s_wb_004edf28);
  uVar4 = 0;
  if (_File != (FILE *)0x0) {
    local_c0 = _File;
    iVar2 = is_network_or_trip_runtime_mode();
    if (iVar2 == 0) {
      iVar2 = multiplayer_chat_ui_context_helper_00452e10();
      if (iVar2 == 0) {
        local_bc = 0;
        local_c4 = get_multiplayer_player_count_or_limit();
        fwrite(&local_c4,4,1,_File);
        fwrite(&local_bc,4,1,_File);
        local_c8 = (FILE *)0x0;
        do {
          pFVar7 = local_c8;
          sVar1 = get_multiplayer_player_record_and_copy_name((int)local_c8,local_a4);
          if (sVar1 != 0) {
            get_multiplayer_player_spawn_score_fields
                      (sVar1,&local_b8,(undefined2 *)&local_b4,(undefined2 *)&local_ac);
            local_58 = local_b4 & 0xffff;
            local_5c = local_ac & 0xffff;
            local_54 = local_b8;
            local_60 = 0;
            iVar2 = multiplayer_player_table_context_helper_004547c0(sVar1);
            if (iVar2 != 0) {
              local_60 = ftol();
            }
            puVar5 = &local_50;
            for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar5 = 0;
              puVar5 = puVar5 + 1;
            }
            local_b0 = 0x50;
            iVar2 = dpGetPlayerData(DAT_00541024,sVar1,1,&local_50,&local_b0,0);
            if (iVar2 == 0) {
              _mbsnbcpy(local_84,local_4a,0x1f);
              local_65 = 0;
            }
            else {
              local_84[0] = DAT_00504c28;
            }
            fwrite(local_a4,0x54,1,local_c0);
            uVar4 = uVar4 + 1;
            _File = local_c0;
            pFVar7 = local_c8;
            if (local_c4 <= uVar4) break;
          }
          local_c8 = (FILE *)((int)&pFVar7->_ptr + 1);
          _File = local_c0;
        } while (local_c8 < (FILE *)0x10);
      }
      else {
        local_a8 = 1;
        local_c8 = (FILE *)get_multiplayer_player_count_or_limit();
        fwrite(&local_c8,4,1,_File);
        fwrite(&local_a8,4,1,_File);
        local_c0 = (FILE *)0x0;
        do {
          local_c4 = 0;
          do {
            uVar6 = local_c4;
            sVar1 = get_multiplayer_player_record_and_copy_name(local_c4,local_a4);
            if ((sVar1 != 0) &&
               (lookup_multiplayer_player_vehicle_config_id(sVar1,&local_b0),
               (local_b0 >> 0x10 & 7) == uVar4)) {
              get_multiplayer_player_spawn_score_fields
                        (sVar1,&local_b4,(undefined2 *)&local_b8,(undefined2 *)&local_ac);
              local_58 = local_b8 & 0xffff;
              local_5c = local_ac & 0xffff;
              local_54 = local_b4;
              local_60 = 0;
              local_64 = uVar4;
              iVar2 = multiplayer_player_table_context_helper_004547c0(sVar1);
              if (iVar2 != 0) {
                local_60 = ftol();
              }
              puVar5 = &local_50;
              for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
                *puVar5 = 0;
                puVar5 = puVar5 + 1;
              }
              local_bc = 0x50;
              iVar2 = dpGetPlayerData(DAT_00541024,sVar1,1,&local_50,&local_bc,0);
              if (iVar2 == 0) {
                _mbsnbcpy(local_84,local_4a,0x1f);
                local_65 = 0;
              }
              else {
                local_84[0] = DAT_00504c28;
              }
              fwrite(local_a4,0x54,1,_File);
              local_c0 = (FILE *)((int)&local_c0->_ptr + 1);
              uVar6 = local_c4;
              if (local_c8 <= local_c0) break;
            }
            local_c4 = uVar6 + 1;
          } while (local_c4 < 0x10);
          uVar4 = uVar4 + 1;
        } while (uVar4 < 8);
      }
    }
    else {
      local_c4 = 1;
      local_c8 = (FILE *)0x0;
      fwrite(&local_c4,4,1,_File);
      fwrite(&local_c8,4,1,_File);
      copy_multiplayer_scoreboard_name_string((char *)local_a4);
      copy_multiplayer_score_results_name_string((char *)local_84);
      get_multiplayer_score_accumulators(&local_a8,(undefined2 *)&local_c0);
      piVar3 = (int *)get_active_player_or_camera_world_object_entry();
      iVar2 = local_bc;
      if (piVar3 != (int *)0x0) {
        iVar2 = *(int *)(*piVar3 + 0x70);
        ftol();
      }
      local_58 = (uint)local_c0 & 0xffff;
      local_5c = (uint)((*(uint *)(iVar2 + 0x454) & 0x8020) != 0);
      local_54 = local_a8;
      local_60 = 0;
      fwrite(local_a4,0x54,1,_File);
    }
    fclose(_File);
  }
  return;
}


