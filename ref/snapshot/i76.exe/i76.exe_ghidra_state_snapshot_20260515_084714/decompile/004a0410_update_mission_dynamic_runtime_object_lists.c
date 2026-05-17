/*
 * Program: i76.exe
 * Function: update_mission_dynamic_runtime_object_lists
 * Entry: 004a0410
 * Signature: undefined __stdcall update_mission_dynamic_runtime_object_lists(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe vehicle engine/suspension rename v28; confidence=medium-high] Per-frame mission
   runtime object/effect list update; broader than vehicle transform update. */

void update_mission_dynamic_runtime_object_lists(void)

{
  float fVar1;
  undefined4 *puVar2;
  int iVar3;
  float10 fVar4;
  
  fVar4 = get_runtime_frame_delta_seconds();
  fVar1 = (float)fVar4;
  update_pending_mission_vehicle_effect_spawns();
  if ((fVar1 != _DAT_004bea34) && (iVar3 = 0, 0 < DAT_005a810c)) {
    puVar2 = &DAT_00655290;
    do {
      update_mission_runtime_object_list_and_release_expired(*(int **)(puVar2[-1] + 100),fVar1,0);
      update_mission_runtime_object_list_and_release_expired((int *)*puVar2,fVar1,1);
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 0x34;
    } while (iVar3 < DAT_005a810c);
  }
  return;
}


