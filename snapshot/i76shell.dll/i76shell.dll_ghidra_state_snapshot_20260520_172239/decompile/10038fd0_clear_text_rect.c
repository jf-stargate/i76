/*
 * Program: i76shell.dll
 * Function: clear_text_rect
 * Entry: 10038fd0
 * Signature: undefined __thiscall clear_text_rect(void * this, int param_1, int param_2, int param_3, int param_4)
 */


/* i76shell text/glyph render rename
   old_name: FUN_10038fd0
   suggested_name: destroy_or_clear_text_label
   basis: Called before recreating cursor/debug text; likely clears old text handle/object.
   
   i76shell text/glyph rename
   old_name: destroy_or_clear_text_label
   suggested_name: clear_text_rect
   basis: Clears/fills the previous text rectangle using the clipped rect primitive.
   
   i76shell forced text/glyph rename
   old_name: destroy_or_clear_text_label
   forced_name: clear_text_rect
   basis: Clears/fills a text rectangle using the clipped rect primitive. */

void __thiscall clear_text_rect(void *this,int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  local_10 = param_1;
  iVar1 = param_3 + -1 + param_1;
  local_14 = (int)this + 0x44;
  iVar2 = param_4 + -1 + param_2;
  local_c = param_2;
  local_8 = iVar1;
  local_4 = iVar2;
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar4 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar4 != 0) goto LAB_100390a8;
    uVar3 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar3;
    **(undefined4 **)((int)this + 0x6c) = uVar3;
  }
  blit_or_fill_rect_clipped
            (&local_14,0,0,(int *)((int)this + 0x6c),param_1,param_2,*(uint *)((int)this + 0x3d0));
  blit_or_fill_rect_clipped
            (&local_14,0,0,(int *)((int)this + 0xa8),param_1,param_2,*(uint *)((int)this + 0x3d0));
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_100390a8:
  if (param_1 < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = param_1;
  }
  if (param_2 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = param_2;
  }
  if (*(int *)((int)this + 0xa0) < iVar1) {
    *(int *)((int)this + 0xa0) = iVar1;
  }
  if (*(int *)((int)this + 0xa4) < iVar2) {
    *(int *)((int)this + 0xa4) = iVar2;
  }
  return;
}


