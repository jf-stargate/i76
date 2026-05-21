/*
 * Program: i76shell.dll
 * Function: set_shell_surface_palette_from_rgb6
 * Entry: 10038550
 * Signature: undefined __thiscall set_shell_surface_palette_from_rgb6(void * this, undefined4 * param_1, undefined4 param_2)
 */


void __thiscall
set_shell_surface_palette_from_rgb6(void *this,undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)((int)this + 0xbc);
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)((int)this + 0x20) = 1;
  *(undefined4 *)((int)this + 0x24) = param_2;
  return;
}


