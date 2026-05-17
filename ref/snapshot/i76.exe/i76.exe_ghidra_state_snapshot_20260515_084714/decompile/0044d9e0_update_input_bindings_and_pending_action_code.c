/*
 * Program: i76.exe
 * Function: update_input_bindings_and_pending_action_code
 * Entry: 0044d9e0
 * Signature: undefined __stdcall update_input_bindings_and_pending_action_code(void)
 */


/* [cgpt i76.exe runtime loop refinement v23; confidence=HIGH] Early per-frame input update. Polls
   device callbacks, evaluates condition/axis bindings, updates bound axis values, and writes
   g_pending_input_action_code. */

void update_input_bindings_and_pending_action_code(void)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined **ppuVar3;
  undefined4 *puVar4;
  uint *puVar5;
  int iVar6;
  byte bVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 *puVar13;
  undefined2 uStack_6;
  int iStack_4;
  
  iVar10 = 0;
  if (0 < g_input_axis_binding_count) {
    piVar12 = &DAT_00536840;
    do {
      puVar11 = (undefined4 *)piVar12[3];
      if (((char *)puVar11[0xb] == (char *)0x0) || (*(char *)puVar11[0xb] == '\0')) {
        if (((char *)puVar11[0xc] != (char *)0x0) && (*(char *)puVar11[0xc] != '\0')) {
          iStack_4 = *(int *)*puVar11 << (*(byte *)(puVar11 + 5) & 0x1f);
          *(undefined4 *)puVar11[1] = 0;
          uVar2 = ftol();
          puVar11[7] = uVar2;
        }
      }
      else {
        if (*piVar12 != 0) {
          iVar8 = piVar12[-2];
          if ((&DAT_0053da50)[iVar8] != 0) {
            (**(code **)((&g_input_device_callback_table)[iVar8] + 0x10))
                      ((&DAT_005363f0)[iVar8 * 0x1d],piVar12[-1]);
          }
        }
        puVar11[7] = puVar11[4];
        *(undefined4 *)puVar11[1] = 0;
        piVar12[1] = 0;
      }
      *(undefined1 *)((int)puVar11 + 0x15) = 0;
      iVar10 = iVar10 + 1;
      piVar12 = piVar12 + 0x20;
    } while (iVar10 < g_input_axis_binding_count);
  }
  ppuVar3 = &PTR_DAT_004f2864;
  do {
    if (ppuVar3[1] != (undefined *)0x0) {
      **ppuVar3 = 0;
    }
    ppuVar3 = ppuVar3 + 8;
  } while (ppuVar3 < &DAT_004f3324);
  if (DAT_0053681c == 0) {
    iVar10 = 0;
    if (0 < g_input_device_context_count) {
      puVar11 = &DAT_005363f0;
      puVar13 = &DAT_005365c8;
      do {
        if (((&DAT_0053da50)[iVar10] != 0) &&
           ((iVar10 != DAT_0053682c ||
            (puVar4 = ui_bitmap_region_context_helper_0049beb0(), puVar4 == (undefined4 *)0x0)))) {
          (**(code **)((&g_input_device_callback_table)[iVar10] + 0x14))
                    (*puVar11,puVar13,puVar13 + 0x10);
        }
        iVar10 = iVar10 + 1;
        puVar13 = puVar13 + 0x14;
        puVar11 = puVar11 + 0x1d;
      } while (iVar10 < g_input_device_context_count);
    }
    iVar10 = 0;
    if (0 < g_input_condition_binding_count) {
      puVar9 = &DAT_0053ae90;
      do {
        if ((DAT_004f2848 != 0) || (puVar9[1] != 0)) {
          iVar8 = 0;
          puVar1 = puVar9;
          if (0 < (int)*puVar9) {
            do {
              puVar5 = puVar1 + 3;
              if (puVar1[4] == 1) {
                if ((*puVar5 & *(uint *)puVar1[2]) != 0) goto LAB_0044dcae;
              }
              else if ((*puVar5 & *(uint *)puVar1[2]) == 0) {
LAB_0044dcae:
                bVar7 = 0;
                goto LAB_0044db74;
              }
              iVar8 = iVar8 + 1;
              puVar1 = puVar5;
            } while (iVar8 < (int)*puVar9);
          }
          bVar7 = 1;
LAB_0044db74:
          if (((char)puVar9[-1] == '\0') || (*(char *)((int)puVar9 + -3) == '\0')) {
            *(byte *)puVar9[-2] = *(byte *)puVar9[-2] | bVar7;
          }
          *(byte *)((int)puVar9 + -3) = bVar7;
        }
        iVar10 = iVar10 + 1;
        puVar9 = puVar9 + 0x1c;
      } while (iVar10 < g_input_condition_binding_count);
    }
    iVar10 = 0;
    if (0 < g_input_axis_binding_count) {
      piVar12 = (int *)&DAT_005368b4;
      do {
        if ((DAT_004f2848 != 0) || (*piVar12 != 0)) {
          iVar8 = input_device_binding_input_action_state_helper_0044d780(piVar12 + -0x1f);
          if ((iVar8 == 0) && ((int *)piVar12[-0x1d] != (int *)0x0)) {
            iVar8 = 0;
            if (0 < piVar12[-0x19]) {
              puVar9 = (uint *)(piVar12 + -0x17);
              do {
                if (puVar9[1] == 1) {
                  if ((*puVar9 & *(uint *)puVar9[-1]) != 0) goto LAB_0044dc23;
                }
                else if ((*puVar9 & *(uint *)puVar9[-1]) == 0) goto LAB_0044dc23;
                iVar8 = iVar8 + 1;
                puVar9 = puVar9 + 3;
              } while (iVar8 < piVar12[-0x19]);
            }
            iVar6 = piVar12[-0x1b] * *(int *)piVar12[-0x1d];
            iVar8 = piVar12[-0x1a];
            if (piVar12[-0x1c] == iVar6) {
              if ((int *)(iVar8 + 0x1c) == *(int **)(iVar8 + 4)) {
                *(int *)(iVar8 + 0x1c) = iVar6;
              }
            }
            else {
              *(int *)(iVar8 + 0x1c) = iVar6;
            }
            piVar12[-0x1c] = iVar6;
          }
LAB_0044dc23:
          puVar11 = (undefined4 *)piVar12[-0x1a];
          iVar8 = puVar11[7];
          if (0x10000 < iVar8) {
            iVar8 = 0x10000;
          }
          if (iVar8 < -0x10000) {
            iVar8 = -0x10000;
          }
          *(int *)*puVar11 =
               ((iVar8 + 0x10000) * puVar11[2]) / 2 + puVar11[3] >> (*(byte *)(puVar11 + 5) & 0x1f);
        }
        iVar10 = iVar10 + 1;
        piVar12 = piVar12 + 0x20;
      } while (iVar10 < g_input_axis_binding_count);
    }
  }
  else {
    keyboard_joystick_input_binding_context_helper_0044eca0();
  }
  if ((&DAT_0053da50)[DAT_0053682c] != 0) {
    (**(code **)((&g_input_device_callback_table)[DAT_0053682c] + 0x18))(&uStack_6);
  }
  g_pending_input_action_code = uStack_6;
  return;
}


