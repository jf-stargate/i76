/*
 * Program: i76.exe
 * Function: multiplayer_vote_prompt_context_helper_004557a0
 * Entry: 004557a0
 * Signature: undefined __stdcall multiplayer_vote_prompt_context_helper_004557a0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer vote prompt context helper
   based on prior focused closure context. */

void multiplayer_vote_prompt_context_helper_004557a0(void)

{
  if (DAT_005414f0 != 0) {
    dpDestroyPlayer(DAT_00541024,DAT_005414f0);
  }
  DAT_005414f0 = 0;
  DAT_005414f4 = 0;
  set_text_widget_visible_flag(DAT_005414fc,0);
  return;
}


