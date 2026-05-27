/*
 * Program: i76.exe
 * Function: construct_geometry_from_geo_buffer
 * Entry: 00446c90
 * Signature: undefined4 * __cdecl construct_geometry_from_geo_buffer(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [i76 level/static/material baseline v48]
   name: construct_geometry_from_geo_buffer
   confidence: high
   module: geo_static_vehicle_mesh
   Parses/builds runtime geometry from GEO buffer. Reused by vehicle and static-object
   reconstruction. Exporter v14-v47 confirms static SDF/SGEO child partName.geo instances parse
   through this path.
   note: Name already matches baseline. */

undefined4 * __cdecl construct_geometry_from_geo_buffer(int *param_1)

{
  float fVar1;
  char cVar2;
  uint *puVar3;
  LPCVOID lpMem;
  float fVar4;
  uint *puVar5;
  undefined1 uVar6;
  bool bVar7;
  undefined4 *lpMem_00;
  SIZE_T SVar8;
  SIZE_T SVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  undefined3 extraout_var;
  undefined4 *puVar13;
  int *piVar14;
  undefined4 *puVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  int *piVar19;
  char *_Str;
  undefined8 uVar20;
  int local_2c;
  int local_28;
  float local_18;
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (*param_1 != 0x2e47454f) {
    return (undefined4 *)0x0;
  }
  iVar12 = param_1[6];
  iVar10 = param_1[7];
  iVar16 = 0;
  piVar19 = param_1 + iVar12 * 6 + 9;
  piVar14 = piVar19;
  iVar18 = iVar10;
  if (0 < iVar10) {
    do {
      iVar16 = iVar16 + piVar14[1];
      iVar18 = iVar18 + -1;
      piVar14 = (int *)((int)piVar14 + piVar14[1] * 0x10 + 0x37);
    } while (iVar18 != 0);
  }
  SVar9 = (iVar16 + iVar10 * 4) * 0x10 + (iVar12 + 1) * 0x18;
  lpMem_00 = HeapAlloc(g_geometry_heap_handle,0,SVar9);
  do {
    if (lpMem_00 != (undefined4 *)0x0) {
      SVar9 = HeapSize(g_geometry_heap_handle,0,lpMem_00);
      g_geo_runtime_heap_bytes_tracked = g_geo_runtime_heap_bytes_tracked - SVar9;
LAB_00446e4d:
      if (lpMem_00 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
      *lpMem_00 = 1;
      iVar10 = param_1[6];
      lpMem_00[1] = iVar10;
      lpMem_00[2] = param_1[6];
      lpMem_00[3] = lpMem_00 + 6;
      lpMem_00[4] = lpMem_00 + (iVar10 + 2) * 3;
      iVar18 = 0;
      lpMem_00[5] = lpMem_00 + (iVar10 + 2) * 3 + iVar10 * 3;
      if (0 < param_1[6]) {
        iVar10 = 0;
        piVar14 = param_1 + 0xb;
        do {
          iVar18 = iVar18 + 1;
          *(int *)(iVar10 + lpMem_00[3]) = piVar14[-2];
          *(int *)(iVar10 + 4 + lpMem_00[3]) = piVar14[-1];
          *(int *)(iVar10 + 8 + lpMem_00[3]) = *piVar14;
          iVar10 = iVar10 + 0xc;
          piVar14 = piVar14 + 3;
        } while (iVar18 < param_1[6]);
      }
      iVar10 = 0;
      if (0 < param_1[6]) {
        iVar18 = 0;
        piVar14 = param_1 + iVar12 * 3 + 0xb;
        do {
          iVar10 = iVar10 + 1;
          *(int *)(iVar18 + lpMem_00[4]) = piVar14[-2];
          *(int *)(iVar18 + 4 + lpMem_00[4]) = piVar14[-1];
          *(int *)(iVar18 + 8 + lpMem_00[4]) = *piVar14;
          iVar18 = iVar18 + 0xc;
          piVar14 = piVar14 + 3;
        } while (iVar10 < param_1[6]);
      }
      local_2c = 0;
      local_28 = 0;
      iVar12 = lpMem_00[5];
      if (0 < param_1[7]) {
        do {
          iVar10 = iVar12;
          *(int *)(iVar10 + 4) = piVar19[1];
          *(char *)(iVar10 + 9) = (char)piVar19[2];
          *(undefined1 *)(iVar10 + 10) = *(undefined1 *)((int)piVar19 + 9);
          *(undefined1 *)(iVar10 + 0xb) = *(undefined1 *)((int)piVar19 + 10);
          uVar6 = cache_nearest_palette_cube_index
                            ((uint)*(byte *)(piVar19 + 2),(uint)*(byte *)((int)piVar19 + 9),
                             (uint)*(byte *)((int)piVar19 + 10));
          *(undefined1 *)(iVar10 + 8) = uVar6;
          *(undefined1 *)(iVar10 + 0x1c) = *(undefined1 *)((int)piVar19 + 0x1f);
          *(char *)(iVar10 + 0x1d) = (char)piVar19[8];
          _Str = (char *)((int)piVar19 + 0x22);
          *(undefined1 *)(iVar10 + 0x1e) = *(undefined1 *)((int)piVar19 + 0x21);
          if (*_Str == '\0') {
            *(undefined1 *)(iVar10 + 0x20) = 0;
          }
          else {
            pcVar11 = strchr(_Str,0x2e);
            if (pcVar11 == (char *)0x0) {
              uVar17 = 0xffffffff;
              local_c = *(undefined4 *)((int)piVar19 + 0x26);
              do {
                if (uVar17 == 0) break;
                uVar17 = uVar17 - 1;
                cVar2 = *_Str;
                _Str = _Str + 1;
              } while (cVar2 != '\0');
              uVar17 = ~uVar17;
              local_4 = *(undefined4 *)((int)piVar19 + 0x2e);
              puVar13 = (undefined4 *)(local_14 + uVar17 + 3);
              local_10 = *(undefined4 *)((int)piVar19 + 0x22);
              local_8 = *(undefined4 *)((int)piVar19 + 0x2a);
              iVar12 = _stricmp((char *)((int)piVar19 + 0x22),&g_last_geometry_texture_basename);
              if (iVar12 == 0) {
                if (g_geo_constructor_material_lookup_active == 0) {
                  *puVar13 = DAT_004f25e8;
                  *(undefined1 *)((int)&local_10 + uVar17 + 3) = DAT_004f25ec;
                }
                else {
                  *puVar13 = DAT_004f25f0;
                  *(undefined1 *)((int)&local_10 + uVar17 + 3) = DAT_004f25f4;
                }
              }
              else {
                _g_last_geometry_texture_basename = local_10;
                _DAT_00531b2c = local_c;
                _DAT_00531b30 = local_8;
                _g_geo_constructor_material_resource_id = local_4;
                g_geo_constructor_material_lookup_active = 1;
                *puVar13 = DAT_004f25f0;
                *(undefined1 *)((int)&local_10 + uVar17 + 3) = DAT_004f25f4;
                bVar7 = resource_exists_in_cache_or_search_paths((char *)&local_10);
                if (CONCAT31(extraout_var,bVar7) == 0) {
                  *puVar13 = DAT_004f25e8;
                  *(undefined1 *)((int)&local_10 + uVar17 + 3) = DAT_004f25ec;
                  g_geo_constructor_material_lookup_active = 0;
                }
              }
              *(undefined4 *)(iVar10 + 0x20) = local_10;
              *(undefined4 *)(iVar10 + 0x24) = local_c;
              *(undefined4 *)(iVar10 + 0x28) = local_8;
              *(undefined4 *)(iVar10 + 0x2c) = local_4;
            }
            else {
              *(undefined4 *)(iVar10 + 0x20) = *(undefined4 *)_Str;
              *(undefined4 *)(iVar10 + 0x24) = *(undefined4 *)((int)piVar19 + 0x26);
              *(undefined4 *)(iVar10 + 0x28) = *(undefined4 *)((int)piVar19 + 0x2a);
              *(undefined4 *)(iVar10 + 0x2c) = *(undefined4 *)((int)piVar19 + 0x2e);
            }
          }
          if (local_2c != 0) {
            *(int *)(local_2c + 0x30) = iVar10;
          }
          fVar4 = _DAT_004bd3a4;
          iVar12 = *(int *)(iVar10 + 4);
          local_18 = _DAT_004bd3a4;
          *(undefined4 *)(iVar10 + 0x30) = 0;
          local_14 = (undefined1  [4])fVar4;
          if (iVar12 < 0x10) {
            fVar1 = *(float *)(&DAT_004f9d38 + iVar12 * 4);
          }
          else {
            fVar1 = _DAT_004bd3a8 / (float)iVar12;
          }
          local_2c = 0;
          if (0 < iVar12) {
            puVar13 = (undefined4 *)(iVar10 + 0x44);
            puVar15 = (undefined4 *)((int)piVar19 + 0x43);
            local_18 = fVar4;
            do {
              iVar12 = puVar15[-3];
              puVar13[-1] = iVar12;
              *puVar13 = *(undefined4 *)((int)piVar19 + (0x37 - (iVar10 + 0x40)) + (int)puVar13);
              puVar13[1] = puVar15[-1];
              puVar13[2] = *puVar15;
              iVar18 = lpMem_00[3];
              puVar13 = puVar13 + 4;
              fVar4 = fVar4 + *(float *)(iVar18 + iVar12 * 0xc);
              local_18 = *(float *)(iVar18 + 4 + iVar12 * 0xc) + local_18;
              local_14 = (undefined1  [4])((float)local_14 + *(float *)(iVar18 + iVar12 * 0xc + 8));
              local_2c = local_2c + 1;
              puVar15 = puVar15 + 4;
            } while (local_2c < *(int *)(iVar10 + 4));
          }
          *(float *)(iVar10 + 0x34) = fVar4 * fVar1;
          *(float *)(iVar10 + 0x38) = local_18 * fVar1;
          *(float *)(iVar10 + 0x3c) = (float)local_14 * fVar1;
          *(undefined4 *)(iVar10 + 0xc) = *(undefined4 *)((int)piVar19 + 0xb);
          *(undefined4 *)(iVar10 + 0x10) = *(undefined4 *)((int)piVar19 + 0xf);
          *(undefined4 *)(iVar10 + 0x14) = *(undefined4 *)((int)piVar19 + 0x13);
          *(undefined4 *)(iVar10 + 0x18) = *(undefined4 *)((int)piVar19 + 0x17);
          local_28 = local_28 + 1;
          piVar19 = (int *)((int)piVar19 + piVar19[1] * 0x10 + 0x37);
          iVar12 = *(int *)(iVar10 + 4) * 0x10 + iVar10 + 0x40;
          local_2c = iVar10;
        } while (local_28 < param_1[7]);
      }
      return lpMem_00;
    }
    lpMem_00 = (undefined4 *)0x0;
    if (g_geo_constructor_allocation_list_head == (uint *)0x0) {
      report_error();
      goto LAB_00446e4d;
    }
    uVar17 = (g_geo_constructor_allocation_list_head[3] * 0x6cd + 0xaab) % 0x7ed;
    puVar5 = &g_geometry_cache_by_handle + uVar17;
    for (puVar3 = (uint *)(&g_geometry_cache_by_handle)[uVar17];
        puVar3 != g_geo_constructor_allocation_list_head; puVar3 = (uint *)puVar3[4]) {
      puVar5 = puVar3 + 4;
    }
    *puVar5 = puVar3[4];
    uVar17 = *puVar3;
    uVar20 = __allshr(0x20,puVar3[1]);
    uVar17 = ((((uint)uVar20 ^ uVar17) & 0xdfdfdfdf) * 0x6cd + 0xaab) % 0x7ed;
    puVar5 = &g_geometry_cache_by_8char_name + uVar17;
    for (puVar3 = (uint *)(&g_geometry_cache_by_8char_name)[uVar17];
        puVar3 != g_geo_constructor_allocation_list_head; puVar3 = (uint *)puVar3[5]) {
      puVar5 = puVar3 + 5;
    }
    *puVar5 = puVar3[5];
    if (g_geo_constructor_allocation_list_head[6] == 0) {
      g_geometry_purge_list_tail = 0;
    }
    else {
      *(undefined4 *)(g_geo_constructor_allocation_list_head[6] + 0x1c) = 0;
    }
    g_geo_constructor_allocation_list_head = (uint *)g_geo_constructor_allocation_list_head[6];
    lpMem = (LPCVOID)puVar3[3];
    SVar8 = HeapSize(g_geometry_heap_handle,0,lpMem);
    g_geo_runtime_heap_bytes_tracked = g_geo_runtime_heap_bytes_tracked + SVar8;
    HeapFree(g_geometry_heap_handle,0,lpMem);
    HeapFree(g_geometry_cache_entry_heap,0,puVar3);
    lpMem_00 = HeapAlloc(g_geometry_heap_handle,0,SVar9);
  } while( true );
}


