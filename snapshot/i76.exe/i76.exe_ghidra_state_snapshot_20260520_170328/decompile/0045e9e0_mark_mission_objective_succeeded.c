/*
 * Program: i76.exe
 * Function: mark_mission_objective_succeeded
 * Entry: 0045e9e0
 * Signature: undefined __cdecl mark_mission_objective_succeeded(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: succeed Objective %d */

void __cdecl mark_mission_objective_succeeded(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1 + -1;
  if ((((&DAT_006093c8)[iVar2] == 0) || (iVar2 < 0)) || (DAT_006093c0 <= iVar2)) {
    report_error();
    return;
  }
  uVar1 = (&DAT_00609420)[iVar2];
  if ((uVar1 & 2) != 0) {
    report_error();
    return;
  }
  if ((uVar1 & 4) == 0) {
    if ((uVar1 & 1) != 0) {
      report_error();
    }
    (&DAT_00609420)[iVar2] = (&DAT_00609420)[iVar2] | 2;
    create_or_queue_positional_audio_object(s_cnote_wav_004f749c,0,(undefined4 *)0x0,(int *)0x0);
    return;
  }
  report_error();
  return;
}


