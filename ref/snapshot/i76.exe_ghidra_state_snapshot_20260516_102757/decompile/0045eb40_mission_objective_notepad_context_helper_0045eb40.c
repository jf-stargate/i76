/*
 * Program: i76.exe
 * Function: mission_objective_notepad_context_helper_0045eb40
 * Entry: 0045eb40
 * Signature: int __stdcall mission_objective_notepad_context_helper_0045eb40(void)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_mission_objective_notepad_helper_0045eb40. Shorten
   readability label. */

int mission_objective_notepad_context_helper_0045eb40(void)

{
  if ((&DAT_006093e0)[DAT_00609438] != 0) {
    if (DAT_00609438 < 0) {
      return 0;
    }
    if (DAT_00609438 < DAT_006093c4) {
      return (&DAT_006093e0)[DAT_00609438];
    }
  }
  if (DAT_00609438 < 0) {
    return 0;
  }
  return DAT_00609438;
}


