/*
 * Program: i76.exe
 * Function: initialize_bridge_validation_node_pool
 * Entry: 0040c160
 * Signature: undefined __stdcall initialize_bridge_validation_node_pool(void)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* cgpt rename v7 fsm predicate/bridge cluster: Initializes the bridge/path validation node pool and
   resets validation globals. */

void initialize_bridge_validation_node_pool(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = 999;
  DAT_0051f65c = &DAT_005dd780;
  puVar1 = &DAT_005dd780;
  do {
    puVar2 = puVar1;
    iVar3 = iVar3 + -1;
    *(undefined1 **)(puVar2 + 0x60) = puVar2 + 0x80;
    puVar1 = puVar2 + 0x80;
  } while (iVar3 != 0);
  *(undefined4 *)(puVar2 + 0xe0) = 0;
  DAT_005244bc = 0;
  DAT_0051f650 = 0;
  _DAT_0051f664 = 0;
  return;
}


