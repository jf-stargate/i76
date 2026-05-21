/*
 * Program: i76.exe
 * Function: initialize_audio_gate_params_defaults
 * Entry: 00422a70
 * Signature: undefined __cdecl initialize_audio_gate_params_defaults(undefined4 * param_1)
 */


/* cgpt readability rename v13 set A: Initializes the short audio gate/category parameter block with
   GAS0 signature and sentinel defaults. */

void __cdecl initialize_audio_gate_params_defaults(undefined4 *param_1)

{
  *param_1 = 0x30534147;
  param_1[1] = 0xffffffff;
  param_1[2] = 0xffffffff;
  param_1[3] = 0xffffffff;
  param_1[4] = 0xffffffff;
  param_1[5] = 0xffffffff;
  param_1[6] = 0xffffffff;
  return;
}


