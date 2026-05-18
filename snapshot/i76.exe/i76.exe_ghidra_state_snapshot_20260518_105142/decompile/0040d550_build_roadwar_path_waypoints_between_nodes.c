/*
 * Program: i76.exe
 * Function: build_roadwar_path_waypoints_between_nodes
 * Entry: 0040d550
 * Signature: undefined __cdecl build_roadwar_path_waypoints_between_nodes(int * param_1, int * param_2, int * param_3, int * param_4, int * param_5, int * param_6)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Builds roadwar/A* path waypoints between two road
   nodes, handling loop direction and emitting offset X/Z/weight triples. */

void __cdecl
build_roadwar_path_waypoints_between_nodes
          (int *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  int *piVar6;
  int iVar7;
  undefined3 extraout_var;
  int *piVar8;
  int *piVar9;
  int *local_10;
  int *local_c;
  int *local_8;
  int *local_4;
  
  piVar2 = param_4;
  piVar1 = param_2;
  piVar8 = param_1;
  local_c = (int *)0x0;
  piVar6 = (int *)compare_roadwar_path_tree_node_order
                            ((int)param_1,(int)param_2,(int)param_3,(int)param_4);
  local_10 = piVar6;
  param_4 = (int *)compute_road_loop_distance_between_nodes
                             ((int)piVar6,(int)piVar8,(int)piVar1,(int)param_3,(int)piVar2);
  iVar7 = road_loop_end_error((int)piVar8,(int *)&param_1,(int *)&param_2);
  piVar9 = local_c;
  if (iVar7 != 0) {
    local_8 = (int *)-(int)piVar6;
    bVar5 = test_road_loop_distance_window_clear
                      ((int)local_8,(int)param_4,(int)piVar8,(int)piVar1,(int)param_2,(int)param_1,
                       (int)param_3,(int)piVar2);
    piVar9 = local_c;
    if (CONCAT31(extraout_var,bVar5) != 0) {
      local_10 = local_8;
      piVar9 = (int *)0x1;
      piVar6 = local_8;
    }
  }
  piVar4 = param_6;
  piVar3 = param_5;
  param_4 = (int *)(param_2[5] + -1);
  if (piVar9 == (int *)0x0) {
    local_4 = (int *)(uint)(piVar6 == (int *)0x1);
    param_4 = piVar1;
    local_8 = piVar8;
    do {
      compute_offset_point_along_road_segment
                ((float)local_8,(int)param_4,(int)local_4,(float *)(piVar3 + *piVar4 * 3),
                 (float *)(piVar3 + *piVar4 * 3 + 1));
      piVar3[*piVar4 * 3 + 2] = 0x3f800000;
      *piVar4 = *piVar4 + 1;
      iVar7 = path_nodes_share_same_position(local_8,(int)param_4,param_3,(int)piVar2);
      if (iVar7 != 0) {
        return;
      }
      iVar7 = roadwar_get_next_road_index((int *)&local_8,(int)local_10,(int *)&param_4);
    } while (iVar7 != 0);
  }
  else if (piVar6 == (int *)0xffffffff) {
    local_10 = piVar1;
    local_c = piVar8;
    local_8 = param_1;
    do {
      compute_offset_point_along_road_segment
                ((float)local_c,(int)local_10,0,(float *)(piVar3 + *piVar4 * 3),
                 (float *)(piVar3 + *piVar4 * 3 + 1));
      piVar3[*piVar4 * 3 + 2] = 0x3f800000;
      *piVar4 = *piVar4 + 1;
      iVar7 = path_nodes_share_same_position(local_c,(int)local_10,local_8,0);
      if (iVar7 != 0) break;
      iVar7 = roadwar_get_next_road_index((int *)&local_c,-1,(int *)&local_10);
    } while (iVar7 != 0);
    iVar7 = path_nodes_share_same_position(param_1,0,param_2,(int)param_4);
    if (iVar7 != 0) {
      param_4 = (int *)((int)param_4 + -1);
    }
    param_6 = param_4;
    param_5 = param_2;
    while( true ) {
      compute_offset_point_along_road_segment
                ((float)param_5,(int)param_6,0,(float *)(piVar3 + *piVar4 * 3),
                 (float *)(piVar3 + *piVar4 * 3 + 1));
      piVar3[*piVar4 * 3 + 2] = 0x3f800000;
      *piVar4 = *piVar4 + 1;
      iVar7 = path_nodes_share_same_position(param_5,(int)param_6,param_3,(int)piVar2);
      if (iVar7 != 0) break;
      iVar7 = roadwar_get_next_road_index((int *)&param_5,-1,(int *)&param_6);
      if (iVar7 == 0) {
        return;
      }
    }
  }
  else {
    local_c = piVar1;
    local_8 = piVar8;
    local_4 = param_2;
    do {
      compute_offset_point_along_road_segment
                ((float)local_8,(int)local_c,1,(float *)(piVar3 + *piVar4 * 3),
                 (float *)(piVar3 + *piVar4 * 3 + 1));
      piVar3[*piVar4 * 3 + 2] = 0x3f800000;
      *piVar4 = *piVar4 + 1;
      iVar7 = path_nodes_share_same_position(local_8,(int)local_c,local_4,(int)param_4);
      if (iVar7 != 0) break;
      iVar7 = roadwar_get_next_road_index((int *)&local_8,(int)local_10,(int *)&local_c);
    } while (iVar7 != 0);
    param_6 = (int *)0x0;
    iVar7 = path_nodes_share_same_position(param_2,(int)param_4,param_1,0);
    piVar8 = (int *)0x1;
    if (iVar7 == 0) {
      piVar8 = param_6;
    }
    param_5 = param_1;
    param_6 = piVar8;
    while( true ) {
      compute_offset_point_along_road_segment
                ((float)param_5,(int)param_6,1,(float *)(piVar3 + *piVar4 * 3),
                 (float *)(piVar3 + *piVar4 * 3 + 1));
      piVar3[*piVar4 * 3 + 2] = 0x3f800000;
      *piVar4 = *piVar4 + 1;
      iVar7 = path_nodes_share_same_position(param_5,(int)param_6,param_3,(int)piVar2);
      if (iVar7 != 0) break;
      iVar7 = roadwar_get_next_road_index((int *)&param_5,(int)local_10,(int *)&param_6);
      if (iVar7 == 0) {
        return;
      }
    }
  }
  return;
}


