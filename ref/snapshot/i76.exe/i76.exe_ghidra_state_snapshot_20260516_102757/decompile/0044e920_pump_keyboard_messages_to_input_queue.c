/*
 * Program: i76.exe
 * Function: pump_keyboard_messages_to_input_queue
 * Entry: 0044e920
 * Signature: undefined __cdecl pump_keyboard_messages_to_input_queue(UINT param_1, WPARAM param_2, uint param_3)
 */


/* [cgpt i76.exe main runtime/FSM rename v21; confidence=HIGH] Processes a supplied keyboard message
   and any queued keyboard messages into the input ring.
   kept_existing_name: pump_keyboard_messages_to_input_queue */

void __cdecl pump_keyboard_messages_to_input_queue(UINT param_1,WPARAM param_2,uint param_3)

{
  bool bVar1;
  ushort uVar2;
  UINT UVar3;
  BOOL BVar4;
  ushort uVar5;
  int iVar6;
  tagMSG local_1c;
  
  bVar1 = false;
  do {
    switch(param_1) {
    case 0x100:
    case 0x104:
      uVar5 = *(ushort *)(&DAT_004f4ea0 + param_2 * 2);
      if (uVar5 == 0) {
        UVar3 = MapVirtualKeyA(param_2,2);
        iVar6 = tolower((uint)(ushort)(short)(char)UVar3);
        uVar5 = (ushort)iVar6;
        if (uVar5 != 0) goto LAB_0044e985;
      }
      else {
LAB_0044e985:
        uVar2 = GetKeyState(0x11);
        if ((uVar2 & 0x1000) != 0) {
          uVar5 = uVar5 | 0x100;
        }
        uVar2 = GetKeyState(0x12);
        if ((uVar2 & 0x1000) != 0) {
          uVar5 = uVar5 | 0x400;
        }
        uVar2 = GetKeyState(0x10);
        if ((uVar2 & 0x1000) != 0) {
          uVar5 = uVar5 | 0x200;
        }
        *(ushort *)(&DAT_00608e60 + DAT_0053eb44 * 2) = uVar5;
        DAT_0053eb44 = DAT_0053eb44 + 1;
        if (DAT_0053eb44 == 0x40) {
          DAT_0053eb44 = 0;
          iVar6 = 1;
          break;
        }
        if ((DAT_0053eb44 == DAT_0053eb40) &&
           (DAT_0053eb40 = DAT_0053eb40 + 1, DAT_0053eb40 == 0x40)) {
          DAT_0053eb40 = 0;
        }
      }
      iVar6 = 1;
      break;
    case 0x101:
    case 0x105:
      iVar6 = 0;
      break;
    default:
      goto switchD_0044e94a_caseD_102;
    }
    keyboard_input_binding_context_helper_0044eab0(param_2,param_3,iVar6);
switchD_0044e94a_caseD_102:
    if (0x103 < param_1) {
      DefWindowProcA(local_1c.hwnd,local_1c.message,local_1c.wParam,local_1c.lParam);
    }
    BVar4 = PeekMessageA(&local_1c,(HWND)0x0,0x100,0x108,1);
    if (BVar4 == 0) {
      bVar1 = true;
    }
    else {
      TranslateMessage(&local_1c);
      param_3 = local_1c.lParam;
      param_1 = local_1c.message;
      param_2 = local_1c.wParam;
    }
    if (bVar1) {
      return;
    }
  } while( true );
}


