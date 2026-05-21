/*
 * Program: i76shell.dll
 * Function: mark_shell_surface_dirty_rect
 * Entry: 10037d60
 * Signature: undefined __thiscall mark_shell_surface_dirty_rect(void * this, int param_1, int param_2, int param_3, int param_4)
 */


void __thiscall
mark_shell_surface_dirty_rect(void *this,int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_3 + -1 + param_1;
  iVar2 = param_4 + -1 + param_2;
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


