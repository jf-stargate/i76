/*
 * Program: i76.exe
 * Function: begin_frame_timing_sample
 * Entry: 00498b50
 * Signature: undefined __stdcall begin_frame_timing_sample(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Begins frame timing sample using
   timeGetTime and timing globals. */

void begin_frame_timing_sample(void)

{
  if (DAT_005a7c90 != 0) {
    DAT_005a7c58 = timeGetTime();
    DAT_005a6c3c = 0;
    DAT_005a7c88 = DAT_005a7c58;
  }
  return;
}


