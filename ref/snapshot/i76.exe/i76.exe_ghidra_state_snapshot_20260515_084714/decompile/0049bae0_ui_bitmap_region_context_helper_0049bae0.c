/*
 * Program: i76.exe
 * Function: ui_bitmap_region_context_helper_0049bae0
 * Entry: 0049bae0
 * Signature: undefined __cdecl ui_bitmap_region_context_helper_0049bae0(int param_1, char * param_2)
 */


/* cgpt label refinement v20: was ui_scroll_input_region_ui_bitmap_region_helper_0049bae0. Remove
   duplicated UI/region wording. */

void __cdecl ui_bitmap_region_context_helper_0049bae0(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  iVar2 = *(int *)(param_1 + 8);
  strncpy((char *)(iVar2 + 0x44 + *(int *)(iVar2 + 0x9c)),param_2,
          *(int *)(iVar2 + 0x98) - *(int *)(iVar2 + 0x9c));
  *(uint *)(iVar2 + 0xb0) = *(uint *)(iVar2 + 0xb0) | 0x200;
  uVar3 = 0xffffffff;
  pcVar4 = (char *)(iVar2 + 0x44);
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  *(uint *)(iVar2 + 0xa0) = ~uVar3 - 2;
  *(uint *)(iVar2 + 0xa4) = ~uVar3 - 1;
  return;
}


