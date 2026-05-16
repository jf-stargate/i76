/*
 * Program: i76.exe
 * Function: vehicle_ground_contact_probe_context_helper_00440670
 * Entry: 00440670
 * Signature: undefined __cdecl vehicle_ground_contact_probe_context_helper_00440670(int * param_1, int param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: vehicle ground contact probe context
   helper based on prior focused closure context. */

void __cdecl vehicle_ground_contact_probe_context_helper_00440670(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int local_18 [6];
  
  piVar2 = *(int **)(param_2 + 0x18);
  if (piVar2 == (int *)0x0) {
    local_18[3] = 0;
    local_18[4] = 0;
    local_18[5] = 0;
    local_18[0] = 0;
    local_18[1] = 0;
    local_18[2] = 0;
  }
  else {
    local_18[0] = piVar2[3];
    local_18[1] = piVar2[8];
    local_18[2] = piVar2[0xb];
    local_18[3] = piVar2[*piVar2 + 2];
    local_18[4] = piVar2[piVar2[1] + 6];
    local_18[5] = piVar2[piVar2[2] + 10];
  }
  piVar2 = local_18;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *piVar2;
    piVar2 = piVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


