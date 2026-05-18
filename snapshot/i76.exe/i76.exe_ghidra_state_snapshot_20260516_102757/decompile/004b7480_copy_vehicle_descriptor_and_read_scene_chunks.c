/*
 * Program: i76.exe
 * Function: copy_vehicle_descriptor_and_read_scene_chunks
 * Entry: 004b7480
 * Signature: undefined __cdecl copy_vehicle_descriptor_and_read_scene_chunks(void * param_1, undefined4 * param_2, char * param_3)
 */


/* [cgpt i76.exe vehicle asset format renames v16; confidence=high] Copies selected vehicle
   descriptor fields, then reads VCST/WLST/WPST scene/state chunks for shell/world-object vehicle
   descriptors. */

void __cdecl
copy_vehicle_descriptor_and_read_scene_chunks(void *param_1,undefined4 *param_2,char *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)((int)param_1 + 0xbc);
  *(undefined4 *)((int)param_1 + 0x3d) = *param_2;
  *(undefined4 *)((int)param_1 + 0x41) = param_2[1];
  *(undefined4 *)((int)param_1 + 0x45) = param_2[2];
  *(undefined4 *)((int)param_1 + 0x4c) = param_2[3];
  *(undefined4 *)((int)param_1 + 0x50) = param_2[4];
  *(undefined4 *)((int)param_1 + 0x54) = param_2[5];
  *(undefined4 *)((int)param_1 + 0x58) = param_2[6];
  *(undefined4 *)((int)param_1 + 0x5c) = param_2[7];
  *(undefined4 *)((int)param_1 + 0x60) = param_2[8];
  if (0 < iVar3) {
    puVar1 = (undefined4 *)((int)param_1 + 0x68);
    puVar2 = param_2 + 0x27;
    do {
      puVar1[-1] = puVar2[-0x1e];
      *puVar1 = *puVar2;
      puVar1[1] = 0xffffffff;
      puVar1 = puVar1 + 3;
      iVar3 = iVar3 + -1;
      puVar2 = puVar2 + 1;
    } while (iVar3 != 0);
  }
  *(undefined1 *)((int)param_1 + 0x49) = *(undefined1 *)(param_2 + 0x45);
  *(undefined1 *)((int)param_1 + 0x4a) = *(undefined1 *)((int)param_2 + 0x115);
  *(undefined1 *)((int)param_1 + 0x4b) = *(undefined1 *)((int)param_2 + 0x116);
  *(undefined4 *)((int)param_1 + 0xd) = param_2[0x46];
  *(undefined4 *)((int)param_1 + 0x11) = param_2[0x47];
  *(undefined4 *)((int)param_1 + 0x15) = param_2[0x48];
  *(undefined4 *)((int)param_1 + 0x19) = param_2[0x49];
  *(undefined4 *)((int)param_1 + 0x1d) = param_2[0x46];
  *(undefined4 *)((int)param_1 + 0x21) = param_2[0x47];
  *(undefined4 *)((int)param_1 + 0x25) = param_2[0x48];
  *(undefined4 *)((int)param_1 + 0x29) = param_2[0x49];
  read_vehicle_scene_state_chunks(param_3,param_1,*(int *)((int)param_1 + 0xbc));
  return;
}


