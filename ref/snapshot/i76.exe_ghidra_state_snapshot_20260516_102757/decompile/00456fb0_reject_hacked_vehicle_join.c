/*
 * Program: i76.exe
 * Function: reject_hacked_vehicle_join
 * Entry: 00456fb0
 * Signature: undefined8 __cdecl reject_hacked_vehicle_join(undefined4 param_1, void * param_2, size_t param_3)
 */


/* i76 second-pass rename
   old_name: FUN_00456fb0
   suggested_name: reject_hacked_vehicle_join
   basis: Diagnostic: player tried to join with hacked vehicle. */

undefined8 __cdecl reject_hacked_vehicle_join(undefined4 param_1,void *param_2,size_t param_3)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  char *_Format;
  undefined8 uVar4;
  undefined4 uVar5;
  byte *pbVar6;
  undefined4 local_210;
  int local_20c;
  byte local_208 [4];
  int local_204;
  uchar local_200 [24];
  uchar local_1e8 [80];
  undefined4 local_198 [102];
  
  local_210 = 4;
  if (DAT_00504c18 == 0) {
    iVar1 = dpGetPlayerData(DAT_00541024,param_1,4,&local_20c,&local_210,0);
    if (iVar1 != 0) {
      return 0;
    }
  }
  uVar4 = write_network_vehicle_file(param_2,param_3);
  uVar2 = (uint)uVar4;
  uVar5 = (undefined4)((ulonglong)uVar4 >> 0x20);
  multiplayer_player_vehicle_lookup_helper_00454750((short)param_1,uVar2,uVar5,0);
  if ((DAT_00504c18 == 0 & uVar2) != 0) {
    copy_shell_session_descriptor_block(local_198);
    pbVar6 = local_208;
    pbVar3 = (byte *)format_8char_resource_basename_with_suffix(uVar2,uVar5,&s_dot_vcf);
    iVar1 = compute_bwd2_file_crc32_and_validate_prefix(pbVar3,local_198[0],pbVar6);
    if ((iVar1 == 0) || (local_204 != local_20c)) {
      network_vehicle_message_context_helper_00456640(param_1,1);
      multiplayer_player_count_context_helper_00454620((short)param_1,local_200);
      _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                                      s______s_has_tried_to_join_with_a_h_004f5ca4,local_200);
      sprintf((char *)local_1e8,_Format);
      draw_multiplayer_chat_message(0,local_1e8);
      dpDestroyPlayer();
    }
    uVar4 = 0;
  }
  return uVar4;
}


