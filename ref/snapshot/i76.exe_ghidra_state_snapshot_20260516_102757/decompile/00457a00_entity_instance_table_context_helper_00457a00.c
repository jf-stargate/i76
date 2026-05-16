/*
 * Program: i76.exe
 * Function: entity_instance_table_context_helper_00457a00
 * Entry: 00457a00
 * Signature: undefined __cdecl entity_instance_table_context_helper_00457a00(int param_1, undefined4 param_2)
 */


/* cgpt label refinement v19: was multiplayer_network_entity_instance_table_helper_00457a00. Remove
   duplicated network/entity wording. */

void __cdecl entity_instance_table_context_helper_00457a00(int param_1,undefined4 param_2)

{
  for (; param_1 != 0; param_1 = *(int *)(param_1 + 0x60)) {
    switch(*(undefined4 *)(param_1 + 0x6c)) {
    case 0x1e:
    case 0x34:
    case 0x3e:
    case 0x4b:
      *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
      break;
    default:
      *(undefined4 *)(param_1 + 0x14) = param_2;
    }
    entity_instance_table_context_helper_00457a00(*(int *)(param_1 + 100),param_2);
  }
  return;
}


