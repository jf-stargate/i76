/*
 * Program: i76.exe
 * Function: network_vehicle_message_context_helper_00456220
 * Entry: 00456220
 * Signature: undefined __cdecl network_vehicle_message_context_helper_00456220(undefined4 param_1, undefined2 param_2, int param_3, int param_4, undefined4 param_5, undefined4 param_6)
 */


/* cgpt label refinement v19: was multiplayer_network_network_vehicle_message_helper_00456220.
   Remove duplicated network wording. */

void __cdecl
network_vehicle_message_context_helper_00456220
          (undefined4 param_1,undefined2 param_2,int param_3,int param_4,undefined4 param_5,
          undefined4 param_6)

{
  char *pcVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  undefined2 local_1a4 [4];
  undefined2 local_19c;
  uint local_198;
  undefined4 local_194;
  undefined4 local_190;
  uint local_18c [99];
  
  get_gameplay_runtime_seconds();
  local_19c = param_2;
  local_1a4[0] = 0x5053;
  local_198 = 0;
  local_194 = param_5;
  local_190 = param_6;
  if (param_3 != 0 || param_4 != 0) {
    pcVar1 = format_8char_resource_basename_with_suffix(param_3,param_4,&s_dot_vcf);
    local_198 = get_loaded_resource_file_size(pcVar1);
    pcVar1 = format_8char_resource_basename_with_suffix(param_3,param_4,&s_dot_vcf);
    puVar2 = open_resource_file_into_memory(pcVar1);
    puVar4 = local_18c;
    for (uVar3 = local_198 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar4 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar4 = puVar4 + 1;
    }
    for (uVar3 = local_198 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
      *(char *)puVar4 = (char)*puVar2;
      puVar2 = (uint *)((int)puVar2 + 1);
      puVar4 = (uint *)((int)puVar4 + 1);
    }
    pcVar1 = format_8char_resource_basename_with_suffix(param_3,param_4,&s_dot_vcf);
    release_resource_file_reference(pcVar1);
  }
  dpSend(DAT_00541024,CONCAT22((short)(local_198 + 0x18 >> 0x10),DAT_00541028),param_1,1,local_1a4,
         local_198 + 0x18);
  return;
}


