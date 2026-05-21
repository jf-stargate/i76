/*
 * Program: i76shell.dll
 * Function: draw_single_glyph_to_shell_surfaces
 * Entry: 10039750
 * Signature: undefined __thiscall draw_single_glyph_to_shell_surfaces(void * this, int param_1, int param_2, int param_3, int param_4, undefined * param_5)
 */


/* i76shell forced text/glyph rename
   old_name: FUN_10039750
   forced_name: draw_single_glyph_to_shell_surfaces
   basis: Draws one glyph to shell front/back surfaces and updates dirty region.
   
   i76shell locale/rich-text rename
   old_name: draw_single_glyph_to_shell_surfaces
   forced_name: draw_single_glyph_to_shell_surfaces
   basis: Draws one glyph to shell surfaces and updates dirty bounds. */

void __thiscall
draw_single_glyph_to_shell_surfaces
          (void *this,int param_1,int param_2,int param_3,int param_4,undefined *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = get_glyph_width(param_3,param_4);
  if (DAT_100f576c != 0) {
    if (*(int *)((int)this + 0xa0) < param_1) {
      return;
    }
    if (iVar2 + -1 + param_1 < *(int *)((int)this + 0x98)) {
      return;
    }
    if (*(int *)((int)this + 0xa4) < param_2) {
      return;
    }
    if (*(int *)(param_3 + 8) + -1 + param_2 < *(int *)((int)this + 0x9c)) {
      return;
    }
  }
  if (param_5 == (undefined *)0x0) {
    param_5 = &DAT_100f5668;
  }
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar3 != 0) goto LAB_10039855;
    uVar1 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar1;
    **(undefined4 **)((int)this + 0x6c) = uVar1;
  }
  blit_glyph_to_surface((int *)((int)this + 0x6c),param_1,param_2,param_3,param_4,(int)param_5);
  blit_glyph_to_surface((int *)((int)this + 0xa8),param_1,param_2,param_3,param_4,(int)param_5);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_10039855:
  iVar2 = iVar2 + -1 + param_1;
  iVar3 = *(int *)(param_3 + 8) + -1 + param_2;
  if (param_1 < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = param_1;
  }
  if (param_2 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = param_2;
  }
  if (*(int *)((int)this + 0xa0) < iVar2) {
    *(int *)((int)this + 0xa0) = iVar2;
  }
  if (*(int *)((int)this + 0xa4) < iVar3) {
    *(int *)((int)this + 0xa4) = iVar3;
  }
  return;
}


