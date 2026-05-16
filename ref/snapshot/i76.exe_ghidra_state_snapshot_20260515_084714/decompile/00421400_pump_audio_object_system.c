/*
 * Program: i76.exe
 * Function: pump_audio_object_system
 * Entry: 00421400
 * Signature: undefined4 __cdecl pump_audio_object_system(int param_1)
 */


/* [cgpt i76.exe shell callback rename v2; confidence=medium-high] ShellMain callback slot +0x28.
   Updates/pumps shell-visible audio object state. */

undefined4 __cdecl pump_audio_object_system(int param_1)

{
  float fVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  LPVOID pvVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  undefined4 *puVar12;
  uint local_c;
  uint local_8;
  uint local_4;
  
  get_tick_count_wrapper_b();
  if (DAT_004ed7e8 != 0) {
    if (DAT_00524564 == 0) {
      return 0;
    }
    if (param_1 != 0) {
      promote_pending_audio_objects_by_priority_flags();
      update_positional_audio_activation_by_distance();
      if (*(int *)(DAT_00524564 + 8) != 0) {
        update_audio_listener_cached_vectors_from_active_object();
      }
    }
    iVar10 = 0;
    piVar2 = *(int **)(DAT_00524564 + 0x1c);
joined_r0x00421459:
    piVar11 = piVar2;
    if (piVar11 != (int *)0x0) {
      piVar2 = (int *)*piVar11;
      if ((LPVOID)piVar11[0x17] != (LPVOID)0x0) {
        pvVar7 = release_world_object_tree_reference((LPVOID)piVar11[0x17],&PTR_DAT_004ed7ec);
        piVar11[0x17] = (int)pvVar7;
        if (pvVar7 == (LPVOID)0x0) {
          if (piVar11 != (int *)0x0) {
            piVar3 = (int *)piVar11[0x15];
            if (piVar3 == (int *)0x0) {
              uVar8 = 0;
            }
            else {
              (**(code **)(*piVar3 + 0x24))(piVar3,&local_c);
              uVar8 = local_c & 1;
            }
            if (uVar8 != 0) {
              (**(code **)(*(int *)piVar11[0x15] + 0x48))((int *)piVar11[0x15]);
              piVar11[0x1e] = piVar11[0x1e] & 0xfffffffb;
              piVar11[0x18] = piVar11[0x18] + -1;
            }
          }
          release_audio_object_resource_and_buffers(piVar11);
          piVar11 = (int *)0x0;
        }
      }
      if ((piVar11 != (int *)0x0) && ((piVar11[0x1e] & 8U) == 0)) {
        if ((piVar11[0x1e] & 4U) == 0) {
          iVar9 = start_audio_object_playback((int)piVar11,1);
          if (iVar9 == 0) {
            if ((piVar11[0x19] == 0) || (piVar11[0xf] == 1)) {
              move_audio_object_between_active_and_pending_lists(piVar11,(undefined4 *)0x0);
            }
            else {
              release_audio_object_resource_and_buffers(piVar11);
            }
            goto joined_r0x00421459;
          }
        }
        else {
          if (piVar11[0xf] == 2) {
            if ((char)piVar11[0x1d] == '\0') {
              piVar3 = (int *)piVar11[0x15];
              if (piVar3 == (int *)0x0) {
                uVar8 = 0;
              }
              else {
                (**(code **)(*piVar3 + 0x24))(piVar3,&local_8);
                uVar8 = local_8 & 1;
              }
              if (uVar8 != 0) {
                (**(code **)(*(int *)piVar11[0x15] + 0x48))((int *)piVar11[0x15]);
                piVar11[0x1e] = piVar11[0x1e] & 0xfffffffb;
                piVar11[0x18] = piVar11[0x18] + -1;
              }
            }
            else {
              *(undefined1 *)(piVar11 + 0x1d) = 0;
            }
          }
          piVar3 = (int *)piVar11[0x15];
          if (piVar3 == (int *)0x0) {
            uVar8 = 0;
          }
          else {
            (**(code **)(*piVar3 + 0x24))(piVar3,&local_4);
            uVar8 = local_4 & 1;
          }
          if (uVar8 == 0) {
            if ((code *)piVar11[0xb] == (code *)0x0) {
              if ((piVar11[0x19] == 0) || (piVar11[0xf] == 1)) {
                move_audio_object_between_active_and_pending_lists(piVar11,(undefined4 *)0x0);
              }
              else {
                release_audio_object_resource_and_buffers(piVar11);
              }
            }
            else {
              iVar9 = (*(code *)piVar11[0xb])(piVar11,3);
              if (iVar9 != 0) goto LAB_004215ba;
            }
            piVar11 = (int *)0x0;
          }
LAB_004215ba:
          if (piVar11 == (int *)0x0) goto joined_r0x00421459;
          if (piVar11[0x17] != 0) {
            piVar11[5] = piVar11[5] | 0x100;
          }
          piVar11[7] = (int)(float)piVar11[0x10];
          if (piVar11[0x11] == 1) {
            if (piVar11[0x11] == 2) {
              iVar9 = rand();
              fVar1 = *(float *)(&DAT_004ed7b8 + (iVar9 % 10) * 4);
              piVar11[5] = piVar11[5] | 0x20;
              piVar11[6] = (int)(fVar1 * (float)piVar11[6]);
            }
          }
          else {
            piVar11[6] = (int)(float)piVar11[0x12];
          }
          if (((code *)piVar11[10] != (code *)0x0) &&
             (iVar9 = (*(code *)piVar11[10])(piVar11,2), iVar9 == 0)) {
            piVar11 = (int *)0x0;
          }
          if (piVar11 == (int *)0x0) goto joined_r0x00421459;
          update_audio_object_buffer_volume_pan_and_release_target((int)piVar11,0);
        }
        iVar10 = iVar10 + 1;
      }
      goto joined_r0x00421459;
    }
    piVar2 = *(int **)(DAT_00524564 + 8);
    if (((piVar2 != (int *)0x0) && (iVar10 != 0)) && (param_1 != 0)) {
      (**(code **)(*piVar2 + 0x44))(piVar2);
    }
    if ((DAT_005fcbfc < DAT_005fcbf4) && (DAT_00524564 != 0)) {
      puVar12 = *(undefined4 **)(DAT_00524564 + 0x20);
      iVar10 = DAT_005fcbf4;
      iVar9 = DAT_005fcbfc;
      while (puVar12 != (undefined4 *)0x0) {
        puVar12 = (undefined4 *)0x0;
        puVar5 = *(undefined4 **)(DAT_00524564 + 0x20);
        iVar6 = 1000000;
        while (puVar5 != (undefined4 *)0x0) {
          if (iVar10 <= iVar9) {
            return 1;
          }
          iVar4 = puVar5[0x1b];
          if (((iVar4 < iVar6) && (puVar5[0x17] == 0)) && ((puVar5[0xf] != 1 && (0 < iVar6)))) {
            puVar12 = (undefined4 *)*puVar5;
            release_audio_object_resource_and_buffers(puVar5);
            puVar5 = puVar12;
            iVar6 = iVar4;
            iVar10 = DAT_005fcbf4;
            iVar9 = DAT_005fcbfc;
          }
          else {
            puVar5 = (undefined4 *)*puVar5;
          }
        }
        if (iVar10 <= iVar9) {
          return 1;
        }
      }
    }
  }
  return 1;
}


