/*
 * Program: i76.exe
 * Function: display_bitmap_surface_context_helper_00474380
 * Entry: 00474380
 * Signature: undefined __thiscall display_bitmap_surface_context_helper_00474380(void * this, undefined4 param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: display bitmap surface context helper
   based on adjacent named subsystem context. */

void __thiscall display_bitmap_surface_context_helper_00474380(void *this,undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  uint **ppuVar5;
  uint *puVar6;
  undefined2 in_FPUControlWord;
  undefined4 local_60;
  undefined4 *local_5c;
  undefined4 local_58;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  uint *local_20;
  int *local_1c;
  int *local_18;
  uint *local_14;
  undefined4 local_10;
  float local_c;
  uint *local_8;
  
  local_10 = CONCAT22(local_10._2_2_,in_FPUControlWord);
  local_5c = &local_40;
  local_38 = &local_60;
  local_60 = 0;
  local_40 = 0xffffffff;
  local_58 = 0;
  local_3c = 0;
  local_8 = (uint *)0x0;
  if (0 < *(int *)((int)this + 0x38)) {
    do {
      puVar6 = local_8;
      local_c = (float)(int)local_8;
      puVar3 = *(uint **)(*(int *)((int)this + 4) + (int)local_8 * 4);
      *(undefined4 *)(*(int *)((int)this + 4) + (int)local_8 * 4) = 0;
      local_20 = *(uint **)(*(int *)((int)this + 8) + (int)local_8 * 4);
      iVar2 = (int)local_8 * 4;
      local_8 = (uint *)0x0;
      *(undefined4 *)(*(int *)((int)this + 8) + iVar2) = 0;
      local_1c = *(int **)(*(int *)((int)this + 0xc) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0xc) + (int)puVar6 * 4) = 0;
      local_18 = *(int **)(*(int *)((int)this + 0x10) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x10) + (int)puVar6 * 4) = 0;
      puVar4 = local_8;
      while (local_8 = puVar4, puVar3 != (uint *)0x0) {
        local_14 = (uint *)puVar3[1];
        ppuVar5 = &local_8;
        for (; (puVar4 != (uint *)0x0 && (*puVar4 < *puVar3)); puVar4 = (uint *)puVar4[1]) {
          ppuVar5 = (uint **)(puVar4 + 1);
        }
        puVar3[1] = (uint)*ppuVar5;
        *ppuVar5 = puVar3;
        puVar3 = local_14;
        puVar4 = local_8;
      }
      raster_span_builder_context_helper_00473400(puVar4,local_20,local_1c,local_18);
      raster_span_builder_context_helper_00473490((int)&local_60);
      raster_edge_step_context_helper_004732e0(&local_60,puVar4);
      raster_edge_record_context_helper_00472fd0(&local_60,(uint)puVar6);
      iVar2 = *(int *)(*(int *)((int)this + 0x24) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x24) + (int)puVar6 * 4) = 0;
      raster_edge_step_context_helper_00473260(iVar2);
      local_8 = (uint *)((int)puVar6 + 1);
    } while ((int)local_8 < *(int *)((int)this + 0x38));
  }
  local_8 = (uint *)0x0;
  if (0 < *(int *)((int)this + 0x38)) {
    do {
      puVar6 = local_8;
      local_c = (float)(int)local_8;
      puVar3 = (uint *)(*(int *)((int)this + 0x14) + (int)local_8 * 4);
      local_8 = (uint *)0x0;
      puVar4 = (uint *)*puVar3;
      *puVar3 = 0;
      local_14 = *(uint **)(*(int *)((int)this + 0x18) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x18) + (int)puVar6 * 4) = 0;
      local_18 = *(int **)(*(int *)((int)this + 0x1c) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x1c) + (int)puVar6 * 4) = 0;
      local_1c = *(int **)(*(int *)((int)this + 0x20) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x20) + (int)puVar6 * 4) = 0;
      puVar3 = local_8;
      while (local_8 = puVar3, puVar4 != (uint *)0x0) {
        local_20 = (uint *)puVar4[1];
        ppuVar5 = &local_8;
        for (; (puVar3 != (uint *)0x0 && (*puVar3 < *puVar4)); puVar3 = (uint *)puVar3[1]) {
          ppuVar5 = (uint **)(puVar3 + 1);
        }
        puVar4[1] = (uint)*ppuVar5;
        *ppuVar5 = puVar4;
        puVar4 = local_20;
        puVar3 = local_8;
      }
      raster_span_builder_context_helper_00473400(puVar3,local_14,local_18,local_1c);
      raster_span_builder_context_helper_00473490((int)&local_60);
      raster_edge_step_context_helper_004732e0(&local_60,puVar3);
      raster_edge_record_context_helper_00472fd0(&local_60,(uint)puVar6);
      iVar2 = *(int *)(*(int *)((int)this + 0x28) + (int)puVar6 * 4);
      *(undefined4 *)(*(int *)((int)this + 0x28) + (int)puVar6 * 4) = 0;
      raster_edge_step_context_helper_00473260(iVar2);
      local_8 = (uint *)((int)puVar6 + 1);
    } while ((int)local_8 < *(int *)((int)this + 0x38));
  }
  piVar1 = (int *)((int)this + 0x2c);
  **(undefined4 **)((int)this + 0x30) = 0;
  for (iVar2 = *piVar1; iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
    if (*(int *)(iVar2 + 0x28) != -1) {
      (**(code **)(iVar2 + 8))(iVar2,param_1);
    }
  }
  DAT_004f9d80 = 0xffffffff;
  DAT_004f9d7c = 0xffffffff;
  DAT_0058dabc = DAT_0058dab8;
  *(int **)((int)this + 0x30) = piVar1;
  *(undefined4 *)((int)this + 0x38) = 0;
  *(undefined4 *)this = 0;
  *piVar1 = 0;
  DAT_0058dac0 = 0;
  return;
}


