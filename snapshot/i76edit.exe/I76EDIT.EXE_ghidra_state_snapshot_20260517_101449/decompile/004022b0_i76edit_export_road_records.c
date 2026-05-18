/*
 * Program: I76EDIT.EXE
 * Function: i76edit_export_road_records
 * Entry: 004022b0
 * Signature: int __cdecl i76edit_export_road_records(int param_1, int * param_2)
 */


/* [cgpt_i76edit_level_renames_v2:medium] References 'Exporting Road %d.' and writes via __write
   call chain; likely per-road export serializer. */

int __cdecl i76edit_export_road_records(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  long _Offset;
  int local_118;
  undefined4 local_114;
  int local_110;
  uint local_10c;
  int local_108;
  long local_104;
  char local_100 [256];
  
  local_118 = 0;
  DAT_00434070 = 0xbf800000;
  DAT_00434074 = 0xbf800000;
  DAT_00434078 = 0xbf800000;
  DAT_00434080 = 0;
  piVar1 = param_2;
  while( true ) {
    if (piVar1 == (int *)0x0) {
      local_114 = 0x47455352;
      DAT_00439a20 = 0;
      do {
        if (param_2 == (int *)0x0) {
          return local_118;
        }
        _sprintf(local_100,s_Exporting_Road__d__00434088,DAT_00439a20);
        i76edit_set_status_bar_text(local_100);
        iVar3 = i76edit_export_one_road_geometry_chunk((int)param_2);
        local_110 = 0x10;
        local_10c = (uint)*(ushort *)(*(int *)(iVar3 + 8) + 4);
        local_108 = 0;
        local_104 = __tell(param_1);
        __write(param_1,&local_114,0x10);
        local_108 = i76edit_export_road_segment_mesh_records(param_1,iVar3);
        local_110 = local_110 + local_108 * 0x18;
        local_118 = local_118 + local_110;
        _Offset = __tell(param_1);
        __lseek(param_1,local_104,0);
        __write(param_1,&local_114,0x10);
        __lseek(param_1,_Offset,0);
        DAT_00439a20 = DAT_00439a20 + 1;
        iVar3 = param_2[2];
        uVar2 = *(uint *)(iVar3 + 0x50);
        while ((uVar2 & 1) != 0) {
          if (param_2 == (int *)0x0) {
            return local_118;
          }
          param_2 = (int *)*param_2;
          if (param_2 != (int *)0x0) {
            iVar3 = param_2[2];
          }
          uVar2 = *(uint *)(iVar3 + 0x50);
        }
      } while( true );
    }
    iVar3 = piVar1[2];
    *(uint *)(iVar3 + 0x50) = *(uint *)(iVar3 + 0x50) & 0xfffffffe;
    if ((*(float *)(iVar3 + 0x10) == *(float *)(iVar3 + 0x34)) &&
       (*(float *)(iVar3 + 0x14) == *(float *)(iVar3 + 0x38))) break;
    piVar1 = (int *)*piVar1;
  }
  i76edit_delete_road_node_and_cleanup_edges(piVar1);
  return -1;
}


