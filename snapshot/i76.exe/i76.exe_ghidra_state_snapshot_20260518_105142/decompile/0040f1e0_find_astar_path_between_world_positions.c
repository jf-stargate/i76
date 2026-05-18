/*
 * Program: i76.exe
 * Function: find_astar_path_between_world_positions
 * Entry: 0040f1e0
 * Signature: undefined4 __cdecl find_astar_path_between_world_positions(int * param_1, int * param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v11 astar/ai/fsm-loader cluster: Main A* path search between world positions using
   terrain costs, open/closed nodes, neighbor allocation, and path emission. */

undefined4 __cdecl find_astar_path_between_world_positions(int *param_1,int *param_2)

{
  int *piVar1;
  float *pfVar2;
  float fVar3;
  double dVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  float fVar9;
  float fVar10;
  bool bVar11;
  ushort uVar12;
  int iVar13;
  int iVar14;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  uint uVar15;
  undefined4 *puVar16;
  int unaff_EBX;
  int unaff_ESI;
  int unaff_EDI;
  float10 fVar17;
  div_t dVar18;
  int iVar19;
  int iVar20;
  float in_stack_ffffffb4;
  int *piVar21;
  float fVar22;
  float fVar23;
  int *piVar24;
  float local_30;
  int local_28;
  int local_1c;
  
  piVar21 = (int *)0x0;
  piVar24 = (int *)0x0;
  bVar11 = false;
  pfVar2 = (float *)(*(int *)(param_1[0x22] + 0x54) + param_1[0x28] * 0xc);
  fVar22 = *pfVar2;
  fVar23 = pfVar2[2];
  piVar1 = param_1 + 0x273d;
  if (*piVar1 == 0) {
    iVar19 = 10;
    iVar13 = ftol();
    dVar18 = div(iVar13,iVar19);
    iVar13 = dVar18.quot * 10;
    if (_DAT_004bc6e0 < (double)dVar18.rem) {
      iVar13 = iVar13 + 10;
    }
    iVar20 = 10;
    iVar19 = ftol();
    dVar18 = div(iVar19,iVar20);
    iVar19 = dVar18.quot * 10;
    if (_DAT_004bc6e0 < (double)dVar18.rem) {
      iVar19 = iVar19 + 10;
    }
    iVar20 = iVar19;
    iVar14 = try_build_direct_astar_segment_between_positions
                       ((int *)(float)iVar13,(float)iVar19,fVar22,fVar23,param_1,unaff_EDI,unaff_ESI
                        ,unaff_EBX,in_stack_ffffffb4,piVar21,fVar22,fVar23,piVar24,iVar19);
    if (iVar14 != 0) {
      return 0;
    }
    piVar21 = allocate_astar_grid_node(iVar13,iVar19,0,0);
    uVar12 = lookup_terrain_material_index_at_world_xz((double)iVar13,(double)iVar20);
    if ((CONCAT22(extraout_var,uVar12) < 2) || (4 < CONCAT22(extraout_var,uVar12))) {
      piVar21[4] = 0;
    }
    else {
      piVar21[4] = 1;
    }
    allocate_astar_neighbor_grid_nodes(piVar21);
    local_28 = piVar21[2];
    if (0 < local_28) {
      iVar13 = 0x3c;
      do {
        piVar5 = *(int **)((int)piVar21 + iVar13);
        *(double *)(piVar5 + 8) = *(double *)(piVar21 + 10) + *(double *)(piVar21 + 8);
        fVar17 = compute_astar_terrain_cost_and_block_flag
                           ((int)param_1,(int)piVar5,*piVar5,piVar5[1],*piVar21,piVar21[1]);
        fVar9 = ABS(fVar22 - (float)*piVar5);
        fVar10 = ABS(fVar23 - (float)piVar5[1]);
        *(double *)(piVar5 + 10) = (double)fVar17;
        *(double *)(piVar5 + 6) =
             *(double *)(piVar5 + 0xc) + *(double *)(piVar5 + 8) + (double)fVar17;
        fVar3 = fVar9;
        if (fVar10 < fVar9) {
          fVar3 = fVar10;
          fVar10 = fVar9;
        }
        fVar3 = (fVar10 - fVar3) - fVar3 * (float)_DAT_004bc6f8;
        *(double *)(piVar5 + 0xc) = (double)fVar3;
        *(double *)(piVar5 + 6) = (double)((float)*(double *)(piVar5 + 8) + fVar3 + (float)fVar17);
        insert_astar_tree_node_recursive((int)piVar5,param_1 + 0x273c,1);
        insert_astar_tree_node_recursive((int)piVar5,piVar1,0);
        iVar13 = iVar13 + 4;
        local_28 = local_28 + -1;
      } while (local_28 != 0);
    }
  }
  piVar5 = param_1 + 0x273c;
  iVar19 = 0;
  remove_astar_tree_leftmost_node_recursive((int *)&stack0xffffffb8,piVar5,1);
  iVar13 = *piVar5;
  while( true ) {
    if (((iVar13 == 0) ||
        (((float)piVar21[1] - fVar23) * ((float)piVar21[1] - fVar23) +
         ((float)*piVar21 - fVar22) * ((float)*piVar21 - fVar22) < _DAT_004bc700)) || (99 < iVar19))
    goto LAB_0040f745;
    iVar13 = allocate_astar_neighbor_grid_nodes(piVar21);
    if (iVar13 == 0) break;
    local_1c = piVar21[2];
    if (0 < local_1c) {
      iVar13 = 0x3c;
      do {
        piVar6 = *(int **)((int)piVar21 + iVar13);
        iVar20 = *piVar6;
        *(double *)(piVar6 + 8) = *(double *)(piVar21 + 10) + *(double *)(piVar21 + 8);
        iVar14 = piVar21[1];
        iVar7 = *piVar21;
        iVar8 = piVar6[1];
        uVar12 = lookup_terrain_material_index_at_world_xz((double)iVar20,(double)iVar8);
        switch(CONCAT22(extraout_var_00,uVar12)) {
        case 2:
        case 3:
        case 4:
          fVar3 = 0.0;
          local_30 = 0.5;
          piVar6[4] = 1;
          break;
        default:
          piVar6[4] = 0;
          local_30 = 15.0;
          if ((param_1[0x2745] == 0) ||
             (uVar15 = terrain_map_context_helper_004926f0((double)iVar20,(double)iVar8),
             fVar3 = _DAT_004bc6dc, uVar15 == 0)) {
            fVar3 = _DAT_004bc6b4;
          }
          break;
        case 6:
        case 7:
          fVar3 = 0.0;
          local_30 = 0.5;
          piVar6[4] = 0;
        }
        dVar4 = _DAT_004bc670;
        if ((iVar20 != iVar7) && (iVar8 != iVar14)) {
          dVar4 = _DAT_004bc6f0;
        }
        dVar4 = (double)((fVar3 + local_30) * (float)dVar4);
        *(double *)(piVar6 + 10) = dVar4;
        *(double *)(piVar6 + 6) = *(double *)(piVar6 + 0xc) + *(double *)(piVar6 + 8) + dVar4;
        iVar20 = find_astar_tree_node_or_insert_parent
                           ((int)piVar6,*piVar1,0,(int *)&stack0xffffffc4);
        if (iVar20 == 1) {
          if (*(double *)(piVar6 + 10) + *(double *)(piVar6 + 8) <
              *(double *)(piVar24 + 10) + *(double *)(piVar24 + 8)) {
            piVar24[0xe] = (int)piVar21;
            relax_astar_neighbor_cost_recursive(piVar24,piVar21,piVar5);
          }
          *(int **)((int)piVar21 + iVar13) = piVar24;
          piVar6[0x18] = (int)DAT_0051f65c;
          DAT_005244bc = DAT_005244bc + -1;
          DAT_0051f65c = piVar6;
        }
        else {
          fVar9 = ABS(fVar22 - (float)*piVar6);
          fVar10 = ABS(fVar23 - (float)piVar6[1]);
          fVar3 = fVar9;
          if (fVar10 < fVar9) {
            fVar3 = fVar10;
            fVar10 = fVar9;
          }
          dVar4 = ((double)fVar10 - (double)fVar3) - (double)fVar3 * _DAT_004bc6f8;
          *(double *)(piVar6 + 0xc) = dVar4;
          *(double *)(piVar6 + 6) = *(double *)(piVar6 + 10) + *(double *)(piVar6 + 8) + dVar4;
          insert_astar_tree_node_recursive((int)piVar6,piVar5,1);
          insert_astar_tree_node_recursive((int)piVar6,piVar1,0);
        }
        iVar13 = iVar13 + 4;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    iVar19 = iVar19 + 1;
    remove_astar_tree_leftmost_node_recursive((int *)&stack0xffffffb8,piVar5,1);
    iVar13 = *piVar5;
  }
  bVar11 = true;
LAB_0040f745:
  param_1[0x1f] = param_1[0x1f] + iVar19;
  *param_2 = *param_2 + iVar19;
  if ((_DAT_004bc700 <=
       ((float)piVar21[1] - fVar23) * ((float)piVar21[1] - fVar23) +
       ((float)*piVar21 - fVar22) * ((float)*piVar21 - fVar22)) && (!bVar11)) {
    return 1;
  }
  emit_astar_path_to_ai_path_state((int)piVar21);
  iVar13 = DAT_0051f650 + 2;
  DAT_0051f65c = (int *)&DAT_005dd780;
  if (999 < DAT_005244bc) {
    iVar13 = 999;
  }
  if (0 < iVar13) {
    puVar16 = &DAT_005dd7e0;
    do {
      *puVar16 = puVar16 + 8;
      puVar16 = puVar16 + 0x20;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
  }
  DAT_005244bc = 0;
  DAT_0051f650 = 0;
  _DAT_005fcb60 = 0;
  _DAT_0051f664 = 0;
  param_1[0x1f] = 0;
  *piVar5 = 0;
  *piVar1 = 0;
  return 0;
}


