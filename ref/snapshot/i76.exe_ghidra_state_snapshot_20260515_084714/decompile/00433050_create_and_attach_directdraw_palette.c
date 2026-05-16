/*
 * Program: i76.exe
 * Function: create_and_attach_directdraw_palette
 * Entry: 00433050
 * Signature: undefined4 __stdcall create_and_attach_directdraw_palette(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_00433050
   suggested_name: create_and_attach_directdraw_palette
   basis: Creates DirectDraw palette and attaches it to front/back buffers; error strings mention
   SetPalette/CreatePalette failures. */

undefined4 create_and_attach_directdraw_palette(void)

{
  HDC hdc;
  undefined1 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  undefined4 local_6c [17];
  uint uStack_28;
  
  puVar3 = local_6c;
  for (iVar2 = 0x1b; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_6c[0] = 0x6c;
  DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x58))(DAT_006080c4,local_6c);
  if (DAT_005fdc0c == 0) {
    DAT_006080c8 = (int *)0x0;
    _DAT_005fdc08 = uStack_28 >> 5 & 1;
    if (_DAT_005fdc08 == 0) {
      DAT_006080c8 = (int *)0x0;
      DAT_005fdc0c = 0;
      return 1;
    }
    hdc = GetDC((HWND)0x0);
    GetSystemPaletteEntries(hdc,0,0x100,(LPPALETTEENTRY)&DAT_005fd520);
    ReleaseDC((HWND)0x0,hdc);
    if (DAT_00608410 == 0) {
      puVar1 = (undefined1 *)((int)&DAT_005fd520 + 3);
      do {
        *puVar1 = 0x40;
        puVar1 = puVar1 + 4;
      } while ((int)puVar1 < 0x5fd54b);
      puVar1 = &DAT_005fd54b;
      do {
        *puVar1 = 1;
        puVar1 = puVar1 + 4;
      } while ((int)puVar1 < 0x5fd8fb);
      puVar1 = &DAT_005fd8fb;
      do {
        *puVar1 = 0x40;
        puVar1 = puVar1 + 4;
      } while ((int)puVar1 < 0x5fd923);
    }
    else {
      DAT_005fd520._3_1_ = 0x40;
      puVar1 = (undefined1 *)((int)&DAT_005fd524 + 3);
      do {
        *puVar1 = 1;
        puVar1 = puVar1 + 4;
      } while ((int)puVar1 < 0x5fd91f);
      DAT_005fd91f = 0x40;
    }
    DAT_005fdc0c = (**(code **)(*DAT_006080b8 + 0x14))
                             (DAT_006080b8,0x44,&DAT_005fd520,&DAT_005fd0e0,0);
    DAT_006080c8 = DAT_005fd0e0;
    if (DAT_005fdc0c == 0) {
      DAT_005fdc0c = (**(code **)(*DAT_006080c4 + 0x7c))(DAT_006080c4,DAT_005fd0e0);
      if (DAT_005fdc0c == 0) {
        DAT_005fdc0c = (**(code **)(*DAT_006080c0 + 0x7c))(DAT_006080c0,DAT_005fd0e0);
        if (DAT_005fdc0c == 0) {
          DAT_005fdc0c = 0;
          _DAT_005fdc10 = 1;
          return 1;
        }
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar4 = s_SetPalette_failed_on_front_buffe_004f10c8;
      }
      else {
        directdraw_error_to_string(DAT_005fdc0c);
        pcVar4 = s_SetPalette_failed_on_back_buffer_004f10f0;
      }
    }
    else {
      directdraw_error_to_string(DAT_005fdc0c);
      pcVar4 = s_CreatePalette_failed___s_004f1118;
    }
  }
  else {
    directdraw_error_to_string(DAT_005fdc0c);
    pcVar4 = s_Failed_to_get_surface_descriptio_004f1134;
  }
  set_directdraw_error_message(pcVar4);
  if (DAT_005fd0e0 != (int *)0x0) {
    (**(code **)(*DAT_005fd0e0 + 8))(DAT_005fd0e0);
    DAT_005fd0e0 = (int *)0x0;
  }
  return 0;
}


