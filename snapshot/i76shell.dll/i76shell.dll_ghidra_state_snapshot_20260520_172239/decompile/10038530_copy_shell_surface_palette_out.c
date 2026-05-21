/*
 * Program: i76shell.dll
 * Function: copy_shell_surface_palette_out
 * Entry: 10038530
 * Signature: undefined __thiscall copy_shell_surface_palette_out(void * this, undefined4 * param_1)
 */


void __thiscall copy_shell_surface_palette_out(void *this,undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)((int)this + 0xbc);
  for (iVar1 = 0xc0; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


