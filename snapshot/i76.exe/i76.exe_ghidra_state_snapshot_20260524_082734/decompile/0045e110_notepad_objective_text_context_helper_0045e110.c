/*
 * Program: i76.exe
 * Function: notepad_objective_text_context_helper_0045e110
 * Entry: 0045e110
 * Signature: undefined __stdcall notepad_objective_text_context_helper_0045e110(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: notepad objective text context helper
   based on prior focused closure context. */

void notepad_objective_text_context_helper_0045e110(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (0 < DAT_006093c0) {
    puVar1 = &DAT_006093c8;
    iVar2 = 6;
    do {
      if ((LPVOID)*puVar1 != (LPVOID)0x0) {
        xfree_global_heap((LPVOID)*puVar1);
        *puVar1 = 0;
      }
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    puVar1 = &DAT_006093e0;
    iVar2 = 0x10;
    do {
      if ((LPVOID)*puVar1 != (LPVOID)0x0) {
        xfree_global_heap((LPVOID)*puVar1);
        *puVar1 = 0;
      }
      puVar1 = puVar1 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    puVar1 = &DAT_006093c0;
    for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar1 = 0;
      puVar1 = puVar1 + 1;
    }
  }
  return;
}


