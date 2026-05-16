/*
 * Program: i76.exe
 * Function: multiplayer_network_network_vehicle_message_helper_00456d70
 * Entry: 00456d70
 * Signature: undefined __cdecl multiplayer_network_network_vehicle_message_helper_00456d70(short param_1, uint * param_2)
 */


/* cgpt readability rename set B v14: Readability pass set B: likely multiplayer_network /
   network_vehicle_message_helper based on address neighborhood and prior focused closure context.
    */

void __cdecl
multiplayer_network_network_vehicle_message_helper_00456d70(short param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int local_20;
  int local_1c [5];
  int local_8;
  int local_4;
  
  uVar2 = multiplayer_player_table_context_helper_004547c0(param_1);
  if ((uVar2 != 0) && (iVar3 = collect_vehicle_weapon_runtime_slots(uVar2,&local_20), iVar3 == 1)) {
    iVar3 = 0;
    puVar4 = param_2 + 1;
    do {
      uVar1 = (ushort)*puVar4;
      if (uVar1 == 0) {
        iVar7 = *(int *)((int)&DAT_004f5c38 + iVar3);
        uVar6 = 0;
      }
      else {
        if ((*param_2 & *(uint *)((int)&DAT_004f5c48 + iVar3)) == 0) {
          uVar6 = multiplayer_player_table_context_helper_004547c0(uVar1);
        }
        else {
          uVar6 = network_vehicle_message_context_helper_00456700(uVar1 - 1);
        }
        iVar7 = *(int *)((int)&DAT_004f5c38 + iVar3);
      }
      radar_render_context_helper_00461430(uVar2,uVar6,iVar7);
      iVar3 = iVar3 + 4;
      puVar4 = (uint *)((int)puVar4 + 2);
    } while (iVar3 < 0xc);
    uVar1 = *(ushort *)((int)param_2 + 10);
    if (uVar1 == 0) {
      uVar8 = 0;
    }
    else if ((*param_2 & 0x40000000) == 0) {
      uVar8 = multiplayer_player_table_context_helper_004547c0(uVar1);
    }
    else {
      uVar8 = network_vehicle_message_context_helper_00456700(uVar1 - 1);
    }
    radar_render_context_helper_00461270(uVar2,uVar8);
    iVar3 = 0;
    if (0 < local_20) {
      piVar5 = local_1c;
      do {
        if ((*param_2 & 1 << ((byte)iVar3 & 0x1f)) != 0) {
          set_weapon_runtime_fire_request_flag(*piVar5,1);
        }
        iVar3 = iVar3 + 1;
        piVar5 = piVar5 + 1;
      } while (iVar3 < local_20);
    }
    if ((*param_2 & 0x20) != 0) {
      set_weapon_runtime_fire_request_flag(local_8,1);
    }
    if ((*param_2 & 0x40) != 0) {
      set_weapon_runtime_fire_request_flag(local_4,1);
    }
  }
  return;
}


