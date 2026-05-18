/*
 * Program: i76.exe
 * Function: spawn_cached_explosion_runtime_object
 * Entry: 0049ead0
 * Signature: uint * __cdecl spawn_cached_explosion_runtime_object(uint param_1, uint param_2, undefined4 param_3, float param_4, float param_5, float param_6, int param_7)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe mission/world/effects rename v16; confidence=HIGH] Finds or allocates a cached
   explosion object, positions it, binds textures/lights/animation/sound, and returns the runtime
   object. */

uint * __cdecl
spawn_cached_explosion_runtime_object
          (uint param_1,uint param_2,undefined4 param_3,float param_4,float param_5,float param_6,
          int param_7)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  uint uVar4;
  float fVar5;
  int iVar6;
  uint *puVar7;
  byte *pbVar8;
  undefined4 uVar9;
  LPVOID pvVar10;
  uint *puVar11;
  uint uVar12;
  uint *puVar13;
  uint *puVar14;
  float10 fVar15;
  undefined8 uVar16;
  
  if (param_1 != 0 || param_2 != 0) {
    uVar12 = 0;
    do {
      iVar6 = toupper((int)*(char *)((int)&param_1 + uVar12));
      *(char *)((int)&param_1 + uVar12) = (char)iVar6;
      uVar4 = param_2;
      uVar3 = param_1;
      uVar12 = uVar12 + 1;
    } while (uVar12 < 8);
    uVar16 = __allshr(0x20,param_2);
    for (puVar11 = (uint *)(&g_explosion_runtime_state)
                           [(((uint)uVar16 ^ uVar3) * 0x6cd + 0xaab) % 0x71]; puVar11 != (uint *)0x0
        ; puVar11 = (uint *)puVar11[8]) {
      if ((*puVar11 == uVar3) && (puVar11[1] == uVar4)) goto LAB_0049eb68;
    }
    puVar11 = (uint *)0x0;
LAB_0049eb68:
    if (puVar11 != (uint *)0x0) {
      puVar7 = (uint *)puVar11[7];
      if (puVar7 == (uint *)0x0) {
        puVar7 = allocate_world_object_node(0);
        *puVar7 = *puVar11;
        puVar7[1] = puVar11[1];
        puVar7[4] = 0x40;
        puVar7[0x17] = 0;
        cache_add_indexed_entry(puVar11[2],(int)puVar7);
        set_world_object_class_and_register_runtime((int)puVar7,0x34);
        puVar13 = (uint *)puVar7[0x1c];
        iVar6 = 0;
        *puVar13 = *puVar11;
        puVar13[1] = puVar11[1];
        do {
          pbVar8 = (byte *)find_object_texture_slot_name((int)puVar7,iVar6);
          if ((pbVar8 != (byte *)0x0) && (*pbVar8 != 0)) {
            bind_texture_resource_to_object_slot((uint)puVar7,pbVar8,pbVar8);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < 2);
      }
      else {
        puVar11[7] = puVar7[0x18];
        puVar7[0x18] = 0;
        puVar7[0x1a] = 0;
        if (puVar11[7] != 0) {
          *(undefined4 *)(puVar11[7] + 0x68) = 0;
        }
      }
      param_1 = puVar7[0x1c];
      puVar13 = &DAT_004faed8;
      puVar14 = puVar7 + 6;
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar14 = *puVar13;
        puVar13 = puVar13 + 1;
        puVar14 = puVar14 + 1;
      }
      *(double *)(puVar7 + 0x10) = (double)param_4;
      *(double *)(puVar7 + 0x12) = (double)param_5;
      *(double *)(puVar7 + 0x14) = (double)param_6;
      fVar15 = get_network_or_session_runtime_seconds();
      uVar12 = param_1;
      fVar1 = (float)puVar11[3];
      *(undefined4 *)(param_1 + 0xc) = param_3;
      *(float *)(param_1 + 8) = (float)(fVar15 + (float10)fVar1);
      *(int *)(param_1 + 0x10) = param_7;
      increment_refcount_recursive_for_object_tree(param_7,s_explsn_004fe6e0);
      iVar6 = 0;
      if (DAT_005a80fc == (LPVOID)0x0) {
        DAT_005a80fc = allocate_world_object_node(0);
        *(undefined4 *)((int)DAT_005a80fc + 0x70) = 0;
        *(undefined4 *)((int)DAT_005a80fc + 0x10) = 0x100;
        register_active_world_object_entry((int)DAT_005a80fc,0,(int *)0x0);
      }
      attach_world_object_as_first_child((int)puVar7,(int)DAT_005a80fc);
      create_lobj_light_runtime_entry((int)puVar7,0,20.0,0.0,(float *)0x0,(undefined4 *)0x0);
      do {
        pbVar8 = (byte *)find_object_texture_slot_name((int)puVar7,iVar6);
        if ((pbVar8 != (byte *)0x0) && (*pbVar8 != 0)) {
          install_texture_animation_linear_timer
                    ((uint)puVar7,pbVar8,0.1,0.0,(float)puVar11[4],6.789683e-39);
        }
        fVar5 = param_6;
        fVar1 = param_4;
        iVar6 = iVar6 + 1;
      } while (iVar6 < 2);
      if ((float)puVar11[5] != _DAT_004bea2c) {
        fVar2 = (float)puVar11[6];
        iVar6 = 0;
        puVar11 = puVar7;
        uVar9 = ftol();
        apply_explosion_radial_damage_effect(fVar1,fVar5,fVar2,uVar9,(int)puVar11,iVar6);
      }
      pvVar10 = *(LPVOID *)(uVar12 + 0x10);
      if (pvVar10 != (LPVOID)0x0) {
        pvVar10 = release_world_object_tree_reference(pvVar10,s_explsn_004fe6e0);
        *(LPVOID *)(uVar12 + 0x10) = pvVar10;
      }
      return puVar7;
    }
  }
  return (uint *)0x0;
}


