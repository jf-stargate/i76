/*
 * Program: i76shell.dll
 * Function: fill_shell_surface_rect_from_buffer
 * Entry: 10038b70
 * Signature: undefined __thiscall fill_shell_surface_rect_from_buffer(void * this, undefined4 param_1, int param_2, int param_3, int param_4, int param_5)
 */


void __thiscall
fill_shell_surface_rect_from_buffer
          (void *this,undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  
  local_28 = &local_14;
  local_1c = param_4 + -1;
  local_18 = param_5 + -1;
  local_24 = 0;
  local_14 = param_1;
  local_20 = 0;
  local_10 = local_1c;
  local_c = local_18;
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar3 != 0) goto LAB_10038c3d;
    uVar2 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar2;
    **(undefined4 **)((int)this + 0x6c) = uVar2;
  }
  blit_or_fill_rect_clipped
            ((int *)&local_28,0,0,(int *)((int)this + 0x6c),param_2,param_3,0xffffffff);
  blit_or_fill_rect_clipped
            ((int *)&local_28,0,0,(int *)((int)this + 0xa8),param_2,param_3,0xffffffff);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_10038c3d:
  iVar3 = param_4 + -1 + param_2;
  iVar1 = param_5 + -1 + param_3;
  if (param_2 < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = param_2;
  }
  if (param_3 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = param_3;
  }
  if (*(int *)((int)this + 0xa0) < iVar3) {
    *(int *)((int)this + 0xa0) = iVar3;
  }
  if (*(int *)((int)this + 0xa4) < iVar1) {
    *(int *)((int)this + 0xa4) = iVar1;
  }
  return;
}


