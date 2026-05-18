/*
 * Program: i76.exe
 * Function: vehicle_gdf_resource_context_helper_004b3a10
 * Entry: 004b3a10
 * Signature: undefined4 __cdecl vehicle_gdf_resource_context_helper_004b3a10(int param_1, uint * param_2)
 */


/* cgpt readability rename set E v17: Readability pass set E: vehicle gdf resource context helper
   based on adjacent named subsystem context. */

undefined4 __cdecl vehicle_gdf_resource_context_helper_004b3a10(int param_1,uint *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = *(int *)(param_1 + 8);
  if ((DAT_005dacd4 != 0) && (iVar3 = 0, 0 < DAT_005db974)) {
    piVar4 = &DAT_005db968;
    do {
      if ((iVar1 != 0) && (iVar1 == *piVar4)) {
        uVar2 = *param_2;
        *param_2 = ((int)(uVar2 << 0x16) >> 0x16 ^ uVar2) & 0x380 ^ uVar2 |
                   (1 << ((byte)iVar3 & 0x1f) & 7U) << 7;
        DAT_005dacd0 = 0;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < DAT_005db974);
  }
  (&DAT_005db968)[DAT_005db974] = iVar1;
  DAT_005db974 = DAT_005db974 + 1;
  return 1;
}


