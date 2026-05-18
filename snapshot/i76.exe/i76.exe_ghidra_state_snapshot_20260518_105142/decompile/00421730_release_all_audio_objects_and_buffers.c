/*
 * Program: i76.exe
 * Function: release_all_audio_objects_and_buffers
 * Entry: 00421730
 * Signature: undefined __stdcall release_all_audio_objects_and_buffers(void)
 */


/* cgpt rename v3: Stops and releases all audio objects from both audio object lists and clears the
   audio runtime active flag. */

void release_all_audio_objects_and_buffers(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint local_4;
  
  if (DAT_00524564 != 0) {
    release_audio_world_object_attachment_records(0);
    puVar3 = *(undefined4 **)(DAT_00524564 + 0x1c);
    while (puVar3 != (undefined4 *)0x0) {
      piVar1 = (int *)puVar3[0x15];
      puVar2 = (undefined4 *)*puVar3;
      uVar4 = 0;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x24))(piVar1,&local_4);
        uVar4 = local_4 & 1;
      }
      if (uVar4 != 0) {
        (**(code **)(*(int *)puVar3[0x15] + 0x48))((int *)puVar3[0x15]);
      }
      release_audio_object_resource_and_buffers(puVar3);
      puVar3 = puVar2;
    }
    puVar3 = *(undefined4 **)(DAT_00524564 + 0x20);
    while (puVar3 != (undefined4 *)0x0) {
      piVar1 = (int *)puVar3[0x15];
      puVar2 = (undefined4 *)*puVar3;
      uVar4 = 0;
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x24))(piVar1,&local_4);
        uVar4 = local_4 & 1;
      }
      if (uVar4 != 0) {
        (**(code **)(*(int *)puVar3[0x15] + 0x48))((int *)puVar3[0x15]);
      }
      release_audio_object_resource_and_buffers(puVar3);
      puVar3 = puVar2;
    }
  }
  DAT_005fcbf4 = 0;
  return;
}


