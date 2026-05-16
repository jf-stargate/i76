/*
 * Program: i76.exe
 * Function: force_feedback_runtime_update_helper_00445fd0
 * Entry: 00445fd0
 * Signature: undefined __cdecl force_feedback_runtime_update_helper_00445fd0(undefined4 * param_1, LPVOID param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: force feedback runtime update helper
   based on prior focused closure context. */

void __cdecl force_feedback_runtime_update_helper_00445fd0(undefined4 *param_1,LPVOID param_2)

{
  if ((param_2 != (LPVOID)0x0) && (param_1 != (undefined4 *)0x0)) {
    if (*(int *)((int)param_2 + 0x1c) == 0) {
      *param_1 = *(undefined4 *)((int)param_2 + 0x18);
    }
    else {
      *(undefined4 *)(*(int *)((int)param_2 + 0x1c) + 0x18) = *(undefined4 *)((int)param_2 + 0x18);
    }
    if (*(int *)((int)param_2 + 0x18) != 0) {
      *(undefined4 *)(*(int *)((int)param_2 + 0x18) + 0x1c) = *(undefined4 *)((int)param_2 + 0x1c);
    }
    HeapFree(g_runtime_parameter_heap,0,param_2);
  }
  return;
}


