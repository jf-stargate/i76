/*
 * Program: i76.exe
 * Function: world_object_texture_binding_state_helper_0046e5a0
 * Entry: 0046e5a0
 * Signature: undefined __cdecl world_object_texture_binding_state_helper_0046e5a0(uint param_1, byte * param_2, undefined4 * param_3)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: world object texture binding state
   helper based on adjacent named subsystem context. */

void __cdecl
world_object_texture_binding_state_helper_0046e5a0(uint param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  float10 fVar10;
  
  if ((param_3 != (undefined4 *)0x0) && (*(int *)(*(int *)(param_1 + 0x70) + 4) != 0)) {
    if ((*(int *)(param_1 + 0x5c) != 0) &&
       ((iVar5 = *(int *)(*(int *)(param_1 + 0x5c) + 0x14), iVar5 != 0 &&
        (iVar5 = _stricmp((char *)(iVar5 + 0x20),(char *)param_2), iVar5 != 0)))) {
      uVar6 = 0xffffffff;
      pbVar8 = param_2;
      do {
        pbVar9 = pbVar8;
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        pbVar9 = pbVar8 + 1;
        bVar1 = *pbVar8;
        pbVar8 = pbVar9;
      } while (bVar1 != 0);
      uVar6 = ~uVar6;
      pbVar8 = pbVar9 + -uVar6;
      pbVar9 = (byte *)(*(int *)(*(int *)(param_1 + 0x5c) + 0x14) + 0x20);
      for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pbVar9 = *(undefined4 *)pbVar8;
        pbVar8 = pbVar8 + 4;
        pbVar9 = pbVar9 + 4;
      }
      for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
        *pbVar9 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        pbVar9 = pbVar9 + 1;
      }
    }
    fVar10 = get_network_or_session_runtime_seconds();
    if ((float)param_3[5] < (float)fVar10) {
      iVar5 = param_3[1];
      iVar2 = param_3[2];
      do {
        fVar4 = (float)param_3[5] - _DAT_004be4d8;
        param_3[5] = fVar4;
        if ((iVar2 < iVar5) && (0 < (int)param_3[1])) {
          param_3[1] = param_3[1] + -1;
        }
        if ((iVar5 < iVar2) && ((int)param_3[1] < 6)) {
          param_3[1] = param_3[1] + 1;
        }
      } while (fVar4 <= (float)fVar10);
      iVar3 = param_3[3];
      if ((iVar3 == 0) && (5 < (int)param_3[1])) {
        param_3[1] = 5;
      }
      if ((iVar3 == 1) && (iVar2 <= iVar5)) {
        param_3[1] = 5;
        param_3[4] = 0;
        param_3[3] = 0;
        param_3[2] = 5;
        *param_3 = 0;
        set_texture_binding_frame_and_reload(param_1,param_2,1,0,0);
        set_texture_binding_frame_and_reload(param_1,param_2,0,5,1);
        return;
      }
      set_texture_binding_frame_and_reload(param_1,param_2,1,iVar3,0);
      set_texture_binding_frame_and_reload(param_1,param_2,0,param_3[1],1);
    }
  }
  return;
}


