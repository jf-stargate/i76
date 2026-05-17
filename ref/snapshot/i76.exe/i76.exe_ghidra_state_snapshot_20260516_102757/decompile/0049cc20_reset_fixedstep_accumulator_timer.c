/*
 * Program: i76.exe
 * Function: reset_fixedstep_accumulator_timer
 * Entry: 0049cc20
 * Signature: undefined __cdecl reset_fixedstep_accumulator_timer(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle mainloop physics rename v30; confidence=medium-high] Resets or initializes
   the fixed-step accumulator/timer embedded in the vehicle runtime context at +0x444. */

void __cdecl reset_fixedstep_accumulator_timer(int param_1)

{
  int iVar1;
  
                    /* I76 vehicle trace anchor: fixed-step accumulator reset helper */
  iVar1 = ftol();
  *(int *)(param_1 + 8) = iVar1 + 1;
  if (0x14 < iVar1 + 1) {
    *(undefined4 *)(param_1 + 8) = 0x14;
  }
  *(float *)(param_1 + 4) = (float)(&DAT_005a7e1c)[*(int *)(param_1 + 8)] * _DAT_004fe420;
  return;
}


