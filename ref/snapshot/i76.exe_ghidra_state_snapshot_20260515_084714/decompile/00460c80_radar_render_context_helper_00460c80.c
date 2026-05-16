/*
 * Program: i76.exe
 * Function: radar_render_context_helper_00460c80
 * Entry: 00460c80
 * Signature: undefined __cdecl radar_render_context_helper_00460c80(uint * param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt label refinement v19: was radar_classifier_specials_radar_render_helper_00460c80. Shorten
   readability label. */

void __cdecl radar_render_context_helper_00460c80(uint *param_1,uint param_2)

{
  float fVar1;
  uint *puVar2;
  uint *puVar3;
  float10 fVar4;
  undefined8 uVar5;
  undefined8 local_18;
  float local_c;
  float local_8;
  uint local_4;
  
  puVar2 = param_1;
  if (param_1 != (uint *)0x0) {
    puVar3 = (uint *)world_object_geometry_context_helper_00458930
                               ((undefined4 *)&local_18,param_2,*param_1);
    local_c = (float)*puVar3;
    local_8 = (float)puVar3[1];
    local_4 = puVar3[2];
    param_1[1] = (uint)local_c;
    param_1[2] = local_4;
    fVar4 = (float10)world_object_geometry_context_helper_00458970(param_2);
    param_1 = (uint *)(float)fVar4;
    if (fVar4 < (float10)_DAT_004be128) {
      param_1 = (uint *)((float)param_1 - _DAT_004be12c);
    }
    local_c = (float)puVar2[1];
    local_8 = (float)puVar2[2];
    uVar5 = mission_flow_map_context_helper_0049d400((float)param_1);
    local_18._4_4_ = (float)((ulonglong)uVar5 >> 0x20);
    local_18._0_4_ = (float)uVar5;
    fVar1 = (float)local_18 * local_8;
    local_8 = (float)local_18 * local_c + local_18._4_4_ * local_8;
    puVar2[3] = (uint)(local_18._4_4_ * local_c - fVar1);
    puVar2[4] = (uint)local_8;
    local_18 = uVar5;
    fVar4 = (float10)world_object_geometry_context_helper_004589f0(param_2,*puVar2);
    puVar2[5] = (uint)(float)fVar4;
    fVar4 = get_multiplayer_or_runtime_seconds();
    if ((float)puVar2[6] <= (float)fVar4) {
      fVar1 = (float)puVar2[6];
      while (fVar1 < (float)fVar4) {
        fVar1 = (float)puVar2[6] - _DAT_004be130;
        puVar2[6] = (uint)fVar1;
        if ((byte)puVar2[7] < 0x69) {
          *(byte *)(puVar2 + 7) = (byte)puVar2[7] + 3;
        }
      }
    }
  }
  return;
}


