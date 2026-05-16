/*
 * Program: i76.exe
 * Function: flip_or_restore_directdraw_front_back_surfaces
 * Entry: 0042e2c0
 * Signature: bool __stdcall flip_or_restore_directdraw_front_back_surfaces(void)
 */


/* cgpt readability rename v13 set A: Handles DirectDraw front/back surface restore, flip/blit
   behavior, and surface state flags for the display backend. */

bool flip_or_restore_directdraw_front_back_surfaces(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piStack_94;
  int *piStack_90;
  int *piStack_8c;
  int *piStack_88;
  int *piStack_84;
  int *piStack_80;
  undefined4 local_6c [27];
  
  piVar2 = DAT_006080c4;
  puVar5 = local_6c;
  for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  piStack_80 = DAT_006080c4;
  iVar4 = 0;
  piStack_84 = (int *)0x42e2e4;
  iVar3 = (**(code **)(*DAT_006080c4 + 0x60))();
  if (iVar3 != 0) {
    piStack_84 = piVar2;
    piStack_88 = (int *)0x42e2ee;
    (**(code **)(*piVar2 + 0x6c))();
  }
  piVar1 = DAT_006080c0;
  piStack_84 = DAT_006080c0;
  piStack_88 = (int *)0x42e2fa;
  iVar3 = (**(code **)(*DAT_006080c0 + 0x60))();
  if (iVar3 != 0) {
    piStack_88 = piVar1;
    piStack_8c = (int *)0x42e304;
    (**(code **)(*piVar1 + 0x6c))();
  }
  if (DAT_005280cc == 0) {
    if (DAT_00608408 == 8) {
      piStack_88 = (int *)0x0;
      piStack_8c = (int *)0x1000000;
      piStack_90 = (int *)0x0;
      piStack_94 = piVar2;
      iVar3 = (**(code **)(*piVar1 + 0x14))(piVar1,0);
      return iVar3 == 0;
    }
    DAT_005280d8 = 1;
    piStack_88 = (int *)0x0;
    piStack_8c = (int *)0x0;
    piStack_90 = DAT_006080c0;
    piStack_94 = (int *)0x42e336;
    iVar3 = (**(code **)(*DAT_006080c0 + 0x2c))();
    if (iVar3 != -0x7789fde4) {
      DAT_005280d8 = 0;
      return true;
    }
  }
  else if (DAT_00608408 == 8) {
    piStack_88 = (int *)0x0;
    piStack_8c = piVar2;
    piStack_90 = (int *)0x42e3c8;
    (**(code **)(*piVar2 + 0x80))();
    piStack_90 = (int *)0x0;
    piStack_94 = (int *)0x1000000;
    iVar3 = (**(code **)(*piVar1 + 0x14))(piVar1,0,piVar2,0);
    if (iVar3 != 0) {
      return false;
    }
    piStack_94 = (int *)0x6c;
    iVar4 = (**(code **)(*piVar2 + 100))(piVar2,0,&piStack_94,1,0);
    if (iVar4 != 0) {
      DAT_005280cc = 0;
    }
  }
  else {
    piStack_88 = (int *)0x0;
    piStack_8c = piVar2;
    piStack_90 = (int *)0x42e385;
    (**(code **)(*piVar2 + 0x80))();
    DAT_005280cc = 0;
    DAT_005280d8 = 1;
    piStack_90 = (int *)0x0;
    piStack_94 = (int *)0x0;
    iVar3 = (**(code **)(*DAT_006080c0 + 0x2c))(DAT_006080c0);
    if (iVar3 != -0x7789fde4) {
      DAT_005280d8 = 0;
      return true;
    }
  }
  return iVar4 == 0;
}


