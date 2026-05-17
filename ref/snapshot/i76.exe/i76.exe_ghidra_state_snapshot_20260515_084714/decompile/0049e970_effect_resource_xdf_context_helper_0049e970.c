/*
 * Program: i76.exe
 * Function: effect_resource_xdf_context_helper_0049e970
 * Entry: 0049e970
 * Signature: undefined4 __cdecl effect_resource_xdf_context_helper_0049e970(uint param_1, uint param_2, uint param_3, uint param_4, uint param_5, uint param_6, uint param_7)
 */


/* cgpt label refinement v20: was effect_xdf_resource_context_helper_0049e970. Clarify effect XDF
   resource context. */

undefined4 __cdecl
effect_resource_xdf_context_helper_0049e970
          (uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6,
          uint param_7)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  undefined8 uVar6;
  uint local_8;
  uint local_4;
  
  if (param_3 != 0) {
    local_8 = param_1;
    local_4 = param_2;
    uVar5 = 0;
    do {
      iVar3 = toupper((int)*(char *)((int)&local_8 + uVar5));
      *(char *)((int)&local_8 + uVar5) = (char)iVar3;
      uVar2 = local_4;
      uVar1 = local_8;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 8);
    uVar6 = __allshr(0x20,local_4);
    for (puVar4 = (uint *)(&g_explosion_runtime_state)
                          [(((uint)uVar6 ^ uVar1) * 0x6cd + 0xaab) % 0x71]; puVar4 != (uint *)0x0;
        puVar4 = (uint *)puVar4[8]) {
      if ((*puVar4 == uVar1) && (puVar4[1] == uVar2)) goto LAB_0049ea04;
    }
    puVar4 = (uint *)0x0;
LAB_0049ea04:
    if (puVar4 != (uint *)0x0) {
      return 0;
    }
    local_8 = param_1;
    local_4 = param_2;
    puVar4 = HeapAlloc(DAT_005a80f8,0,0x28);
    uVar5 = 0;
    do {
      iVar3 = toupper((int)*(char *)((int)&local_8 + uVar5));
      *(char *)((int)&local_8 + uVar5) = (char)iVar3;
      uVar1 = local_8;
      uVar5 = uVar5 + 1;
    } while (uVar5 < 8);
    if (puVar4 != (uint *)0x0) {
      *puVar4 = local_8;
      puVar4[1] = local_4;
      uVar6 = __allshr(0x20,local_4);
      uVar5 = (((uint)uVar6 ^ uVar1) * 0x6cd + 0xaab) % 0x71;
      puVar4[8] = (&g_explosion_runtime_state)[uVar5];
      (&g_explosion_runtime_state)[uVar5] = puVar4;
    }
    puVar4[2] = param_3;
    puVar4[3] = param_4;
    puVar4[4] = param_5;
    puVar4[5] = param_6;
    puVar4[6] = param_7;
    puVar4[7] = 0;
  }
  return 1;
}


