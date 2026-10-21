/*
 * Program: i76.exe
 * Function: world_object_placement_flags_helper_0046a060
 * Entry: 0046a060
 * Signature: undefined __cdecl world_object_placement_flags_helper_0046a060(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: world object placement flags helper
   based on adjacent named subsystem context. */

void __cdecl world_object_placement_flags_helper_0046a060(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  *(int *)(param_1 + 0x28) = param_2;
  if (0 < DAT_0058d900) {
    piVar2 = &DAT_00588e00;
    do {
      if (*piVar2 == param_2) goto LAB_0046a08d;
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x18;
    } while (iVar1 < DAT_0058d900);
  }
  iVar1 = -1;
LAB_0046a08d:
  *(int *)(param_1 + 0x2c) = iVar1;
  return;
}


