/*
 * Program: i76.exe
 * Function: start_pending_audio_objects
 * Entry: 00422400
 * Signature: undefined __stdcall start_pending_audio_objects(void)
 */


/* cgpt rename v3: Walks active audio objects, starts objects that are not flagged as playing, and
   clears pending flags. */

void start_pending_audio_objects(void)

{
  undefined4 *puVar1;
  
  if (DAT_00524564 != 0) {
    for (puVar1 = *(undefined4 **)(DAT_00524564 + 0x1c); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if ((*(byte *)(puVar1 + 0x1e) & 4) == 0) {
        start_audio_object_playback((int)puVar1,1);
      }
      puVar1[0x1e] = puVar1[0x1e] & 0xfffffff7;
    }
  }
  return;
}


