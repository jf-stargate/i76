/*
 * Program: i76.exe
 * Function: free_mission_salvage_resource_list
 * Entry: 004b19d0
 * Signature: undefined __stdcall free_mission_salvage_resource_list(void)
 */


/* [cgpt i76.exe mission/vehicle runtime rename v15; confidence=high] Frees the full nested mission
   salvage/resource linked list and clears g_mission_salvage_resource_list. */

void free_mission_salvage_resource_list(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = g_mission_salvage_resource_list;
  while (puVar4 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar4;
    puVar3 = (undefined4 *)puVar4[1];
    while (puVar3 != (undefined4 *)0x0) {
      puVar2 = (undefined4 *)*puVar3;
      xfree_global_heap(puVar3);
      puVar3 = puVar2;
    }
    xfree_global_heap(puVar4);
    puVar4 = puVar1;
  }
  g_mission_salvage_resource_list = (undefined4 *)0x0;
  return;
}


