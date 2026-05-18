/*
 * Program: i76.exe
 * Function: target_reticle_context_helper_00459330
 * Entry: 00459330
 * Signature: undefined __cdecl target_reticle_context_helper_00459330(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was cockpit_hud_ui_target_reticle_helper_00459330. Shorten readability
   label. */

void __cdecl target_reticle_context_helper_00459330(int param_1)

{
  int iVar1;
  undefined4 local_4;
  
  iVar1 = *(int *)(param_1 + 0x70);
  _DAT_0054a328 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x158)) * _DAT_004bdfdc;
  _DAT_0054a32c = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x15c)) * _DAT_004bdfdc;
  _DAT_0054a330 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x160)) * _DAT_004bdfdc;
  _DAT_0054a334 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x164)) * _DAT_004bdfdc;
  _DAT_0054a3b0 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x168)) * _DAT_004bdfdc;
  _DAT_0054a3b4 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x16c)) * _DAT_004bdfdc;
  _DAT_0054a3b8 = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x170)) * _DAT_004bdfdc;
  _DAT_0054a3bc = (_DAT_004bdfd8 / (float)*(int *)(iVar1 + 0x174)) * _DAT_004bdfdc;
  extract_engine_or_suspension_state_pair(*(int *)(iVar1 + 0x3c4),&local_4,&param_1);
  _DAT_0054a2a8 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_engine_or_suspension_state_pair(*(int *)(iVar1 + 0x3c8),&local_4,&param_1);
  _DAT_0054ab8c = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3cc),&local_4,&param_1);
  _DAT_0054a404 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3b8),&local_4,&param_1);
  _DAT_0054a268 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3bc),&local_4,&param_1);
  _DAT_0054a408 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3a8),&local_4,&param_1);
  _DAT_0054a2a4 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  extract_part_damage_state_pair(*(int *)(iVar1 + 0x3ac),&local_4,&param_1);
  _DAT_0054a410 = (_DAT_004bdfd8 / (float)param_1) * _DAT_004bdfdc;
  return;
}


