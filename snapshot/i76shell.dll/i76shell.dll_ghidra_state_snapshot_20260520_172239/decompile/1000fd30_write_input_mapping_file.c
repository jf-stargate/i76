/*
 * Program: i76shell.dll
 * Function: write_input_mapping_file
 * Entry: 1000fd30
 * Signature: undefined4 __stdcall write_input_mapping_file(void)
 */


undefined4 write_input_mapping_file(void)

{
  byte bVar1;
  FILE *_File;
  int iVar2;
  FILE *_File_00;
  char *pcVar3;
  int *piVar4;
  undefined *puVar5;
  char *pcVar6;
  char *local_10c;
  int local_108;
  int *local_104;
  char local_100 [256];
  
  _File = fopen(s_input_map_10046630,&DAT_1004662c);
  if (_File == (FILE *)0x0) {
    return 0;
  }
  fprintf(_File,s___Interstate__76_Input_mapping_f_1004663c);
  piVar4 = &DAT_100450a8;
  pcVar3 = (char *)&DAT_100450d0;
  local_10c = s_throttle_100450b0;
  local_104 = &DAT_100450ac;
  do {
    if ((*local_104 == 0) && (*piVar4 != 0)) {
      iVar2 = _stricmp(local_10c,s_pilot_glance_left_10046664);
      if (iVar2 == 0) {
        local_108 = *piVar4;
        fprintf(_File,s__s___10046abc,s_pilot_glance_left_1004669c);
        fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[local_108],pcVar3);
        fprintf(_File,s___10046aa8);
        fprintf(_File,s__s___10046abc,s_track_yaw_minus_1004668c);
        fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[local_108],pcVar3);
        fprintf(_File,s___10046aa8);
        fprintf(_File,s__s___10046abc,s_overview_x_minus_10046678);
LAB_1001002d:
        puVar5 = (&PTR_DAT_100462a8)[local_108];
LAB_10010035:
        fprintf(_File,s_____10s__s_10046aac,puVar5,pcVar3);
        pcVar6 = s___10046aa8;
      }
      else {
        iVar2 = _stricmp(local_10c,s_pilot_glance_right_100466b0);
        if (iVar2 == 0) {
          iVar2 = *piVar4;
          fprintf(_File,s__s___10046abc,s_pilot_glance_right_100466e4);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[iVar2],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_track_yaw_plus_100466d4);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[iVar2],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_overview_x_plus_100466c4);
          puVar5 = (&PTR_DAT_100462a8)[iVar2];
          goto LAB_10010035;
        }
        iVar2 = _stricmp(local_10c,s_pilot_glance_down_100466f8);
        if (iVar2 == 0) {
          iVar2 = *piVar4;
          fprintf(_File,s__s___10046abc,s_pilot_glance_down_10046734);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[iVar2],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_track_pitch_minus_10046720);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[iVar2],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_overview_z_minus_1004670c);
          puVar5 = (&PTR_DAT_100462a8)[iVar2];
          goto LAB_10010035;
        }
        iVar2 = _stricmp(local_10c,s_pilot_glance_up_10046748);
        if (iVar2 == 0) {
          local_108 = *piVar4;
          fprintf(_File,s__s___10046abc,s_pilot_glance_up_1004677c);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[local_108],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_track_pitch_plus_10046768);
          fprintf(_File,s_____10s__s_10046aac,(&PTR_DAT_100462a8)[local_108],pcVar3);
          fprintf(_File,s___10046aa8);
          fprintf(_File,s__s___10046abc,s_overview_z_plus_10046758);
          goto LAB_1001002d;
        }
        iVar2 = *piVar4;
        if ((iVar2 == 2) || (iVar2 == 3)) {
          iVar2 = _strnicmp(local_10c,&DAT_1004678c,2);
          if (iVar2 == 0) {
            pcVar6 = s_throttle___10046790;
          }
          else {
            iVar2 = _strnicmp(local_10c,&DAT_1004679c,2);
            if (iVar2 != 0) {
              fprintf(_File,s__s___100467ac,local_10c);
              fprintf(_File,s_____10s__s_100467b4,(&PTR_DAT_100462a8)[*piVar4],pcVar3);
              pcVar6 = s___100467c4;
              goto LAB_1001022a;
            }
            pcVar6 = s_steer___100467a0;
          }
          fprintf(_File,pcVar6);
          iVar2 = _strnicmp(pcVar3,s_up_100467c8,2);
          if ((iVar2 == 0) || (iVar2 = _strnicmp(pcVar3,s_down_100467cc,4), iVar2 == 0)) {
            puVar5 = (&PTR_DAT_100462a8)[*piVar4];
            pcVar6 = s_____10s_Down_Up_100467d4;
LAB_100101d4:
            fprintf(_File,pcVar6,puVar5);
          }
          else {
            iVar2 = _strnicmp(pcVar3,s_left_100467e8,4);
            if ((iVar2 == 0) || (iVar2 = _strnicmp(pcVar3,s_righ_100467f0,4), iVar2 == 0)) {
              puVar5 = (&PTR_DAT_100462a8)[*piVar4];
              pcVar6 = s_____10s_Left_Right_100467f8;
              goto LAB_100101d4;
            }
            fprintf(_File,s_____10s__s_10046810,(&PTR_DAT_100462a8)[*piVar4],pcVar3);
          }
          pcVar6 = s___10046820;
          local_104 = local_104 + 0x16;
          local_10c = local_10c + 0x58;
          pcVar3 = pcVar3 + 0x58;
          piVar4 = piVar4 + 0x16;
        }
        else if (iVar2 == 1) {
          fprintf(_File,s__s___10046824,local_10c);
          fprintf(_File,s_____10s__s_1004682c,(&PTR_DAT_100462a8)[*piVar4],pcVar3);
          iVar2 = _stricmp(pcVar3,s_Control_1004683c);
          if ((iVar2 != 0) && (iVar2 = _stricmp(pcVar3,s_Shift_10046844), iVar2 != 0)) {
            fprintf(_File,s___Keyboard_Shift_1004684c);
            fprintf(_File,s___Keyboard_Control_10046860);
          }
          pcVar6 = s___10046878;
        }
        else {
          fprintf(_File,s__s___1004687c,local_10c);
          fprintf(_File,s_____10s__s_10046884,(&PTR_DAT_100462a8)[*piVar4],pcVar3);
          pcVar6 = s___10046894;
        }
      }
LAB_1001022a:
      fprintf(_File,pcVar6);
    }
    local_104 = local_104 + 0x16;
    local_10c = local_10c + 0x58;
    pcVar3 = pcVar3 + 0x58;
    piVar4 = piVar4 + 0x16;
    if (0x10045e6b < (int)local_104) {
      _File_00 = fopen(s_input_def_1004689c,s_r_10046898);
      if (_File_00 != (FILE *)0x0) {
        bVar1 = (byte)_File_00->_flag;
        while ((bVar1 & 0x10) == 0) {
          pcVar3 = fgets(local_100,0x100,_File_00);
          if (pcVar3 != (char *)0x0) {
            fputs(local_100,_File);
          }
          bVar1 = (byte)_File_00->_flag;
        }
        fclose(_File_00);
      }
      fclose(_File);
      return 1;
    }
  } while( true );
}


