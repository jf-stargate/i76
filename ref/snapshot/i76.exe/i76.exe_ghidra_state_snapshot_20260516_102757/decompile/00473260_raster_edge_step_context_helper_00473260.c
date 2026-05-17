/*
 * Program: i76.exe
 * Function: raster_edge_step_context_helper_00473260
 * Entry: 00473260
 * Signature: undefined __stdcall raster_edge_step_context_helper_00473260(int param_1)
 */


/* cgpt readability rename set C v15: Readability pass set C: raster edge step context helper based
   on adjacent named subsystem context. */

void raster_edge_step_context_helper_00473260(int param_1)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x38)) {
    iVar1 = *(int *)(param_1 + 0x24);
    pbVar2 = *(byte **)(param_1 + 0x20);
    *(undefined4 *)(*(int *)(iVar1 + 4) + 8) = *(undefined4 *)(iVar1 + 8);
    *(undefined4 *)(*(int *)(iVar1 + 8) + 4) = *(undefined4 *)(iVar1 + 4);
    iVar4 = *(int *)(iVar1 + 0x10);
    for (pbVar3 = *(byte **)(iVar1 + 8); pbVar3 != pbVar2; pbVar3 = *(byte **)(pbVar3 + 8)) {
      iVar1 = *(int *)(pbVar3 + 0x10);
      if ((*pbVar3 & 1) == 0) {
        if (iVar1 == param_1) {
          *(int *)(pbVar3 + 0x10) = iVar4;
        }
        else if (iVar4 == iVar1) {
          iVar4 = *(int *)(pbVar3 + 0xc);
        }
      }
      else if (iVar1 == param_1) {
        *(int *)(pbVar3 + 0x10) = iVar4;
      }
      else if (iVar4 == *(int *)(pbVar3 + 0xc)) {
        iVar4 = iVar1;
      }
    }
    *(undefined4 *)(*(int *)(pbVar2 + 4) + 8) = *(undefined4 *)(pbVar2 + 8);
    *(undefined4 *)(*(int *)(pbVar2 + 8) + 4) = *(undefined4 *)(pbVar2 + 4);
  }
  return;
}


