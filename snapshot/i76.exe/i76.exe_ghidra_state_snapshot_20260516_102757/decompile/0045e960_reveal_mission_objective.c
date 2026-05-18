/*
 * Program: i76.exe
 * Function: reveal_mission_objective
 * Entry: 0045e960
 * Signature: undefined __cdecl reveal_mission_objective(int param_1)
 */


/* cgpt whole-binary semantic rename v1: string evidence: reveal Objective %d */

void __cdecl reveal_mission_objective(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + -1;
  if ((((&DAT_006093c8)[iVar1] != 0) && (-1 < iVar1)) && (iVar1 < DAT_006093c0)) {
    if ((*(byte *)(&DAT_00609420 + iVar1) & 1) == 0) {
      report_chunk_parse_error();
    }
    (&DAT_00609420)[iVar1] = (&DAT_00609420)[iVar1] & 0xfffffffe;
    create_or_queue_positional_audio_object(s_cnote_wav_004f749c,0,(undefined4 *)0x0,(int *)0x0);
    return;
  }
  report_chunk_parse_error();
  return;
}


