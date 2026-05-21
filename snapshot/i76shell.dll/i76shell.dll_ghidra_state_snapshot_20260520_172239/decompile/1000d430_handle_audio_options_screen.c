/*
 * Program: i76shell.dll
 * Function: handle_audio_options_screen
 * Entry: 1000d430
 * Signature: undefined __stdcall handle_audio_options_screen(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void handle_audio_options_screen(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (DAT_100443c0 != 0) {
    DAT_100443c0 = 0;
    PTR_s_Music_Level_100443a0 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Music_Level_1004451c);
    PTR_s_Sfx_Level_100443a4 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Sfx_Level_10044528);
    PTR_s_Voice_Level_100443a8 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Voice_Level_10044534);
    PTR_s_Number_Of_Channels_100443ac =
         (undefined *)
         resolve_localized_shell_string_cached(DAT_100f5360,s_Number_Of_Channels_10044540);
    PTR_s_Done_100443b0 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Done_10044554);
    PTR_s_Stereo_100443b4 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Stereo_1004455c);
    PTR_s_Rev_Channels_100443b8 =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Rev_Channels_10044564);
    PTR_s_Cancel_100443bc =
         (undefined *)resolve_localized_shell_string_cached(DAT_100f5360,s_Cancel_10044574);
  }
  _DAT_10053a30 = 0xffffffff;
  _DAT_10053a34 = 0xffffffff;
  _DAT_10053a5c = 0xffffffff;
  _DAT_10053a60 = 0xffffffff;
  _DAT_10053a2c = 0x8c;
  _DAT_10053a3c = &DAT_10055c88;
  _DAT_10053a4c = PTR_s_Music_Level_100443a0;
  _DAT_10053a58 = 0x8c;
  _DAT_10053a68 = &DAT_10055c88;
  _DAT_10053a28 = 0xcc;
  _DAT_10053a38 = 0;
  _DAT_10053a40 = 0;
  _DAT_10053a44 = &LAB_100168f0;
  _DAT_10053a48 = 0;
  _DAT_10053a50 = 0;
  _DAT_10053a54 = 400;
  _DAT_10053a64 = 0;
  _DAT_10053a6c = 0;
  _DAT_10053a70 = &LAB_1000d290;
  _DAT_10053a74 = &LAB_1000d310;
  _DAT_10053a78 = &DAT_100477b0;
  _DAT_10053a7c = &DAT_100477b0;
  iVar2 = 0;
  iVar1 = 0xca;
  piVar3 = &DAT_10053a80;
  do {
    iVar2 = iVar2 + 1;
    *piVar3 = iVar1;
    iVar1 = iVar1 + 0x11;
    piVar3[1] = 0xa4;
    piVar3[2] = 0xc;
    piVar3[3] = 0xf;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = (int)&LAB_1000d350;
    piVar3[8] = (int)&LAB_1000d3a0;
    piVar3[9] = (int)&DAT_100477b0;
    piVar3[10] = iVar2;
    piVar3 = piVar3 + 0xb;
  } while (iVar1 < 0x174);
  _DAT_10053c40 = 0xffffffff;
  _DAT_10053c44 = 0xffffffff;
  _DAT_10053c6c = 0xffffffff;
  _DAT_10053c70 = 0xffffffff;
  _DAT_10053c3c = 0xd1;
  _DAT_10053c4c = &DAT_10055c88;
  _DAT_10053c5c = PTR_s_Sfx_Level_100443a4;
  _DAT_10053c68 = 0xd1;
  _DAT_10053c78 = &DAT_10055c88;
  _DAT_10053c38 = 0xcc;
  _DAT_10053c48 = 0;
  _DAT_10053c50 = 0;
  _DAT_10053c54 = &LAB_100168f0;
  _DAT_10053c58 = 0;
  _DAT_10053c60 = 0;
  _DAT_10053c64 = 400;
  _DAT_10053c74 = 0;
  _DAT_10053c7c = 0;
  _DAT_10053c80 = &LAB_1000d290;
  _DAT_10053c84 = &LAB_1000d310;
  _DAT_10053c88 = 0x100477b1;
  _DAT_10053c8c = 0x100477b1;
  iVar2 = 0;
  iVar1 = 0xca;
  piVar3 = &DAT_10053c90;
  do {
    iVar2 = iVar2 + 1;
    *piVar3 = iVar1;
    iVar1 = iVar1 + 0x11;
    piVar3[1] = 0xe9;
    piVar3[2] = 0xc;
    piVar3[3] = 0xf;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = (int)&LAB_1000d350;
    piVar3[8] = (int)&LAB_1000d3d0;
    piVar3[9] = 0x100477b1;
    piVar3[10] = iVar2;
    piVar3 = piVar3 + 0xb;
  } while (iVar1 < 0x174);
  _DAT_10053e50 = 0xffffffff;
  _DAT_10053e54 = 0xffffffff;
  _DAT_10053e7c = 0xffffffff;
  _DAT_10053e80 = 0xffffffff;
  _DAT_10053e4c = 0x116;
  _DAT_10053e5c = &DAT_10055c88;
  _DAT_10053e6c = PTR_s_Voice_Level_100443a8;
  _DAT_10053e78 = 0x116;
  _DAT_10053e88 = &DAT_10055c88;
  _DAT_10053e48 = 0xcc;
  _DAT_10053e58 = 0;
  _DAT_10053e60 = 0;
  _DAT_10053e64 = &LAB_100168f0;
  _DAT_10053e68 = 0;
  _DAT_10053e70 = 0;
  _DAT_10053e74 = 400;
  _DAT_10053e84 = 0;
  _DAT_10053e8c = 0;
  _DAT_10053e90 = &LAB_1000d290;
  _DAT_10053e94 = &LAB_1000d310;
  _DAT_10053e98 = 0x100477b2;
  _DAT_10053e9c = 0x100477b2;
  iVar2 = 0;
  iVar1 = 0xca;
  piVar3 = &DAT_10053ea0;
  do {
    iVar2 = iVar2 + 1;
    *piVar3 = iVar1;
    iVar1 = iVar1 + 0x11;
    piVar3[1] = 0x12e;
    piVar3[2] = 0xc;
    piVar3[3] = 0xf;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = (int)&LAB_1000d350;
    piVar3[8] = (int)&LAB_1000d400;
    piVar3[9] = 0x100477b2;
    piVar3[10] = iVar2;
    piVar3 = piVar3 + 0xb;
  } while (iVar1 < 0x174);
  _DAT_10054060 = 0xffffffff;
  _DAT_10054064 = 0xffffffff;
  _DAT_1005408c = 0xffffffff;
  _DAT_10054090 = 0xffffffff;
  _DAT_1005405c = 0x15b;
  _DAT_1005406c = &DAT_10055c88;
  _DAT_1005407c = PTR_s_Number_Of_Channels_100443ac;
  _DAT_10054088 = 0x15b;
  _DAT_10054098 = &DAT_10055c88;
  _DAT_10054058 = 0xcc;
  _DAT_10054068 = 0;
  _DAT_10054070 = 0;
  _DAT_10054074 = &LAB_100168f0;
  _DAT_10054078 = 0;
  _DAT_10054080 = 0;
  _DAT_10054084 = 400;
  _DAT_10054094 = 0;
  _DAT_1005409c = 0;
  _DAT_100540a0 = &LAB_1000d290;
  _DAT_100540a4 = &LAB_1000d330;
  _DAT_100540a8 = 0x100477b3;
  _DAT_100540ac = 0x100477b3;
  iVar2 = 0;
  iVar1 = 0xca;
  piVar3 = &DAT_100540b0;
  do {
    iVar2 = iVar2 + 1;
    *piVar3 = iVar1;
    iVar1 = iVar1 + 0x11;
    piVar3[1] = 0x173;
    piVar3[2] = 0xc;
    piVar3[3] = 0xf;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = (int)&LAB_1000d350;
    piVar3[8] = (int)&LAB_1000d390;
    piVar3[9] = 0x100477b3;
    piVar3[10] = iVar2;
    piVar3 = piVar3 + 0xb;
  } while (iVar1 < 0x152);
  _DAT_10054210 = 0x15e;
  _DAT_10054214 = 0x1b6;
  _DAT_10054218 = 0xffffffff;
  _DAT_1005421c = 0xffffffff;
  _DAT_10054220 = 0;
  _DAT_10054224 = &DAT_10055c88;
  _DAT_10054228 = 0;
  _DAT_1005422c = &LAB_10016860;
  _DAT_10054230 = &LAB_1000d990;
  _DAT_10054234 = PTR_s_Done_100443b0;
  _DAT_10054238 = 1;
  FUN_1000dcc0((undefined4 *)&DAT_1005423c,0x192,0x1b6,0xffffffff,&LAB_10016860,
               PTR_s_Cancel_100443bc,&LAB_1000d990,2);
  _DAT_10054268 = 0xffffffff;
  return;
}


