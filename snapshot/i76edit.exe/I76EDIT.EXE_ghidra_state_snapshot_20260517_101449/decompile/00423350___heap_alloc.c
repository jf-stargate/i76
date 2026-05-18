/*
 * Program: I76EDIT.EXE
 * Function: __heap_alloc
 * Entry: 00423350
 * Signature: void * __cdecl __heap_alloc(size_t _Size)
 */


/* Library Function - Single Match
    __heap_alloc
   
   Library: Visual Studio 1998 Release */

void * __cdecl __heap_alloc(size_t _Size)

{
  undefined *puVar1;
  LPVOID pvVar2;
  uint dwBytes;
  
  dwBytes = _Size + 0xf & 0xfffffff0;
  if ((dwBytes <= DAT_00438674) &&
     (puVar1 = ___sbh_alloc_block(_Size + 0xf >> 4), puVar1 != (undefined *)0x0)) {
    return puVar1;
  }
  pvVar2 = HeapAlloc(DAT_016424f0,0,dwBytes);
  return pvVar2;
}


