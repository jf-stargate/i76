/*
 * Program: i76.exe
 * Function: flush_keyboard_messages_to_input_ring
 * Entry: 0044e750
 * Signature: undefined4 __stdcall flush_keyboard_messages_to_input_ring(void)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Drains WM_KEYDOWN/WM_SYSKEYDOWN
   messages, maps modifiers, fills the keyboard/input ring, then resets ring cursors.
   old_name: FUN_0044e750 */

undefined4 flush_keyboard_messages_to_input_ring(void)

{
  bool bVar1;
  ushort uVar2;
  BOOL BVar3;
  UINT UVar4;
  uint uVar5;
  UINT UVar6;
  ushort uVar7;
  WPARAM uCode;
  int iVar8;
  tagMSG local_38;
  tagMSG local_1c;
  
  BVar3 = PeekMessageA(&local_1c,(HWND)0x0,0x100,0x108,1);
  if (BVar3 != 0) {
    bVar1 = false;
    uVar5 = local_1c.lParam;
    UVar6 = local_1c.message;
    uCode = local_1c.wParam;
    do {
      switch(UVar6) {
      case 0x100:
      case 0x104:
        uVar7 = *(ushort *)(&DAT_004f4ea0 + uCode * 2);
        if (uVar7 == 0) {
          UVar4 = MapVirtualKeyA(uCode,2);
          iVar8 = tolower((uint)(ushort)(short)(char)UVar4);
          uVar7 = (ushort)iVar8;
          if (uVar7 != 0) goto LAB_0044e7d6;
        }
        else {
LAB_0044e7d6:
          uVar2 = GetKeyState(0x11);
          if ((uVar2 & 0x1000) != 0) {
            uVar7 = uVar7 | 0x100;
          }
          uVar2 = GetKeyState(0x12);
          if ((uVar2 & 0x1000) != 0) {
            uVar7 = uVar7 | 0x400;
          }
          uVar2 = GetKeyState(0x10);
          if ((uVar2 & 0x1000) != 0) {
            uVar7 = uVar7 | 0x200;
          }
          *(ushort *)(&DAT_00608e60 + DAT_0053eb44 * 2) = uVar7;
          DAT_0053eb44 = DAT_0053eb44 + 1;
          if (DAT_0053eb44 == 0x40) {
            DAT_0053eb44 = 0;
            iVar8 = 1;
            break;
          }
          if ((DAT_0053eb44 == DAT_0053eb40) &&
             (DAT_0053eb40 = DAT_0053eb40 + 1, DAT_0053eb40 == 0x40)) {
            DAT_0053eb40 = 0;
          }
        }
        iVar8 = 1;
        break;
      case 0x101:
      case 0x105:
        iVar8 = 0;
        break;
      default:
        goto switchD_0044e79b_caseD_102;
      }
      keyboard_input_binding_context_helper_0044eab0(uCode,uVar5,iVar8);
switchD_0044e79b_caseD_102:
      if (0x103 < UVar6) {
        DefWindowProcA(local_38.hwnd,local_38.message,local_38.wParam,local_38.lParam);
      }
      BVar3 = PeekMessageA(&local_38,(HWND)0x0,0x100,0x108,1);
      if (BVar3 == 0) {
        bVar1 = true;
      }
      else {
        TranslateMessage(&local_38);
        uVar5 = local_38.lParam;
        UVar6 = local_38.message;
        uCode = local_38.wParam;
      }
    } while (!bVar1);
  }
  DAT_0053eb44 = 0;
  DAT_0053eb40 = 0;
  return 0;
}


