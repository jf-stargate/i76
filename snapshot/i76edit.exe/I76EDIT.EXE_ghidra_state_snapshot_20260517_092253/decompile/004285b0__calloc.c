/*
 * Program: I76EDIT.EXE
 * Function: _calloc
 * Entry: 004285b0
 * Signature: void * __cdecl _calloc(size_t _Count, size_t _Size)
 */


/* Library Function - Single Match
    _calloc
   
   Library: Visual Studio 1998 Release */

void * __cdecl _calloc(size_t _Count,size_t _Size)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint dwBytes;
  undefined4 *puVar4;
  
  dwBytes = _Size * _Count;
  if (dwBytes < 0xffffffe1) {
    if (dwBytes == 0) {
      dwBytes = 0x10;
    }
    else {
      dwBytes = dwBytes + 0xf & 0xfffffff0;
    }
  }
  do {
    puVar3 = (undefined4 *)0x0;
    if (dwBytes < 0xffffffe1) {
      if (DAT_00438674 < dwBytes) {
LAB_0042860d:
        if (puVar3 != (undefined4 *)0x0) {
          return puVar3;
        }
      }
      else {
        puVar3 = (undefined4 *)___sbh_alloc_block(dwBytes >> 4);
        if (puVar3 != (undefined4 *)0x0) {
          puVar4 = puVar3;
          for (uVar2 = dwBytes >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          for (uVar2 = dwBytes & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
            *(undefined1 *)puVar4 = 0;
            puVar4 = (undefined4 *)((int)puVar4 + 1);
          }
          goto LAB_0042860d;
        }
      }
      puVar3 = HeapAlloc(DAT_016424f0,8,dwBytes);
    }
    if ((puVar3 != (undefined4 *)0x0) || (DAT_00438678 == 0)) {
      return puVar3;
    }
    iVar1 = __callnewh(dwBytes);
    if (iVar1 == 0) {
      return (void *)0x0;
    }
  } while( true );
}


