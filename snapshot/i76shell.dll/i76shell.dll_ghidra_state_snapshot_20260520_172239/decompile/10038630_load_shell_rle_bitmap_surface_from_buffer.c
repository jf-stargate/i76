/*
 * Program: i76shell.dll
 * Function: load_shell_rle_bitmap_surface_from_buffer
 * Entry: 10038630
 * Signature: undefined __thiscall load_shell_rle_bitmap_surface_from_buffer(void * this, uint param_1, uint param_2, uint param_3, undefined1 param_4, undefined1 param_5)
 */


void __thiscall
load_shell_rle_bitmap_surface_from_buffer
          (void *this,uint param_1,uint param_2,uint param_3,undefined1 param_4,undefined1 param_5)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  byte *pbVar5;
  
  *(uint *)((int)this + 0x10) = param_2;
  *(uint *)((int)this + 0x14) = param_3;
  *(uint *)((int)this + 0xc) = param_1;
  *(undefined1 *)((int)this + 8) = param_4;
  *(undefined1 *)((int)this + 9) = param_5;
  if (param_3 != 2) {
    *(undefined4 *)this = 0;
    shutdown_shell_display_backend_candidate();
    log_or_report_shell_ddraw_error_candidate(s_vdriver_error_1004d568);
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  uVar2 = get_shell_bitmap_dimensions_packed(param_1);
  *(undefined4 *)this = uVar2;
  *(int *)((int)this + 0x3c4) = ((int)*(uint *)this >> 0x10) + -1;
  *(uint *)((int)this + 0x3c8) = (*(uint *)this & 0xffff) - 1;
  if (DAT_100f6368 == 0) {
    extract_shell_bitmap_palette_from_buffer
              (*(int *)((int)this + 0xc),*(int *)((int)this + 0x10),(byte *)((int)this + 0xbc));
  }
  else {
    puVar4 = (undefined4 *)(*(int *)((int)this + 0xc) + *(int *)((int)this + 0x10) + -0x300);
    pbVar5 = (byte *)((int)this + 0xbc);
    for (iVar3 = 0xc0; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined4 *)pbVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      pbVar5 = pbVar5 + 4;
    }
  }
  *(undefined4 *)((int)this + 0x20) = 1;
  *(undefined4 *)((int)this + 0x24) = 1;
  if (DAT_100f6368 != 0) {
    if (DAT_100d3114 != 0) {
      (**(code **)(DAT_100533d8 + 0x24))();
      *(undefined4 *)((int)this + 0x30) = 0;
    }
    iVar3 = (**(code **)(DAT_100533d8 + 0x20))();
    if (iVar3 != 0) goto LAB_10038782;
    uVar2 = *DAT_100533e8;
    *(undefined4 *)((int)this + 0x30) = uVar2;
    **(undefined4 **)((int)this + 0x6c) = uVar2;
  }
  piVar1 = (int *)((int)this + 0x6c);
  decode_simple_rle_bitmap_to_shell_surface(piVar1,*(int *)((int)this + 0xc));
  blit_or_fill_rect_clipped(piVar1,0,0,(int *)((int)this + 0x80),0,0,0xffffffff);
  blit_or_fill_rect_clipped(piVar1,0,0,(int *)((int)this + 0xa8),0,0,0xffffffff);
  if (DAT_100f6368 != 0) {
    (**(code **)(DAT_100533d8 + 0x24))();
    *(undefined4 *)((int)this + 0x30) = 0;
  }
LAB_10038782:
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
  return;
}


