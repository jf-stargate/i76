/*
 * Program: i76.exe
 * Function: decode_tmt_texture_set_header_into_record
 * Entry: 0044ab90
 * Signature: undefined4 __cdecl decode_tmt_texture_set_header_into_record(int param_1, int param_2)
 */


/* [cgpt i76.exe GEO mesh/render renames v29; confidence=high] Decodes TMT texture-set headers:
   dimension count/values, animation period/rate, flags, and 8-byte frame basenames. */

undefined4 __cdecl decode_tmt_texture_set_header_into_record(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  LPVOID pvVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  void *_Src;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  int local_4;
  
  iVar2 = param_1;
  local_4 = 1;
  *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)(param_1 + 0x14);
  iVar6 = *(int *)(param_1 + 0x14);
  iVar4 = 0;
  if (0 < iVar6) {
    piVar8 = (int *)(param_2 + 0x20);
    do {
      local_4 = *(int *)(param_1 + 0x14 + (iVar6 - iVar4) * 4) * local_4;
      *piVar8 = local_4;
      iVar6 = *(int *)(param_1 + 0x14);
      iVar4 = iVar4 + 1;
      piVar8 = piVar8 + 1;
    } while (iVar4 < iVar6);
  }
  pvVar3 = HeapAlloc(g_texture_name_array_heap,0,local_4 << 4);
  *(LPVOID *)(param_2 + 0x2c) = pvVar3;
  if (0 < local_4) {
    param_1 = 0;
    _Src = (void *)(iVar2 + 0x40);
    do {
      pcVar9 = (char *)(*(int *)(param_2 + 0x2c) + param_1);
      memmove(pcVar9,_Src,8);
      uVar5 = 0xffffffff;
      pcVar9[8] = '\0';
      _Src = (void *)((int)_Src + 8);
      pcVar11 = (char *)&DAT_004f25e8;
      do {
        pcVar10 = pcVar11;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar10 = pcVar11 + 1;
        cVar1 = *pcVar11;
        pcVar11 = pcVar10;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar6 = -1;
      do {
        pcVar11 = pcVar9;
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar11 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar11;
      } while (cVar1 != '\0');
      pcVar9 = pcVar10 + -uVar5;
      pcVar11 = pcVar11 + -1;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar11 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar11 = pcVar11 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar11 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar11 = pcVar11 + 1;
      }
      param_1 = param_1 + 0x10;
      local_4 = local_4 + -1;
    } while (local_4 != 0);
  }
  return 1;
}


