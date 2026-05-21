/*
 * Program: i76shell.dll
 * Function: open_internet_entry_list_dialog
 * Entry: 1000c520
 * Signature: undefined __cdecl open_internet_entry_list_dialog(int * param_1)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __cdecl open_internet_entry_list_dialog(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  
  DAT_100533c0 = param_1;
  iVar1 = param_1[2];
  iVar2 = param_1[3];
  iVar3 = param_1[1];
  iVar4 = *param_1;
  uVar8 = iVar1 * 6;
  puVar5 = HeapAlloc(DAT_10051c50,1,uVar8);
  if (puVar5 != (undefined4 *)0x0) {
    puVar9 = puVar5;
    for (uVar7 = uVar8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar9 = 0xf0f0f0f;
      puVar9 = puVar9 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar9 = 0xf;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar5,iVar4 + 6,iVar2 + iVar3,iVar1,6);
    HeapFree(DAT_10051c50,1,puVar5);
  }
  uVar8 = iVar2 * 6;
  puVar5 = HeapAlloc(DAT_10051c50,1,uVar8);
  if (puVar5 != (undefined4 *)0x0) {
    puVar9 = puVar5;
    for (uVar7 = uVar8 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar9 = 0xf0f0f0f;
      puVar9 = puVar9 + 1;
    }
    for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
      *(undefined1 *)puVar9 = 0xf;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    }
    fill_shell_surface_rect_from_buffer(DAT_100cc518,puVar5,iVar1 + iVar4,iVar3 + 6,6,iVar2);
    HeapFree(DAT_10051c50,1,puVar5);
  }
  draw_mw2_image_subresource_to_shell_surface
            (DAT_100cc518,g_shell_ui_image_record_ptr_100f4f90,0x1d,*param_1,param_1[1],param_1[2],
             param_1[3]);
  _DAT_10053380 = (undefined4 *)0x0;
  DAT_10053398 = (LPVOID)0x0;
  _DAT_10053384 = 0;
  _DAT_1005339c = 0;
  _DAT_10053388 = 0;
  _DAT_100533a0 = 0;
  _DAT_1005338c = 0;
  _DAT_100533a4 = 0;
  _DAT_10053390 = 0;
  _DAT_100533a8 = 0;
  DAT_10053398 = HeapAlloc(DAT_10051c50,9,
                           *(int *)((int)DAT_100cc518 + 0x3c0) * *(int *)((int)DAT_100cc518 + 0x3bc)
                          );
  _DAT_1005339c = *(undefined4 *)((int)DAT_100cc518 + 0x48);
  _DAT_100533a0 = *(undefined4 *)((int)DAT_100cc518 + 0x4c);
  _DAT_10053384 = 0;
  _DAT_10053388 = 0;
  _DAT_1005338c = 0x27f;
  _DAT_10053390 = 0x1df;
  _DAT_10053380 = &DAT_10053398;
  uVar6 = lock_shell_surface_for_draw((int)DAT_100cc518);
  if ((char)uVar6 == '\0') {
    blit_or_fill_rect_clipped
              ((int *)((int)DAT_100cc518 + 0x6c),0,0,(int *)&DAT_10053380,0,0,0xffffffff);
    unlock_shell_surface_after_draw((int)DAT_100cc518);
  }
  DAT_100533c0[7] = 0;
  DAT_100533c0[4] = DAT_100533c0[4] + *DAT_100533c0;
  DAT_100533c0[5] = DAT_100533c0[5] + DAT_100533c0[1];
  (*(code *)DAT_100533c0[10])(DAT_100533c0[4],DAT_100533c0[5],DAT_100533c0[7],DAT_100533c0[6]);
  DAT_100d21a4 = &LAB_10009d20;
  return;
}


