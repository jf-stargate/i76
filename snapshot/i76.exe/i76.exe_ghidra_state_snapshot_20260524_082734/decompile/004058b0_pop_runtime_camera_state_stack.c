/*
 * Program: i76.exe
 * Function: pop_runtime_camera_state_stack
 * Entry: 004058b0
 * Signature: undefined4 __stdcall pop_runtime_camera_state_stack(void)
 */


/* cgpt readability rename v13 set A: Pops one saved runtime camera/view state from the stack into
   the active display-mode camera state. */

undefined4 pop_runtime_camera_state_stack(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (DAT_004c2988 < 1) {
    return 0;
  }
  DAT_004c2988 = DAT_004c2988 + -1;
  puVar2 = &g_runtime_display_mode_change_callback;
  puVar3 = (undefined4 *)(DAT_004c2988 * 0x268 + 0x5dbb20);
  for (iVar1 = 0x9a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return 1;
}


