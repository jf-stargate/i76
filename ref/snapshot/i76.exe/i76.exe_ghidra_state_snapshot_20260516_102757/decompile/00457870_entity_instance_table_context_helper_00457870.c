/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_00457870
 * Entry: 00457870
 * Signature: undefined __stdcall entity_instance_table_context_helper_00457870(void)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457870. Remove
   duplicated network/entity wording. */

void entity_instance_table_context_helper_00457870(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_4;
  
  uVar3 = 0xffffffff;
  uVar5 = 0xffffffff;
  if (DAT_00654b84 == '\0') {
    uVar3 = 0xffffffeb;
  }
  if (DAT_00654b85 == '\0') {
    uVar5 = 0xffffffeb;
  }
  local_4 = 0;
  if (0 < g_active_world_object_entry_count) {
    piVar4 = &g_active_world_object_entries;
    do {
      iVar1 = *piVar4;
      if (iVar1 != 0) {
        iVar2 = is_vehicle_or_weapon_source_world_object(iVar1);
        if (iVar2 == 1) {
          uVar6 = uVar3;
          switch(*(undefined4 *)(iVar1 + 0x6c)) {
          case 0x1e:
          case 0x34:
          case 0x3e:
          case 0x4b:
            *(undefined4 *)(iVar1 + 0x14) = 0xffffffff;
            entity_instance_table_context_helper_00457a00(*(int *)(iVar1 + 100),uVar3);
            break;
          default:
            *(undefined4 *)(iVar1 + 0x14) = uVar3;
            entity_instance_table_context_helper_00457a00(*(int *)(iVar1 + 100),uVar3);
          }
        }
        else {
          switch(*(undefined4 *)(iVar1 + 0x6c)) {
          case 0x1e:
          case 0x34:
          case 0x3e:
          case 0x4b:
            *(undefined4 *)(iVar1 + 0x14) = 0xffffffff;
            break;
          default:
            *(undefined4 *)(iVar1 + 0x14) = uVar5;
          }
          entity_instance_table_context_helper_00457a00(*(int *)(iVar1 + 100),uVar5);
          uVar6 = uVar5;
        }
        entity_instance_table_context_helper_00457a00(*(int *)(iVar1 + 0x60),uVar6);
      }
      local_4 = local_4 + 1;
      piVar4 = piVar4 + 0x1e;
    } while (local_4 < g_active_world_object_entry_count);
  }
  return;
}


