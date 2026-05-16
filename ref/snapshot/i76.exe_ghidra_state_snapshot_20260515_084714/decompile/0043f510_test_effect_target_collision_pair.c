/*
 * Program: i76.exe
 * Function: test_effect_target_collision_pair
 * Entry: 0043f510
 * Signature: undefined4 __cdecl test_effect_target_collision_pair(int * param_1, int * param_2, int * param_3, int * param_4)
 */


/* cgpt rename v9 vehicle effect/collision/particle cluster: Tests two effect-target/collision
   records for possible collision using transformed bounds and swept payload tests. */

undefined4 __cdecl
test_effect_target_collision_pair(int *param_1,int *param_2,int *param_3,int *param_4)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 *puVar8;
  int local_108 [12];
  int local_d8;
  int local_d4;
  int local_d0 [6];
  undefined4 local_b8 [16];
  undefined4 local_78 [6];
  int local_60;
  int local_5c;
  int local_58 [6];
  undefined4 local_40 [16];
  
  iVar5 = param_2[5];
  if (iVar5 == 1) {
    puVar3 = (undefined4 *)effect_target_list_scan_context_helper_004387b0(local_108,param_1);
    iVar5 = param_1[4];
    puVar8 = local_78;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar8 = puVar8 + 1;
    }
    local_60 = iVar5;
    local_5c = *param_1;
    piVar4 = (int *)param_1[6];
    if (piVar4 == (int *)0x0) {
      local_108[3] = 0;
      local_108[4] = 0;
      local_108[5] = 0;
      local_108[0] = 0;
      local_108[1] = 0;
      local_108[2] = 0;
    }
    else {
      local_108[0] = piVar4[3];
      local_108[1] = piVar4[8];
      local_108[2] = piVar4[0xb];
      local_108[3] = piVar4[*piVar4 + 2];
      local_108[4] = piVar4[piVar4[1] + 6];
      local_108[5] = piVar4[piVar4[2] + 10];
    }
    piVar4 = local_108;
    piVar1 = local_58;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar1 = piVar1 + 1;
    }
    puVar3 = (undefined4 *)(local_5c + 0x18);
    puVar8 = local_40;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar8 = puVar8 + 1;
    }
    piVar4 = (int *)effect_target_list_scan_context_helper_004387b0(local_108,param_2);
    iVar5 = param_2[4];
    piVar1 = local_108 + 6;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar1 = piVar1 + 1;
    }
    local_d8 = iVar5;
    local_d4 = *param_2;
    piVar4 = (int *)param_2[6];
    if (piVar4 == (int *)0x0) {
      local_108[3] = 0;
      local_108[4] = 0;
      local_108[5] = 0;
      local_108[0] = 0;
      local_108[1] = 0;
      local_108[2] = 0;
    }
    else {
      local_108[0] = piVar4[3];
      local_108[1] = piVar4[8];
      local_108[2] = piVar4[0xb];
      local_108[3] = piVar4[*piVar4 + 2];
      local_108[4] = piVar4[piVar4[1] + 6];
      local_108[5] = piVar4[piVar4[2] + 10];
    }
    piVar4 = local_108;
    piVar1 = local_d0;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar1 = piVar1 + 1;
    }
    puVar3 = (undefined4 *)(local_d4 + 0x18);
    puVar8 = local_b8;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar8 = puVar8 + 1;
    }
    iVar5 = test_collision_between_effect_target_bounds
                      ((int)local_78,(int)(local_108 + 6),param_3,param_4);
    if (iVar5 == 0) {
      iVar5 = test_collision_between_effect_target_bounds
                        ((int)(local_108 + 6),(int)local_78,param_4,param_3);
      if (iVar5 == 0) {
        return 0;
      }
    }
  }
  else if (iVar5 != 2) {
    if (iVar5 != 3) {
      return 0;
    }
    piVar1 = (int *)effect_target_list_scan_context_helper_004387b0(local_108,param_1);
    local_d4 = *param_1;
    piVar4 = (int *)param_1[6];
    piVar7 = local_108 + 6;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar7 = *piVar1;
      piVar1 = piVar1 + 1;
      piVar7 = piVar7 + 1;
    }
    local_d8 = param_1[4];
    if (piVar4 == (int *)0x0) {
      local_108[3] = 0;
      local_108[4] = 0;
      local_108[5] = 0;
      local_108[0] = 0;
      local_108[1] = 0;
      local_108[2] = 0;
    }
    else {
      local_108[0] = piVar4[3];
      local_108[1] = piVar4[8];
      local_108[2] = piVar4[0xb];
      local_108[3] = piVar4[*piVar4 + 2];
      local_108[4] = piVar4[piVar4[1] + 6];
      local_108[5] = piVar4[piVar4[2] + 10];
    }
    iVar5 = *param_2;
    piVar4 = local_108;
    piVar1 = local_d0;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar1 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar1 = piVar1 + 1;
    }
    puVar3 = (undefined4 *)(local_d4 + 0x18);
    puVar8 = local_b8;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar8 = puVar8 + 1;
    }
    uVar2 = test_effect_target_swept_collision_against_object
                      (local_108 + 6,iVar5,(float *)&DAT_004faed8,param_3,param_4);
    return uVar2;
  }
  return 1;
}


