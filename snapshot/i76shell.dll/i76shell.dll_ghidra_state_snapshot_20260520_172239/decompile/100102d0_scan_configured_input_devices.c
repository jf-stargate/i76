/*
 * Program: i76shell.dll
 * Function: scan_configured_input_devices
 * Entry: 100102d0
 * Signature: undefined __stdcall scan_configured_input_devices(void)
 */


void scan_configured_input_devices(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  
  FUN_10018640();
  iVar2 = FUN_100184b0(1);
  iVar6 = 0;
  DAT_10056bfc = 0;
  if (0 < iVar2) {
    do {
      iVar3 = FUN_10018610(iVar6);
      pcVar8 = (char *)(iVar3 + 4);
      iVar3 = _strnicmp(pcVar8,s_k_100468a8,1);
      if (iVar3 == 0) {
        DAT_10056bfc = DAT_10056bfc | 0x8000;
        uVar4 = 0xffffffff;
        do {
          pcVar7 = pcVar8;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar8 + 1;
          cVar1 = *pcVar8;
          pcVar8 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar7 = pcVar7 + -uVar4;
        pcVar8 = PTR_s_keyboard_100462ac;
LAB_100103ae:
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
LAB_100103b5:
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
      }
      else {
        iVar3 = _strnicmp(pcVar8,s_j_100468ac,1);
        if (iVar3 == 0) {
          uVar4 = 0xffffffff;
          DAT_10056bfc = DAT_10056bfc | 0x4000;
          do {
            pcVar7 = pcVar8;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar7 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar7;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          pcVar7 = pcVar7 + -uVar4;
          pcVar8 = PTR_s_Joystick_100462b0;
          for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
            pcVar7 = pcVar7 + 4;
            pcVar8 = pcVar8 + 4;
          }
          goto LAB_100103b5;
        }
        iVar3 = _strnicmp(pcVar8,s_m_100468b0,1);
        if (iVar3 == 0) {
          DAT_10056bfc = DAT_10056bfc | 0x2000;
          uVar4 = 0xffffffff;
          do {
            pcVar7 = pcVar8;
            if (uVar4 == 0) break;
            uVar4 = uVar4 - 1;
            pcVar7 = pcVar8 + 1;
            cVar1 = *pcVar8;
            pcVar8 = pcVar7;
          } while (cVar1 != '\0');
          uVar4 = ~uVar4;
          pcVar7 = pcVar7 + -uVar4;
          pcVar8 = PTR_s_Mouse_100462b4;
          goto LAB_100103ae;
        }
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < iVar2);
  }
  return;
}


