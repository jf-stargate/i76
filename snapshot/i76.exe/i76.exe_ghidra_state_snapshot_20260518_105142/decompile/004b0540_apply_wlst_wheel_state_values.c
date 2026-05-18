/*
 * Program: i76.exe
 * Function: apply_wlst_wheel_state_values
 * Entry: 004b0540
 * Signature: undefined4 __cdecl apply_wlst_wheel_state_values(int param_1, int * param_2)
 */


/* [cgpt i76.exe descriptor callback rename v6; confidence=medium-high] Alternate WLST callback.
   Applies six wheel state values to already-created wheel objects. */

undefined4 __cdecl apply_wlst_wheel_state_values(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(*param_2 + 0x70);
  if ((*(int *)(iVar1 + 0x3a8) != 0) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x3a8) + 0x70), iVar2 != 0)) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 8);
  }
  if ((*(int *)(iVar1 + 0x3ac) != 0) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x3ac) + 0x70), iVar2 != 0)) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 0xc);
  }
  if ((*(int *)(iVar1 + 0x3b0) != 0) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x3b0) + 0x70), iVar2 != 0)) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 0x10);
  }
  if ((*(int *)(iVar1 + 0x3b4) != 0) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x3b4) + 0x70), iVar2 != 0)) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 0x14);
  }
  if ((*(int *)(iVar1 + 0x3b8) != 0) &&
     (iVar2 = *(int *)(*(int *)(iVar1 + 0x3b8) + 0x70), iVar2 != 0)) {
    *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(param_1 + 0x18);
  }
  if ((*(int *)(iVar1 + 0x3bc) != 0) &&
     (iVar1 = *(int *)(*(int *)(iVar1 + 0x3bc) + 0x70), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 4) = *(undefined4 *)(param_1 + 0x1c);
  }
  return 1;
}


