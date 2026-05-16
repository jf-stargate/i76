/*
 * Program: i76.exe
 * Function: weapon_selection_contains_slot
 * Entry: 004a5840
 * Signature: undefined4 __cdecl weapon_selection_contains_slot(int * param_1, int param_2)
 */


/* [cgpt i76.exe player weapon HUD rename v25; confidence=high] Returns true when a candidate weapon
   slot appears in the current selected-slot list. */

undefined4 __cdecl weapon_selection_contains_slot(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    param_1 = param_1 + 1;
    if (*param_1 == param_2) {
      return 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return 0;
}


