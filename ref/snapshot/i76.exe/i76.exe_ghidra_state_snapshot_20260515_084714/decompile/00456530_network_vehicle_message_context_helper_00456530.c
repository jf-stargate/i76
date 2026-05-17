/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456530
 * Entry: 00456530
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456530(undefined4 param_1, int param_2, undefined4 * param_3)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456530.
   Remove duplicated network wording. */

void __cdecl
network_vehicle_message_context_helper_00456530(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined2 local_b8;
  undefined1 local_b6;
  float local_b4;
  int local_b0;
  undefined4 local_ac [43];
  
  fVar5 = get_runtime_time_seconds();
  local_b4 = (float)fVar5;
  local_b0 = param_2;
  local_b8 = 0x4353;
  local_b6 = 0;
  uVar2 = param_2 + 0x1fU >> 5;
  puVar4 = local_ac;
  for (uVar3 = uVar2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *puVar4 = *param_3;
    param_3 = param_3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar1 = uVar2 * 4 + 0xc;
  dpSend(DAT_00541024,CONCAT22((short)((uint)iVar1 >> 0x10),DAT_00541028),param_1,1,&local_b8,iVar1)
  ;
  return;
}


