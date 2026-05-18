/*
 * Program: I76EDIT.EXE
 * Function: __heap_init
 * Entry: 00424f00
 * Signature: int __cdecl __heap_init(void)
 */


/* Library Function - Single Match
    __heap_init
   
   Library: Visual Studio 1998 Release */

int __cdecl __heap_init(void)

{
  undefined **ppuVar1;
  
  DAT_016424f0 = HeapCreate(1,0x1000,0);
  if (DAT_016424f0 == (HANDLE)0x0) {
    return 0;
  }
  ppuVar1 = ___sbh_new_region();
  if (ppuVar1 == (undefined **)0x0) {
    HeapDestroy(DAT_016424f0);
    return 0;
  }
  return 1;
}


