/*
 * Program: I76EDIT.EXE
 * Function: _malloc
 * Entry: 004232e0
 * Signature: void * __cdecl _malloc(size_t _Size)
 */


/* Library Function - Single Match
    _malloc
   
   Library: Visual Studio 1998 Release */

void * __cdecl _malloc(size_t _Size)

{
  void *pvVar1;
  
  pvVar1 = __nh_malloc(_Size,DAT_00438678);
  return pvVar1;
}


