/*
 * Program: i76.exe
 * Function: clear_scrolling_text_widget_buffer
 * Entry: 0049b2e0
 * Signature: undefined __cdecl clear_scrolling_text_widget_buffer(int param_1)
 */


/* cgpt rename v4: Clears a scrolling text widget buffer, resets cursor/range fields, and marks the
   widget dirty. */

void __cdecl clear_scrolling_text_widget_buffer(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)(param_1 + 8);
  puVar5 = *(undefined4 **)(iVar1 + 0x5c);
  for (uVar2 = (*(int *)(iVar1 + 0x44) + 5) * 0x15 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar5 = 0;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
  }
  uVar4 = 0;
  *(undefined4 *)(iVar1 + 0x50) = 0;
  if ((*(uint *)(iVar1 + 0x94) & 8) == 0) {
    uVar4 = *(undefined4 *)(iVar1 + 0x44);
  }
  *(undefined4 *)(iVar1 + 0x54) = uVar4;
  *(uint *)(iVar1 + 0x94) = *(uint *)(iVar1 + 0x94) | 0x80000000;
  return;
}


