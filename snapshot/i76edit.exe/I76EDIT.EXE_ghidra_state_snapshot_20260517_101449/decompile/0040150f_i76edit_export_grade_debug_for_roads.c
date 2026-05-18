/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_grade_debug_for_roads
 * Entry: 0040150f
 * Signature: undefined4 __cdecl i76edit_export_grade_debug_for_roads(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __cdecl i76edit_export_grade_debug_for_roads(int *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  DAT_0043c110 = (FILE *)FUN_004232c0(s_grade_txt_00437ad4,&DAT_00436a3c);
  DAT_004379c8 = 0xbf800000;
  DAT_004379cc = 0xbf800000;
  DAT_004379d0 = 0xbf800000;
  DAT_004379d8 = 0xbf800000;
  DAT_004379dc = 0xbf800000;
  DAT_004379e0 = 0xbf800000;
  DAT_004379e8 = 0xbf800000;
  DAT_004379ec = 0xbf800000;
  DAT_004379f0 = 0xbf800000;
  DAT_004379f4 = 0;
  piVar3 = param_1;
  if (param_1 != (int *)0x0) {
    do {
      iVar2 = piVar3[2];
      *(uint *)(iVar2 + 0x50) = *(uint *)(iVar2 + 0x50) & 0xfffffffe;
      if ((*(float *)(iVar2 + 0x10) == *(float *)(iVar2 + 0x34)) &&
         (*(float *)(iVar2 + 0x14) == *(float *)(iVar2 + 0x38))) {
        i76edit_delete_road_node_and_cleanup_edges(piVar3);
        return 1;
      }
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)0x0);
    while (param_1 != (int *)0x0) {
      iVar2 = i76edit_export_one_road_geometry_chunk((int)param_1);
      DAT_004379c8 = 0xbf800000;
      DAT_004379cc = 0xbf800000;
      DAT_004379d0 = 0xbf800000;
      DAT_004379d8 = 0xbf800000;
      DAT_004379dc = 0xbf800000;
      DAT_004379e0 = 0xbf800000;
      DAT_004379e8 = 0xbf800000;
      DAT_004379ec = 0xbf800000;
      DAT_004379f0 = 0xbf800000;
      _DAT_0043c128 = 0xffffffff;
      i76edit_build_grade_debug_road_link_table(iVar2);
      iVar2 = param_1[2];
      uVar1 = *(uint *)(iVar2 + 0x50);
      while ((uVar1 & 1) != 0) {
        if (param_1 == (int *)0x0) goto LAB_00420ff1;
        param_1 = (int *)*param_1;
        if (param_1 != (int *)0x0) {
          iVar2 = param_1[2];
        }
        uVar1 = *(uint *)(iVar2 + 0x50);
      }
    }
  }
LAB_00420ff1:
  _fclose(DAT_0043c110);
  return 0;
}


