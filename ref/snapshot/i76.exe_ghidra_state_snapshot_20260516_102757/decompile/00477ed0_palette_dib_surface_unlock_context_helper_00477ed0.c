/*
 * Program: i76.exe
 * Function: palette_dib_surface_unlock_context_helper_00477ed0
 * Entry: 00477ed0
 * Signature: undefined __cdecl palette_dib_surface_unlock_context_helper_00477ed0(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set D v16: Readability pass set D: palette dib surface unlock context
   helper based on adjacent named subsystem context. */

void __cdecl palette_dib_surface_unlock_context_helper_00477ed0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  undefined4 *puVar8;
  int iVar9;
  float *pfVar10;
  float *pfVar11;
  undefined4 *puVar12;
  float10 extraout_ST0;
  undefined4 *local_104;
  int local_100;
  int local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  undefined4 local_c4 [4];
  undefined4 local_b4;
  undefined4 uStack_b0;
  float local_ac [3];
  undefined4 local_a0 [6];
  float local_88 [16];
  float local_48 [17];
  
  if (*(int *)(&DAT_004fa0b0 + DAT_0058db00 * 0x14) != 1) {
    local_104 = &DAT_0058db24;
    local_100 = 0;
    local_f0 = 0;
    pfVar10 = (float *)&DAT_0058db9c;
    do {
      if (g_runtime_light_entry_count <= local_f0) break;
      if (((uint)pfVar10[-5] & 8) != 0) {
        local_d4 = pfVar10[-6];
        pfVar7 = (float *)compute_transform_relative_to_ancestor(local_48,(int)local_d4,0);
        pfVar11 = local_88;
        for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
          *pfVar11 = *pfVar7;
          pfVar7 = pfVar7 + 1;
          pfVar11 = pfVar11 + 1;
        }
        puVar8 = (undefined4 *)
                 zone_satellite_map_context_helper_00494be0(pfVar10 + 2,local_88,local_a0);
        puVar12 = local_c4;
        for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar12 = *puVar8;
          puVar8 = puVar8 + 1;
          puVar12 = puVar12 + 1;
        }
        pfVar7 = (float *)raster_scratch_arena_context_helper_00472d30
                                    (local_ac,param_1,(double)CONCAT44(local_c4[1],local_c4[0]),
                                     (double)CONCAT44(local_c4[3],local_c4[2]),
                                     (double)CONCAT44(uStack_b0,local_b4));
        local_ec = *pfVar7;
        local_e8 = pfVar7[1];
        local_e4 = pfVar7[2];
        iVar9 = software_raster_queue_context_helper_00472c10
                          (param_1,&local_ec,pfVar10[-2] * _DAT_004be63c);
        if (iVar9 < 1) {
          fVar4 = (float)(double)CONCAT44(local_c4[1],local_c4[0]);
          fVar5 = (float)(double)CONCAT44(local_c4[3],local_c4[2]);
          fVar6 = (float)(double)CONCAT44(uStack_b0,local_b4);
          *local_104 = pfVar10 + -6;
          pfVar10[0xf] = fVar4;
          pfVar10[0x10] = fVar5;
          pfVar10[0x11] = fVar6;
          pfVar10[0xc] = local_ec;
          pfVar7 = pfVar10 + 6;
          pfVar10[0xd] = local_e8;
          local_100 = local_100 + 1;
          pfVar10[0xe] = local_e4;
          fVar1 = *(float *)((int)local_d4 + 0x20);
          fVar2 = *(float *)((int)local_d4 + 0x38);
          local_104 = local_104 + 1;
          local_e0 = *(float *)((int)local_d4 + 0x24) * *pfVar10 +
                     *(float *)((int)local_d4 + 0x30) * pfVar10[1] +
                     *(float *)((int)local_d4 + 0x18) * pfVar10[-1];
          local_dc = *(float *)((int)local_d4 + 0x28) * *pfVar10 +
                     *(float *)((int)local_d4 + 0x34) * pfVar10[1] +
                     *(float *)((int)local_d4 + 0x1c) * pfVar10[-1];
          fVar3 = *(float *)((int)local_d4 + 0x2c);
          *pfVar7 = local_e0;
          pfVar10[7] = local_dc;
          local_d8 = fVar3 * *pfVar10 + fVar2 * pfVar10[1] + fVar1 * pfVar10[-1];
          pfVar10[8] = local_d8;
          local_d0 = *(float *)(param_1 + 0x58) * pfVar10[8] +
                     *(float *)(param_1 + 0x4c) * pfVar10[7] + *(float *)(param_1 + 0x40) * *pfVar7;
          local_cc = *(float *)(param_1 + 0x50) * pfVar10[7] +
                     *(float *)(param_1 + 0x5c) * pfVar10[8] + *(float *)(param_1 + 0x44) * *pfVar7;
          fVar1 = *(float *)(param_1 + 0x48);
          fVar2 = *(float *)(param_1 + 0x54);
          fVar3 = *(float *)(param_1 + 0x60);
          pfVar10[9] = local_d0;
          local_c8 = fVar3 * pfVar10[8] + fVar2 * pfVar10[7] + fVar1 * *pfVar7;
          pfVar10[10] = local_cc;
          pfVar10[0xb] = local_c8;
          pfVar10[0x12] = fVar4;
          pfVar10[0x13] = fVar5;
          pfVar10[0x14] = fVar6;
          pfVar10[5] = 0.0;
          apply_world_object_transform_to_bounds_or_geometry((double)fVar4,(double)fVar6);
          if ((float10)fVar5 - extraout_ST0 < (float10)_DAT_004be640) {
            pfVar10[0x13] = pfVar10[0x13] - _DAT_004be644;
            pfVar10[5] = pfVar10[5] - _DAT_004be640;
          }
        }
      }
      local_f0 = local_f0 + 1;
      pfVar10 = pfVar10 + 0x1b;
    } while ((int)local_104 < 0x58db84);
    DAT_0058db08 = local_100;
  }
  return;
}


