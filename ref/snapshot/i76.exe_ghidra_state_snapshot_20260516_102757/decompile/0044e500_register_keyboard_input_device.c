/*
 * Program: i76.exe
 * Function: register_keyboard_input_device
 * Entry: 0044e500
 * Signature: undefined4 __cdecl register_keyboard_input_device(undefined4 param_1, char * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: Escape Key / keyboard */

undefined4 __cdecl register_keyboard_input_device(undefined4 param_1,char *param_2)

{
  int iVar1;
  undefined **ppuVar2;
  undefined4 uVar3;
  char *_Format;
  undefined4 *puVar4;
  undefined **ppuVar5;
  bool bVar6;
  
  ppuVar5 = *(undefined ***)(PTR_DAT_004fe194 + 0x18);
  iVar1 = *(int *)(PTR_DAT_004fe194 + 0x14);
  if (DAT_0053eb48 == 0) {
    DAT_0053eb48 = 1;
    if (iVar1 != 0) {
      ppuVar2 = &PTR_DAT_004f4ca8;
      do {
        *ppuVar2 = *(undefined **)(iVar1 + -0x4f4ca8 + (int)ppuVar2);
        ppuVar2 = ppuVar2 + 1;
      } while ((int)ppuVar2 < 0x4f4e9c);
    }
    if (ppuVar5 == (undefined **)0x0) {
      ppuVar5 = &PTR_s_Escape_Key_004f56f0;
    }
    puVar4 = &DAT_00608ee0;
    do {
      uVar3 = StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,
                            *(undefined4 *)((int)(ppuVar5 + -0x1823b8) + (int)puVar4));
      *puVar4 = uVar3;
      puVar4 = puVar4 + 1;
    } while ((int)puVar4 < 0x6090d4);
    if (PTR_DAT_004fe194 == (undefined *)0x0) {
      bVar6 = false;
    }
    else {
      bVar6 = *(int *)PTR_DAT_004fe194 == 2;
    }
    if (bVar6) {
      _DAT_004f5014 = 0xfc;
      _DAT_004f5016 = 0x2b;
      _DAT_004f501a = 0x2d;
      _DAT_004f501e = 0xe4;
      _DAT_004f5020 = 0xf6;
      _DAT_004f5056 = 0xdf;
      _DAT_004f5058 = 0x60;
      _DAT_004f505a = 0x27;
      _DAT_004f505c = 0xe4;
      _DAT_004f5064 = 0x3c;
    }
  }
  param_2[0x58] = '\0';
  param_2[0x59] = '\0';
  param_2[0x5a] = '\0';
  param_2[0x5b] = '\0';
  param_2[0x5c] = '}';
  param_2[0x5d] = '\0';
  param_2[0x5e] = '\0';
  param_2[0x5f] = '\0';
  sprintf(param_2,s_keyboard_004f4c94);
  _Format = (char *)StrLookupFind(*(undefined4 *)StrLookup_Global_Object_exref,s_Keyboard_004f5228);
  sprintf(param_2 + 0xc,_Format);
  sprintf(param_2 + 0x4c,s_keyboard_004f4c94);
  param_2[0x60] = '\0';
  param_2[0x61] = '\0';
  param_2[0x62] = '\0';
  param_2[99] = '\0';
  param_2[100] = '\0';
  param_2[0x65] = '\0';
  param_2[0x66] = '\0';
  param_2[0x67] = '\0';
  *(undefined4 **)(param_2 + 0x68) = &DAT_00608ee0;
  *(undefined ***)(param_2 + 0x6c) = &PTR_DAT_004f4ca8;
  param_2[0x70] = '\0';
  param_2[0x71] = '\0';
  param_2[0x72] = '\0';
  param_2[0x73] = '\0';
  return 0;
}


