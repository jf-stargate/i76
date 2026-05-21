/*
 * Program: i76shell.dll
 * Function: step_rich_text_object
 * Entry: 100377c0
 * Signature: uint __fastcall step_rich_text_object(undefined4 * param_1)
 */


/* i76shell localized glyph rename
   old_name: FUN_100377c0
   forced_name: step_rich_text_object
   basis: Steps rich-text object state/iterator. */

uint __fastcall step_rich_text_object(undefined4 *param_1)

{
  char cVar1;
  undefined4 in_EAX;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  
  if (*(char *)(param_1 + 0xe) == '\x01') {
    return CONCAT31((int3)((uint)in_EAX >> 8),1);
  }
  iVar3 = -1;
  pcVar4 = (char *)param_1[7];
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  if (iVar3 == -2) {
    return 1;
  }
  uVar2 = process_rich_text_glyph_stream(param_1);
  return uVar2;
}


