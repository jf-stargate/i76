/*
 * Program: I76EDIT.EXE
 * Function: _realloc
 * Entry: 00423cf0
 * Signature: void * __cdecl _realloc(void * _Memory, size_t _NewSize)
 */


/* Library Function - Single Match
    _realloc
   
   Library: Visual Studio 1998 Release */

void * __cdecl _realloc(void *_Memory,size_t _NewSize)

{
  void *pvVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *local_c;
  int *local_8;
  int local_4;
  
  if (_Memory == (void *)0x0) {
    pvVar1 = _malloc(_NewSize);
    return pvVar1;
  }
  if (_NewSize != 0) {
    if (_NewSize < 0xffffffe1) {
      if (_NewSize == 0) {
        _NewSize = 0x10;
      }
      else {
        _NewSize = _NewSize + 0xf & 0xfffffff0;
      }
    }
    do {
      local_c = (undefined4 *)0x0;
      if (_NewSize < 0xffffffe1) {
        pbVar2 = (byte *)___sbh_find_block(_Memory,&local_4,(uint *)&local_8);
        if (pbVar2 == (byte *)0x0) {
          local_c = HeapReAlloc(DAT_016424f0,0,_Memory,_NewSize);
        }
        else {
          if (_NewSize < DAT_00438674) {
            iVar3 = ___sbh_resize_block(local_4,local_8,pbVar2,_NewSize >> 4);
            if (iVar3 == 0) {
              local_c = (undefined4 *)___sbh_alloc_block(_NewSize >> 4);
              if (local_c != (undefined4 *)0x0) {
                uVar5 = (uint)*pbVar2 << 4;
                if (_NewSize <= (uint)*pbVar2 << 4) {
                  uVar5 = _NewSize;
                }
                puVar6 = _Memory;
                puVar7 = local_c;
                for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
                  *puVar7 = *puVar6;
                  puVar6 = puVar6 + 1;
                  puVar7 = puVar7 + 1;
                }
                for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
                  *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
                  puVar6 = (undefined4 *)((int)puVar6 + 1);
                  puVar7 = (undefined4 *)((int)puVar7 + 1);
                }
                ___sbh_free_block(local_4,(int)local_8,(char *)pbVar2);
              }
            }
            else {
              local_c = _Memory;
            }
          }
          if (local_c != (undefined4 *)0x0) {
            return local_c;
          }
          local_c = HeapAlloc(DAT_016424f0,0,_NewSize);
          if (local_c != (undefined4 *)0x0) {
            uVar5 = (uint)*pbVar2 << 4;
            if (_NewSize <= (uint)*pbVar2 << 4) {
              uVar5 = _NewSize;
            }
            puVar6 = _Memory;
            puVar7 = local_c;
            for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
            for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
              *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
              puVar6 = (undefined4 *)((int)puVar6 + 1);
              puVar7 = (undefined4 *)((int)puVar7 + 1);
            }
            ___sbh_free_block(local_4,(int)local_8,(char *)pbVar2);
          }
        }
      }
      if ((local_c != (undefined4 *)0x0) || (DAT_00438678 == 0)) {
        return local_c;
      }
      iVar3 = __callnewh(_NewSize);
      if (iVar3 == 0) {
        return (void *)0x0;
      }
    } while( true );
  }
  _free(_Memory);
  return (void *)0x0;
}


