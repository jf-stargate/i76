/*
 * Program: i76.exe
 * Function: multiplayer_respawn_timer_context_helper_00451540
 * Entry: 00451540
 * Signature: undefined __cdecl multiplayer_respawn_timer_context_helper_00451540(int param_1, int param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: multiplayer respawn timer context
   helper based on prior focused closure context. */

void __cdecl multiplayer_respawn_timer_context_helper_00451540(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)(&g_odef_spawn_transform_table + param_2 * 0x40);
  puVar3 = (undefined4 *)(param_1 + 0x18);
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return;
}


