/*
 * Program: i76.exe
 * Function: update_flamer_effect_state
 * Entry: 00443e90
 * Signature: undefined __stdcall update_flamer_effect_state(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt whole-binary semantic rename v1: string evidence: flamer */

void update_flamer_effect_state(void)

{
  int *piVar1;
  
  piVar1 = DAT_0052bb90;
  if (DAT_0052bb90 != (int *)0x0) {
    do {
      if ((piVar1[1] != 0) && (piVar1[4] == 0)) {
        if (piVar1[6] != piVar1[7]) {
          piVar1[7] = (&DAT_0052baf0)[piVar1[7]];
          piVar1[5] = piVar1[5] + -1;
          if (piVar1[6] != piVar1[7]) {
            piVar1[7] = (&DAT_0052baf0)[piVar1[7]];
            piVar1[5] = piVar1[5] + -1;
          }
        }
        if (piVar1[3] != 0) {
          release_world_object_light_runtime(piVar1[3]);
          if (piVar1[7] < piVar1[6] + 2) {
            unlink_and_release_world_object_node_refcounted((LPVOID)piVar1[3],s_flamer_004f22e0);
            piVar1[3] = 0;
          }
          else {
            create_lobj_light_runtime_entry
                      (piVar1[3],0,(float)piVar1[5] - _DAT_004bd310,0.0,(float *)0x0,
                       (undefined4 *)0x0);
          }
        }
        if (piVar1[6] == piVar1[7]) {
          release_world_object_light_runtime(piVar1[1]);
          if ((LPVOID)piVar1[3] != (LPVOID)0x0) {
            unlink_and_release_world_object_node_refcounted((LPVOID)piVar1[3],s_flamer_004f22e0);
          }
          finalize_released_world_object_after_damage((LPVOID)piVar1[1],s_flamer_004f22e0);
          finalize_released_world_object_after_damage((LPVOID)piVar1[2],s_flamer_004f22e0);
          piVar1[1] = 0;
          piVar1[2] = 0;
          piVar1[3] = 0;
          piVar1[6] = 0;
          piVar1[7] = 0;
          piVar1[5] = 0;
          piVar1[10] = 0;
          piVar1[0xb] = 0;
          piVar1[0xc] = 0;
          piVar1[0xd] = 0;
        }
      }
      piVar1[4] = 0;
      piVar1 = (int *)*piVar1;
    } while (piVar1 != DAT_0052bb90);
  }
  return;
}


