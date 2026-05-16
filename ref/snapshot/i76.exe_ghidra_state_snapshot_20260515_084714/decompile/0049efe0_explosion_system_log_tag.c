/*
 * Program: i76.exe
 * Function: explosion_system_log_tag
 * Entry: 0049efe0
 * Signature: undefined __stdcall explosion_system_log_tag(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence explsn */

void explosion_system_log_tag(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  undefined8 uVar8;
  uint local_8;
  uint local_4;
  
  if ((DAT_005a80fc != 0) && (uVar7 = *(uint *)(DAT_005a80fc + 100), uVar7 != 0)) {
    if (uVar7 == 0) goto LAB_0049f0d5;
    do {
      release_world_object_light_runtime(uVar7);
      radar_context_setup_helper_0045f310(uVar7);
      puVar1 = *(uint **)(uVar7 + 0x70);
      if (puVar1 != (uint *)0x0) {
        local_8 = *puVar1;
        local_4 = puVar1[1];
        uVar5 = 0;
        do {
          iVar4 = toupper((int)*(char *)((int)&local_8 + uVar5));
          *(char *)((int)&local_8 + uVar5) = (char)iVar4;
          uVar3 = local_4;
          uVar2 = local_8;
          uVar5 = uVar5 + 1;
        } while (uVar5 < 8);
        uVar8 = __allshr(0x20,local_4);
        for (puVar6 = (uint *)(&g_explosion_runtime_state)
                              [(((uint)uVar8 ^ uVar2) * 0x6cd + 0xaab) % 0x71];
            puVar6 != (uint *)0x0; puVar6 = (uint *)puVar6[8]) {
          if ((*puVar6 == uVar2) && (puVar6[1] == uVar3)) goto LAB_0049f0a1;
        }
        puVar6 = (uint *)0x0;
LAB_0049f0a1:
        if (puVar6 != (uint *)0x0) {
          if ((LPVOID)puVar1[4] != (LPVOID)0x0) {
            finalize_released_world_object_after_damage((LPVOID)puVar1[4],s_explsn_004fe6e0);
            puVar1[4] = 0;
          }
          if (puVar6[7] != 0) {
            *(uint *)(puVar6[7] + 0x68) = uVar7;
          }
          uVar5 = puVar6[7];
          *(undefined4 *)(uVar7 + 0x68) = 0;
          *(uint *)(uVar7 + 0x60) = uVar5;
          puVar6[7] = uVar7;
        }
      }
LAB_0049f0d5:
      uVar7 = *(uint *)(DAT_005a80fc + 100);
    } while (uVar7 != 0);
  }
  DAT_005a80fc = 0;
  return;
}


