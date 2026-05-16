/*
 * Program: i76.exe
 * Function: loaded_resource_cache_load_record_helper_0046f5b0
 * Entry: 0046f5b0
 * Signature: undefined4 __cdecl loaded_resource_cache_load_record_helper_0046f5b0(int param_1, int param_2)
 */


/* cgpt readability rename set C v15: Readability pass set C: loaded resource cache load record
   helper based on adjacent named subsystem context. */

undefined4 __cdecl loaded_resource_cache_load_record_helper_0046f5b0(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = *(int **)(param_1 + 0x70);
  iVar3 = 0;
  piVar4 = (int *)(param_2 + 8);
  do {
    uVar2 = 1 << ((byte)iVar3 & 0x1f);
    if ((uVar2 & *(ushort *)(param_2 + 4)) != 0) {
      if ((uVar2 == 3) && ((*(byte *)(param_2 + 6) & 1) != 0)) {
        *piVar4 = *piVar4 * 100;
      }
      if (*piVar1 < *piVar4) {
        uVar2 = *(int *)(param_2 + 8 + iVar3 * 4) - *piVar1;
        *(uint *)(param_2 + 8 + iVar3 * 4) = uVar2;
        if ((1 << ((byte)iVar3 & 0x1f) == 3) && ((*(byte *)(param_2 + 6) & 1) != 0)) {
          *(uint *)(param_2 + 8 + iVar3 * 4) = uVar2 / 100;
        }
        *piVar1 = 0;
        return 1;
      }
      *piVar1 = *piVar1 - *piVar4;
      *piVar4 = 0;
    }
    iVar3 = iVar3 + 1;
    piVar4 = piVar4 + 1;
    if (3 < iVar3) {
      return 0;
    }
  } while( true );
}


