/*
 * Program: i76.exe
 * Function: allocate_initialized_ai_fsm_behavior_state_block
 * Entry: 00415640
 * Signature: int __stdcall allocate_initialized_ai_fsm_behavior_state_block(void)
 */


/* cgpt rename v12 fsm/roadwar/path cluster: Allocates and initializes the large AI/FSM behavior
   state block with tactics, timers, target slots, and path state defaults. */

int allocate_initialized_ai_fsm_behavior_state_block(void)

{
  int iVar1;
  
  iVar1 = xalloc_global_heap(0xa9d8);
  *(undefined4 *)(iVar1 + 8) = 0;
  *(undefined4 *)(iVar1 + 0x98) = 0;
  *(undefined4 *)(iVar1 + 0x7c) = 0;
  *(undefined4 *)(iVar1 + 0x88) = 0;
  *(undefined4 *)(iVar1 + 0x94) = 0;
  *(undefined4 *)(iVar1 + 0x90) = 0;
  *(undefined4 *)(iVar1 + 0x9c) = 0;
  *(undefined4 *)(iVar1 + 0x9cf0) = 0;
  *(undefined4 *)(iVar1 + 0x9cf4) = 0;
  *(undefined4 *)(iVar1 + 0x84) = 2;
  *(int *)(iVar1 + 0x60) = iVar1 + 100;
  *(undefined4 *)(iVar1 + 0x5c) = 1;
  *(undefined4 *)(iVar1 + 0xa818) = 4;
  set_fsm_tactics_weights_from_indices(iVar1,4,4,4,4);
  *(undefined4 *)(iVar1 + 0xa6d0) = 1;
  *(undefined4 *)(iVar1 + 0x9d58) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d5c) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d60) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d64) = 0x3f800000;
  *(undefined4 *)(iVar1 + 0x9d14) = 1;
  *(undefined4 *)(iVar1 + 0xa6d4) = 0xfffffff6;
  *(undefined4 *)(iVar1 + 0xa6d8) = 0xfffffff6;
  *(undefined4 *)(iVar1 + 0xa6dc) = 0xfffffff6;
  *(undefined4 *)(iVar1 + 0xa6e4) = 0;
  *(undefined4 *)(iVar1 + 0xa6e8) = 0;
  *(undefined4 *)(iVar1 + 0xa6ec) = 0;
  *(undefined4 *)(iVar1 + 0xa6e0) = 0;
  *(undefined4 *)(iVar1 + 0xa6f0) = 0;
  *(undefined4 *)(iVar1 + 0xa954) = 1;
  *(undefined4 *)(iVar1 + 0xa96c) = 0;
  *(undefined4 *)(iVar1 + 0xa998) = 0;
  *(undefined4 *)(iVar1 + 0xa99c) = 0;
  *(undefined4 *)(iVar1 + 0xa9a0) = 0;
  *(undefined4 *)(iVar1 + 0xa9a4) = 0;
  *(undefined4 *)(iVar1 + 0xa9a8) = 1;
  *(undefined4 *)(iVar1 + 0xa9ac) = 0;
  *(undefined4 *)(iVar1 + 0xa9b0) = 0;
  *(undefined4 *)(iVar1 + 0xa9b4) = 0;
  *(undefined4 *)(iVar1 + 0xa9b8) = 0;
  *(undefined4 *)(iVar1 + 0xa9bc) = 0;
  *(undefined4 *)(iVar1 + 0xa9c0) = 0;
  *(undefined4 *)(iVar1 + 0xa9c4) = 0;
  *(undefined4 *)(iVar1 + 0xa9c8) = 0;
  *(undefined4 *)(iVar1 + 0xa9cc) = 0x7f7fffff;
  *(undefined1 *)(iVar1 + 0xa9d0) = 0;
  *(undefined4 *)(iVar1 + 0xa9d4) = 0;
  *(undefined4 *)(iVar1 + 0xa714) = 1;
  return iVar1;
}


