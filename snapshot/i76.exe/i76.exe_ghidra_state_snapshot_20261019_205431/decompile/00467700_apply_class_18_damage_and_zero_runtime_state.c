/*
 * Program: i76.exe
 * Function: apply_class_18_damage_and_zero_runtime_state
 * Entry: 00467700
 * Signature: undefined4 __cdecl apply_class_18_damage_and_zero_runtime_state(int param_1, int param_2)
 */


undefined4 __cdecl apply_class_18_damage_and_zero_runtime_state(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = *(int *)(param_1 + 0x70);
  iVar2 = 0;
  piVar3 = (int *)(param_2 + 8);
  do {
    if (((uint)*(ushort *)(param_2 + 4) & 1 << ((byte)iVar2 & 0x1f)) != 0) {
      if (*(int *)(iVar1 + 8) < *piVar3) {
        *(undefined4 *)(iVar1 + 8) = 0;
        *(undefined4 *)(iVar1 + 4) = 0;
        *(undefined4 *)(iVar1 + 0x10) = 0;
        return 1;
      }
      *(int *)(iVar1 + 8) = *(int *)(iVar1 + 8) - *piVar3;
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar2 < 4);
  return 0;
}


