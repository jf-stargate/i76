/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0041e730
 * Entry: 00401118
 * Signature: undefined __cdecl thunk_FUN_0041e730(UINT param_1, byte param_2)
 */


void __cdecl thunk_FUN_0041e730(UINT param_1,byte param_2)

{
  if ((DAT_016420fe & param_2) == 0) {
    CheckMenuItem(DAT_01641ed0,param_1,8);
    SendMessageA(DAT_01641fa8,0x402,param_1,1);
    DAT_016420fe = DAT_016420fe | param_2;
    if (param_1 == 0x8011) {
      CheckMenuItem(DAT_01641ed0,0x8010,0);
      SendMessageA(DAT_01641fa8,0x402,0x8010,0);
      DAT_016420fe = DAT_016420fe & 0xfd;
    }
    else if (param_1 == 0x8010) {
      CheckMenuItem(DAT_01641ed0,0x8011,0);
      SendMessageA(DAT_01641fa8,0x402,0x8011,0);
      DAT_016420fe = DAT_016420fe & 0xfb;
    }
  }
  else {
    CheckMenuItem(DAT_01641ed0,param_1,0);
    SendMessageA(DAT_01641fa8,0x402,param_1,0);
    DAT_016420fe = DAT_016420fe & ~param_2;
  }
  InvalidateRgn(DAT_01641fb4,(HRGN)0x0,1);
  return;
}


