/*
 * Program: i76.exe
 * Function: dequeue_player_control_input
 * Entry: 0041f8e0
 * Signature: undefined4 __cdecl dequeue_player_control_input(int param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5, undefined4 * param_6, undefined4 * param_7)
 */


/* cgpt whole-binary semantic rename v1: string evidence: Dequeued control from empty queue */

undefined4 __cdecl
dequeue_player_control_input
          (int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
          undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xa6c8) == *(int *)(param_1 + 0xa6cc)) {
    report_error();
    return 0;
  }
  *param_2 = *(undefined4 *)(param_1 + 0x9d68 + *(int *)(param_1 + 0xa6c8) * 0x18);
  *param_3 = *(undefined4 *)(param_1 + 0x9d6c + *(int *)(param_1 + 0xa6c8) * 0x18);
  *param_4 = *(undefined4 *)(param_1 + 0x9d74 + *(int *)(param_1 + 0xa6c8) * 0x18);
  *param_5 = *(undefined4 *)(param_1 + 0x9d70 + *(int *)(param_1 + 0xa6c8) * 0x18);
  *param_6 = *(undefined4 *)(param_1 + 0x9d78 + *(int *)(param_1 + 0xa6c8) * 0x18);
  *param_7 = *(undefined4 *)(param_1 + 0x9d7c + *(int *)(param_1 + 0xa6c8) * 0x18);
  iVar1 = *(int *)(param_1 + 0xa6c8) + 1;
  *(int *)(param_1 + 0xa6c8) = iVar1;
  if (iVar1 == 100) {
    *(undefined4 *)(param_1 + 0xa6c8) = 0;
  }
  if (*(int *)(param_1 + 0xa6c8) == *(int *)(param_1 + 0xa6cc)) {
    *(undefined4 *)(param_1 + 0xa6d0) = 1;
  }
  return 1;
}


