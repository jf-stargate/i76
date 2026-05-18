/*
 * Program: i76.exe
 * Function: register_texture_set_cache_record_from_header
 * Entry: 0044aa20
 * Signature: undefined4 __cdecl register_texture_set_cache_record_from_header(int param_1)
 */


/* [cgpt i76.exe image payload renames v27; confidence=high] Registers a decoded TMT/MAP texture-set
   cache record, including name, dimensions, animation fields, frame-name array, and hash chain. */

undefined4 __cdecl register_texture_set_cache_record_from_header(int param_1)

{
  byte *pbVar1;
  char cVar2;
  byte bVar3;
  char *_Dest;
  int iVar4;
  LPVOID pvVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  byte *_Source;
  void *_Src;
  char *pcVar11;
  char *pcVar12;
  char *pcVar13;
  int local_c;
  
  iVar8 = param_1;
  _Dest = HeapAlloc(g_texture_set_cache_heap,0,0x34);
  if (_Dest == (char *)0x0) {
    return 0;
  }
  _Source = (byte *)(param_1 + 4);
  strncpy(_Dest,(char *)_Source,0xf);
  local_c = 1;
  _Dest[0x10] = '\x01';
  _Dest[0x11] = '\0';
  _Dest[0x12] = '\0';
  _Dest[0x13] = '\0';
  *(undefined4 *)(_Dest + 0x14) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(_Dest + 0x18) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(_Dest + 0x1c) = *(undefined4 *)(param_1 + 0x14);
  iVar4 = *(int *)(param_1 + 0x14);
  iVar6 = 0;
  if (0 < iVar4) {
    piVar10 = (int *)(_Dest + 0x20);
    do {
      local_c = *(int *)(param_1 + 0x14 + (iVar4 - iVar6) * 4) * local_c;
      *piVar10 = local_c;
      iVar4 = *(int *)(param_1 + 0x14);
      iVar6 = iVar6 + 1;
      piVar10 = piVar10 + 1;
    } while (iVar6 < iVar4);
  }
  pvVar5 = HeapAlloc(g_texture_name_array_heap,0,local_c << 4);
  *(LPVOID *)(_Dest + 0x2c) = pvVar5;
  if (0 < local_c) {
    param_1 = 0;
    _Src = (void *)(iVar8 + 0x40);
    do {
      pcVar11 = (char *)(param_1 + *(int *)(_Dest + 0x2c));
      memmove(pcVar11,_Src,8);
      uVar7 = 0xffffffff;
      pcVar11[8] = '\0';
      _Src = (void *)((int)_Src + 8);
      pcVar13 = (char *)&DAT_004f25e8;
      do {
        pcVar12 = pcVar13;
        if (uVar7 == 0) break;
        uVar7 = uVar7 - 1;
        pcVar12 = pcVar13 + 1;
        cVar2 = *pcVar13;
        pcVar13 = pcVar12;
      } while (cVar2 != '\0');
      uVar7 = ~uVar7;
      iVar8 = -1;
      do {
        pcVar13 = pcVar11;
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        pcVar13 = pcVar11 + 1;
        cVar2 = *pcVar11;
        pcVar11 = pcVar13;
      } while (cVar2 != '\0');
      pcVar11 = pcVar12 + -uVar7;
      pcVar13 = pcVar13 + -1;
      for (uVar9 = uVar7 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined4 *)pcVar13 = *(undefined4 *)pcVar11;
        pcVar11 = pcVar11 + 4;
        pcVar13 = pcVar13 + 4;
      }
      for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
        *pcVar13 = *pcVar11;
        pcVar11 = pcVar11 + 1;
        pcVar13 = pcVar13 + 1;
      }
      param_1 = param_1 + 0x10;
      local_c = local_c + -1;
    } while (local_c != 0);
  }
  uVar7 = 0;
  bVar3 = *_Source;
  while (bVar3 != 0) {
    uVar7 = uVar7 * 2 ^ bVar3 & 0xdf;
    pbVar1 = _Source + 1;
    _Source = _Source + 1;
    bVar3 = *pbVar1;
  }
  uVar7 = (uVar7 * 0x6cd + 0xaab) % 0x7ed;
  *(undefined4 *)(_Dest + 0x30) = (&g_texture_set_cache_hash)[uVar7];
  (&g_texture_set_cache_hash)[uVar7] = _Dest;
  return 1;
}


