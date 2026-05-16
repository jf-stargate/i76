/*
 * Program: i76.exe
 * Function: update_weapon_muzzle_flash_runtime_effect
 * Entry: 0049f2f0
 * Signature: undefined __cdecl update_weapon_muzzle_flash_runtime_effect(LPVOID param_1)
 */


/* [cgpt i76.exe weapon/projectile v27; confidence=high] Maintains mzlfls muzzle flash runtime
   objects, installs light state, and starts texture animation for visible muzzle flash records. */

void __cdecl update_weapon_muzzle_flash_runtime_effect(LPVOID param_1)

{
  LPVOID pvVar1;
  LPVOID pvVar2;
  LPVOID lpMem;
  
  if (*(int *)((int)param_1 + 100) != 0) {
    world_object_geometry_context_helper_004587d0(*(int *)((int)param_1 + 100),1);
    for (lpMem = g_weapon_muzzle_flash_runtime_list; lpMem != (LPVOID)0x0;
        lpMem = *(LPVOID *)((int)lpMem + 0x2c)) {
      if (*(LPVOID *)((int)lpMem + 8) == param_1) goto LAB_0049f328;
    }
    lpMem = (LPVOID)0x0;
LAB_0049f328:
    if (lpMem != (LPVOID)0x0) {
      pvVar2 = release_world_object_tree_reference(param_1,s_mzlfls_004fe6e8);
      if (pvVar2 == (LPVOID)0x0) {
        pvVar2 = g_weapon_muzzle_flash_runtime_list;
        if (g_weapon_muzzle_flash_runtime_list != (LPVOID)0x0) {
          do {
            if ((*(int *)((int)pvVar2 + 8) == *(int *)((int)lpMem + 8)) ||
               (pvVar1 = *(LPVOID *)((int)pvVar2 + 0x2c),
               *(int *)((int)pvVar1 + 8) == *(int *)((int)lpMem + 8))) break;
            pvVar2 = pvVar1;
          } while (pvVar1 != (LPVOID)0x0);
        }
        if (pvVar2 == lpMem) {
          g_weapon_muzzle_flash_runtime_list = *(LPVOID *)((int)lpMem + 0x2c);
        }
        finalize_released_world_object_after_damage(*(LPVOID *)((int)lpMem + 8),s_mzlfls_004fe6e8);
        HeapFree(g_weapon_muzzle_flash_runtime_heap,0,lpMem);
        return;
      }
      if ((*(int *)((int)lpMem + 0x10) == 1) && (*(char *)((int)lpMem + 0x1c) != '\0')) {
        release_texture_animation_record(*(int *)((int)param_1 + 100),(char *)((int)lpMem + 0x1c));
      }
      if (*(char *)((int)lpMem + 0x1c) != '\0') {
        if (*(int *)((int)lpMem + 0x10) != 1) {
          create_lobj_light_runtime_entry
                    (*(int *)((int)param_1 + 100),0,25.0,0.0,(float *)0x0,(undefined4 *)0x0);
        }
        install_texture_animation_linear_timer
                  (*(uint *)((int)param_1 + 100),(byte *)((int)lpMem + 0x1c),0.1,0.0,
                   *(float *)((int)lpMem + 0x18),6.791544e-39);
        *(undefined4 *)((int)lpMem + 0x10) = 1;
      }
    }
  }
  return;
}


