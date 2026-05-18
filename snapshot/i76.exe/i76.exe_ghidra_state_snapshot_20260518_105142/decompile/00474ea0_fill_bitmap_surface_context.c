/*
 * Program: i76.exe
 * Function: fill_bitmap_surface_context
 * Entry: 00474ea0
 * Signature: undefined __cdecl fill_bitmap_surface_context(int * param_1, byte param_2)
 */


/* [cgpt i76.exe image payload renames v28; confidence=medium] Fills or initializes
   bitmap/surface-context pixel memory. */

void __cdecl fill_bitmap_surface_context(int *param_1,byte param_2)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  
  if (param_1[0xb] == 1) {
    if (param_1 == &DAT_005dcec0) {
      (*DAT_005dd2e4)(&DAT_005dcec0,(&DAT_00608460)[param_2]);
      return;
    }
    puVar5 = (uint *)param_1[5];
    uVar2 = CONCAT11(param_2,param_2);
    uVar3 = (uint)uVar2;
    iVar4 = *param_1 * (param_1[1] & 0xffffU);
    if (0x3f < iVar4) {
      uVar3 = CONCAT22(uVar2,uVar2);
      iVar1 = iVar4 + -0x40;
      do {
        iVar4 = iVar1;
        *puVar5 = uVar3;
        puVar5[8] = uVar3;
        puVar5[1] = uVar3;
        puVar5[9] = uVar3;
        puVar5[2] = uVar3;
        puVar5[10] = uVar3;
        puVar5[3] = uVar3;
        puVar5[0xb] = uVar3;
        puVar5[4] = uVar3;
        puVar5[0xc] = uVar3;
        puVar5[5] = uVar3;
        puVar5[0xd] = uVar3;
        puVar5[6] = uVar3;
        puVar5[0xe] = uVar3;
        puVar5[7] = uVar3;
        puVar5[0xf] = uVar3;
        puVar5 = puVar5 + 0x10;
        iVar1 = iVar4 + -0x40;
      } while (iVar4 + -0x40 != 0 && 0x3f < iVar4);
      if (iVar4 == 0) {
        return;
      }
    }
    do {
      *(char *)puVar5 = (char)uVar3;
      puVar5 = (uint *)((int)puVar5 + 1);
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return;
}


