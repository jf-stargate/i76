/*
 * Program: I76EDIT.EXE
 * Function: ___crtMessageBoxA
 * Entry: 0042b680
 * Signature: int __cdecl ___crtMessageBoxA(LPCSTR _LpText, LPCSTR _LpCaption, UINT _UType)
 */


/* Library Function - Single Match
    ___crtMessageBoxA
   
   Library: Visual Studio 1998 Release */

int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType)

{
  HMODULE hModule;
  int iVar1;
  
  iVar1 = 0;
  if (DAT_00438fa4 != (FARPROC)0x0) {
LAB_0042b6cf:
    if (DAT_00438fa8 != (FARPROC)0x0) {
      iVar1 = (*DAT_00438fa8)();
    }
    if ((iVar1 != 0) && (DAT_00438fac != (FARPROC)0x0)) {
      iVar1 = (*DAT_00438fac)(iVar1);
    }
    iVar1 = (*DAT_00438fa4)(iVar1,_LpText,_LpCaption,_UType);
    return iVar1;
  }
  hModule = LoadLibraryA("user32.dll");
  if (hModule != (HMODULE)0x0) {
    DAT_00438fa4 = GetProcAddress(hModule,"MessageBoxA");
    if (DAT_00438fa4 != (FARPROC)0x0) {
      DAT_00438fa8 = GetProcAddress(hModule,"GetActiveWindow");
      DAT_00438fac = GetProcAddress(hModule,"GetLastActivePopup");
      goto LAB_0042b6cf;
    }
  }
  return 0;
}


