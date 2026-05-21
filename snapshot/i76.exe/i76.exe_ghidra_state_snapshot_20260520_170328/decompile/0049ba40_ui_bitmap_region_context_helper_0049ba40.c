/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049ba40
 * Entry: 0049ba40
 * Signature: undefined __cdecl ui_bitmap_region_context_helper_0049ba40(int param_1, char * param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049ba40. Remove
   duplicated UI/region wording. */

void __cdecl ui_bitmap_region_context_helper_0049ba40(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint _Size;
  uint uVar3;
  size_t _Count;
  uint uVar4;
  char *pcVar5;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar3 = 0xffffffff;
  pcVar5 = param_2;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  _Count = ~uVar3 - 1;
  _Size = *(int *)(iVar2 + 0xa0) - *(int *)(iVar2 + 0x9c);
  uVar4 = *(int *)(iVar2 + 0x98) - _Count;
  if (uVar4 < _Size) {
    _Size = uVar4;
  }
  memmove((void *)(~uVar3 + 0x43 + iVar2),(void *)(iVar2 + 0x44 + *(int *)(iVar2 + 0x9c)),_Size);
  *(size_t *)(iVar2 + 0xa0) = *(int *)(iVar2 + 0xa0) + (_Count - *(int *)(iVar2 + 0x9c));
  *(size_t *)(iVar2 + 0xa4) = *(int *)(iVar2 + 0xa4) + (_Count - *(int *)(iVar2 + 0x9c));
  strncpy((char *)(iVar2 + 0x44),param_2,_Count);
  *(size_t *)(iVar2 + 0x9c) = _Count;
  *(uint *)(iVar2 + 0xb0) = *(uint *)(iVar2 + 0xb0) | 0x200;
  return;
}


