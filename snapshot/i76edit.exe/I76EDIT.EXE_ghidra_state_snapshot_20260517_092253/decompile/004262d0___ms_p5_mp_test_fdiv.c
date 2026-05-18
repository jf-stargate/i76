/*
 * Program: I76EDIT.EXE
 * Function: __ms_p5_mp_test_fdiv
 * Entry: 004262d0
 * Signature: undefined __stdcall __ms_p5_mp_test_fdiv(void)
 */


/* Library Function - Single Match
    __ms_p5_mp_test_fdiv
   
   Library: Visual Studio 1998 Release */

void __ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  
  hModule = GetModuleHandleA("KERNEL32");
  if (hModule != (HMODULE)0x0) {
    pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent");
    if (pFVar1 != (FARPROC)0x0) {
      (*pFVar1)(0);
      return;
    }
  }
  __ms_p5_test_fdiv();
  return;
}


