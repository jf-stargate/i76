/*
 * Program: i76shell.dll
 * Function: create_multiplayer_connection
 * Entry: 10036010
 * Signature: undefined4 __cdecl create_multiplayer_connection(undefined4 param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl create_multiplayer_connection(undefined4 param_1)

{
  byte bVar1;
  char *pcVar2;
  int iVar3;
  LPCSTR pCVar4;
  LPCSTR lpText;
  byte *pbVar5;
  bool bVar6;
  UINT UVar7;
  undefined4 local_104;
  char local_100 [256];
  
  dp_enableDebugPrint(1);
  if (DAT_100f5354 == 0) {
    if (DAT_100f5344 == (byte *)0x0) {
LAB_100361b4:
      DAT_100f5344 = &DAT_100f5358;
    }
    else {
      pcVar2 = s_Unknown_1004cef8;
      pbVar5 = DAT_100f5344;
      do {
        bVar1 = *pcVar2;
        bVar6 = bVar1 < *pbVar5;
        if (bVar1 != *pbVar5) {
LAB_100361ab:
          iVar3 = (1 - (uint)bVar6) - (uint)(bVar6 != 0);
          goto LAB_100361b0;
        }
        if (bVar1 == 0) break;
        bVar1 = pcVar2[1];
        bVar6 = bVar1 < pbVar5[1];
        if (bVar1 != pbVar5[1]) goto LAB_100361ab;
        pcVar2 = pcVar2 + 2;
        pbVar5 = pbVar5 + 2;
      } while (bVar1 != 0);
      iVar3 = 0;
LAB_100361b0:
      if (iVar3 == 0) goto LAB_100361b4;
    }
    read_modem_ini_settings();
    _DAT_100f5330 = DAT_10057a8c + -1;
    _DAT_100f5334 = DAT_10057a88;
    _DAT_100f5348 = &DAT_10057a94;
    _DAT_100f5350 = DAT_10057a90;
    _DAT_100f533c = 0x3039;
    _DAT_100f5340 = &DAT_100f5318;
    _DAT_100f5318 = 0;
    if ((DAT_100d21b0 == 0) && (DAT_100d21b4 == 0)) {
      pcVar2 = (char *)0x0;
    }
    else {
      pcVar2 = s_lobby_dat_1004cf00;
    }
    iVar3 = dpCreate(&local_104,param_1,&DAT_100f5328,pcVar2);
    if (iVar3 != 0) goto LAB_1003608b;
    iVar3 = 0;
    if ((((DAT_100f531c != 0) && (DAT_100f5320 != 0)) && (DAT_100d21b0 == 0)) && (DAT_100d21b4 == 0)
       ) {
      iVar3 = dpSetGameServer(local_104,DAT_100f531c);
      if (iVar3 == 0) {
        return local_104;
      }
      iVar3 = DAT_100f531c;
      pcVar2 = (char *)resolve_localized_shell_string_cached
                                 (DAT_100f5360,s_Bad_Game_Server_Address___s___1004cf0c);
      sprintf(local_100,pcVar2,iVar3);
      UVar7 = 0;
      pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004cf2c);
      MessageBoxA(DAT_100f702c,local_100,pCVar4,UVar7);
      dpDestroy(local_104,0);
      return 0;
    }
  }
  else {
    read_modem_ini_settings();
    _DAT_100f5330 = DAT_10057a8c + -1;
    _DAT_100f5334 = DAT_10057a88;
    if ((DAT_100d21b0 == 0) && (DAT_100d21b4 == 0)) {
      pcVar2 = (char *)0x0;
    }
    else {
      pcVar2 = s_lobby_dat_1004ceec;
    }
    iVar3 = dpCreate(&local_104,param_1,&DAT_100f5328,pcVar2);
  }
  if (iVar3 == 0) {
    return local_104;
  }
LAB_1003608b:
  switch(DAT_100f5324) {
  case 0:
    UVar7 = 0;
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004cf34);
    pcVar2 = s_Unable_to_create_an_internet_con_1004cf3c;
    break;
  case 1:
    UVar7 = 0;
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004cffc);
    pcVar2 = s_Unable_to_create_a_modem_connect_1004d004;
    break;
  case 2:
    UVar7 = 0;
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004d108);
    pcVar2 = s_Unable_to_create_an_IPX_connecti_1004d110;
    break;
  case 3:
    UVar7 = 0;
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004d184);
    pcVar2 = s_Unable_to_create_a_null_modem_co_1004d18c;
    break;
  default:
    UVar7 = 0;
    pCVar4 = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,s_Error_1004d204);
    pcVar2 = s_This_service_could_not_be_opened_1004d20c;
  }
  lpText = (LPCSTR)resolve_localized_shell_string_cached(DAT_100f5360,pcVar2);
  MessageBoxA(DAT_100f702c,lpText,pCVar4,UVar7);
  dpDestroy(local_104,0);
  return 0;
}


