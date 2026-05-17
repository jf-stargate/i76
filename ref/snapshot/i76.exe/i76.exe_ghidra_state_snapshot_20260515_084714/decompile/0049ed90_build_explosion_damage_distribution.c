/*
 * Program: i76.exe
 * Function: build_explosion_damage_distribution
 * Entry: 0049ed90
 * Signature: undefined __cdecl build_explosion_damage_distribution(undefined4 * param_1, int param_2)
 */


/* [cgpt i76.exe damage runtime deeptrace v20; confidence=medium-high] Builds damage/distribution
   context for explosion radial damage. */

void __cdecl build_explosion_damage_distribution(undefined4 *param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  uint local_20;
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10 [4];
  
  puVar7 = &local_18;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar7 = 0;
    puVar7 = puVar7 + 1;
  }
  if ((param_2 == 0) || (puVar1 = *(uint **)(param_2 + 0x70), puVar1 == (uint *)0x0)) {
    local_14 = local_14 & 0xffff0000;
    local_10[0] = 0;
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
  }
  else {
    local_20 = *puVar1;
    local_1c = puVar1[1];
    uVar6 = 0;
    do {
      iVar5 = toupper((int)*(char *)((int)&local_20 + uVar6));
      *(char *)((int)&local_20 + uVar6) = (char)iVar5;
      uVar3 = local_1c;
      uVar2 = local_20;
      uVar6 = uVar6 + 1;
    } while (uVar6 < 8);
    uVar8 = __allshr(0x20,local_1c);
    for (puVar1 = (uint *)(&g_explosion_runtime_state)
                          [(((uint)uVar8 ^ uVar2) * 0x6cd + 0xaab) % 0x71];
        (puVar1 != (uint *)0x0 && ((*puVar1 != uVar2 || (puVar1[1] != uVar3))));
        puVar1 = (uint *)puVar1[8]) {
    }
    local_14 = CONCAT22(local_14._2_2_,2);
    iVar5 = 0;
    do {
      iVar5 = iVar5 + 1;
    } while (iVar5 < 4);
    iVar5 = 0;
    puVar7 = local_10;
    do {
      *puVar7 = 0;
      if ((local_14 & 0xffff & 1 << ((byte)iVar5 & 0x1f)) != 0) {
        uVar4 = ftol();
        *puVar7 = uVar4;
      }
      iVar5 = iVar5 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar5 < 4);
  }
  puVar7 = &local_18;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *param_1 = *puVar7;
    puVar7 = puVar7 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


