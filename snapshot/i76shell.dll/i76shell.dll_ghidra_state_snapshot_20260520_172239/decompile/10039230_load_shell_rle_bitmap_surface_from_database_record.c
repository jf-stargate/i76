/*
 * Program: i76shell.dll
 * Function: load_shell_rle_bitmap_surface_from_database_record
 * Entry: 10039230
 * Signature: undefined __thiscall load_shell_rle_bitmap_surface_from_database_record(void * this, LPVOID param_1)
 */


void __thiscall load_shell_rle_bitmap_surface_from_database_record(void *this,LPVOID param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  byte *pbVar4;
  SIZE_T local_8;
  
  iVar2 = mpack_database_get_item_alloc_or_alias(DAT_100cc53c,(SIZE_T)param_1,&param_1,&local_8);
  if (iVar2 != 0) {
    return;
  }
  if (DAT_100f6368 == 0) {
    extract_shell_bitmap_palette_from_buffer((int)param_1,local_8,(byte *)((int)this + 0xbc));
  }
  else {
    puVar3 = (undefined4 *)((int)param_1 + (local_8 - 0x300));
    pbVar4 = (byte *)((int)this + 0xbc);
    for (iVar2 = 0xc0; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined4 *)pbVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      pbVar4 = pbVar4 + 4;
    }
  }
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar2 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar2 != 0) goto LAB_10039311;
    uVar1 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar1;
    **(undefined4 **)((int)this + 0x6c) = uVar1;
  }
  decode_simple_rle_bitmap_to_shell_surface((int *)((int)this + 0x6c),(int)param_1);
  blit_or_fill_rect_clipped((int *)((int)this + 0x6c),0,0,(int *)((int)this + 0xa8),0,0,0xffffffff);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_10039311:
  if (*(int *)((int)this + 0x70) < *(int *)((int)this + 0x98)) {
    *(int *)((int)this + 0x98) = *(int *)((int)this + 0x70);
  }
  if (*(int *)((int)this + 0x74) < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x9c) = *(int *)((int)this + 0x74);
  }
  if (*(int *)((int)this + 0xa0) < *(int *)((int)this + 0x78)) {
    *(int *)((int)this + 0xa0) = *(int *)((int)this + 0x78);
  }
  if (*(int *)((int)this + 0xa4) < *(int *)((int)this + 0x7c)) {
    *(int *)((int)this + 0xa4) = *(int *)((int)this + 0x7c);
  }
  *(undefined4 *)((int)this + 0x20) = 1;
  *(undefined4 *)((int)this + 0x24) = 1;
  DAT_100f5770 = 1;
  HeapFree(DAT_10051c50,1,param_1);
  return;
}


