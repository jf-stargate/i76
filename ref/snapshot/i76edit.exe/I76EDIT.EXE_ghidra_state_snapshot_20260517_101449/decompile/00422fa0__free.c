/*
 * Program: I76EDIT.EXE
 * Function: _free
 * Entry: 00422fa0
 * Signature: void __cdecl _free(void * _Memory)
 */


/* Library Function - Single Match
    _free
   
   Library: Visual Studio 1998 Release */

void __cdecl _free(void *_Memory)

{
  char *pcVar1;
  uint local_8;
  int local_4;
  
  if (_Memory != (void *)0x0) {
    pcVar1 = (char *)___sbh_find_block(_Memory,&local_4,&local_8);
    if (pcVar1 != (char *)0x0) {
      ___sbh_free_block(local_4,local_8,pcVar1);
      return;
    }
    HeapFree(DAT_016424f0,0,_Memory);
  }
  return;
}


