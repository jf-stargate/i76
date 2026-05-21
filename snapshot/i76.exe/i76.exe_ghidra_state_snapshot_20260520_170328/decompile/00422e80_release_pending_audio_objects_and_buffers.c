/*
 * Program: i76.exe
 * Function: release_pending_audio_objects_and_buffers
 * Entry: 00422e80
 * Signature: undefined __stdcall release_pending_audio_objects_and_buffers(void)
 */


/* cgpt readability rename v13 set A: Releases all pending audio objects and clears one audio-list
   runtime flag. */

void release_pending_audio_objects_and_buffers(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if (DAT_00524564 != 0) {
    puVar2 = *(undefined4 **)(DAT_00524564 + 0x20);
    while (puVar2 != (undefined4 *)0x0) {
      puVar1 = (undefined4 *)*puVar2;
      release_audio_object_resource_and_buffers(puVar2);
      puVar2 = puVar1;
    }
  }
  DAT_005fcbf4 = 0;
  return;
}


