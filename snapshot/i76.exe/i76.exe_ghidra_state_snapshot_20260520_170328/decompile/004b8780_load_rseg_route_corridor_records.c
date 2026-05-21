/*
 * Program: i76.exe
 * Function: load_rseg_route_corridor_records
 * Entry: 004b8780
 * Signature: undefined4 __cdecl load_rseg_route_corridor_records(int param_1)
 */


/* cgpt readability rename set E v17: Readability pass set E: mission scrounge record context helper
   based on adjacent named subsystem context.
   [cgpt-i76-v36 high] RSEG loader; serialized kind,count,count*0x18 records and runtime node
   chunking.
   
   I76 rename v43: load_rdef_rseg_route_corridor_records
   RSEG route/corridor loader; chunks serialized 0x18 records into runtime nodes. */

undefined4 __cdecl load_rseg_route_corridor_records(int param_1)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int local_1c;
  int local_18;
  
  piVar2 = (int *)0x0;
  uVar3 = *(int *)(param_1 + 0xc) - 1;
  for (uVar6 = uVar3; 0x18 < (int)uVar6; uVar6 = (uVar6 & 1) + ((int)uVar6 >> 1)) {
  }
  iVar4 = uVar3 - uVar6;
  iVar8 = 0;
  local_1c = 0;
  uVar3 = (uVar6 + 1) * 0x18;
  if (4 < iVar4) {
    piVar9 = (int *)(param_1 + 0x10);
    local_18 = iVar4;
    do {
      piVar2 = (int *)xalloc_global_heap(uVar3 + 0x2c);
      if (piVar2 == (int *)0x0) {
        return 0;
      }
      piVar2[1] = 0;
      piVar2[2] = 0;
      *piVar2 = g_runtime_rseg_node_count;
      piVar2[3] = 0;
      iVar8 = *(int *)(param_1 + 8);
      piVar2[5] = uVar6 + 1;
      piVar2[4] = iVar8;
      piVar2[10] = (int)(piVar2 + 0xb);
      piVar10 = piVar9;
      piVar11 = piVar2 + 0xb;
      for (uVar5 = uVar3 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *piVar11 = *piVar10;
        piVar10 = piVar10 + 1;
        piVar11 = piVar11 + 1;
      }
      for (iVar8 = 0; iVar8 != 0; iVar8 = iVar8 + -1) {
        *(char *)piVar11 = (char)*piVar10;
        piVar10 = (int *)((int)piVar10 + 1);
        piVar11 = (int *)((int)piVar11 + 1);
      }
      piVar10 = piVar2;
      if (g_runtime_rseg_node_list_head != (int *)0x0) {
        piVar11 = (int *)g_runtime_rseg_node_list_head[1];
        piVar10 = g_runtime_rseg_node_list_head;
        while (piVar1 = piVar11, piVar1 != (int *)0x0) {
          piVar10 = piVar1;
          piVar11 = (int *)piVar1[1];
        }
        piVar10[1] = (int)piVar2;
        piVar2[2] = (int)piVar10;
        piVar10 = g_runtime_rseg_node_list_head;
      }
      g_runtime_rseg_node_list_head = piVar10;
      iVar8 = local_1c + uVar6;
      local_18 = local_18 - uVar6;
      piVar9 = piVar9 + uVar6 * 6;
      local_1c = iVar8;
    } while (4 < local_18);
  }
  iVar7 = uVar6 + (iVar4 - iVar8);
  iVar4 = iVar7 + 1;
  uVar6 = iVar4 * 0x18;
  piVar9 = g_runtime_rseg_node_list_head;
  if (1 < iVar7) {
    piVar2 = (int *)xalloc_global_heap(uVar6 + 0x2c);
    if (piVar2 == (int *)0x0) {
      return 0;
    }
    piVar2[1] = 0;
    piVar2[2] = 0;
    *piVar2 = g_runtime_rseg_node_count;
    piVar2[3] = 0;
    piVar2[4] = *(int *)(param_1 + 8);
    piVar2[5] = iVar4;
    piVar2[10] = (int)(piVar2 + 0xb);
    piVar9 = (int *)(param_1 + 0x10 + iVar8 * 0x18);
    piVar10 = piVar2 + 0xb;
    for (uVar6 = uVar6 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
      *piVar10 = *piVar9;
      piVar9 = piVar9 + 1;
      piVar10 = piVar10 + 1;
    }
    for (iVar4 = 0; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(char *)piVar10 = (char)*piVar9;
      piVar9 = (int *)((int)piVar9 + 1);
      piVar10 = (int *)((int)piVar10 + 1);
    }
    piVar9 = piVar2;
    if (g_runtime_rseg_node_list_head != (int *)0x0) {
      piVar10 = (int *)g_runtime_rseg_node_list_head[1];
      piVar9 = g_runtime_rseg_node_list_head;
      while (piVar11 = piVar10, piVar11 != (int *)0x0) {
        piVar9 = piVar11;
        piVar10 = (int *)piVar11[1];
      }
      piVar9[1] = (int)piVar2;
      piVar2[2] = (int)piVar9;
      piVar9 = g_runtime_rseg_node_list_head;
    }
  }
  g_runtime_rseg_node_list_head = piVar9;
  if (piVar2 != (int *)0x0) {
    piVar2[3] = 1;
  }
  g_runtime_rseg_node_count = g_runtime_rseg_node_count + 1;
  return 1;
}


