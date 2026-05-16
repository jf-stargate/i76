/*
 * Program: i76.exe
 * Function: load_raster_plugin_and_resolve_exports
 * Entry: 00426900
 * Signature: undefined __cdecl load_raster_plugin_and_resolve_exports(LPCSTR param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* i76 first-pass rename
   old_name: FUN_00426900
   suggested_name: load_raster_plugin_and_resolve_exports
   basis: Loads raster/render plugin DLL and resolves render backend exports such as Render,
   SetState, LockDisplay, UpdateTexture. */

void __cdecl load_raster_plugin_and_resolve_exports(LPCSTR param_1)

{
  char cVar1;
  bool bVar2;
  HMODULE hModule;
  FARPROC pFVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 *puVar9;
  int local_104;
  char local_100 [256];
  
  hModule = LoadLibraryA(param_1);
  if ((hModule != (HMODULE)0x0) &&
     (pFVar3 = GetProcAddress(hModule,s_GetFuncDesc_004ede54), pFVar3 != (FARPROC)0x0)) {
    (*pFVar3)(local_100,&local_104,0);
    iVar4 = _stricmp(local_100,s_RASTER_004c2628);
    if (iVar4 == 0) {
      if (DAT_00524690 != 0) {
        if ((char)DAT_00524694 == '\0') {
          if (DAT_005246d4 != local_104) {
            FreeLibrary(hModule);
            return;
          }
        }
        else {
          iVar4 = _stricmp((char *)&DAT_00524694,param_1);
          if (iVar4 != 0) {
            FreeLibrary(hModule);
            return;
          }
        }
      }
      pFVar3 = GetProcAddress(hModule,s_CheckFunc_004ede48);
      if ((char)DAT_005246b4 == '\0') {
        puVar9 = (undefined4 *)0x0;
      }
      else {
        puVar9 = &DAT_005246b4;
      }
      iVar4 = (*pFVar3)(puVar9);
      if (iVar4 == 0) {
        bVar2 = false;
      }
      else if (((local_104 == 0) || (local_104 == 1)) || (local_104 == 2)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        DAT_00608ba0 = local_104;
        _DAT_00608ba4 = GetProcAddress(hModule,s_SetLumaTable_004ede38);
        DAT_00608ba8 = GetProcAddress(hModule,s_FirstDevice_004ede2c);
        DAT_00608bac = GetProcAddress(hModule,s_LastDevice_004ede20);
        DAT_00608bb0 = GetProcAddress(hModule,s_Render_004ede18);
        DAT_00608bb4 = GetProcAddress(hModule,s_RenderRefresh_004ede08);
        _DAT_00608bbc = GetProcAddress(hModule,s_GetSocketCaps_004eddf8);
        DAT_00608bc0 = GetProcAddress(hModule,s_SetState_004eddec);
        _DAT_00608bc4 = GetProcAddress(hModule,s_SetTexturePalette_004eddd8);
        DAT_00608bc8 = GetProcAddress(hModule,s_LockDisplay_004eddcc);
        DAT_00608bcc = GetProcAddress(hModule,s_UnlockDisplay_004eddbc);
        DAT_00608bd0 = GetProcAddress(hModule,s_RefreshDisplay_004eddac);
        _DAT_00608bd4 = GetProcAddress(hModule,s_PreloadTexture_004edd9c);
        _DAT_00608bd8 = GetProcAddress(hModule,s_RenderNoClip_004edd8c);
        _DAT_00608bdc = GetProcAddress(hModule,s_RestoreDevice_004edd7c);
        _DAT_00608be0 = GetProcAddress(hModule,s_LostDeviceDisplay_004edd68);
        DAT_00608be4 = GetProcAddress(hModule,s_UpdateTexture_004edd58);
        uVar5 = 0xffffffff;
        DAT_005246d4 = local_104;
        do {
          pcVar7 = param_1;
          if (uVar5 == 0) break;
          uVar5 = uVar5 - 1;
          pcVar7 = param_1 + 1;
          cVar1 = *param_1;
          param_1 = pcVar7;
        } while (cVar1 != '\0');
        uVar5 = ~uVar5;
        pcVar7 = pcVar7 + -uVar5;
        pcVar8 = (char *)&DAT_00524694;
        for (uVar6 = uVar5 >> 2; iVar4 = DAT_00524688, uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar8 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar8 = pcVar8 + 4;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *pcVar8 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        }
        if (iVar4 != 0) {
          FreeLibrary(DAT_00524680);
        }
        DAT_00524688 = 1;
        DAT_00524680 = hModule;
      }
    }
  }
  return;
}


