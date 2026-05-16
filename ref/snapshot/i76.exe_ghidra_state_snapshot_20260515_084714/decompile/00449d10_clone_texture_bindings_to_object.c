/*
 * Program: i76.exe
 * Function: clone_texture_bindings_to_object
 * Entry: 00449d10
 * Signature: undefined4 __cdecl clone_texture_bindings_to_object(int param_1, uint param_2)
 */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* [cgpt i76.exe texture/resource-cache rename v10; confidence=high] Clones texture bindings from
   one object/list key to another object, preserving frame offsets and lazy cache state. */

undefined4 __cdecl clone_texture_bindings_to_object(int param_1,uint param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int *piVar6;
  int iVar7;
  
  piVar6 = (int *)(&g_texture_bindings_by_object_hash)[(param_1 * 0x6cd + 0xaabU) % 0x71];
  if (piVar6 != (int *)0x0) {
    do {
      if (*piVar6 == param_1) break;
      piVar6 = (int *)piVar6[2];
    } while (piVar6 != (int *)0x0);
    if (piVar6 == (int *)0x0) {
      return 0;
    }
    iVar7 = piVar6[1];
    if (iVar7 == 0) {
      return 1;
    }
    while( true ) {
      iVar2 = *(int *)(iVar7 + 0x30);
      pbVar1 = (byte *)(iVar7 + 0x14);
      *(int *)(iVar2 + 0x10) = *(int *)(iVar2 + 0x10) + 1;
      puVar4 = create_texture_slot_binding_for_object(param_2,pbVar1,iVar2,iVar2);
      if (puVar4 == (uint *)0x0) break;
      if ((*(uint *)(iVar2 + 0x18) & 1) != 0) {
        if ((*(uint *)(iVar2 + 0x18) & 2) == 0) {
          install_texture_animation_linear_timer
                    (param_2,pbVar1,_DAT_004bd3bc / *(float *)(iVar2 + 0x14),0.0,
                     *(float *)(iVar2 + 0x20),6.307143e-39);
        }
        else {
          install_texture_animation_pingpong_timer
                    (param_2,pbVar1,_DAT_004bd3bc / *(float *)(iVar2 + 0x14),0.0,
                     *(float *)(iVar2 + 0x20),1);
        }
      }
      puVar4[9] = *(uint *)(iVar7 + 0x24);
      puVar4[10] = *(uint *)(iVar7 + 0x28);
      puVar4[0xb] = *(uint *)(iVar7 + 0x2c);
      puVar4[1] = *(uint *)(iVar7 + 4);
      puVar4[2] = *(uint *)(iVar7 + 8);
      puVar4[3] = *(uint *)(iVar7 + 0xc);
      puVar4[4] = *(uint *)(iVar7 + 0x10);
      uVar3 = *(uint *)(iVar7 + 0x3c);
      puVar4[0xf] = uVar3 & 0xfffffffe;
      if ((uVar3 & 2) == 0) {
        puVar5 = load_texture_resource_resolving_vqm_cbk_to_cache((byte *)(puVar4 + 1));
        puVar4[0xd] = (uint)puVar5;
      }
      else {
        puVar4[0xd] = 0;
      }
      iVar7 = *(int *)(iVar7 + 0x44);
      if (iVar7 == 0) {
        return 1;
      }
    }
  }
  return 0;
}


