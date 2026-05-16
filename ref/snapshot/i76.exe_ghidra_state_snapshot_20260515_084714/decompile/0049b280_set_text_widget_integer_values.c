/*
 * Program: i76.exe
 * Function: set_text_widget_integer_values
 * Entry: 0049b280
 * Signature: undefined __cdecl set_text_widget_integer_values(int param_1, int param_2, undefined4 * param_3)
 */


/* cgpt rename v4: Stores a count and a caller-provided integer array into a text/widget backing
   record. */

void __cdecl set_text_widget_integer_values(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  *(int *)(iVar1 + 0x68) = param_2;
  if (0 < param_2) {
    puVar3 = (undefined4 *)(iVar1 + 0x6c);
    do {
      uVar2 = *param_3;
      param_3 = param_3 + 1;
      *puVar3 = uVar2;
      puVar3 = puVar3 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}


