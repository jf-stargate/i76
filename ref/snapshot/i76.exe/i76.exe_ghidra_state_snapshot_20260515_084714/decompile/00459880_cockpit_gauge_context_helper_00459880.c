/*
 * Program: i76.exe
 * Function: cockpit_gauge_context_helper_00459880
 * Entry: 00459880
 * Signature: undefined __stdcall cockpit_gauge_context_helper_00459880(void)
 */


/* cgpt label refinement v19: was cockpit_hud_ui_cockpit_gauge_helper_00459880. Remove duplicated
   cockpit wording. */

void cockpit_gauge_context_helper_00459880(void)

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
    puVar1[0x10] = 0x15;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
  }
  return;
}


