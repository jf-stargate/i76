/*
 * Program: i76.exe
 * Function: mission_objective_notepad_context_helper_0045e190
 * Entry: 0045e190
 * Signature: undefined4 __cdecl mission_objective_notepad_context_helper_0045e190(int * param_1)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_mission_objective_notepad_helper_0045e190. Shorten
   readability label. */

undefined4 __cdecl mission_objective_notepad_context_helper_0045e190(int *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int aiStack_68 [13];
  int aiStack_34 [13];
  
  puVar5 = (undefined4 *)&stack0xffffff94;
  iVar1 = (*DAT_005dd2bc)();
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = DAT_005dcee4 - DAT_005dcedc;
  uVar3 = DAT_005dcee8 - DAT_005dcee0;
  if ((iVar1 + 1 == *param_1) && (uVar3 + 1 == (param_1[1] << 3) >> 3)) {
    blit_bitmap_surface_context_clipped_with_palette_blend
              (&DAT_005dcec0,param_1,0,(uint *)0x0,(uint *)0x0);
  }
  else if (DAT_005dd2a8 == 1) {
    puVar2 = (undefined4 *)construct_bitmap_surface_context(aiStack_34,iVar1 + 1,uVar3 + 1,0,0);
    for (iVar4 = 0xd; puVar5 = puVar5 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = *puVar2;
      puVar2 = puVar2 + 1;
    }
    projection_or_clip_context_helper_0047a220(aiStack_68,param_1,0,0,iVar1,uVar3,0,'\0');
    blit_bitmap_surface_context_clipped_with_palette_blend
              (&DAT_005dcec0,aiStack_68,0,(uint *)0x0,(uint *)0x0);
    release_bitmap_surface_context(aiStack_68);
  }
  else {
    projection_or_clip_context_helper_0047a220(&DAT_005dcec0,param_1,0,0,iVar1,uVar3,0,'\0');
  }
  (*DAT_005dd2c0)(&DAT_005dcec0);
  (*DAT_005dd2e0)(&DAT_005dcec0);
  return 1;
}


