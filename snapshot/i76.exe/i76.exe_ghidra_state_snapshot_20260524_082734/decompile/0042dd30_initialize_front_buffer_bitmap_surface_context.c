/*
 * Program: i76.exe
 * Function: initialize_front_buffer_bitmap_surface_context
 * Entry: 0042dd30
 * Signature: undefined4 __stdcall initialize_front_buffer_bitmap_surface_context(void)
 */


/* cgpt rename v8 display/d3d cluster: Initializes a bitmap-surface context for the current
   front/back display surface, querying surface description and constructing a clipped bitmap
   context. */

undefined4 initialize_front_buffer_bitmap_surface_context(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int unaff_EDI;
  int *piVar4;
  uint uVar5;
  int local_a0 [21];
  int aiStack_4c [14];
  int *piStack_14;
  
  if (DAT_005280cc == 0) {
    DAT_005280cc = 0;
    piVar2 = DAT_006080c4;
    while (DAT_006080c4 = piVar2, DAT_005280d8 != 0) {
      iVar1 = (**(code **)(*DAT_006080c0 + 0x2c))(DAT_006080c0,0,0);
      piVar2 = DAT_006080c4;
      if (iVar1 != -0x7789fde4) {
        DAT_005280d8 = 0;
      }
    }
    piVar3 = local_a0;
    for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    DAT_005280cc = 1;
    local_a0[0] = 0x6c;
    piVar3 = piVar2;
    iVar1 = (**(code **)(*piVar2 + 0x60))();
    if (iVar1 != 0) {
      (**(code **)(*piVar2 + 0x6c))(piVar2);
    }
    uVar5 = 0;
    iVar1 = (**(code **)(*piVar2 + 100))(piVar2,0,&stack0xffffff5c,1);
    if (iVar1 != 0) {
      DAT_005280cc = 0;
      return 0;
    }
    if (DAT_00608408 == 8) {
      iVar1 = 0;
    }
    else {
      unaff_EDI = unaff_EDI >> 1;
      if ((int)piVar3 < unaff_EDI) {
        piVar3 = (int *)((int)piVar3 + -1);
      }
      iVar1 = 1;
    }
    piVar2 = (int *)construct_bitmap_surface_context(aiStack_4c,unaff_EDI,uVar5,local_a0[3],iVar1);
    piVar4 = piStack_14;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar4 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar4 = piVar4 + 1;
    }
    set_bitmap_surface_clip_rect(piStack_14,0,0,(int)piVar3,uVar5);
  }
  return 1;
}


