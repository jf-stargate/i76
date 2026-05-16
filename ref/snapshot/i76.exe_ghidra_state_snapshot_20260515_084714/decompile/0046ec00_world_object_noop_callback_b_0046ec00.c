/*
 * Program: i76.exe
 * Function: world_object_noop_callback_b_0046ec00
 * Entry: 0046ec00
 * Signature: undefined __cdecl world_object_noop_callback_b_0046ec00(int param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt readability rename set C v15: Readability pass set C: world object noop callback b based on
   adjacent named subsystem context. */

void __cdecl world_object_noop_callback_b_0046ec00(int param_1)

{
  double dVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar2 = *(undefined4 **)(param_1 + 0x70);
  if (puVar2 != (undefined4 *)0x0) {
    puVar5 = puVar2;
    for (iVar4 = 0x2e; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    uVar3 = get_root_ancestor_world_object(param_1);
    *puVar2 = uVar3;
    puVar2[1] = 0;
    puVar2[8] = (float)*(double *)(param_1 + 0x40);
    puVar2[9] = (float)*(double *)(param_1 + 0x48) - _DAT_004be510;
    dVar1 = *(double *)(param_1 + 0x50);
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[10] = (float)dVar1;
    puVar2[7] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x3f19999a;
    puVar2[4] = 0;
    puVar2[0xb] = 0;
    puVar2[0xc] = 0;
    puVar2[0xd] = 0;
    puVar2[0xe] = 0;
    puVar2[0xf] = 0;
    mission_flow_map_context_helper_0049e0f0((double *)(puVar2 + 0x10),0.5,4.0);
    mission_flow_map_context_helper_0049e0f0((double *)(puVar2 + 0x1a),0.5,4.0);
    mission_flow_map_context_helper_0049e0f0((double *)(puVar2 + 0x24),0.5,4.0);
  }
  return;
}


