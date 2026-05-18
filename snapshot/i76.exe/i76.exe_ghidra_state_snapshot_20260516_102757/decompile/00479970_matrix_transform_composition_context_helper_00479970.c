/*
 * Program: i76.exe
 * Function: matrix_transform_composition_context_helper_00479970
 * Entry: 00479970
 * Signature: undefined __cdecl matrix_transform_composition_context_helper_00479970(int param_1, int param_2)
 */


/* cgpt readability rename set D v16: Readability pass set D: matrix transform composition context
   helper based on adjacent named subsystem context. */

void __cdecl matrix_transform_composition_context_helper_00479970(int param_1,int param_2)

{
  uint uVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_300;
  
  uVar1 = DAT_00654b8c & 0xff;
  puVar4 = &g_game_8bpp_palette_rgb_triplets;
  puVar6 = &local_300;
  for (iVar3 = 0xc0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  if ((uVar1 == 0) || (10 < uVar1)) {
    uVar1 = 3;
  }
  iVar3 = uVar1 * 0x100 + 0x6094a0;
  if (param_1 < param_2) {
    iVar5 = param_2 - param_1;
    pbVar2 = (byte *)((int)&local_300 + param_1 * 3 + 1);
    do {
      pbVar2[-1] = *(byte *)(iVar3 + (uint)pbVar2[-1]);
      *pbVar2 = *(byte *)(iVar3 + (uint)*pbVar2);
      iVar5 = iVar5 + -1;
      pbVar2[1] = *(byte *)(iVar3 + (uint)pbVar2[1]);
      pbVar2 = pbVar2 + 3;
    } while (iVar5 != 0);
  }
  (*DAT_005dd2c8)(&DAT_005dcec0,&local_300);
  return;
}


