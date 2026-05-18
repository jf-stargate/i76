/*
 * Program: i76.exe
 * Function: detect_language_and_keyboard
 * Entry: 00499640
 * Signature: uint __stdcall detect_language_and_keyboard(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 second-pass rename
   old_name: FUN_00499640
   suggested_name: detect_language_and_keyboard
   basis: Uses locale, keyboard type, and language strings. */

uint detect_language_and_keyboard(void)

{
  LCID LVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  uint uVar5;
  short sVar6;
  ushort uVar7;
  char local_20 [32];
  
  LVar1 = GetSystemDefaultLCID();
  GetKeyboardType(0);
  iVar2 = GetKeyboardType(1);
  GetKeyboardType(2);
  setlocale(0,s_English_004fe1f4);
  iVar3 = load_project_info_file(s_Language_004fe1e8,local_20,0x20);
  if (iVar3 == 0) {
    uVar7 = (ushort)LVar1 & 0x3ff;
    if (uVar7 == 9) {
      DAT_006547e0 = 1;
    }
    else if (uVar7 == 7) {
      DAT_006547e0 = 2;
    }
    else {
      DAT_006547e0 = (uVar7 != 0x11) - 1 & 3;
    }
  }
  else {
    iVar3 = _stricmp(local_20,s_english_004fe1e0);
    if (iVar3 == 0) {
      DAT_006547e0 = 1;
    }
    else {
      iVar3 = _stricmp(local_20,s_german_004fe1d8);
      if (iVar3 == 0) {
        DAT_006547e0 = 2;
      }
      else {
        iVar3 = _stricmp(local_20,s_japanese_004fe1cc);
        if (iVar3 == 0) {
          DAT_006547e0 = 3;
          iVar3 = load_project_info_file(s_Keyboard_004f5228,local_20,0x20);
          if (iVar3 != 0) {
            iVar3 = _stricmp(local_20,(char *)&PTR_LAB_004fe1c8);
            if (iVar3 == 0) {
              iVar2 = 0xd01;
            }
          }
        }
        else {
          DAT_006547e0 = 0;
        }
      }
    }
  }
  if (DAT_006547e0 == 3) {
    PTR_DAT_004fe194 = (undefined *)&DAT_004fe170;
    if (iVar2 == 0xd01) {
      _DAT_004fe184 = &PTR_PTR_00501388;
      PTR_PTR_004fe188 = (undefined *)&PTR_PTR_00501190;
    }
    else {
      PTR_PTR_004fe188 = (undefined *)&PTR_s_Escape_Key_00500f98;
      if (iVar2 != 0xd05) {
        PTR_PTR_004fe188 = (undefined *)&PTR_s_Escape_Key_004f56f0;
      }
    }
    setlocale(0,s_Japanese_004fe1b4);
    if (DAT_005a7c98 == 0) {
      sVar6 = 0xc0;
      uVar5 = 0x81;
      psVar4 = &DAT_00654902;
      do {
        if (((((psVar4 != (short *)&DAT_0065490a) && (psVar4 != (short *)&DAT_0065490c)) &&
             (psVar4 != (short *)&DAT_006549d6)) &&
            ((psVar4 != (short *)&DAT_006549d8 &&
             (((uVar5 & 0xf0) < 0x91 || (0xdf < (uVar5 & 0xf0))))))) &&
           (((int)psVar4 < 0x6549dd || (0x6549f3 < (int)psVar4)))) {
          *psVar4 = sVar6;
          sVar6 = sVar6 + 0xc0;
        }
        psVar4 = psVar4 + 1;
        uVar5 = uVar5 + 1;
      } while ((int)psVar4 < 0x6549f9);
      DAT_005a7c98 = 1;
    }
    *(undefined **)(PTR_DAT_004fe194 + 0x1c) = &DAT_00654800;
  }
  else {
    PTR_DAT_004fe194 = (undefined *)&DAT_004fe148;
    if (DAT_006547e0 == 2) {
      PTR_PTR_004fe160 = (undefined *)&PTR_s_Escape_Key_00501580;
      setlocale(0,s_German_004fe1c0);
    }
    else {
      PTR_PTR_004fe160 = (undefined *)&PTR_s_Escape_Key_004f56f0;
      setlocale(0,s_English_004fe1f4);
    }
  }
  DAT_006547e4 = *(undefined4 *)(PTR_DAT_004fe194 + 0x1c);
  DAT_005a7c94 = *(undefined4 *)(PTR_DAT_004fe194 + 0x20);
  *(uint *)PTR_DAT_004fe194 = DAT_006547e0;
  return DAT_006547e0;
}


