/*
 * Program: i76.exe
 * Function: emit_astar_path_to_ai_path_state
 * Entry: 0040e770
 * Signature: undefined __cdecl emit_astar_path_to_ai_path_state(int param_1)
 */


/* cgpt rename v11 astar/ai/fsm-loader cluster: Expands checked A* path nodes and emits them into
   the AI path-state block, handling direct and multi-node cases. */

void __cdecl emit_astar_path_to_ai_path_state(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int unaff_retaddr;
  int *in_stack_0000bb8c;
  int in_stack_0000bb90;
  
  zfsf_error_context_helper_004ba0a0();
  piVar1 = (int *)in_stack_0000bb8c[0xe];
  if (piVar1 == (int *)0x0) {
    *(float *)(in_stack_0000bb90 + 0xb0) = (float)*in_stack_0000bb8c;
    *(float *)(in_stack_0000bb90 + 0xb4) = (float)in_stack_0000bb8c[1];
    iVar2 = in_stack_0000bb8c[4];
    *(undefined4 *)(in_stack_0000bb90 + 0xac) = 1;
    *(int *)(in_stack_0000bb90 + 0xb8) = iVar2;
    return;
  }
  if (piVar1[0xe] == 0) {
    *(float *)(in_stack_0000bb90 + 0xb0) = (float)*piVar1;
    *(float *)(in_stack_0000bb90 + 0xb4) = (float)*(int *)(in_stack_0000bb8c[0xe] + 4);
    *(undefined4 *)(in_stack_0000bb90 + 0xb8) = *(undefined4 *)(in_stack_0000bb8c[0xe] + 0x10);
    *(float *)(in_stack_0000bb90 + 0xc4) = (float)*in_stack_0000bb8c;
    *(float *)(in_stack_0000bb90 + 200) = (float)in_stack_0000bb8c[1];
    iVar2 = in_stack_0000bb8c[4];
    *(undefined4 *)(in_stack_0000bb90 + 0xac) = 2;
    *(int *)(in_stack_0000bb90 + 0xcc) = iVar2;
    return;
  }
  astar_expand_path_node_checked(in_stack_0000bb8c,(int)&stack0x00000008,(int *)&stack0x00000000);
  if (0 < unaff_retaddr) {
    puVar3 = (undefined4 *)&stack0x00005dcc;
    iVar2 = unaff_retaddr * 0xc;
    iVar4 = unaff_retaddr;
    do {
      puVar3[-1] = *(undefined4 *)(&stack0xfffffffc + iVar2);
      *puVar3 = *(undefined4 *)(&stack0x00000000 + iVar2);
      puVar3[1] = *(undefined4 *)((int)&param_1 + iVar2);
      puVar3 = puVar3 + 3;
      iVar4 = iVar4 + -1;
      iVar2 = iVar2 + -0xc;
    } while (iVar4 != 0);
  }
  smooth_astar_path_corner_points
            ((undefined4 *)&stack0x00005dc8,(undefined4 *)&stack0x00000008,unaff_retaddr,&param_1);
  collapse_astar_path_collinear_runs();
  astar_report_path_too_long
            ((float *)&stack0x00005dc8,param_1,(int *)&stack0x00000008,(int *)&stack0x00000000);
  astar_expand_path_neighbor_checked
            ((float *)&stack0x00000008,(int)&stack0x00005dc8,(int *)&stack0x00000000);
  copy_astar_path_points_to_ai_path_state(in_stack_0000bb90,(int)&stack0x00005dc8,unaff_retaddr);
  return;
}


