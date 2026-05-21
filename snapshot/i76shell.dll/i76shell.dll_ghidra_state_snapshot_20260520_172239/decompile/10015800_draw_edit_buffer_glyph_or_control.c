/*
 * Program: i76shell.dll
 * Function: draw_edit_buffer_glyph_or_control
 * Entry: 10015800
 * Signature: undefined __thiscall draw_edit_buffer_glyph_or_control(void * this, int param_1, int param_2, int param_3, undefined * param_4)
 */


/* i76shell localized glyph rename
   old_name: FUN_10015800
   forced_name: draw_edit_buffer_glyph_or_control
   basis: Draws or handles edit-buffer glyph/control input; name still slightly cautious. */

void __thiscall
draw_edit_buffer_glyph_or_control(void *this,int param_1,int param_2,int param_3,undefined *param_4)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  
  if (param_3 == 8) {
    iVar4 = *(int *)((int)this + 0x404) + -1;
    *(int *)((int)this + 0x404) = iVar4;
    if (iVar4 < 0) {
      *(undefined4 *)((int)this + 0x404) = 0;
    }
    iVar4 = *(int *)((int)this + 0x404);
    if (iVar4 == 0) {
      iVar1 = *(int *)((int)this + 4);
      puVar2 = (undefined4 *)((int)this + 4);
      iVar4 = param_1;
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      iVar1 = *(int *)((int)this + iVar4 * 4 + 4);
      puVar2 = (undefined4 *)((int)this + iVar4 * 4 + 4);
      iVar4 = *(int *)((int)this + iVar4 * 4) + param_1;
    }
    *puVar2 = 0;
    for (; iVar4 < param_1 + iVar1; iVar4 = iVar4 + iVar3) {
      iVar3 = draw_single_glyph_to_shell_surfaces
                        (*(void **)((int)this + 0x410),iVar4,param_2,*(int *)this,0x20,param_4);
    }
  }
  else if (param_3 != 0xd) {
    if (param_3 == 0x1b) {
      *(undefined4 *)((int)this + 0x404) = 0;
      for (iVar4 = 0x100; this = (void *)((int)this + 4), iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined4 *)this = 0;
      }
      return;
    }
    iVar4 = 0;
    if (*(int *)((int)this + 0x404) != 0) {
      iVar4 = *(int *)((int)this + *(int *)((int)this + 0x404) * 4);
    }
    iVar1 = draw_single_glyph_to_shell_surfaces
                      (*(void **)((int)this + 0x410),iVar4 + param_1,param_2,*(int *)this,param_3,
                       param_4);
    iVar4 = *(int *)((int)this + 0x404);
    if (iVar4 < 1) {
      *(int *)((int)this + iVar4 * 4 + 4) = iVar1;
      *(int *)((int)this + 0x404) = *(int *)((int)this + 0x404) + 1;
      return;
    }
    *(int *)((int)this + iVar4 * 4 + 4) = *(int *)((int)this + iVar4 * 4) + iVar1;
    *(int *)((int)this + 0x404) = *(int *)((int)this + 0x404) + 1;
    return;
  }
  return;
}


