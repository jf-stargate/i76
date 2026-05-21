/*
 * Program: i76shell.dll
 * Function: destroy_pointer_list_with_optional_item_destructor
 * Entry: 100278f0
 * Signature: undefined __cdecl destroy_pointer_list_with_optional_item_destructor(LPVOID param_1, undefined * param_2)
 */


void __cdecl destroy_pointer_list_with_optional_item_destructor(LPVOID param_1,undefined *param_2)

{
  LPVOID lpMem;
  int iVar1;
  
  if (param_1 != (LPVOID)0x0) {
    iVar1 = 0;
    if (0 < *(int *)((int)param_1 + 4)) {
      do {
        lpMem = *(LPVOID *)(*(int *)((int)param_1 + 8) + iVar1 * 4);
        if (lpMem != (LPVOID)0x0) {
          if (param_2 == (undefined *)0x0) {
            HeapFree(DAT_10051c50,1,lpMem);
            *(undefined4 *)(*(int *)((int)param_1 + 8) + iVar1 * 4) = 0;
          }
          else {
            (*(code *)param_2)();
          }
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < *(int *)((int)param_1 + 4));
    }
    if (*(LPVOID *)((int)param_1 + 8) != (LPVOID)0x0) {
      HeapFree(DAT_10051c50,1,*(LPVOID *)((int)param_1 + 8));
      *(undefined4 *)((int)param_1 + 8) = 0;
    }
    HeapFree(DAT_10051c50,1,param_1);
  }
  return;
}


