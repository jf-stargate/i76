/*
 * Program: i76.exe
 * Function: preload_smoke_or_dust_textures
 * Entry: 00442ae0
 * Signature: undefined __stdcall preload_smoke_or_dust_textures(void)
 */


/* i76 second-pass rename
   old_name: FUN_00442ae0
   suggested_name: preload_smoke_or_dust_textures
   basis: References xsh/xdu .map texture frames and is called from startup. */

void preload_smoke_or_dust_textures(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  iVar3 = 0;
  do {
    piVar5 = (int *)((int)&DAT_004f1d1c + iVar3);
    iVar4 = 0;
    piVar6 = (int *)((int)&DAT_004f1d08 + iVar3);
    do {
      if (*piVar6 != 0) {
        release_vqm_texture_cache_reference_by_name(s_xdu1_101_map_004f1cf8 + iVar4 + iVar3);
      }
      iVar4 = iVar4 + 0xd;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 0xd);
    iVar4 = 0;
    do {
      if (*piVar5 != 0) {
        release_vqm_texture_cache_reference_by_name(s_xdu1_201_map_004f1d0c + iVar4 + iVar3);
      }
      iVar4 = iVar4 + 0xd;
      piVar5 = piVar5 + 1;
    } while (iVar4 < 0xd);
    iVar4 = 0;
    piVar6 = (int *)((int)&DAT_004f1d30 + iVar3);
    do {
      if (*piVar6 != 0) {
        release_vqm_texture_cache_reference_by_name(s_xdu1_301_map_004f1d20 + iVar4 + iVar3);
      }
      puVar1 = DAT_0052bae8;
      iVar4 = iVar4 + 0xd;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 0xd);
    iVar3 = iVar3 + 0x40;
  } while (iVar3 < 0x1c0);
  if (DAT_0052bae8 != (undefined4 *)0x0) {
    do {
      puVar2 = DAT_0052bae8;
      DAT_0052bae8 = (undefined4 *)*DAT_0052bae8;
      xfree_global_heap(puVar2);
    } while (DAT_0052bae8 != puVar1);
  }
  DAT_0052bae8 = (undefined4 *)0x0;
  return;
}


