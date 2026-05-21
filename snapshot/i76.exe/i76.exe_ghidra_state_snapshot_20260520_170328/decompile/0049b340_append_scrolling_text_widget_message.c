/*
 * Program: i76.exe
 * Function: append_scrolling_text_widget_message
 * Entry: 0049b340
 * Signature: undefined __cdecl append_scrolling_text_widget_message(int param_1, uchar * param_2)
 */


/* cgpt rename v4: Appends a timed line to a scrolling text widget ring buffer and marks the widget
   dirty. */

void __cdecl append_scrolling_text_widget_message(int param_1,uchar *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  
  iVar2 = *(int *)(param_1 + 8);
  if (((*(byte *)(iVar2 + 0x94) & 8) == 0) || (*(int *)(iVar2 + 0x54) != *(int *)(iVar2 + 0x44) + 1)
     ) {
    _mbsnbcpy((uchar *)(*(int *)(iVar2 + 0x5c) + *(int *)(iVar2 + 0x54) * 0x54),param_2,
              *(size_t *)(iVar2 + 0x48));
    *(undefined1 *)(*(int *)(iVar2 + 0x48) + *(int *)(iVar2 + 0x54) * 0x54 + *(int *)(iVar2 + 0x5c))
         = 0;
    fVar5 = get_network_or_session_runtime_seconds();
    *(float *)(*(int *)(iVar2 + 0x5c) + 0x50 + *(int *)(iVar2 + 0x54) * 0x54) =
         (float)(fVar5 + (float10)*(float *)(iVar2 + 0x8c));
    uVar3 = *(uint *)(iVar2 + 0x94);
    if ((uVar3 & 8) != 0) {
      *(int *)(iVar2 + 0x54) = *(int *)(iVar2 + 0x54) + 1;
      *(uint *)(iVar2 + 0x94) = uVar3 | 0x80000000;
      return;
    }
    uVar1 = *(int *)(iVar2 + 0x44) + 5;
    uVar4 = (*(int *)(iVar2 + 0x54) + 1U) % uVar1;
    *(uint *)(iVar2 + 0x54) = uVar4;
    if (uVar4 == *(uint *)(iVar2 + 0x50)) {
      *(uint *)(iVar2 + 0x50) = (*(uint *)(iVar2 + 0x50) + 1) % uVar1;
      if (3 < *(uint *)(iVar2 + 0x58)) {
        *(uint *)(iVar2 + 0x58) = *(uint *)(iVar2 + 0x58) - 4;
      }
    }
    *(int *)(iVar2 + 0x58) = *(int *)(iVar2 + 0x58) + 4;
    *(uint *)(iVar2 + 0x94) = uVar3 | 0x80000000;
  }
  return;
}


