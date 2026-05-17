/*
 * Program: i76.exe
 * Function: world_instance_id_remove_context_helper_004ad5b0
 * Entry: 004ad5b0
 * Signature: undefined4 __cdecl world_instance_id_remove_context_helper_004ad5b0(int param_1, int param_2, int param_3)
 */


/* cgpt readability rename set E v17: Readability pass set E: world instance id remove context
   helper based on adjacent named subsystem context. */

undefined4 __cdecl
world_instance_id_remove_context_helper_004ad5b0(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  uVar1 = 0;
  iVar2 = *(int *)(param_1 + 8) + -1;
  if (-1 < iVar2) {
    piVar3 = (int *)(iVar2 * 0x10 + *(int *)(param_1 + 4));
    while ((*piVar3 != param_2 || (piVar3[1] != param_3))) {
      iVar2 = iVar2 + -1;
      piVar3 = piVar3 + -4;
      if (iVar2 < 0) {
        return uVar1;
      }
    }
    uVar1 = *(undefined4 *)(iVar2 * 0x10 + 8 + *(int *)(param_1 + 4));
  }
  return uVar1;
}


