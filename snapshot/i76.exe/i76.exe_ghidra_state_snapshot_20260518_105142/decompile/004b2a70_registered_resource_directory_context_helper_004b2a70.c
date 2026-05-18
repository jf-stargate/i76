/*
 * Program: i76.exe
 * Function: registered_resource_directory_context_helper_004b2a70
 * Entry: 004b2a70
 * Signature: int __cdecl registered_resource_directory_context_helper_004b2a70(int * param_1, int param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: registered resource directory context
   helper based on adjacent named subsystem context. */

int __cdecl registered_resource_directory_context_helper_004b2a70(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar1 = param_1;
  do {
    iVar2 = *piVar1 - *(int *)((int)piVar1 + (param_2 - (int)param_1));
    if (iVar2 != 0) goto LAB_004b2a98;
    piVar1 = piVar1 + 1;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  iVar2 = 0;
LAB_004b2a98:
  if (iVar2 == 0) {
    if (*(uint *)(param_2 + 0x10) < (uint)param_1[4]) {
      return 1;
    }
    iVar2 = -(uint)((uint)param_1[4] < *(uint *)(param_2 + 0x10));
  }
  return iVar2;
}


