/*
 * Program: i76shell.dll
 * Function: load_or_apply_shell_surface_record_by_id_candidate
 * Entry: 100387d0
 * Signature: undefined __thiscall load_or_apply_shell_surface_record_by_id_candidate(void * this, void * param_1, LPVOID param_2)
 */


void __thiscall
load_or_apply_shell_surface_record_by_id_candidate(void *this,void *param_1,LPVOID param_2)

{
  undefined4 uVar1;
  LPVOID pvVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  void *local_4;
  
  pvVar2 = param_2;
  local_4 = this;
  load_shell_rle_bitmap_surface_from_database_record(this,param_2);
  iVar3 = mpack_database_get_item_alloc_or_alias(param_1,(SIZE_T)pvVar2,&param_2,(SIZE_T *)&local_4)
  ;
  if (iVar3 != 0) {
    return;
  }
  if (*(int *)((int)this + 0x20) == 0) {
    if (DAT_100f6368 != 0) {
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)((int)this + 0x30) = 0;
      }
      iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar3 != 0) goto LAB_10038963;
      uVar1 = *DAT_100533e8;
      *(undefined4 *)((int)this + 0x30) = uVar1;
      **(undefined4 **)((int)this + 0x6c) = uVar1;
    }
    decode_simple_rle_bitmap_to_shell_surface((int *)((int)this + 0x6c),(int)param_2);
    uVar4 = *(int *)((int)this + 0x3bc) * *(int *)((int)this + 0x3c0);
    puVar6 = *(undefined4 **)((int)this + 0x30);
    puVar7 = *(undefined4 **)((int)this + 0x44);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    uVar4 = *(int *)((int)this + 0x3bc) * *(int *)((int)this + 0x3c0);
    puVar6 = *(undefined4 **)((int)this + 0x30);
    puVar7 = *(undefined4 **)((int)this + 0x58);
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
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
    if (DAT_100f6368 == 0) goto LAB_10038963;
    (**(code **)(DAT_100533d8 + 0x24))();
  }
  else {
    if (DAT_100f6368 != 0) {
      if (DAT_100d3114 != 0) {
        (**(code **)(DAT_100533d8 + 0x24))();
        *(undefined4 *)((int)this + 0x30) = 0;
      }
      iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
      if (iVar3 == 0) {
        uVar1 = *DAT_100533e8;
        *(undefined4 *)((int)this + 0x30) = uVar1;
        **(undefined4 **)((int)this + 0x6c) = uVar1;
      }
    }
    decode_simple_rle_bitmap_to_shell_surface((int *)((int)this + 0x80),(int)param_2);
    flush_or_repaint_shell_surface_context((int)this);
    if (DAT_100f6368 == 0) goto LAB_10038963;
    (**(code **)(DAT_100533d8 + 0x24))();
  }
  *(undefined4 *)((int)this + 0x30) = 0;
LAB_10038963:
  HeapFree(DAT_10051c50,1,param_2);
  return;
}


