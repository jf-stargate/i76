/*
 * Program: i76.exe
 * Function: move_audio_object_between_active_and_pending_lists
 * Entry: 00422540
 * Signature: undefined4 __cdecl move_audio_object_between_active_and_pending_lists(int * param_1, undefined4 * param_2)
 */


/* cgpt rename v3: Unlinks an audio object from its current list and reinserts it into the
   active/pending audio list with priority ordering. */

undefined4 __cdecl
move_audio_object_between_active_and_pending_lists(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  int *piVar10;
  
  puVar8 = param_2;
  if (param_2 == (undefined4 *)0x0) {
    param_2 = (undefined4 *)(DAT_00524564 + 0x20);
  }
  else {
    param_2 = (undefined4 *)(DAT_00524564 + 0x1c);
  }
  uVar5 = 2 - (puVar8 != (undefined4 *)0x0);
  uVar6 = param_1[0x1e] & 3;
  if (((uVar6 != 0) && ((param_1[0x1e] & uVar5) == 0)) && (uVar6 != 0)) {
    if (uVar6 == 1) {
      piVar7 = (int *)(DAT_00524564 + 0x1c);
    }
    else {
      piVar7 = (int *)(DAT_00524564 + 0x20);
    }
    piVar4 = (int *)*piVar7;
    piVar10 = piVar4;
    piVar9 = piVar4;
    while (piVar2 = piVar10, piVar2 != (int *)0x0) {
      if (param_1 == piVar2) {
        if (piVar2 == piVar4) {
          *piVar7 = *param_1;
        }
        else {
          *piVar9 = *param_1;
        }
        *param_1 = 0;
        break;
      }
      piVar9 = piVar2;
      piVar10 = (int *)*piVar2;
    }
    if (uVar6 == 1) {
      *(int *)(DAT_00524564 + 0xc) = *(int *)(DAT_00524564 + 0xc) + -1;
    }
    param_1[0x1e] = param_1[0x1e] & ~uVar6;
  }
  if (puVar8 == (undefined4 *)0x0) {
    iVar1 = param_1[0x17];
    param_1[0x1e] = param_1[0x1e] & 0xfffffffb;
    if (DAT_00524564 != 0) {
      for (puVar8 = *(undefined4 **)(DAT_00524564 + 0x20); puVar8 != (undefined4 *)0x0;
          puVar8 = (undefined4 *)*puVar8) {
        if ((puVar8[0x17] == iVar1) &&
           ((param_1 + 1 == (int *)0x0 ||
            (iVar3 = _stricmp((char *)(puVar8 + 1),(char *)(param_1 + 1)), iVar3 == 0))))
        goto LAB_00422636;
      }
    }
    puVar8 = (undefined4 *)0x0;
LAB_00422636:
    if (puVar8 != (undefined4 *)0x0) {
      release_audio_object_resource_and_buffers(param_1);
      return 0;
    }
    if (((LPVOID)param_1[0x17] != (LPVOID)0x0) && (param_1[0xf] != 1)) {
      finalize_released_world_object_after_damage((LPVOID)param_1[0x17],&PTR_DAT_004ed7ec);
      param_1[0x17] = 0;
    }
  }
  if ((*(byte *)(param_1 + 0x1e) & 3) == 0) {
    piVar7 = (int *)*param_2;
    if (piVar7 == (int *)0x0) {
      *param_2 = param_1;
    }
    else {
      iVar1 = param_1[0xd];
      piVar4 = piVar7;
      piVar9 = piVar7;
      do {
        piVar10 = piVar4;
        iVar3 = piVar10[0xd];
        piVar4 = piVar10;
        if (iVar1 != iVar3 && iVar3 <= iVar1) {
          if (piVar10 == piVar7) {
            *param_2 = param_1;
            *param_1 = (int)piVar10;
            piVar10 = piVar9;
          }
          else {
            *piVar9 = (int)param_1;
            *param_1 = (int)piVar10;
            piVar10 = piVar9;
          }
          break;
        }
        if (iVar1 == iVar3) {
          *param_1 = *piVar10;
          *piVar10 = (int)param_1;
          piVar10 = piVar9;
          break;
        }
        piVar4 = (int *)*piVar10;
        piVar9 = piVar10;
      } while (piVar4 != (int *)0x0);
      if (piVar4 == (int *)0x0) {
        *param_1 = 0;
        *piVar10 = (int)param_1;
      }
    }
    if (uVar5 == 1) {
      *(int *)(DAT_00524564 + 0xc) = *(int *)(DAT_00524564 + 0xc) + 1;
    }
    param_1[0x1e] = param_1[0x1e] | uVar5;
  }
  return 1;
}


