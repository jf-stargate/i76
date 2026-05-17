/*
 * Program: i76.exe
 * Function: initialize_muzzle_flash_effect_system
 * Entry: 0049f470
 * Signature: undefined __stdcall initialize_muzzle_flash_effect_system(void)
 */


/* cgpt whole-binary semantic rename v1: string evidence mzlfls */

void initialize_muzzle_flash_effect_system(void)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID lpMem;
  LPVOID pvVar3;
  
  lpMem = g_weapon_muzzle_flash_runtime_list;
  do {
    if (lpMem == (LPVOID)0x0) {
      HeapDestroy(g_weapon_muzzle_flash_runtime_heap);
      return;
    }
    pvVar1 = *(LPVOID *)((int)lpMem + 0x2c);
    pvVar3 = g_weapon_muzzle_flash_runtime_list;
    if (g_weapon_muzzle_flash_runtime_list != (LPVOID)0x0) {
      do {
        if ((*(int *)((int)pvVar3 + 8) == *(int *)((int)lpMem + 8)) ||
           (pvVar2 = *(LPVOID *)((int)pvVar3 + 0x2c),
           *(int *)((int)pvVar2 + 8) == *(int *)((int)lpMem + 8))) break;
        pvVar3 = pvVar2;
      } while (pvVar2 != (LPVOID)0x0);
    }
    if (pvVar3 == lpMem) {
      g_weapon_muzzle_flash_runtime_list = *(LPVOID *)((int)lpMem + 0x2c);
    }
    finalize_released_world_object_after_damage(*(LPVOID *)((int)lpMem + 8),s_mzlfls_004fe6e8);
    HeapFree(g_weapon_muzzle_flash_runtime_heap,0,lpMem);
    lpMem = pvVar1;
  } while( true );
}


