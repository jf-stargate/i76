/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049bb40
 * Entry: 0049bb40
 * Signature: undefined4 __cdecl ui_bitmap_region_context_helper_0049bb40(int param_1, uint param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049bb40. Remove
   duplicated UI/region wording. */

undefined4 __cdecl ui_bitmap_region_context_helper_0049bb40(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  undefined4 *puVar5;
  byte abStackY_3c [12];
  undefined4 uStackY_30;
  
  iVar1 = *(int *)(param_1 + 8);
  if (((param_2 == 0) || ((*(uint *)(iVar1 + 0xb0) & 0x100) == 0)) || ((param_2 & 0x500) != 0)) {
    return 0;
  }
  bVar3 = (byte)param_2;
  switch(param_2 & 0xff) {
  case 8:
    uVar2 = *(uint *)(iVar1 + 0xa4);
    if (*(uint *)(iVar1 + 0x9c) < uVar2) {
      uStackY_30 = 0x49bbcd;
      memmove((void *)(iVar1 + 0x43 + uVar2),(void *)(iVar1 + 0x44 + uVar2),
              (*(int *)(iVar1 + 0x98) - uVar2) + 2);
      *(int *)(iVar1 + 0xa4) = *(int *)(iVar1 + 0xa4) + -1;
      *(int *)(iVar1 + 0xa0) = *(int *)(iVar1 + 0xa0) + -1;
      *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) | 0x200;
      return 1;
    }
    goto LAB_0049bdae;
  default:
    if ((param_2 & 0x200) != 0) {
      iVar4 = toupper(param_2 & 0xff);
      bVar3 = (byte)iVar4;
      if (bVar3 == 0x27) {
        bVar3 = 0x22;
      }
      else if (((char)bVar3 < ',') || (';' < (char)bVar3)) {
        if (('Z' < (char)bVar3) && ((char)bVar3 < '^')) {
          bVar3 = bVar3 + 0x20;
        }
      }
      else {
        bVar3 = abStackY_3c[(char)bVar3];
      }
      if (bVar3 == 0x60) {
        bVar3 = 0x7e;
      }
    }
    if (bVar3 < 0x20) {
      return 0;
    }
    if (*(int *)(iVar1 + 0xa0) == *(int *)(iVar1 + 0x98)) {
      return 1;
    }
    iVar4 = *(int *)(iVar1 + 0xa4);
    uStackY_30 = 0x49bd87;
    memmove((void *)(iVar1 + 0x45 + iVar4),(void *)(iVar1 + 0x44 + iVar4),
            (*(int *)(iVar1 + 0x98) - iVar4) + 2);
    *(byte *)(iVar1 + 0x44 + *(int *)(iVar1 + 0xa4)) = bVar3;
    *(int *)(iVar1 + 0xa4) = *(int *)(iVar1 + 0xa4) + 1;
    *(int *)(iVar1 + 0xa0) = *(int *)(iVar1 + 0xa0) + 1;
LAB_0049bdae:
    *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) | 0x200;
    return 1;
  case 0xd:
    if (*(code **)(iVar1 + 0xb4) != (code *)0x0) {
      (**(code **)(iVar1 + 0xb4))();
    }
    *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) | 0x200;
    return 2;
  case 0x1b:
    puVar5 = (undefined4 *)(iVar1 + 0x44);
    for (iVar4 = 0x14; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    *(undefined4 *)(iVar1 + 0xa0) = 0;
    *(undefined4 *)(iVar1 + 0xa4) = 0;
    *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) | 0x200;
    return 1;
  case 200:
    if (*(uint *)(iVar1 + 0xa0) < *(uint *)(iVar1 + 0xa4)) goto LAB_0049bc99;
    iVar4 = *(uint *)(iVar1 + 0xa4) + 1;
    break;
  case 0xc9:
    if (*(int *)(iVar1 + 0xa4) == 0) goto LAB_0049bc99;
    iVar4 = *(int *)(iVar1 + 0xa4) + -1;
  }
  *(int *)(iVar1 + 0xa4) = iVar4;
LAB_0049bc99:
  *(uint *)(iVar1 + 0xb0) = *(uint *)(iVar1 + 0xb0) | 0x200;
  return 1;
}


