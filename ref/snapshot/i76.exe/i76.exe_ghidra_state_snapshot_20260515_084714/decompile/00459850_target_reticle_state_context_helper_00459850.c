/*
 * Program: i76.exe
 * Function: target_reticle_state_context_helper_00459850
 * Entry: 00459850
 * Signature: undefined __stdcall target_reticle_state_context_helper_00459850(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: target reticle state context helper
   based on prior focused closure context. */

void target_reticle_state_context_helper_00459850(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)xalloc_global_heap(0x50);
  if (puVar1 != (undefined4 *)0x0) {
    puVar3 = &DAT_004faed8;
    puVar4 = puVar1;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    puVar1[0x10] = 0x14;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
  }
  return;
}


