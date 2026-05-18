/*
 * Program: i76.exe
 * Function: texture_cache_record_lookup_helper_00447d20
 * Entry: 00447d20
 * Signature: undefined __stdcall texture_cache_record_lookup_helper_00447d20(void)
 */


/* cgpt readability rename set B v14: Readability pass set B: texture cache record lookup helper
   based on prior focused closure context. */

void texture_cache_record_lookup_helper_00447d20(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  piVar4 = &g_vqm_texture_cache_hash;
  do {
    for (iVar1 = *piVar4; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x20)) {
      iVar2 = (((*(int **)(iVar1 + 0x10))[1] << 3) >> 3) * **(int **)(iVar1 + 0x10);
      if (iVar2 != -8 && -1 < iVar2 + 8) {
        uVar3 = iVar2 + 0x1007U >> 0xc;
        do {
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
      }
    }
    piVar4 = piVar4 + 1;
    iVar1 = g_vqm_texture_lru_tail;
  } while ((int)piVar4 < 0x531cf4);
  for (; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x1c)) {
    iVar2 = (((*(int **)(iVar1 + 0x10))[1] << 3) >> 3) * **(int **)(iVar1 + 0x10);
    if (iVar2 != -8 && -1 < iVar2 + 8) {
      uVar3 = iVar2 + 0x1007U >> 0xc;
      do {
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  return;
}


