/*
 * Program: I76EDIT.EXE
 * Function: __nh_malloc
 * Entry: 00423300
 * Signature: void * __cdecl __nh_malloc(size_t _Size, int _NhFlag)
 */


/* Library Function - Single Match
    __nh_malloc
   
   Library: Visual Studio 1998 Release */

void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  void *pvVar1;
  int iVar2;
  
  if (0xffffffe0 < _Size) {
    return (void *)0x0;
  }
  if (_Size == 0) {
    _Size = 1;
  }
  do {
    pvVar1 = (void *)0x0;
    if (_Size < 0xffffffe1) {
      pvVar1 = __heap_alloc(_Size);
    }
    if (pvVar1 != (void *)0x0) {
      return pvVar1;
    }
    if (_NhFlag == 0) {
      return (void *)0x0;
    }
    iVar2 = __callnewh(_Size);
  } while (iVar2 != 0);
  return (void *)0x0;
}


