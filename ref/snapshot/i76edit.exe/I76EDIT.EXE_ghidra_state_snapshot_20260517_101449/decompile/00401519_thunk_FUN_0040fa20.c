/*
 * Program: I76EDIT.EXE
 * Function: thunk_FUN_0040fa20
 * Entry: 00401519
 * Signature: undefined4 __cdecl thunk_FUN_0040fa20(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl thunk_FUN_0040fa20(int *param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  
  DAT_00434970 = 0xbf800000;
  DAT_00434974 = 0xbf800000;
  DAT_00434978 = 0xbf800000;
  DAT_00434980 = 0xbf800000;
  DAT_00434984 = 0xbf800000;
  DAT_00434988 = 0xbf800000;
  DAT_00434990 = 0xbf800000;
  DAT_00434994 = 0xbf800000;
  DAT_00434998 = 0xbf800000;
  DAT_0043499c = 0;
  piVar4 = param_1;
  if (param_1 != (int *)0x0) {
    do {
      iVar3 = piVar4[2];
      *(uint *)(iVar3 + 0x50) = *(uint *)(iVar3 + 0x50) & 0xfffffffe;
      if ((*(float *)(iVar3 + 0x10) == *(float *)(iVar3 + 0x34)) &&
         (*(float *)(iVar3 + 0x14) == *(float *)(iVar3 + 0x38))) {
        i76edit_delete_road_node_and_cleanup_edges(piVar4);
        return 1;
      }
      piVar4 = (int *)*piVar4;
    } while (piVar4 != (int *)0x0);
    while (param_1 != (int *)0x0) {
      puVar2 = (undefined4 *)i76edit_export_one_road_geometry_chunk((int)param_1);
      _DAT_00439eb0 = 0xffffffff;
      DAT_00434970 = 0xbf800000;
      DAT_00434974 = 0xbf800000;
      DAT_00434978 = 0xbf800000;
      i76edit_build_or_emit_linked_object_road_links(puVar2);
      iVar3 = param_1[2];
      uVar1 = *(uint *)(iVar3 + 0x50);
      while ((uVar1 & 1) != 0) {
        if (param_1 == (int *)0x0) {
          return 0;
        }
        param_1 = (int *)*param_1;
        if (param_1 != (int *)0x0) {
          iVar3 = param_1[2];
        }
        uVar1 = *(uint *)(iVar3 + 0x50);
      }
    }
  }
  return 0;
}


