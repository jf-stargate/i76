/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049ab50
 * Entry: 0049ab50
 * Signature: undefined4 __cdecl ui_bitmap_region_context_helper_0049ab50(char * param_1, int * param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049ab50. Remove
   duplicated UI/region wording. */

undefined4 __cdecl ui_bitmap_region_context_helper_0049ab50(char *param_1,int *param_2)

{
  uint *_DstBuf;
  int iVar1;
  long lVar2;
  uint *puVar3;
  undefined1 *puVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined1 local_200 [512];
  
  iVar1 = _open(param_1,0x8000);
  if (iVar1 == -1) {
    return 0;
  }
  _read(iVar1,param_2,4);
  iVar6 = *param_2;
  if ((iVar6 != 0x614b4d53) && (iVar6 != 0x624b4d53)) {
    if (iVar6 == 0x324b4d53) {
      _read(iVar1,param_2 + 1,4);
      _read(iVar1,param_2 + 2,4);
      _read(iVar1,param_2 + 3,4);
      puVar3 = (uint *)(param_2 + 6);
      _read(iVar1,puVar3,4);
      uVar8 = *puVar3;
      if ((int)uVar8 < 0) {
        uVar8 = -uVar8;
      }
      else {
        uVar8 = uVar8 * 100;
      }
      uVar5 = (int)(10000000 / (ulonglong)uVar8) + 5;
      param_2[5] = (int)(((ulonglong)uVar5 / 10) % 10);
      param_2[4] = uVar5 / 100;
      _DstBuf = (uint *)(param_2 + 0xb);
      param_2[7] = (int)(((ulonglong)(uVar8 + 5) / 10) % 10);
      *puVar3 = (uVar8 + 5) / 100;
      _read(iVar1,_DstBuf,4);
      uVar8 = *_DstBuf;
      uVar5 = uVar8 >> 1 & 1;
      *_DstBuf = uVar8 & 1;
      uVar8 = uVar8 >> 2 & 1;
      param_2[0xc] = uVar5;
      param_2[0xd] = uVar8;
      if ((uVar5 != 0) || (uVar8 != 0)) {
        param_2[2] = param_2[2] << 1;
      }
      _read(iVar1,param_2 + 0x16,0x1c);
      _read(iVar1,param_2 + 0x1d,0x14);
      puVar3 = (uint *)(param_2 + 0xf);
      _read(iVar1,puVar3,0x1c);
      _read(iVar1,param_2 + 0x1d,4);
      iVar6 = 7;
      do {
        if (puVar3[7] == 0) {
          *puVar3 = 0;
        }
        else if ((*puVar3 & 0x40000000) == 0) {
          *puVar3 = 0xffffffff;
        }
        else {
          puVar3[7] = (-(uint)((*puVar3 & 0x20000000) != 0) & 8) + 8;
          puVar3[0xe] = *puVar3 >> 0x1c & 1;
          *puVar3 = *puVar3 & 0xffffff;
        }
        puVar3 = puVar3 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
      iVar6 = param_2[3];
      if (param_2[0xb] != 0) {
        iVar6 = iVar6 + 1;
      }
      param_2[9] = 0;
      param_2[8] = 0;
      for (; 0 < iVar6; iVar6 = iVar6 + -0x80) {
        _read(iVar1,local_200,0x200);
        iVar7 = 0x80;
        if (iVar6 < 0x81) {
          iVar7 = iVar6;
        }
        if (0 < iVar7) {
          puVar4 = local_200 + iVar7 * 4;
          do {
            uVar8 = *(uint *)(puVar4 + -4);
            param_2[8] = param_2[8] + uVar8;
            if ((uint)param_2[9] < uVar8) {
              param_2[9] = uVar8;
            }
            puVar4 = puVar4 + -4;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
      }
      uVar8 = param_2[3];
      if (param_2[0xb] != 0) {
        uVar8 = uVar8 + 1;
      }
      param_2[8] = (uint)param_2[8] / uVar8;
      lVar2 = _lseek(iVar1,0,2);
      param_2[0xe] = lVar2;
      _close(iVar1);
      return 1;
    }
    _close(iVar1);
    return 0;
  }
  _close(iVar1);
  piVar9 = param_2;
  for (iVar1 = 0x24; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar9 = 0;
    piVar9 = piVar9 + 1;
  }
  *param_2 = 0x314b4d53;
  return 1;
}


