/*
 * Program: i76.exe
 * Function: parse_fsm_tactics_tag
 * Entry: 00412630
 * Signature: undefined __cdecl parse_fsm_tactics_tag(undefined4 param_1, int param_2)
 */


/* cgpt whole-binary semantic rename v1: string evidence: tactics tag bad value */

void __cdecl parse_fsm_tactics_tag(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  *(undefined4 *)(param_2 + 0x110) = 0xffffffff;
  iVar2 = 0;
  piVar1 = &DAT_004c3e50;
  do {
    if (*piVar1 != iVar2) {
      report_chunk_parse_error();
    }
    piVar1 = piVar1 + 0x4d5;
    iVar2 = iVar2 + 1;
  } while ((int)piVar1 < 0x4d86e4);
  *(undefined4 *)(param_2 + 0x11c) = 1;
  return;
}


