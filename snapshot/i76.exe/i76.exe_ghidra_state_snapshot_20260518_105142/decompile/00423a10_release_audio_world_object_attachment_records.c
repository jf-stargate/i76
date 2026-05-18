/*
 * Program: i76.exe
 * Function: release_audio_world_object_attachment_records
 * Entry: 00423a10
 * Signature: undefined __cdecl release_audio_world_object_attachment_records(int param_1)
 */


/* cgpt rename v4: Walks and frees the audio world-object attachment/association list, releasing
   nested audio objects and clearing the global list head. */

void __cdecl release_audio_world_object_attachment_records(int param_1)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  int iVar3;
  
  if (DAT_0052457c != (LPVOID)0x0) {
    pvVar1 = DAT_0052457c;
    if (param_1 != 0) {
      pvVar1 = *(LPVOID *)((int)DAT_0052457c + 0x20);
    }
    while (pvVar1 != (LPVOID)0x0) {
      pvVar2 = *(LPVOID *)((int)pvVar1 + 0x20);
      iVar3 = world_object_has_optional_runtime_flag(*(int *)((int)pvVar1 + 0x10));
      if ((iVar3 != 0) && (iVar3 = cockpit_gauge_context_helper_00459d90(), iVar3 != 0)) {
        cockpit_hud_texture_context_helper_00459d60();
      }
      if (*(undefined4 **)((int)pvVar1 + 0x14) != (undefined4 *)0x0) {
        release_audio_object_if_present(*(undefined4 **)((int)pvVar1 + 0x14));
      }
      xfree_global_heap(pvVar1);
      pvVar1 = pvVar2;
    }
  }
  DAT_0052457c = (LPVOID)0x0;
  return;
}


