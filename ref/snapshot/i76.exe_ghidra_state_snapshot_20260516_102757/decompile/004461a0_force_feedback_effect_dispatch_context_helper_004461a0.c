/*
 * Program: i76.exe
 * Function: force_feedback_effect_dispatch_context_helper_004461a0
 * Entry: 004461a0
 * Signature: undefined __stdcall force_feedback_effect_dispatch_context_helper_004461a0(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: force feedback effect dispatch context
   helper based on prior focused closure context. */

void force_feedback_effect_dispatch_context_helper_004461a0(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  geometry_binding_table_helper_00446900();
  DAT_0052db9c = HeapCreate(0,0,0);
  DAT_0052dba0 = HeapCreate(0,0,0);
  puVar2 = &g_geometry_binding_hash;
  for (iVar1 = 0x7ed; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}


