/*
 * Program: i76shell.dll
 * Function: draw_mw2_image_subresource_to_shell_surface
 * Entry: 10039390
 * Signature: undefined __thiscall draw_mw2_image_subresource_to_shell_surface(void * this, int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
 */


void __thiscall
draw_mw2_image_subresource_to_shell_surface
          (void *this,int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar3 != 0) goto LAB_10039429;
    uVar2 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar2;
    **(undefined4 **)((int)this + 0x6c) = uVar2;
  }
  blit_mw2_image_subresource_rle_clipped((int *)((int)this + 0x6c),param_1,param_2,param_3,param_4);
  blit_mw2_image_subresource_rle_clipped((int *)((int)this + 0xa8),param_1,param_2,param_3,param_4);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_10039429:
  iVar3 = param_5 + -1 + param_3;
  iVar1 = param_6 + -1 + param_4;
  if (param_3 < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = param_3;
  }
  if (param_4 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = param_4;
  }
  if (*(int *)((int)this + 0xa0) < iVar3) {
    *(int *)((int)this + 0xa0) = iVar3;
  }
  if (*(int *)((int)this + 0xa4) < iVar1) {
    *(int *)((int)this + 0xa4) = iVar1;
  }
  return;
}


